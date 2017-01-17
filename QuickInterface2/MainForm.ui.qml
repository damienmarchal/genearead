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
        }
    }
    Text {
        id: colorText
        //text: qsTr("Surlignez les lignes ! ")
        text: itemPalet.currentItem
        anchors.top: parent.top
        anchors.topMargin: 10
        style: Text.Raised
        font.capitalization: Font.AllUppercase
        font.family: "Arial"
        fontSizeMode: Text.HorizontalFit
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: painterPalet.currentSize
        color: colorPalet.currentColorLeft

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
    ItemPalet {
        id: itemPalet
        x: 532
        anchors.verticalCenterOffset: -63
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 8
    }
    ColorPalette {
        id: colorPalet
        x: 532
        y: 42
    }

    ReturnColor {
        id: returnColor
        x: 552
        y: 378
        currentColorLeft: colorPalet.currentColorLeft
        currentColorRight: colorPalet.currentColorRight
    }

    Text {
        id: returnText
        x: 532
        y: 362
        width: 116
        height: 20
        text: qsTr("Couleurs actuelles")
        font.pointSize: 7
        renderType: Text.NativeRendering
    }

    PainterPalet {
        id: painterPalet
        x: 532
        y: 199
        visible: itemPalet.paintMenu
    }
}
