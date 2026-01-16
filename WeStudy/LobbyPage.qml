import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page{
    id:lobby
    signal createRoom()
    signal joinRoom(string roomId)

    header:ToolBar{
        background:Rectangle{
            color:"#3498db"
        }

        RowLayout{
            anchors.fill:parent
            anchors.leftMargin: 20
            anchors.rightMargin: 20

            Label{
                text:"WeStudy"
                font.pixelSize: 24
                font.bold: true
                color: "light blue"
            }

            Item{
                Layout.fillWidth:true
            }

            Label {
                text: wsClient.connected ? "已连接" : "未连接"
                color: wsClient.connected ? "#2ecc71" : "#e74c3c"
                font.pixelSize: 14
            }

            Rectangle {
                width: 10
                height: 10
                radius: 5
                color: wsClient.connected ? "#2ecc71" : "#e74c3c"
            }
        }
    }

    ColumnLayout{
        anchors.fill:parent
        anchors.margins:20
        spacing:20

        // 欢迎区域
        Rectangle {
            Layout.fillWidth: true
            height: 150
            color: "white"
            radius: 10

            ColumnLayout {
                anchors.centerIn: parent
                spacing: 15

                Label {
                    text: "Welcome to WeStudy"
                    font.pixelSize: 28
                    font.bold: true
                    color: "#2c3e50"
                    Layout.alignment: Qt.AlignHCenter
                }

                Label {
                    text: "选择加入或创建一个自习室开始学习"
                    font.pixelSize: 16
                    color: "#7f8c8d"
                    Layout.alignment: Qt.AlignHCenter
                }
            }
        }

        // 按钮区域
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 20

            Button {
                text: "创建自习室"
                font.pixelSize: 16
                implicitWidth: 180
                implicitHeight: 50

                background: Rectangle {
                    color: parent.down ? "#27ae60" : "#2ecc71"
                    radius: 8
                }

                contentItem: Text {
                    text: parent.text
                    font: parent.font
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                onClicked: lobby.createRoom()

            }

            TextField {
                id: serveripFiled
                text: "ws://localhost:8080"
                // placeholderText: "ws://localhost:9999"
                // placeholderTextColor: "#999999"
                font.pixelSize: 16
                implicitWidth: 250
                implicitHeight: 50

                background: Rectangle {
                    color: "white"
                    border.color: serveripFiled.focus ? "#3498db" : "#bdc3c7"
                    border.width: 2
                    radius: 8
                }


                // 文本区域内边距
                leftPadding: 15
                rightPadding: 15
                //验证器
                // validator: RegularExpressionValidator {
                //                    regularExpression: /^(ws:\/\/|wss:\/\/)[^\s]+$/
                //                }
            }

            Button{
                id: connectButton
                text: wsClient.connected ? "已连接" : "连接服务器"
                font.pixelSize: 16
                implicitWidth: 180
                implicitHeight: 50

                background: Rectangle {
                    color: parent.down ? "#2980b9" : "#3498db"
                    radius: 8
                }

                contentItem: Text {
                    text: parent.text
                    font: parent.font
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
              onClicked: {
                  if(!wsClient.connected){
                     wsClient.connectToServer(serveripFiled.text.toString());
                  }
              }
            }
        }

        Rectangle{
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "white"
            radius: 10

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 15

                RowLayout {
                            spacing: 12
                            Layout.fillWidth: true

                            // 标题
                            Label {
                                text: "可用自习室"
                                font.pixelSize: 20
                                font.bold: true
                                color: "#2c3e50"
                            }

                            // 占位空间
                            Item { Layout.fillWidth: true }

                            // 搜索输入框
                            TextField {
                                id: searchField2
                                placeholderText: "请输入自习室ID....."
                                placeholderTextColor: "#999999"  // 提示文本颜色
                                font.pixelSize: 14
                                implicitWidth: 250
                                background: Rectangle {
                                    implicitHeight: 40
                                    radius: 20
                                    color: "#f5f5f5"
                                    border.width: 1
                                    border.color: "#e0e0e0"
                                }

                            }

                            // 搜索按钮
                            Button {
                                id: searchButton
                                text: "搜索"
                                font.pixelSize: 14
                                font.bold: true
                                implicitWidth: 100
                                implicitHeight: 40

                                background: Rectangle {
                                    radius: 8
                                    color: parent.down ? "#1976D2" : "#2196F3"
                                }

                                contentItem: Text {
                                    text: parent.text
                                    font: parent.font
                                    color: "white"
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }
                        }

                Connections {
                    target: wsClient
                    function onRoomListReceived(rooms) {
                        roomListModel.clear()
                        for (let i = 0; i < rooms.length; ++i) {
                            const room = rooms[i]
                            roomListModel.append({
                                roomId: room.roomId,
                                roomName: room.roomName,
                                currentParticipants: room.currentParticipants,
                                maxParticipants: room.maxParticipants,
                                isPrivate: room.isPrivate
                            })
                        }
                    }
                }
                Component.onCompleted: {
                }

                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    clip: true

                    ListView {
                        id: roomListView
                        model: ListModel {
                            id: roomListModel
                        }

                        spacing: 10

                        delegate: Rectangle {
                            width: roomListView.width
                            height: 80
                            color: "#ecf0f1"
                            radius: 8

                            RowLayout {
                                anchors.fill: parent
                                anchors.margins: 15
                                spacing: 20

                                Rectangle {
                                    width: 50
                                    height: 50
                                    radius: 25
                                    color: "#3498db"

                                    Label {
                                        anchors.centerIn: parent
                                        text: "自"
                                        font.pixelSize: 20
                                        font.bold: true
                                        color: "white"
                                    }
                                }

                                ColumnLayout {
                                    Layout.fillWidth: true
                                    spacing: 5

                                    Label {
                                        text:model.roomName
                                        font.pixelSize: 18
                                        font.bold: true
                                        color: "#2c3e50"
                                    }

                                    RowLayout {
                                        spacing: 10

                                        Label {
                                            text:  model.currentParticipants + "/" + model.maxParticipants + " 人"
                                            font.pixelSize: 14
                                            color: "#7f8c8d"
                                        }

                                        Rectangle {
                                            width: 1
                                            height: 15
                                            color: "#bdc3c7"
                                        }

                                        Label {
                                            text: model.isPrivate ? "私密" : "公开"
                                            font.pixelSize: 14
                                            color: model.isPrivate ? "#e74c3c" : "#27ae60"
                                        }
                                    }
                                }
                                //大厅的加入不需要密码
                                Button {
                                    text: "加入"
                                    font.pixelSize: 14
                                    implicitWidth: 80
                                    implicitHeight: 40

                                    background: Rectangle {
                                        color: parent.down ? "#27ae60" : "#2ecc71"
                                        radius: 6
                                    }

                                    contentItem: Text {
                                        text: parent.text
                                        font: parent.font
                                        color: "white"
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                    }
                                onClicked: lobby.joinRoom(model.roomId)

                                }
                            }
                        }
                    }
                }
            }

        }


    }
    function connectToServer() {
            var url = serveripField.text.trim()

            if (url === "") {
                url = "ws://localhost:8080"
                serveripField.text = url
            }

            // 验证URL格式
            console.log("正在连接服务器:", url)
            wsClient.connectToServer(url)
        }
}
