import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2



Rectangle {
    id: page
    width: 100; height: 100
    color: "lightgray"
    radius: 1
    property color currentColorLeft : "red"
    property color currentColorRight : "blue"

    Grid {
        id: colorPicker
        x: 8
        y: 8
        width: 101
        height: 100
        rows: 3
        columns: 3
        spacing: 3

        Cell {
            cellColor: "red"
            //onClicked: mouseArea.pressedButtons == 1 ? currentColorLeft = cellColor : currentColorRight = cellColor
            onClicked:
                if(mouseArea.pressedButtons == 1 && !Qt.colorEqual(cellColor,currentColorRight)){
                    currentColorLeft = cellColor
                }
                else if (mouseArea.pressedButtons == 2 && !Qt.colorEqual(cellColor,currentColorLeft)){
                    currentColorRight = cellColor
                }
        }
        Cell {
            cellColor: "#1ee100"
            //onClicked: mouseArea.pressedButtons == 1 ? currentColorLeft = cellColor : currentColorRight = cellColor
            onClicked:
                if(mouseArea.pressedButtons == 1 && !Qt.colorEqual(cellColor,currentColorRight)){
                    currentColorLeft = cellColor
                }
                else if (mouseArea.pressedButtons == 2 && !Qt.colorEqual(cellColor,currentColorLeft)){
                    currentColorRight = cellColor
                }
        }
        Cell {
            cellColor: "blue"
            //onClicked: mouseArea.pressedButtons == 1 ? currentColorLeft = cellColor : currentColorRight = cellColor
            onClicked:
                if(mouseArea.pressedButtons == 1 && !Qt.colorEqual(cellColor,currentColorRight)){
                    currentColorLeft = cellColor
                }
                else if (mouseArea.pressedButtons == 2 && !Qt.colorEqual(cellColor,currentColorLeft)){
                    currentColorRight = cellColor
                }
        }
        Cell {
            cellColor: "yellow"
           //onClicked: mouseArea.pressedButtons == 1 ? currentColorLeft = cellColor : currentColorRight = cellColor
            onClicked:
                if(mouseArea.pressedButtons == 1 && !Qt.colorEqual(cellColor,currentColorRight)){
                    currentColorLeft = cellColor
                }
                else if (mouseArea.pressedButtons == 2 && !Qt.colorEqual(cellColor,currentColorLeft)){
                    currentColorRight = cellColor
                }
        }
        Cell {
            cellColor: "#9e02e1"
            //onClicked: mouseArea.pressedButtons == 1 ? currentColorLeft = cellColor : currentColorRight = cellColor
            onClicked:
                if(mouseArea.pressedButtons == 1 && !Qt.colorEqual(cellColor,currentColorRight)){
                    currentColorLeft = cellColor
                }
                else if (mouseArea.pressedButtons == 2 && !Qt.colorEqual(cellColor,currentColorLeft)){
                    currentColorRight = cellColor
                }
        }
        Cell {
            cellColor: "#ff9e00"
            //onClicked: mouseArea.pressedButtons == 1 ? currentColorLeft = cellColor : currentColorRight = cellColor
            onClicked:
                if(mouseArea.pressedButtons == 1 && !Qt.colorEqual(cellColor,currentColorRight)){
                    currentColorLeft = cellColor
                }
                else if (mouseArea.pressedButtons == 2 && !Qt.colorEqual(cellColor,currentColorLeft)){
                    currentColorRight = cellColor
                }
        }
        Cell {
            cellColor: "#ff8ee2"
           // onClicked: mouseArea.pressedButtons == 1 ? currentColorLeft = cellColor : currentColorRight = cellColor
            onClicked:
                if(mouseArea.pressedButtons == 1 && !Qt.colorEqual(cellColor,currentColorRight)){
                    currentColorLeft = cellColor
                }
                else if (mouseArea.pressedButtons == 2 && !Qt.colorEqual(cellColor,currentColorLeft)){
                    currentColorRight = cellColor
                }
        }
        Cell {
            cellColor: "#945d26"
           // onClicked: mouseArea.pressedButtons == 1 ? currentColorLeft = cellColor : currentColorRight = cellColor
            onClicked:
                if(mouseArea.pressedButtons == 1 && !Qt.colorEqual(cellColor,currentColorRight)){
                    currentColorLeft = cellColor
                }
                else if (mouseArea.pressedButtons == 2 && !Qt.colorEqual(cellColor,currentColorLeft)){
                    currentColorRight = cellColor
                }
        }

        ColorCell {
            //onClicked: console.log("More Color required")
        }

    }
}
