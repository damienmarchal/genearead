import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2

Item {
    id: container
    property alias cellItem: image.source
    signal clicked(string cellItem)

    width: 25; height: 25
    property alias mouseArea: mouseArea
    property alias image : image

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        acceptedButtons: Qt.AllButtons
        onClicked: container.clicked(container.cellItem)
    }

    Image {
        id: image
        anchors.fill: parent
    }
}
