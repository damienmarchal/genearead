import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2

Item {
    id: container
    width: 160
    height: 60
    property bool clickedTool: true

    Item {
        id: item1
        width: 160
        height: 20

        Text {
            id: title
            width: 120
            height: 20
            text: qsTr("Nettoyer le fond")
            anchors.left: parent.left
            anchors.leftMargin: 10
            font.pointSize: 10

            Image {
                id: fleche
                x: 126
                y: -4
                width: 20
                height: 29
                scale: 0.7
                fillMode: Image.PreserveAspectFit
                source: "triangleBas.png"
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
            id: backgroundToolBar
            visible: clickedTool
            Item {
                id: backTool
                width: 160
                height: 60

                ItemPalet {
                    id: itemPalet
                    x: 8
                    y: 20
                }
            }
        }
    }
}
