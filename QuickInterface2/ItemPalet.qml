import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2


Rectangle {
    id: page
    width: 60; height:30
    color: "lightgray"
    radius: 2
    property string currentItem

    Grid {
        id: itemPicker
        x: 0
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.horizontalCenter: parent.horizontalCenter
        rows: 1
        columns: 2
        spacing: 3

        ItemCell {
            onClicked: currentItem = cellItem
            cellItem: "pinceau.png"
            //cellItem: "Livret F.jpg"

        }
        ItemCell {
            onClicked: currentItem = cellItem
            cellItem: "Editing-Rectangle-icon.png"
            //cellItem: "Livret F.jpg"
        }
    }
}
