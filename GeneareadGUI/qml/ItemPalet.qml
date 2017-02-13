
import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2


Rectangle {
    id: page
    width: 130; height:33
    color: "#b0aaaa"
    radius: 1
    property alias eraserRectangle: eraserRectangle
    property alias rectangleRectangle: rectangleRectangle
    property alias paintRectangle: paintRectangle
    property alias selectRectangle: selectRectangle
    property string currentItem: "noTool"
    property bool paintMenu : false

    Grid {
        id: itemPicker
        width: 130
        height: 33
        anchors.fill: parent
        rows: 1
        columns: 4
        spacing: 3

        Rectangle {
            id: selectRectangle
            width: 33
            height: 33
            color: "#b0aaaa"
            ItemCell {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    selectRectangle.color = currentItem == "select" ? "#b0aaaa" : "#626262"
                    paintRectangle.color = "#b0aaaa"
                    rectangleRectangle.color = "#b0aaaa"
                    eraserRectangle.color = "#b0aaaa"
                    backTool.backAlgoPalet.backItems.selectEraser.color = "#b0aaaa"
                    paintMenu = false
                    currentItem = currentItem =="select" ? "noTool" : "select"

                }
                cellItem: "select.png"

            }
        }

        Rectangle {
            id: paintRectangle
            width: 33
            height: 33
            color: "#b0aaaa"
            ItemCell {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    selectRectangle.color = "#b0aaaa"
                    paintRectangle.color = currentItem == "brush" ? "#b0aaaa" : "#626262"
                    rectangleRectangle.color = "#b0aaaa"
                    eraserRectangle.color = "#b0aaaa"
                    backTool.backAlgoPalet.backItems.selectEraser.color = "#b0aaaa"
                    paintMenu = currentItem =="brush" ? false : true
                    currentItem = currentItem =="brush" ? "noTool" : "brush"

                }
                cellItem: "pinceau.png"

            }
        }

        Rectangle {
            id: rectangleRectangle
            width: 33
            height: 33
            color: "#b0aaaa"
            ItemCell {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    selectRectangle.color = "#b0aaaa"
                    paintRectangle.color = "#b0aaaa"
                    rectangleRectangle.color = currentItem =="rectangle" ? "#b0aaaa" : "#626262"
                    eraserRectangle.color = "#b0aaaa"
                    backTool.backAlgoPalet.backItems.selectEraser.color = "#b0aaaa"
                    paintMenu = false
                    currentItem = currentItem =="rectangle" ? "noTool" : "rectangle"
                }
                cellItem: "Editing-Rectangle-icon.png"

            }
        }

        Rectangle {
            id: eraserRectangle
            width: 33
            height: 33
            color: "#b0aaaa"
            ItemCell {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    selectRectangle.color = "#b0aaaa"
                    paintRectangle.color = "#b0aaaa"
                    rectangleRectangle.color = "#b0aaaa"
                    backTool.backAlgoPalet.backItems.selectEraser.color = "#b0aaaa"
                    eraserRectangle.color = currentItem =="eraser" ? "#b0aaaa" : "#626262"
                    paintMenu = currentItem =="eraser" ? false : true
                    currentItem = currentItem == "eraser" ? "noTool" : "eraser"
                }
                cellItem: "gomme.png"
            }
        }


    }
}

