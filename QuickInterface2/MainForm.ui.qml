import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3

Item {
    id: item1
    width: 640
    height: 480
    property alias itemPalet: itemPalet
    property alias mouseArea1: mouseArea1
    property alias colorText: colorText
    property alias colorPalet: colorPalet
    property alias mouseArea: mouseArea

    property alias image: image

    Image {
        id: image
        x: 106
        y: 72
        width: 213
        height: 336
        source: "Livret F.jpg"

        MouseArea {
            id: mouseArea1
            anchors.fill: parent
            //onClicked: states.changes
        }
    }
    Text {
        id: colorText
        //text: qsTr("Surlignez les lignes ! ")
        text : itemPalet.currentItem
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

    ItemPalet {
        id: itemPalet
        anchors.verticalCenterOffset: -160
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
