import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3

Item {
    id: page
    width: 640
    height: 480
    property alias mouseArea1: mouseArea1
    property alias mouseArea2: mouseArea2
    property alias mouseArea3: mouseArea3
    property alias bottomLeftRect: bottomLeftRect
    property alias middleRightRect: middleRightRect
    property alias topLeftRect: topLeftRect
    property alias icon: icon

    Image {
        id: icon
        x: 10
        y: 20
        width: 55
        height: 41
        fillMode: Image.PreserveAspectCrop
        source: "toastNatacha.jpg"
    }

    Rectangle {
        id: topLeftRect
        x: 10
        y: 20
        width: 55
        height: 41
        color: "#00000000"
        radius: 2
        anchors.leftMargin: 10
        anchors.topMargin: 20
        border.width: 1
        border.color: "#808080"
        anchors.left: parent.left
        anchors.top: parent.top

        MouseArea {
            id: mouseArea1
            anchors.fill: parent
        }
    }

    Rectangle {
        id: middleRightRect
        x: 0
        y: 0
        width: 55
        height: 41
        color: "#00000000"
        radius: 2
        anchors.right: parent.right
        anchors.rightMargin: 10
        MouseArea {
            id: mouseArea2
            anchors.fill: parent
        }
        border.color: "#808080"
        border.width: 1
        anchors.top: parent.top
    }

    Rectangle {
        id: bottomLeftRect
        x: 100
        y: 100
        width: 55
        height: 41
        color: "#00000000"
        radius: 2
        border.color: "#808080"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.leftMargin: 10
        MouseArea {
            id: mouseArea3
            anchors.fill: parent
        }
        border.width: 1
        anchors.left: parent.left
    }
}
