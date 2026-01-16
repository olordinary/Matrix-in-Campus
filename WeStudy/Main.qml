
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 1280
    height: 800
    title: "WeStudy"
    
    color: "#f5f7fa"
    
    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: lobbyPage
    }
    
    // 大厅页面
    Component {
        id: lobbyPage
        LobbyPage {
            onCreateRoom: {
                stackView.push(createRoomPage)
            }
            onJoinRoom: function(roomId) {
               controller.joinRoom(roomId, "")//房间控制器对象来实现
            }

        }
    }
    // 创建自习室页面
    Component {
        id: createRoomPage
        CreateRoomPage {
            onBack: {
                stackView.pop()
            }
        }
    }

    // 自习室页面
    Component {
        id: studyRoomPage
        StudyRoomPage {
        }
    }



      // 监听房间状态变化
    Connections {
        target: controller

        function onCurrentRoomChanged() {
            if (controller.isInRoom) {
                stackView.replace(studyRoomPage)
            } else {
                stackView.replace(lobbyPage)
            }
        }

        function onErrorOccurred(error) {
            errorDialog.text = error
            errorDialog.open()
        }
    }


    // 错误对话框
    Dialog {
        id: errorDialog
        title: "提示"
        modal: true
        anchors.centerIn: parent
        standardButtons: Dialog.Ok

        property string text: ""

        Label {
            text: errorDialog.text
        }
    }
}

