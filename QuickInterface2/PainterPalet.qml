import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2


Rectangle {
    id: page
    width: 100; height:90
    color: "lightgray"
    radius: 1
    property alias paintValue: paintValue
    property int currentSize : Number.fromLocaleString(paintValue.text)

    Grid {
        id: paintNumeric
        width: 90
        height: 50
        anchors.left: parent.left
        anchors.leftMargin: 10
        rows: 2
        columns: 1
        spacing: 3

        Text {
            id: labelPainter
            text: qsTr("Size")
            font.pixelSize: 18
        }
        TextField {
            id: paintValue
            width: 80
            text: "5"
            placeholderText: qsTr("")
        }
    }
    Grid {
        id: paintPicker
        x: 0
        y: 56
        width: 100
        height: 40
        rows: 1
        columns: 3
        spacing: 0

        Rectangle {
            id: smallRectangle
            x: 0
            width: 33
            height: 33
            color:  "lightgray"

            ItemCell {
                id: itemCell
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    paintValue.text = "3"
                    smallRectangle.color = "darkgray"
                    mediumRectangle.color = "lightgray"
                    bigRectangle.color = "lightgray"
                }
                cellItem: "point.png"
                image.scale: 0.3

            }
        }

        Rectangle {
            id: mediumRectangle
            width: 33
            height: 33
            color:  "lightgray"

            ItemCell {

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    paintValue.text = "9"
                    smallRectangle.color = "lightgray"
                    mediumRectangle.color = "darkgray"
                    bigRectangle.color = "lightgray"
                }
                cellItem: "point.png"
                image.scale: 0.5


            }
        }

        Rectangle {
            id: bigRectangle
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
                    paintValue.text = "18"
                    smallRectangle.color = "lightgray"
                    mediumRectangle.color = "lightgray"
                    bigRectangle.color = "darkgray"
                }
                cellItem: "point.png"
                image.scale: 0.7
            }
        }
    }
}
