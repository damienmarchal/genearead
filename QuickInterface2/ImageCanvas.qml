import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2


Image {
    id: image
    width: 213
    height: 336
    clip: false
    source: "Livret F.jpg"
    fillMode: Image.PreserveAspectFit
    property real mouseX: mouseArea1.mouseX
    property real mouseY: mouseArea1.mouseY
    property color colorLeft : "red"
    property color colorRight : "blue"
    property int size : 5
    property string item

    Canvas {
        id: mycanvas
        z: 1
        anchors.fill: parent
        onPaint : {
            var ctx = getContext("2d");
            ctx.reset()
            if(mouseArea1.containsMouse && item == "pinceau"){
                ctx.fillStyle = colorLeft;
                ctx.beginPath();
                ctx.arc(mouseX, mouseY, size, 0, Math.PI*2, true);
                ctx.closePath();
                ctx.fill();
            }
            else if (mouseArea1.containsMouse && item == "gomme"){
                ctx.fillStyle = colorRight;
                ctx.beginPath();
                ctx.arc(mouseX, mouseY, size, 0, Math.PI*2, true);
                ctx.closePath();
                ctx.fill();
            }
            else if (mouseArea1.containsMouse && item == "rectangle"){
                ctx.fillStyle = colorRight;
                ctx.fillRect(mouseX-size/2, mouseY-size/2,size,size);
            }
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
        onPositionChanged: {
            if(containsMouse){
                mycanvas.requestPaint()
            }
        }
        onExited: mycanvas.requestPaint()

    }
}

