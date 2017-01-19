import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2

Item {
    id: container
    width: 200
    height: 350
    property bool clickedTool: false
    property color currentColorLeft: colorPalet.currentColorLeft
    property color currentColorRight :  colorPalet.currentColorRight
    property string currentItem :  itemPalet.currentItem
    property int currentSize :  painterPalet.currentSize


    Item {
        id: item1
        width: 200
        height: 20

        Text {
            id: title
            width: 120
            height: 20
            text: qsTr("Sélectionner les lignes")
            anchors.left: parent.left
            anchors.leftMargin: 10
            font.pointSize: 10

            Image {
                id: fleche
                x: 166
                y: 0
                width: 20
                height: 20
                scale: 0.7
                fillMode: Image.PreserveAspectFit
                source: "triangleHaut.png"
            }

        }

        MouseArea {
            id:click
            anchors.fill: parent
            onClicked: {
                //fleche.source == "triangleHaut.png" ? "triangleBas.png" : "triangleHaut.png"
                if(clickedTool){
                    fleche.source = "triangleHaut.png"
                }
                else{
                    fleche.source = "triangleBas.png"
                }
                clickedTool = !clickedTool
            }
        }

        Item {
            id: linesTool
            visible: clickedTool
            anchors.horizontalCenter: parent.horizontalCenter
            ColorPalette {
                id: colorPalet
                x: -20
                y: 25
                width: 100
                height: 100
                anchors.horizontalCenterOffset: 0
                anchors.horizontalCenter: parent.horizontalCenter
            }

            ItemPalet {
                id: itemPalet
                y: 138
                height: 33
                anchors.horizontalCenterOffset: 0
                anchors.horizontalCenter: parent.horizontalCenter
            }

            PainterPalet {
                id: painterPalet
                y: 177
                width: 100
                height: 95
                anchors.horizontalCenterOffset: 0
                anchors.horizontalCenter: parent.horizontalCenter
                visible: itemPalet.paintMenu
            }

            Text {
                id: returnText
                x: -2
                y: 278
                width: 101
                height: 20
                text: qsTr("Couleurs actuelles")
                font.pointSize: 7
                renderType: Text.NativeRendering
            }

            ReturnColor {
                id: returnColor
                x: 20
                y: 304
                width: 60
                height: 30
                currentColorLeft: colorPalet.currentColorLeft
                currentColorRight: colorPalet.currentColorRight
            }

        }
    }
}
