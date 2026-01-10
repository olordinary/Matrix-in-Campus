import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Page {
    id: root
    
    signal leaveRoom()
    
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

                text:"RoomName"
                font.pixelSize: 20
                font.bold: true
                color: "white"
            }
            
            Rectangle {
                width: 80
                height: 30
                radius: 15          
                
                Label {
                    anchors.centerIn: parent         
                    text:"参与者权限"
                    font.pixelSize: 12
                    color: "white"
                }
            }
            
            Item { Layout.fillWidth: true }
            
            Label {

                text:"当前人数 ？/MAX人"
                font.pixelSize: 14
                color: "white"
            }
            
            Button {

                text:"开始自习"
                font.pixelSize: 14
                implicitWidth: 100
                implicitHeight: 35
                
                background: Rectangle {

                    color:"#27ae60"
                    radius: 6
                }
                
                contentItem: Text {
                    text: parent.text
                    font: parent.font
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                

            }
            
            Button {

                text:"离开自习室"
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
                    //todo:如果是房主，提示弹窗
                    root.leaveRoom()
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

                        text:"参与者（人数）"
                        font.pixelSize: 18
                        font.bold: true
                        color: "white"
                    }
                }
                
                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    clip: true
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
                
                // 视频网格
                GridLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    columns: 2
                    rowSpacing: 15
                    columnSpacing: 15
                    
                    // 这里应该动态生成视频窗口
                    Repeater {
                        model: 2
                        
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            color: "#34495e"
                            radius: 10
                            
                            Label {
                                anchors.centerIn: parent
                                text: "视频窗口 " + (index + 1)
                                font.pixelSize: 16
                                color: "#7f8c8d"
                            }
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
    

}
