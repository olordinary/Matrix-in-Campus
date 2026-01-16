#pragma once
#include <QObject>
#include <QQmlListProperty>
#include "studyroom.h"
#include "participant.h"

class WebSocketClient;
class WebRTCManager;


class Controller:public QObject//只管理用户当前所在的1个房间，在服务器上可以能有很多房间
{

Q_OBJECT
    //setter
    Q_PROPERTY(StudyRoom* currentRoom READ currentRoom NOTIFY currentRoomChanged)   //是否加入自习室 使qml能访问自习室里面的信息（m_curentRoom）
    Q_PROPERTY(QQmlListProperty<Participant> participants READ participants NOTIFY participantsChanged)     //表示当前自习室的成员列表
    Q_PROPERTY(bool isInRoom READ isInRoom NOTIFY isInRoomChanged)  //表示当前客户端是否已经进入某个自习室
    Q_PROPERTY(bool isOwner READ isOwner NOTIFY isOwnerChanged)     //表示是否为房主
    Q_PROPERTY(bool isStudying READ isStudying NOTIFY isStudyingChanged)    //是否处于自习状态

public:
    explicit Controller(WebSocketClient *client, WebRTCManager *webrtc, QObject *parent = nullptr); //防止隐式构造
    //getter
    StudyRoom *currentRoom() const { return m_currentRoom; }
    QQmlListProperty<Participant> participants();
    bool isInRoom() const { return m_currentRoom != nullptr; }//websocket通信是异步过程，A发出请求创建房间，等待服务器响应，会有更对应该的handle函数处理
    bool isOwner() const;
    bool isStudying() const { return m_isStudying; }


    //ui接口
    Q_INVOKABLE void createRoom(const QString &roomName,
                                int maxParticipants,
                                bool isPrivate,
                                bool videoStatus,
                                bool audioStatus,
                                const QString &password = " ");
    Q_INVOKABLE void joinRoom(const QString &roomId, const QString &password = "");
    Q_INVOKABLE void startStudying();
    Q_INVOKABLE void stopStudying();
    ~Controller();
    //信号：Controller通知QML刷新与错误通知
signals:
    void currentRoomChanged();
    void errorOccurred(const QString &error);
    void isInRoomChanged();
    void isOwnerChanged();
    void participantsChanged();
    void isStudyingChanged();

    //接收WebSocketCient的异步事件
private slots:
    void handleRoomCreated(const QString &roomId, const QJsonObject &roomInfo);//创建房间后对客户端的改变。更新当前房间的m_currentRoom,更新当前房间的m_participants
    void handleRoomJoined(const QString &roomId, const QJsonObject &roomInfo);
    void handleParticipantJoined(const QJsonObject &participant);

private:
    void clearCurrentRoom();//清空UI模型+关闭WebRTC
    void updateParticipantsFromJson(const QJsonArray &participantsArray);//更新当前房间的m_participants
    Participant* findParticipant(const QString &participantId); //防止重复加入同一个participantid


   StudyRoom *m_currentRoom;    //当前自习室（自习室、房主、最大人数、当前人数、默认音视频状态）
   QList<Participant*> m_participants;  //当前自习室成员列表（给QML的ListView用）
   bool m_isStudying;   //当前客户端是否处于“开始自习”状态
   //与transport连接的指针 与media层连接的指针
   WebSocketClient *m_client;   //负责跟服务器通信、收发自习室/成员事件
   WebRTCManager *m_webrtc;     //负责与WebRTC连接与音视频链路

};
