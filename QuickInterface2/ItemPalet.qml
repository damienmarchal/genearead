import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2


Rectangle {
    id: page
    width: 100; height:30
    color: "lightgray"
    radius: 1
    property string currentItem

    Grid {
        id: itemPicker
        x: 0
        width: 78
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.horizontalCenter: parent.horizontalCenter
        rows: 1
        columns: 3
        spacing: 3
        Rectangle {
            id: paintRectangle
            x: 0
            width: 25
            height: 25
            color:  "lightgray"

            ItemCell {
                x: 0
                y: 0
                onClicked: {
                    currentItem = cellItem
                    paintRectangle.color = "darkgray"
                    rectangleRectangle.color = "lightgray"
                    eraserRectangle.color = "lightgray"

                }
                cellItem: "pinceau.png"
                //cellItem: "Livret F.jpg"

            }
        }

        Rectangle {
            id: rectangleRectangle
            x: 0
            width: 25
            height: 25
            color:  "lightgray"

            ItemCell {
                x: 0
                y: 0
                onClicked: {
                    currentItem = cellItem
                    paintRectangle.color = "lightgray"
                    rectangleRectangle.color = "darkgray"
                    eraserRectangle.color = "lightgray"
                }
                cellItem: "Editing-Rectangle-icon.png"
                //cellItem: "Livret F.jpg"
            }
        }

        Rectangle {
            id: eraserRectangle
            x: 0
            width: 25
            height: 25
            color:  "lightgray"

            ItemCell {
                x: -2
                y: 0
                onClicked: {
                    currentItem = cellItem
                    paintRectangle.color = "lightgray"
                    rectangleRectangle.color = "lightgray"
                    eraserRectangle.color = "darkgray"
                }
                cellItem: "gomme.png"
                //cellItem: "Livret F.jpg"
            }
        }

    }
}
