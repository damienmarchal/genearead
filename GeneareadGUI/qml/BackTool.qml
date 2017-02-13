import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2

Rectangle {
    id: container
    width: 420
    height: 450
    color : "lightgray"
    property alias backAlgoPalet: backAlgoPalet
    property bool clickedTool: true
    property string imageSource : !clickedTool ?  "triangleHaut.png" :"triangleBas.png"
    property int boxSize :  !clickedTool ?  20 : 450
    property string currentAlgo : backAlgoPalet.currentAlgo
    /*property bool clickedTool: true
     property string imageSource : "triangleHaut.png"
     property int boxSize : 20*/

    Rectangle {
        id: item1
        width: 420
        height: 20
        color: "#b0aaaa"
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
                /*if(clickedTool){
                    imageSource = "triangleHaut.png"
                    boxSize = 20
                }
                else{
                    imageSource = "triangleBas.png"
                    boxSize = 420
                }*/
                clickedTool = !clickedTool
            }
        }
        Item {
            id: backgroundToolBar
            width: 420
            height: 430
            anchors.top: parent.top
            anchors.topMargin: 20
            visible: clickedTool

            BackAlgoPalet {
                id: backAlgoPalet
                x: 0
                y: 21
            }
        }
    }
}
