// WebSocket信令服务器示例 (Node.js)
// 安装依赖: npm install ws

const WebSocket = require('ws');
const wss = new WebSocket.Server({ port: 8080 });

// 存储连接的客户端
const clients = new Map();
// 存储自习室
const rooms = new Map();

console.log('WebSocket服务器启动在端口 8080');

wss.on('connection', (ws) => {
    let userId = null;
    
    console.log('新客户端连接');
    
    ws.on('message', (data) => {
        try {
            const message = JSON.parse(data);
            console.log('收到消息:', message.type);
            
            switch (message.type) {
                case 'register':
                    userId = message.userId || generateId();
                    clients.set(userId, ws);//存储useId和唯一对应的ws客户端
                    ws.send(JSON.stringify({
                        type: 'registered',
                        userId: userId
                    }));
                    console.log('用户注册:', userId);
                    break;
                    
                case 'createRoom':
                    handleCreateRoom(message, userId);
                    break;
                    
                case 'joinRoom':
                    handleJoinRoom(message, userId);
                    break;
                    
                case 'leaveRoom':
                    handleLeaveRoom(message, userId);
                    break;
                    
                case 'closeRoom':
                    handleCloseRoom(message, userId);
                    break;
                    
                case 'getRoomList':
                    handleGetRoomList(userId);
                    break;
                    
                case 'muteParticipant':
                case 'stopParticipantVideo':
                case 'kickParticipant':
                case 'muteAll':
                case 'transferOwnership':
                    handleRoomManagement(message, userId);
                    break;
                    
                case 'webrtcOffer':
                case 'webrtcAnswer':
                case 'iceCandidate':
                    handleWebRTCSignaling(message, userId);
                    break;
                    
                default:
                    console.log('未知消息类型:', message.type);
            }
        } catch (error) {
            console.error('处理消息错误:', error);
        }
    });
    
    ws.on('close', () => {
        if (userId) {
            console.log('客户端断开:', userId);
            clients.delete(userId);
            
            // 清理用户所在的房间
            for (const [roomId, room] of rooms) {
                if (room.participants.has(userId)) {
                    room.participants.delete(userId);
                    broadcastToRoom(roomId, {
                        type: 'participantLeft',
                        participantId: userId
                    });
                    
                    if (room.participants.size === 0) {
                        rooms.delete(roomId);
                    }
                }
            }
        }
    });
    
    function handleCreateRoom(message, userId) {
        const roomId = generateId();
        const room = {
            roomId: roomId,
            roomName: message.roomName,
            ownerId: userId,
            maxParticipants: message.maxParticipants,
            isPrivate: message.isPrivate,
            password: message.password,
            videoStatus:message.videoStatus,
            audioStatus:message.audioStatus,
            participants: new Map(),
            isActive: true
        };
        
        room.participants.set(userId, {
            participantId: userId,
            nickname: '用户' + userId.substring(0, 6),
            isOwner: true,
            defaultvideostatus:message.videoStatus,
            defaultaudiostatus:  message.audioStatus
        });
        
        rooms.set(roomId, room);
        
        sendToClient(userId, {
            type: 'roomCreated',
            roomId: roomId,
            roomInfo: getRoomInfo(roomId)
        });
        
        console.log('自习室创建:', roomId);
    }
    
    function handleJoinRoom(message, userId) {
        const roomId = message.roomId;
        const room = rooms.get(roomId);
        
        if (!room) {
            sendToClient(userId, {
                type: 'error',
                message: '自习室不存在'
            });
            return;
        }
        
        if (room.participants.size >= room.maxParticipants) {
            sendToClient(userId, {
                type: 'error',
                message: '自习室已满'
            });
            return;
        }
        
        if (room.isPrivate && room.password !== message.password) {
            sendToClient(userId, {
                type: 'error',
                message: '密码错误'
            });
            return;
        }
        
        room.participants.set(userId, {
            participantId: userId,
            nickname: '用户' + userId.substring(0, 6),
            isOwner: false
        });
        
        sendToClient(userId, {
            type: 'roomJoined',
            roomId: roomId,
            roomInfo: getRoomInfo(roomId)
        });
        
        // 通知其他参与者
        broadcastToRoom(roomId, {
            type: 'participantJoined',
            participant: {
                participantId: userId,
                nickname: '用户' + userId.substring(0, 6),
                isOwner: false
            }
        }, userId);
        
        console.log('用户加入自习室:', userId, roomId);
    }
    
    function handleLeaveRoom(message, userId) {
        const roomId = message.roomId;
        const room = rooms.get(roomId);
        
        if (!room) return;
        
        room.participants.delete(userId);
        
        sendToClient(userId, {
            type: 'roomLeft'
        });
        
        broadcastToRoom(roomId, {
            type: 'participantLeft',
            participantId: userId
        });
        
        // 如果房间空了，删除房间
        if (room.participants.size === 0) {
            rooms.delete(roomId);
        }
        
        console.log('用户离开自习室:', userId, roomId);
    }
    
    function handleCloseRoom(message, userId) {
        const roomId = message.roomId;
        const room = rooms.get(roomId);
        
        if (!room || room.ownerId !== userId) return;
        
        // 通知所有参与者
        broadcastToRoom(roomId, {
            type: 'roomClosed'
        });
        
        rooms.delete(roomId);
        console.log('自习室关闭:', roomId);
    }
    
    function handleGetRoomList(userId) {
        const roomList = [];
        for (const [roomId, room] of rooms) {
            if (!room.isPrivate && room.isActive) {
                roomList.push({
                    roomId: roomId,
                    roomName: room.roomName,
                    currentParticipants: room.participants.size,
                    maxParticipants: room.maxParticipants,
                    isPrivate: room.isPrivate
                });
            }
        }
        
        sendToClient(userId, {
            type: 'roomList',
            rooms: roomList
        });
    }
    
    function handleRoomManagement(message, userId) {
        // 转发管理命令到房间内的其他参与者
        const roomId = message.roomId;
        broadcastToRoom(roomId, message, userId);
    }
    
    function handleWebRTCSignaling(message, userId) {
        const targetId = message.targetId;
        
        sendToClient(targetId, {
            type: message.type,
            fromId: userId,
            sdp: message.sdp,
            candidate: message.candidate
        });
    }
    
    function getRoomInfo(roomId) {
        const room = rooms.get(roomId);
        if (!room) return null;
        
        const participants = [];
        for (const [id, participant] of room.participants) {
            participants.push(participant);
        }
        
        return {
            roomName: room.roomName,
            ownerId: room.ownerId,
            maxParticipants: room.maxParticipants,
            currentParticipants: room.participants.size,
            isPrivate: room.isPrivate,
            participants: participants
        };
    }
    
    function sendToClient(userId, message) {
        const ws = clients.get(userId);
        if (ws && ws.readyState === WebSocket.OPEN) {
            ws.send(JSON.stringify(message));
        }
    }
    
    function broadcastToRoom(roomId, message, excludeUserId = null) {
        const room = rooms.get(roomId);
        if (!room) return;
        
        for (const participantId of room.participants.keys()) {
            if (participantId !== excludeUserId) {
                sendToClient(participantId, message);
            }
        }
    }
    
    function generateId() {
        return Math.random().toString(36).substring(2, 15) + 
               Math.random().toString(36).substring(2, 15);
    }
});
