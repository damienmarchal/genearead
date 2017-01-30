import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2

Item{
    id: container
    property real mouseX: mouseArea1.mouseX
    property real mouseY: mouseArea1.mouseY
    property color colorLeft : "red"
    property color colorRight : "blue"
    property int size : 5
    property string item
    property int heightImage : 300

    Image {
        id: image
        x: 0
        anchors.horizontalCenter: parent.horizontalCenter
        clip: false
        source: "Livret F.jpg"
        fillMode: Image.PreserveAspectFit
        sourceSize.height: heightImage

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            implicitWidth: image.implicitWidth
        }
        //fillMode: Image.PreserveAspectFit
    }

    Canvas {
        id: mycanvas
        height: 1
        z: 1
        anchors.fill: parent
        //implicitWidth: image.implicitWidth
        onPaint : {
            var ctx = getContext("2d");
            ctx.reset()
            if(mouseArea1.containsMouse && item == "pinceau"){
                ctx.fillStyle = Qt.rgba(colorLeft.r, colorLeft.g, colorLeft.b, 0.5)
                ctx.beginPath()
                ctx.arc(mouseX, mouseY, size, 0, Math.PI*2, true)
                ctx.closePath()
                ctx.fill()
            }
            else if (mouseArea1.containsMouse && item == "gomme"){
                ctx.strokeStyle = Qt.rgba(0, 0, 0, 0.5)
                ctx.beginPath()
                ctx.arc(mouseX, mouseY, size, 0, Math.PI*2, true)
                ctx.closePath()
                ctx.stroke()
            }
            else if (mouseArea1.containsMouse && item == "rectangle"){
                ctx.fillStyle = Qt.rgba(colorLeft.r, colorLeft.g, colorLeft.b, 0.5)
                ctx.fillRect(mouseX-20/2, mouseY-20/2,20,20)
            }
        }

        MouseArea {
            id: mouseArea1
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.fill: parent
            hoverEnabled : true
            focus: true
            onPositionChanged: {
                if(containsMouse){
                    mycanvas.requestPaint()
                }
            }
            onWheel: {
                if(item== "pinceau" || item == "gomme"){
                    if(wheel.angleDelta.y >0){
                        linesTool.painterPalet.currentSize++
                    }
                    else if((wheel.angleDelta.y<0 && size>=1)){
                        linesTool.painterPalet.currentSize--
                    }

                    mycanvas.requestPaint()
                }
            }
            onExited: mycanvas.requestPaint()

            Keys.onPressed: {
                if (event.key === Qt.Key_Control) {
                    if(item == "gomme"){
                        linesTool.itemPalet.currentItem = "pinceau"
                    }
                    else if (item == "pinceau"){
                        linesTool.itemPalet.currentItem = "gomme"
                    }
                    mycanvas.requestPaint()
                    event.accepted = true;
                }
                else if(event.key === Qt.Key_Alt){
                    var tmp = Qt.rgba(colorLeft.r, colorLeft.g, colorLeft.b,1)
                    linesTool.colorPalet.currentColorLeft = linesTool.colorPalet.currentColorRight
                    linesTool.colorPalet.currentColorRight = tmp
                    mycanvas.requestPaint()
                    event.accepted = true;
                }
            }
            Keys.onReleased: {
                if (event.key === Qt.Key_Control) {
                    if(item == "gomme"){
                        linesTool.itemPalet.currentItem = "pinceau"
                    }
                    else if (item == "pinceau"){
                        linesTool.itemPalet.currentItem = "gomme"
                    }
                    mycanvas.requestPaint()
                    event.accepted = true;
                }
                else if(event.key === Qt.Key_Alt){
                    var tmp = Qt.rgba(colorLeft.r, colorLeft.g, colorLeft.b,1)
                    linesTool.colorPalet.currentColorLeft = linesTool.colorPalet.currentColorRight
                    linesTool.colorPalet.currentColorRight = tmp
                    mycanvas.requestPaint()
                    event.accepted = true;
                }
            }

        }

    }
}
