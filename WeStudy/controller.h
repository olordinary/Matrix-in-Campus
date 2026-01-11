#pragma once
#include <QObject>
#include <QQmlListProperty>
#include "studyroom.h"
#include "participant.h"

class WebSocketClient;
class WebRTCManager;


class Controller:public QObject//只管理用户当前所在的1个房间，在服务器上可以能有很多房间
{
        //只要底层数据改变了，并且希望QML界面更新，就必须发出对应的NOTIFY信号！
Q_OBJECT//只要改变了属性就一定要发射对应的信号（有些隐士/显示处理函数）
    Q_PROPERTY(StudyRoom* currentRoom READ currentRoom NOTIFY currentRoomChanged)//因为属性是指针或列表，需要手动发出信号：
    Q_PROPERTY(QQmlListProperty<Participant> participants READ participants NOTIFY participantsChanged)//当这些信号发出时属性绑定的会自动更新
    Q_PROPERTY(bool isInRoom READ isInRoom NOTIFY isInRoomChanged)                                     //显示监听信号
    Q_PROPERTY(bool isOwner READ isOwner NOTIFY isOwnerChanged)                                        //列表绑定model: controller.participants  // 自动监听participantsChanged信号
<<<<<<< HEAD

=======
    Q_PROPERTY(bool isStudying READ isStudying NOTIFY isStudyingChanged)
>>>>>>> bca9fd1 (without mediacapture)
public:
    explicit Controller(WebSocketClient *client, WebRTCManager *webrtc, QObject *parent = nullptr);
    StudyRoom *currentRoom() const { return m_currentRoom; }//getter
    QQmlListProperty<Participant> participants();//getter
    bool isInRoom() const { return m_currentRoom != nullptr; }//websocket通信是异步过程，A发出请求创建房间，等待服务器响应，会有更对应该的handle函数处理
    bool isOwner() const;
<<<<<<< HEAD
=======
    bool isStudying() const{return m_isStudying;}
>>>>>>> bca9fd1 (without mediacapture)
    Q_INVOKABLE void createRoom(const QString &roomName,
                                int maxParticipants,
                                bool isPrivate,
                                bool videoStatus,
                                bool audioStatus,
                                const QString &password = " ");
    Q_INVOKABLE void joinRoom(const QString &roomId, const QString &password = "");
<<<<<<< HEAD
=======
    Q_INVOKABLE void startStudying();
    Q_INVOKABLE void stopStudying();
>>>>>>> bca9fd1 (without mediacapture)

    ~Controller();
signals:
    void currentRoomChanged();
    void errorOccurred(const QString &error);
    void isInRoomChanged();
    void isOwnerChanged();
    void participantsChanged();
<<<<<<< HEAD
=======
    void isStudyingChanged();
>>>>>>> bca9fd1 (without mediacapture)

private slots:
    void handleRoomCreated(const QString &roomId, const QJsonObject &roomInfo);//创建房间后对客户端的改变。更新当前房间的m_currentRoom,更新当前房间的m_participants
    void handleRoomJoined(const QString &roomId, const QJsonObject &roomInfo);
    void handleParticipantJoined(const QJsonObject &participant);

private:
    void clearCurrentRoom();//清除当前房间
    void updateParticipantsFromJson(const QJsonArray &participantsArray);//更新当前房间的m_participants
    Participant* findParticipant(const QString &participantId);

   WebSocketClient *m_client;
   WebRTCManager *m_webrtc;
   StudyRoom *m_currentRoom;//存储我所有房间信息和参与者等等
   QList<Participant*> m_participants;
<<<<<<< HEAD
=======
   bool m_isStudying;
>>>>>>> bca9fd1 (without mediacapture)

};
