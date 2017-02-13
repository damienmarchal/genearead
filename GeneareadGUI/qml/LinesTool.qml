import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2


Rectangle {
    id: container
    property int boxSize : 20
    width: 420
    height : boxSize
    color: "lightgray"
    border.color: "#00000000"
    border.width: 10
    property alias itemPalet: itemPalet
    property alias painterPalet: painterPalet
    property bool clickedTool: false
    property color currentColorLeft: "red"
    property color currentColorRight : "blue"
    property string currentItem :  itemPalet.currentItem
    property int currentSize :  painterPalet.currentSize
    property string imageSource : "triangleHaut.png"
    property bool dispo : false


    Connections {
        target: imageManager
        onPreviewSelection: {
            dispo = imageManager.getSelectedAlgorithmID()
            if(!dispo)
                click.close()
        }
    }

    Rectangle {
        id: item1
        width: 420
        height: 20
        color: dispo ? "#b0aaaa" : "#960000"
        border.color: "#00000000"
        border.width: 2
        enabled: dispo

        Text {
            id: title
            width: 120
            height: 20
            text: qsTr("Sélectionner les lignes")
            font.pointSize: 10
            //enabled: false
            styleColor: "#000000"
            font.family: "Tahoma"
            anchors.left: parent.left
            anchors.leftMargin: 10

            Image {
                id: fleche
                x: 166
                y: 0
                width: 20
                height: 20
                scale: 0.7
                fillMode: Image.PreserveAspectFit
                source: imageSource
            }

        }

        MouseArea {
            id:click
            anchors.fill: parent

            function close() {
                clickedTool = 0
                imageSource = "triangleHaut.png"
                boxSize = 20
            }

            function open() {
                clickedTool = 1
                imageSource = "triangleBas.png"
                boxSize = 350
            }

            function toggle() {
                if(clickedTool)
                    close()
                else
                    open()
            }

            onClicked: toggle()
        }

        Rectangle {
            id: linesTool
            x: 0
            width: 420
            height: 330
            visible: clickedTool
            color: "lightgray"
            anchors.top: parent.top
            anchors.topMargin: 20

//            ColorPalette {
//                id: colorPalet
//                x: -20
//                y: 25
//                width: 100
//                height: 100
//                anchors.horizontalCenterOffset: 0
//                anchors.horizontalCenter: parent.horizontalCenter
//                visible: false
//            }

            ItemPalet {
                id: itemPalet
                x: 0
                y: 23
                height: 33
                anchors.horizontalCenterOffset: 0
                anchors.horizontalCenter: parent.horizontalCenter
            }

            PainterPalet {
                id: painterPalet
                y: 62
                width: 100
                height: 95
                anchors.horizontalCenterOffset: 0
                anchors.horizontalCenter: parent.horizontalCenter
                visible: itemPalet.paintMenu
            }

            Text {
                id: returnText
                x: 259
                y: 165
                width: 101
                height: 20
                text: qsTr("Couleurs actuelles")
                anchors.right: parent.right
                anchors.rightMargin: 61
                font.pointSize: 7
                renderType: Text.NativeRendering
            }

            ReturnColor {
                id: returnColor
                x: 279
                y: 191
                width: 60
                height: 30
                anchors.right: parent.right
                anchors.rightMargin: 81
                currentColorLeft: container.currentColorLeft
                currentColorRight: container.currentColorRight
            }

            Button {
                id: separation
                x: 48
                y: 270
                text: qsTr("Séparer la sélection")
                onClicked: {
                    imageManager.showIsolatedLines()
                    returnSelection.visible = true
                    separation.visible = false
                }
            }

            Button {
                id: returnSelection
                x: 48
                y: 270
                text: qsTr("Corriger la sélection")
                visible : false
                onClicked: {
                    imageManager.showSelectionLayers()
                     returnSelection.visible = false
                     separation.visible = true
                }
            }

            Button {
                id: colorSwitch
                x: 253
                y: 227
                text: qsTr("Echanger les couleurs")
                onClicked: {
                    var tmp = Qt.rgba(currentColorLeft.r, currentColorLeft.g, currentColorLeft.b,1)
                    currentColorLeft = currentColorRight
                    currentColorRight = tmp
                }
            }

        }
    }
}
