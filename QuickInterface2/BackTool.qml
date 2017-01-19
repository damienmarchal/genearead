import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2

Item {
    id: container
    width: 160
    height: 60
    property bool clickedTool: true
    property string imageSource : "triangleBas.png"
    property int boxSize : 60
    /*property bool clickedTool: true
     property string imageSource : "triangleHaut.png"
     property int boxSize : 20*/

    Item {
        id: item1
        width: 160
        height: boxSize

        Text {
            id: title
            width: 120
            height: 20
            text: qsTr("Nettoyer le fond")
            rightPadding: -2
            bottomPadding: -3
            font.family: "Arial"
            font.capitalization: Font.MixedCase
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
                source: imageSource
            }

        }

        MouseArea {
            id:click
            anchors.fill: parent
            onClicked: {
                //fleche.source == "triangleHaut.png" ? "triangleBas.png" : "triangleHaut.png"
                if(clickedTool){
                    imageSource = "triangleHaut.png"
                    boxSize = 20
                }
                else{
                    imageSource = "triangleBas.png"
                    boxSize = 60
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
