import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: root
    
    signal back()

    property var existingRoomNameMap: ({})

    function isDuplicateRoomName(name) {
        const n = (name || "").trim()
        if (n === "") return false
        return existingRoomNameMap[n] === true
    }
    header: ToolBar {
        background: Rectangle {
            color: "#3498db"
        }
        
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 20
            anchors.rightMargin: 20
            
            ToolButton {
                text: "← 返回"
                font.pixelSize: 16
                
                contentItem: Text {
                    text: parent.text
                    font: parent.font
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                
                onClicked: root.back()
            }
            
            Label {
                text: "创建自习室"
                font.pixelSize: 24
                font.bold: true
                color: "white"
                Layout.fillWidth: true
            }
        }
    }
    
    ScrollView {
        //可滚动的视图组件
        anchors.fill: parent
        contentWidth: availableWidth
        
        ColumnLayout {
            width: Math.min(parent.width, 600)
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 40
            spacing: 20
            
            // 自习室名称
            Rectangle {
                Layout.fillWidth: true
                height: 120
                color: "white"
                radius: 10
                
                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 10
                    
                    Label {
                        text: "自习室名称"
                        font.pixelSize: 16
                        font.bold: true
                        color: "#2c3e50"
                    }
                    
                    TextField {
                        id: roomNameField
                        Layout.fillWidth: true
                        placeholderText: "请输入自习室名称"
                        font.pixelSize: 14
                        placeholderTextColor: "#5d6d7e"
                        
                        background: Rectangle {
                            color: "#ecf0f1"
                            radius: 6
                            border.color: roomNameField.focus ? "#3498db" : "transparent"
                            border.width: 2
                        }
                    }
                    
                    Label {
                        text: root.isDuplicateRoomName(roomNameField.text) ? "名称已存在，请更换一个名称" : "自习室名称不能为空且不能与已有自习室重复"
                        font.pixelSize: 12
                        color: root.isDuplicateRoomName(roomNameField.text) ? "#e74c3c" : "#7f8c8d"
                    }
                }
            }
            
            // 人数上限
            Rectangle {
                Layout.fillWidth: true
                height: 140
                color: "white"
                radius: 10
                
                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 10
                    
                    Label {
                        text: "人数上限"
                        font.pixelSize: 16
                        font.bold: true
                        color: "#2c3e50"
                    }
                    
                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 15
                        
                        Slider {
                            id: maxParticipantsSlider
                            Layout.fillWidth: true
                            from: 1
                            to: 2
                            value: 10
                            stepSize: 1
                        }
                        
                        Label {
                            text: Math.round(maxParticipantsSlider.value) + " 人"
                            font.pixelSize: 18
                            font.bold: true
                            color: "#3498db"
                            Layout.minimumWidth: 60
                        }
                    }
                    
                    Label {
                        text: "设置自习室最多可容纳的人数"
                        font.pixelSize: 12
                        color: "#7f8c8d"
                    }
                }
            }
            
            // 私密性设置
            Rectangle {
                Layout.fillWidth: true
                height: 180
                color: "white"
                radius: 10
                
                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 15
                    
                    Label {
                        text: "私密性设置"
                        font.pixelSize: 16
                        font.bold: true
                        color: "#2c3e50"
                    }
                    
                    Switch {
                        id: privateSwitch
                        text: "设为私密自习室"
                        font.pixelSize: 14
                    }
                    
                    TextField {
                        id: passwordField
                        visible: privateSwitch.checked
                        Layout.fillWidth: true
                        placeholderText: "请输入密码"
                        placeholderTextColor: "#5d6d7e"
                        echoMode: TextInput.Password
                        enabled: privateSwitch.checked
                        font.pixelSize: 14
                        
                        background: Rectangle {
                            color: passwordField.enabled ? "#ecf0f1" : "#f8f9fa"
                            radius: 6
                            border.color: passwordField.focus ? "#3498db" : "transparent"
                            border.width: 2
                        }
                    }
                    
                    Label {
                        text: "私密自习室需要密码才能加入"
                        font.pixelSize: 12
                        color: "#7f8c8d"
                    }
                }
            }


            //初始设备状态

            Rectangle {
                Layout.fillWidth: true
                height: 180
                color: "white"
                radius: 10

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 10

                Label {
                        text: "默认开启"
                        font.pixelSize: 16
                        font.bold: true
                        color: "#2c3e50"
                    }
                Switch {
                    id: audioSwitch
                    text: "麦克风"
                    font.pixelSize: 14
                }
                Switch {
                    id: videoSwitch
                    text: "摄像头"
                    font.pixelSize: 14
                }

            }


        }


            
            // 按钮区域
            RowLayout {
                Layout.fillWidth: true
                Layout.topMargin: 20
                spacing: 15
                
                Button {
                    text: "取消"
                    font.pixelSize: 16
                    Layout.fillWidth: true
                    implicitHeight: 50
                    
                    background: Rectangle {
                        color: parent.down ? "#95a5a6" : "#bdc3c7"
                        radius: 8
                    }
                    
                    contentItem: Text {
                        text: parent.text
                        font: parent.font
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    
                    onClicked: root.back()
                }
                
                Button {
                    text: "创建并加入"
                    font.pixelSize: 16
                    Layout.fillWidth: true
                    implicitHeight: 50
                    enabled: roomNameField.text.trim() !== ""&&!root.isDuplicateRoomName(roomNameField.text)
                    
                    background: Rectangle {
                        color: parent.enabled ? (parent.down ? "#27ae60" : "#2ecc71") : "#95a5a6"
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
                        controller.createRoom(
                            roomNameField.text.trim(),
                            Math.round(maxParticipantsSlider.value),
                            privateSwitch.checked,
                            videoSwitch.checked,
                            audioSwitch.checked,
                            passwordField.text

                        )
                    }
                }
            }
            
            Item { height: 40 }
        }
    }
    Connections {
        target: wsClient
        function onRoomListReceived(rooms) {
            const m = ({})
            for (let i = 0; i < rooms.length; ++i) {
                const r = rooms[i]
                if (r && r.roomName) {
                    m[r.roomName] = true
                }
            }
            root.existingRoomNameMap = m
        }
    }
}
