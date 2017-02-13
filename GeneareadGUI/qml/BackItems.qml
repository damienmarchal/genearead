import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2


Rectangle {
    id: page
    width: 33
    height: 33
    color: "lightgray"
    radius: 1
    property alias itemPicker: itemPicker
    property alias selectEraser: selectEraser

    property string currentItem: linesTool.itemPalet.currentItem
    property bool paintMenu : false


    Column {
        spacing: 10

        Grid {
            id: itemPicker
            width: 33
            height: 33
            anchors.fill: parent
            rows: 1
            columns: 1
            spacing: 3

            Rectangle {
                id: selectEraser
                width: 33
                height: 33
                color:  "#b0aaaa"

                ItemCell {
                    id: itemCell
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {
                        if(imageManager.getSelectedAlgorithmID()) {
                            linesTool.itemPalet.selectRectangle.color = "#b0aaaa"
                            linesTool.itemPalet.paintRectangle.color = "#b0aaaa"
                            linesTool.itemPalet.rectangleRectangle.color = "#b0aaaa"
                            linesTool.itemPalet.eraserRectangle.color = "#b0aaaa"
                            selectEraser.color = currentItem =="whiteOut" ? "#b0aaaa" : "#626262"
                            linesTool.itemPalet.paintMenu = false
                            linesTool.itemPalet.currentItem = linesTool.itemPalet.currentItem =="whiteOut" ? "noTool" : "whiteOut"
                            imageManager.toggleHiddenPixels()
                        }
                    }
                    cellItem: "whiteOut.png"

                }
            }
        }
    }
}
