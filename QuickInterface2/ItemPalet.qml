
import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2


Rectangle {
    id: page
    width: 140; height:33
    color: "lightgray"
    radius: 1
    property string currentItem
    property bool paintMenu : false

    Grid {
        id: itemPicker
        width: 133
        height: 35
        anchors.fill: parent
        rows: 1
        columns: 4
        spacing: 3

        Rectangle {
            id: selectRectangle
            x: 0
            width: 33
            height: 33
            color:  "lightgray"

            ItemCell {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    selectRectangle.color = currentItem == "select" ? "lightgray" : "darkgray"
                    paintRectangle.color = "lightgray"
                    rectangleRectangle.color = "lightgray"
                    eraserRectangle.color = "lightgray"
                    paintMenu = false
                    currentItem = currentItem =="select" ? "" : "select"

                }
                cellItem: "select.png"

            }
        }
        Rectangle {
            id: paintRectangle
            x: 0
            width: 33
            height: 33
            color:  "lightgray"

            ItemCell {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    paintRectangle.color = currentItem == "pinceau" ? "lightgray" : "darkgray"
                    rectangleRectangle.color = "lightgray"
                    eraserRectangle.color = "lightgray"
                    selectRectangle.color = "lightgray"
                    paintMenu = currentItem =="pinceau" ? false : true
                    currentItem = currentItem =="pinceau" ? "" : "pinceau"

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
                    paintRectangle.color = "lightgray"
                    rectangleRectangle.color = currentItem =="rectangle" ? "lightgray" : "darkgray"
                    eraserRectangle.color = "lightgray"
                    selectRectangle.color = "lightgray"
                    paintMenu = false
                    currentItem = currentItem =="rectangle" ? "" : "rectangle"
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
                    paintRectangle.color = "lightgray"
                    rectangleRectangle.color = "lightgray"
                    selectRectangle.color = "lightgray"
                    eraserRectangle.color = currentItem =="gomme" ? "lightgray" : "darkgray"
                    paintMenu = currentItem =="gomme" ? false : true
                    currentItem = currentItem == "gomme" ? "" : "gomme"
                }
                cellItem: "gomme.png"
            }
        }


    }
}

