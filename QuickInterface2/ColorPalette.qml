import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2


Rectangle {
    id: page
    width: 60; height: 84
    color: "lightgray"
    radius: 2
    property color currentColorLeft
    property color currentColorRight

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
            onClicked: {
                if(mouseArea.pressedButtons == 1){
                   currentColorLeft = cellColor
                }
                else{
                   currentColorRight = cellColor
                }
            }
        }
        Cell {
            cellColor: "#1ee100"
            onClicked: {
                if(mouseArea.pressedButtons == 1){
                   currentColorLeft = cellColor
                }
                else{
                   currentColorRight = cellColor
                }
            }
        }
        Cell {
            cellColor: "blue"
            onClicked: {
                if(mouseArea.pressedButtons == 1){
                   currentColorLeft = cellColor
                }
                else{
                   currentColorRight = cellColor
                }
            }

        }
        Cell {
            cellColor: "yellow"
            onClicked: {
                if(mouseArea.pressedButtons == 1){
                   currentColorLeft = cellColor
                }
                else{
                   currentColorRight = cellColor
                }
            }
        }
        Cell {
            cellColor: "#9e02e1"
            onClicked: {
                if(mouseArea.pressedButtons == 1){
                   currentColorLeft = cellColor
                }
                else{
                   currentColorRight = cellColor
                }
            }
        }
        Cell {
            cellColor: "#945d26"
            onClicked: {
                if(mouseArea.pressedButtons == 1){
                   currentColorLeft = cellColor
                }
                else{
                   currentColorRight = cellColor
                }
            }
        }
    }
}
