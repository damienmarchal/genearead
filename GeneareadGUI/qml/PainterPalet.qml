import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2


Rectangle {
    id: page
    width: 100; height:90
    color: "#b0aaaa"
    radius: 1
    property int currentSize : 5

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
            text: currentSize
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
            color:  "#b0aaaa"
            ItemCell {
                id: itemCell
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    currentSize = 3
                    smallRectangle.color =  "#626262"
                    mediumRectangle.color = "#b0aaaa"
                    bigRectangle.color = "#b0aaaa"
                }
                cellItem: "point.png"
                image.scale: 0.3

            }
        }

        Rectangle {
            id: mediumRectangle
            width: 33
            height: 33
            color:  "#b0aaaa"

            ItemCell {

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    currentSize = 9
                    smallRectangle.color = "#b0aaaa"
                    mediumRectangle.color =  "#626262"
                    bigRectangle.color = "#b0aaaa"
                }
                cellItem: "point.png"
                image.scale: 0.5


            }
        }

        Rectangle {
            id: bigRectangle
            width: 33
            height: 33
            color:  "#b0aaaa"
            ItemCell {
                x: 0
                y: 0
                anchors.verticalCenterOffset: 0
                anchors.horizontalCenterOffset: 0
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    currentSize = 18
                    smallRectangle.color = "#b0aaaa"
                    mediumRectangle.color = "#b0aaaa"
                    bigRectangle.color =  "#626262"
                }
                cellItem: "point.png"
                image.scale: 0.7
            }
        }
    }
}
