import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtMultimedia

Page {
    id: root
    
    signal leaveRoom()

    Camera {
        id: camera
        active: true   // ⚠ 默认不打开
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
            
            Button {

                text: controller.isStudying ? "结束自习" : "开始自习"
                font.pixelSize: 14
                implicitWidth: 100
                implicitHeight: 35
                
                background:  Rectangle {
                    color: controller.isStudying ? "#e74c3c" : "#27ae60"
                    radius: 6
                }
                
                contentItem: Text {
                    text: parent.text
                    font: parent.font
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                
                onClicked: {
                    if (controller.isStudying) {
                        controller.stopStudying()
                    } else {
                        controller.startStudying()
                    }
                }

            }
            
            Button {

                text:controller.isOwner ? "关闭自习室" : "离开自习室"
                font.pixelSize: 14
                implicitWidth: 120
                implicitHeight: 35
                
                background: Rectangle {

                    color:"#e74c3c"
                    radius: 6
                }
                
                contentItem: Text {
                    text: parent.text
                    font: parent.font
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                
                onClicked: {
                    if (controller.isOwner) {
                        closeRoomDialog.open()
                    } else {
                        root.leaveRoom()
                    }
                }

            }
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

                    Button {
                        anchors.centerIn: parent
                        text: "全体静音"
                        font.pixelSize: 14
                        implicitWidth: 200
                        implicitHeight: 40

                        background: Rectangle {
                            color: parent.down ? "#c0392b" : "#e74c3c"
                            radius: 6
                        }

                        contentItem: Text {
                            text: parent.text
                            font: parent.font
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        onClicked: muteAllDialog.open()
                    }
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
                anchors.margins: 20
                spacing: 15
                
                Label {
                    text: "视频预览区域"
                    font.pixelSize: 24
                    font.bold: true
                    color: "white"
                    Layout.alignment: Qt.AlignHCenter
                }
                
                // // 视频网格
                // GridLayout {
                //     Layout.fillWidth: true
                //     Layout.fillHeight: true
                //     columns: 2
                //     rowSpacing: 15
                //     columnSpacing: 15
                    
                //     // 这里应该动态生成视频窗口
                //     // Repeater {
                //     //     model: 2
                //         VideoSink{
                //             id: localVideo
                //             onVideoFrameChanged: {
                //                         // mediaController.onVideoFrame(videoSink.videoFrame)
                //                         if (localVideo.videoFrame && localVideo.videoFrame.isValid)
                //                                    mediaController.onVideoFrame(localVideo.videoFrame)
                //                     }
                //         }

                // }
                GridLayout {
                        id: videoGrid
                        columns: 2
                        rowSpacing: 15
                        columnSpacing: 15
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        // 1️⃣ 本地视频窗口
                        Rectangle {
                            width: 380
                            height: 300
                            color: "black"

                            VideoSink {
                                id: localVideoSink
                                onVideoFrameChanged: {
                                    if (localVideoSink.videoFrame && localVideoSink.videoFrame.isValid)
                                        mediaController.onVideoFrame(localVideoSink.videoFrame) // 传给C++
                                }
                            }

                            VideoOutput {
                                id:localOutput
                                anchors.fill: parent
                                // videoSink: localVideoSink

                            }
                        }

                        // 2️⃣ 远程视频窗口
                        Rectangle {
                            width: 380
                            height: 300
                            color: "black"

                            // VideoOutput 直接显示 C++ 传来的远端帧
                            VideoOutput {
                                id: remoteVideoOutput
                                anchors.fill: parent
                                // C++ 层会通过 setSource(QVideoFrame) 或者自定义 VideoSink 替代
                                // videoSink: remoteVideoSink
                            }
                        }
                    }



                
                // 控制栏
                Rectangle {
                    Layout.fillWidth: true
                    height: 80
                    color: "#34495e"
                    radius: 10
                    
                    RowLayout {
                        anchors.centerIn: parent
                        spacing: 30
                        
                        Button {
                            id:micB
                            text:"🎤"
                            font.pixelSize: 24
                            implicitWidth: 60
                            implicitHeight: 60
                            
                            background: Rectangle {
                                color:"#27ae60"
                                radius: 30
                            }
                            
                            onClicked: {
                                micB.text="🔇"
                                // color:"#27ae60"

                            }
                        }
                        
                        Button {

                            text:"📹"
                            font.pixelSize: 24
                            implicitWidth: 60
                            implicitHeight: 60
                            
                            background: Rectangle {

                                radius: 30
                            }
                            

                            onClicked: {
                                text:"📷"

                            }
                        }
                    }
                }
            }
        }
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
