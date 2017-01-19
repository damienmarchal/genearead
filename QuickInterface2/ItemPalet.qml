
import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2


Rectangle {
    id: page
    width: 100; height:33
    color: "lightgray"
    radius: 1
    property string currentItem
    property bool paintMenu : false

    Grid {
        id: itemPicker
        width: 100
        height: 35
        anchors.fill: parent
        rows: 1
        columns: 3
        spacing: 3
        Rectangle {
            id: paintRectangle
            x: 0
            width: 33
            height: 33
            color:  "lightgray"

            ItemCell {
                id: itemCell
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    currentItem = cellItem
                    paintRectangle.color = "darkgray"
                    rectangleRectangle.color = "lightgray"
                    eraserRectangle.color = "lightgray"
                    paintMenu = true

                }
                cellItem: "pinceau.png"

            }
        }

        Rectangle {
            id: rectangleRectangle
            width: 33
            height: 33
            color:  "lightgray"

            ItemCell {

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    currentItem = cellItem
                    paintRectangle.color = "lightgray"
                    rectangleRectangle.color = "darkgray"
                    eraserRectangle.color = "lightgray"
                    paintMenu = false
                }
                cellItem: "Editing-Rectangle-icon.png"

            }
        }

        Rectangle {
            id: eraserRectangle
            width: 33
            height: 33
            color:  "lightgray"
            ItemCell {
                x: 0
                y: 0
                anchors.verticalCenterOffset: 0
                anchors.horizontalCenterOffset: 0
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    currentItem = cellItem
                    paintRectangle.color = "lightgray"
                    rectangleRectangle.color = "lightgray"
                    eraserRectangle.color = "darkgray"
                    paintMenu = true
                }
                cellItem: "gomme.png"
            }
        }

    }
}

