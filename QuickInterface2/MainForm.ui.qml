import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3

Item {
    id: item1
    width: 640
    height: 480
    property alias principalSplitView: principalSplitView
    property alias toolBarSplitView: toolBarSplitView
    property alias image: image
    property alias mouseArea1: mouseArea1
    property alias colorText: colorText
    property alias mouseArea: mouseArea

    Text {
        id: colorText
        x: 0
        y: 0
        width: 200
        height: 30
        //text: qsTr("Surlignez les lignes ! ")
        anchors.horizontalCenterOffset: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        style: Text.Raised
        font.capitalization: Font.AllUppercase
        font.family: "Arial"
        fontSizeMode: Text.HorizontalFit
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: linesTool.currentSize
        color: linesTool.currentColorLeft
        text: linesTool.currentItem
        z: 1

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            opacity: 0
        }
    }

    states: [
        State {
            name: "State1"
            when: mouseArea.containsMouse
            PropertyChanges {
                target: colorText
                visible: false
            }
        }
    ]

    SplitView {
        id: principalSplitView
        anchors.fill: parent
        orientation: Qt.Horizontal

        Image {
            id: image
            width: 213
            height: 336
            clip: false
            source: "Livret F.jpg"
            Layout.fillWidth: true
            fillMode: Image.PreserveAspectFit

            MouseArea {
                id: mouseArea1
                anchors.rightMargin: 0
                anchors.bottomMargin: 0
                anchors.leftMargin: 0
                anchors.topMargin: 0
                anchors.fill: parent
            }
        }

        Column {
            id: toolBarSplitView
            width: 400
            spacing: 10

            BackTool {
                id: backTool
                height: boxSize
            }

            LinesTool {
                id: linesTool
                dispo: !backTool.clickedTool || backTool.validation
            }
        }

        /*LinesTool {
                    id: linesTool
                                y:0
                                            width: 400
                                                        height: 350
                                                                    dispo: !backTool.clickedTool || backTool.validation
                                                                                //clickedTool : !backTool.clickedTool
                                                                                            //enabled : false

                                                                                                        height: boxSize
                                                                                                                }*/
    }
}
