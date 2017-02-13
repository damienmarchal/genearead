import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3

Item {
    id: item1
    width: 1200
    height: 500
    property alias imageCanvas: imageCanvas
    property alias principalSplitView: principalSplitView
    property alias toolBarSplitView: toolBarSplitView
    property color currentColorLeft: linesTool.currentColorLeft
    property color currentColorRight: linesTool.currentColorRight
    property int currentSize: linesTool.currentSize
    property string currentItem: linesTool.currentItem

    //    Text {
    //        id: colorText
    //        x: 1
    //        y: 0
    //        width: 200
    //        height: 30
    //        //text: qsTr("Surlignez les lignes ! ")
    //        anchors.horizontalCenterOffset: 0
    //        anchors.top: parent.top
    //        anchors.topMargin: 0
    //        style: Text.Raised
    //        font.capitalization: Font.AllUppercase
    //        font.family: "Arial"
    //        fontSizeMode: Text.HorizontalFit
    //        anchors.horizontalCenter: parent.horizontalCenter
    //        font.pixelSize: linesTool.currentSize
    //        color: linesTool.currentColorLeft
    //        text: linesTool.currentItem
    //        z: 1

    //        MouseArea {
    //            id: mouseArea
    //            x: 1
    //            anchors.fill: parent
    //            opacity: 0
    //        }
    //    }

    //    states: [
    //        State {
    //            name: "State1"
    //            when: mouseArea.containsMouse
    //            PropertyChanges {
    //                target: colorText
    //                visible: false
    //            }
    //        }
    //    ]

    SplitView {
        id: principalSplitView
        x: 0
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        orientation: Qt.Horizontal

        ImageCanvas {
            id: imageCanvas
            x: 0
            colorLeft: currentColorLeft
            colorRight: currentColorRight
            size: linesTool.currentSize
            item: currentItem
            heightImage: item1.height
            Layout.fillWidth: true
        }
        Rectangle{
            width: 420
            color: "lightgray"
            Column {
                id: toolBarSplitView
                width: 420

                BackTool {
                    id: backTool
                    height: boxSize
                }

                LinesTool {
                    id: linesTool
                }
            }
        }

    }
}
