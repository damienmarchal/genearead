import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2

Item {
    id: container
    width: 160
    height: 20
    property alias clickedTool: fleche.source == "triangleBas.png"
    signal clicked(boolean clickedTool)

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
                x: 125
                y: 0
                width: 20
                height: 20
                fillMode: Image.PreserveAspectFit
                source: "triangleHaut.png"
            }

        }

        MouseArea {
            id:click
            anchors.fill: parent
            onClicked: {
                fleche.source == "triangleHaut.png" ? "triangleBas.png" : "triangleHaut.png"
            }
        }
    }
}
