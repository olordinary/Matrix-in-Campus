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

    
    // 监听房间状态变化


}
