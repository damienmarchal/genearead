import QtQuick 2.5

Rectangle {
    property alias mouseArea: mouseArea
    property alias textEdit: textEdit

    width: 360
    height: 360

    TextEdit {
        id: textEdit
        text: qsTr("Enter some text...")
        verticalAlignment: Text.AlignVCenter
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        Rectangle {
            anchors.fill: parent
            anchors.margins: -10
            color: "transparent"
            anchors.rightMargin: -158
            border.width: 1
        }
    }

    Rectangle {
        id: rectangle
        x: 35
        y: 81
        width: 145
        height: 45
        color: "#ffffff"

        MouseArea {
            id: mouseArea
            x: 112
            y: 103
            visible: true
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            enabled: true
            anchors.fill: parent
        }

        Text {
            id: text1
            text: qsTr("Text")
            font.pixelSize: 12
        }
    }
}
