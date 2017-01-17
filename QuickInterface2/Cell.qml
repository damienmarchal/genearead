import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2

Item {
    id: container
    property alias cellColor: rectangle.color
    signal clicked(color cellColor)

    width: 25; height: 25
    property alias mouseArea: mouseArea
    property alias rectangle: rectangle
    Rectangle {
        id: rectangle
        border.color: "white"
        anchors.fill: parent
    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        acceptedButtons: Qt.AllButtons
        //onClicked: container.clicked(container.cellColor)
        //onPressed: console.log(pressedButtons)
        onPressed: container.clicked(container.cellColor)
    }
}
