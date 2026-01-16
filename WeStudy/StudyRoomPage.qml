import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtMultimedia
Page {
    id: root
    
    signal leaveRoom()

    Camera {
        id: camera
        active: true
        }
    CaptureSession {
        camera: camera
        videoOutput: localOutput
        // audioInput: mic
    }



    header: ToolBar {
        background: Rectangle {
            color: "#2c3e50"
        }
        
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 20
            anchors.rightMargin: 20
            spacing: 20
            
            Label {
                text:controller.currentRoom?controller.currentRoom.roomName:""
                font.pixelSize: 20
                font.bold: true
                color: "white"
            }
            
            Rectangle {
                width: 80
                height: 30
                radius: 15
                color:controller.isOwner ? "#f39c12" : "#3498db"
                
                Label {
                    anchors.centerIn: parent         
                    text:controller.isOwner ? "房主" : "成员"
                    font.pixelSize: 12
                    color: "white"
                }
            }
            
            Item { Layout.fillWidth: true }
            
            Label {

                text:controller.currentRoom ?
                         controller.currentRoom.currentParticipants + "/" +
                         controller.currentRoom.maxParticipants + " 人" : ""
                font.pixelSize: 14
                color: "white"
            }
            
            // Button {

            //     text: controller.isStudying ? "结束自习" : "开始自习"
            //     font.pixelSize: 14
            //     implicitWidth: 100
            //     implicitHeight: 35
                
            //     background:  Rectangle {
            //         color: controller.isStudying ? "#e74c3c" : "#27ae60"
            //         radius: 6
            //     }
                
            //     contentItem: Text {
            //         text: parent.text
            //         font: parent.font
            //         color: "white"
            //         horizontalAlignment: Text.AlignHCenter
            //         verticalAlignment: Text.AlignVCenter
            //     }
                
            //     onClicked: {
            //         if (controller.isStudying) {
            //             controller.stopStudying()
            //         } else {
            //             controller.startStudying()
            //         }
            //     }

            // }
            
            // Button {

            //     text:controller.isOwner ? "关闭自习室" : "离开自习室"
            //     font.pixelSize: 14
            //     implicitWidth: 120
            //     implicitHeight: 35
                
            //     background: Rectangle {

            //         color:"#e74c3c"
            //         radius: 6
            //     }
                
            //     contentItem: Text {
            //         text: parent.text
            //         font: parent.font
            //         color: "white"
            //         horizontalAlignment: Text.AlignHCenter
            //         verticalAlignment: Text.AlignVCenter
            //     }
                
            //     onClicked: {
            //         if (controller.isOwner) {
            //             closeRoomDialog.open()
            //         } else {
            //             root.leaveRoom()
            //         }
            //     }

            // }
        }
    }
    
    RowLayout {
        anchors.fill: parent
        spacing: 0
        
        // 左侧：参与者列表
        Rectangle {
            Layout.preferredWidth: 280
            Layout.fillHeight: true
            color: "#ecf0f1"
            
            ColumnLayout {
                anchors.fill: parent
                spacing: 0
                
                //参与者（人数）
                Rectangle {
                    Layout.fillWidth: true
                    height: 60
                    color: "#34495e"
                    
                    Label {
                        anchors.centerIn: parent

                        text: "自习人数 (" + (controller.currentRoom ?   controller.currentRoom.currentParticipants : 0) + ")"
                        font.pixelSize: 18
                        font.bold: true
                        color: "white"
                    }
                }
                
                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    clip: true

                    ListView {
                        id: participantListView
                        model: controller.participants
                        spacing: 1

                        delegate: Rectangle {
                            width: participantListView.width
                            height: 80
                            color: index % 2 === 0 ? "white" : "#f8f9fa"

                            RowLayout {
                                anchors.fill: parent
                                anchors.margins: 15
                                spacing: 15

                                Rectangle {
                                    width: 50
                                    height: 50
                                    radius: 25
                                    color: model.isOwner ? "#f39c12" : "#3498db"

                                    Label {
                                        anchors.centerIn: parent
                                        text: model.nickname ? model.nickname.substring(0, 1) : "?"
                                        font.pixelSize: 20
                                        font.bold: true
                                        color: "white"
                                    }
                                }

                                ColumnLayout {
                                    Layout.fillWidth: true
                                    spacing: 5

                                    Label {
                                        text: model.nickname
                                        font.pixelSize: 16
                                        font.bold: true
                                        color: "#2c3e50"
                                    }

                                    RowLayout {
                                        spacing: 10

                                        Rectangle {
                                            width: 20
                                            height: 20
                                            radius: 10
                                            color: model.audioEnabled ? "#27ae60" : "#e74c3c"

                                            Label {
                                                anchors.centerIn: parent
                                                text: "🎤"
                                                font.pixelSize: 10
                                            }
                                        }

                                        Rectangle {
                                            width: 20
                                            height: 20
                                            radius: 10
                                            color: model.videoEnabled ? "#27ae60" : "#e74c3c"

                                            Label {
                                                anchors.centerIn: parent
                                                text: "📹"
                                                font.pixelSize: 10
                                            }
                                        }

                                        Label {
                                            text: model.isStudying ? "学习中" : "休息中"
                                            font.pixelSize: 12
                                            color: model.isStudying ? "#27ae60" : "#95a5a6"
                                        }
                                    }
                                }

                                // 管理按钮（仅房主可见）
                                Button {
                                    visible: controller.isOwner && model.participantId !== wsClient.userId
                                    text: "..."
                                    implicitWidth: 40
                                    implicitHeight: 40

                                    onClicked: participantMenu.popup()

                                    Menu {
                                        id: participantMenu

                                        MenuItem {
                                            text: "静音"
                                            onTriggered: controller.muteParticipant(model.participantId)
                                        }
                                        MenuItem {
                                            text: "关闭摄像头"
                                            onTriggered: controller.stopParticipantVideo(model.participantId)
                                        }
                                        MenuItem {
                                            text: "移除"
                                            onTriggered: {
                                                kickDialog.targetId = model.participantId
                                                kickDialog.targetName = model.nickname
                                                kickDialog.open()
                                            }
                                        }
                                        MenuItem {
                                            text: "移交权限"
                                            onTriggered: {
                                                transferDialog.targetId = model.participantId
                                                transferDialog.targetName = model.nickname
                                                transferDialog.open()
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                Rectangle {
                    Layout.fillWidth: true
                    height: 60
                    color: "#34495e"
                    visible: controller.isOwner

                    // Button {
                    //     anchors.centerIn: parent
                    //     text: "全体静音"
                    //     font.pixelSize: 14
                    //     implicitWidth: 200
                    //     implicitHeight: 40

                    //     background: Rectangle {
                    //         color: parent.down ? "#c0392b" : "#e74c3c"
                    //         radius: 6
                    //     }

                    //     contentItem: Text {
                    //         text: parent.text
                    //         font: parent.font
                    //         color: "white"
                    //         horizontalAlignment: Text.AlignHCenter
                    //         verticalAlignment: Text.AlignVCenter
                    //     }

                    //     onClicked: muteAllDialog.open()
                    // }
                }
            }
        }
        
        // 右侧：视频区域
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#2c3e50"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 25
                spacing: 20
                // --- 视频展示区域 ---
                GridLayout {
                    id: videoGrid
                    columns: 2
                    rowSpacing: 20
                    columnSpacing: 20
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    // 本地视频窗口容器
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        color: "#1a252f"
                        border.color: "#27ae60"
                        border.width: 2
                        radius: 12
                        clip: true

                        VideoOutput {
                            id: localOutput
                            anchors.fill: parent
                            anchors.margins: 2
                            fillMode: VideoOutput.PreserveAspectFit

                            Component.onCompleted: {
                                // if (typeof mediaController !== "undefined") {
                                    mediaController.videoSink = videoSink
                                    console.log("已绑定本地 VideoSink")
                                    // mediaController.startCapture()
                                // }
                            }
                        }

                        // 浮动标签
                        Rectangle {
                            anchors.left: parent.left
                            anchors.top: parent.top
                            anchors.margins: 10
                            width: 70; height: 24
                            color: "#AA000000"
                            radius: 4
                            Label {
                                anchors.centerIn: parent
                                text: "本地"
                                color: "white"
                                font.pixelSize: 12
                            }
                        }
                    }

                    // 远程视频窗口容器
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        color: "#1a252f"
                        border.color: "#34495e"
                        border.width: 2
                        radius: 12
                        clip: true

                        VideoOutput {
                            id: remoteVideoOutput
                            anchors.fill: parent
                            anchors.margins: 2
                            fillMode: VideoOutput.PreserveAspectFit

                            Component.onCompleted: {
                                            // 将 QML 内部创建的 videoSink 对象传回给 C++
                                            mediaController.remoteSink = videoSink
                                            console.log("已绑定远程 VideoSink")
                                    }

                        }

                        // // 远程占位提示
                        // ColumnLayout {
                        //     anchors.centerIn: parent
                        //     visible: !remoteVideoOutput.videoSink || !remoteVideoOutput.videoSink.videoFrame
                        //     spacing: 10
                        //     Label {
                        //         text: "⌛"
                        //         font.pixelSize: 40
                        //         Layout.alignment: Qt.AlignHCenter
                        //     }
                        //     Label {
                        //         text: "等待对方加入..."
                        //         color: "#95a5a6"
                        //         font.pixelSize: 14
                        //         Layout.alignment: Qt.AlignHCenter
                        //     }
                        // }

                        // 浮动标签
                        Rectangle {
                            anchors.left: parent.left
                            anchors.top: parent.top
                            anchors.margins: 10
                            width: 70; height: 24
                            color: "#AA000000"
                            radius: 4
                            Label {
                                anchors.centerIn: parent
                                text: "远程视频"
                                color: "white"
                                font.pixelSize: 12
                            }
                        }
                    }
                }
            }

                // --- 控制栏区域 ---
                // Rectangle {
                //     Layout.fillWidth: true
                //     Layout.preferredHeight: 100
                //     color: "#34495e"
                //     radius: 15

                //     RowLayout {
                //         anchors.centerIn: parent
                //         spacing: 40

                //         // 麦克风按钮
                //         Button {
                //             id: micBtn
                //             property bool isMuted: false
                //             implicitWidth: 64; implicitHeight: 64

                //             contentItem: Text {
                //                 text: micBtn.isMuted ? "🔇" : "🎤"
                //                 font.pixelSize: 28
                //                 horizontalAlignment: Text.AlignHCenter
                //                 verticalAlignment: Text.AlignVCenter
                //             }

                //             background: Rectangle {
                //                 color: micBtn.isMuted ? "#e74c3c" : "#27ae60"
                //                 radius: 32
                //                 // 简单的点击缩放效果
                //                 scale: micBtn.pressed ? 0.9 : 1.0
                //                 Behavior on color { ColorAnimation { duration: 200 } }
                //             }

                //             onClicked: isMuted = !isMuted
                //         }

                //         // 摄像头按钮
                //         Button {
                //             id: camBtn
                //             property bool isOff: false
                //             implicitWidth: 64; implicitHeight: 64

                //             contentItem: Text {
                //                 text: camBtn.isOff ? "❌" : "📹"
                //                 font.pixelSize: 28
                //                 horizontalAlignment: Text.AlignHCenter
                //                 verticalAlignment: Text.AlignVCenter
                //             }

                //             background: Rectangle {
                //                 color: camBtn.isOff ? "#e74c3c" : "#2980b9"
                //                 radius: 32
                //                 scale: camBtn.pressed ? 0.9 : 1.0
                //                 Behavior on color { ColorAnimation { duration: 200 } }
                //             }

                //             onClicked: isOff = !isOff
                //         }
                //     }
                // }
        }

    
    // 关闭自习室确认对话框
    Dialog {
        id: closeRoomDialog
        title: "确认关闭"
        modal: true
        anchors.centerIn: parent
        standardButtons: Dialog.Yes | Dialog.No

        Label {
            text: "确定要关闭自习室吗？所有参与者将被移除。"
        }

        onAccepted: controller.closeRoom()
    }
}
}
