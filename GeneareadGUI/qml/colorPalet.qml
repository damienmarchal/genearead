import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2


Rectangle {
    id: page
    width: 60; height: 84
    color: "lightgray"
    radius: 2
    property color currentColor

    Grid {
        id: colorPicker
        x: 0
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.horizontalCenter: parent.horizontalCenter
        rows: 3
        columns: 2
        spacing: 3

        Cell {
            cellColor: "red"
            onClicked: currentColor = cellColor
        }
        Cell {
            cellColor: "#1ee100"
             onClicked: currentColor = cellColor
        }
        Cell {
            //cellColor: "blue"
            //onClicked: currentColor = cellColor
            onClicked: console.log(onClicked)
        }
        Cell {
            cellColor: "yellow"
            onClicked: currentColor = cellColor
        }
        Cell {
            cellColor: "#9e02e1"
             onClicked: currentColor = cellColor
        }
        Cell {
            cellColor: "#945d26"
            onClicked: currentColor = cellColor
        }
    }
}
