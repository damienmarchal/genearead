import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3

Item {
    id: item1
    width: 640
    height: 480
    property alias mouseArea: mouseArea

    property alias image: image

    Image {
        id: image
        x: 106
        y: 72
        width: 213
        height: 336
        source: "Livret F.jpg"
    }
    Text {
        id: colorText
        text: qsTr("Surlignez les lignes ! ")
        anchors.top: parent.top
        anchors.topMargin: 10
        style: Text.Raised
        font.capitalization: Font.AllUppercase
        font.family: "Arial"
        fontSizeMode: Text.HorizontalFit
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 25
        color: colorPalet.currentColor

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            opacity: 0
        }
    }

    ColorPalet {
        id: colorPalet
        anchors.verticalCenterOffset: -100
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 10
    }

    states: [
        State {
            name: "State1"
            when: mouseArea.containsMouse
            PropertyChanges {
                target: colorText
                visible : false
            }
        }
    ]
}
