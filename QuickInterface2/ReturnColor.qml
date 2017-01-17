import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2

Rectangle {
    id: returnColor
    width: 60; height: 30
    color: "lightgray"
    radius: 2
    property color currentColorLeft
    property color currentColorRight

    Grid {
        id: colorReturn
        x: 0
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.horizontalCenter: parent.horizontalCenter
        rows: 3
        columns: 2
        spacing: 3

        Cell {
            cellColor: currentColorLeft
        }
        Cell {
            cellColor: currentColorRight

        }
    }
}

