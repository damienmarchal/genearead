import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2

Item{
    id: container
    property real mouseX: mouseArea1.mouseX
    property real mouseY: mouseArea1.mouseY
    property color colorLeft
    property color colorRight
    property color colorOther : "#00000000"
    property int size : 5
    property string item
    property int heightImage : 300

   /* Rectangle {
        x:500
        y:700
        width:100
        height:100
        color:"red"
        z:42
        MouseArea {
            anchors.fill: parent
            onClicked: imageManager.showIsolatedLines()
        }
    }
    Rectangle {
        x:600
        y:700
        width:100
        height:100
        color:"green"
        z:42
        MouseArea {
            anchors.fill: parent
            onClicked: imageManager.showSelectionLayers()
        }
    }*/

    Connections {
        target: imageManager
        onImageUpdate: {
            image.refresh();
        }
        onImageSizeUpdate: {
            image.refreshZoom();
        }
        onImageMoved: {
            image.x = imageManager.getMainX()
            image.y = imageManager.getMainY()
            console.log("mv", image.x, image.y)
        }
    }

    Image {
        id: image
        objectName: "mainImage"
        z: 2
        //anchors.horizontalCenter: parent.horizontalCenter
        //anchors.verticalCenter: parent.verticalCenter
        source: "image://imageProvider/main"
        fillMode: Image.PreserveAspectFit
        clip: false
        cache: false

        function refreshZoom() {
            width = imageManager.getMainRenderWidth() * imageManager.getImageZoom();
            height = imageManager.getMainRenderHeight() * imageManager.getImageZoom();
        }

        function refresh() {
            var oldSource = source;
            source = "";
            source = oldSource;
        }
    }

    Canvas {
        id: mycanvas
        objectName: "mainCanvas"
        height: 1
        z: 2
        anchors.fill: parent
        onPaint : {
            var ctx = getContext("2d");
            ctx.reset()
            if(mouseArea1.containsMouse) {
                var x = mouseX
                var y = mouseY
                var alpha = imageManager.getLayerAlpha()
                //var colorRef = mouse.button === Qt.RightButton ? colorRight : colorLeft
                var colorRef = colorLeft
                var color = Qt.rgba(colorRef.r, colorRef.g, colorRef.b, alpha)
                var eraser = Qt.rgba(0, 0, 0, alpha)
                var realSize = size * imageManager.getImageZoom()
                if(item == "brush" || item == "whiteOut") {
                    ctx.fillStyle = item == "brush" ? color : Qt.rgba(0xDF, 0xDF, 0xDF, alpha)
                    ctx.beginPath()
                    ctx.arc(x, y, realSize, 0, Math.PI*2, true)
                    ctx.closePath()
                    ctx.fill()
                } else if (item == "eraser") {
                    ctx.strokeStyle = eraser
                    ctx.beginPath()
                    ctx.arc(x, y, realSize, 0, Math.PI*2, true)
                    ctx.closePath()
                    ctx.stroke()
                } else if (item == "rectangle") {
                    ctx.fillStyle = color
                    var xs = mouseArea1.startCanvasX
                    var xe = mouseArea1.previousCanvasX
                    var ys = mouseArea1.startCanvasY
                    var ye = mouseArea1.previousCanvasY
                    var a;
                    if(xe<xs) {
                        a = xs
                        xs = xe
                        xe = a
                    }
                    if(ye<ys) {
                        a = ys
                        ys = ye
                        ye = a
                    }
                    var w = Math.abs(xe-xs)
                    var h = Math.abs(ye-ys)
                    console.log(xs, ys, w, h)
                    ctx.fillRect(xs, ys, w, h)
                }
            }
        }
    }

    MouseArea {
        id: mouseArea1
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        z: 3
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        hoverEnabled : true
        focus: true

        property real previousX: -1
        property real previousY: -1
        property real startX: -1
        property real startY: -1

        property real previousCanvasX: -1
        property real previousCanvasY: -1
        property real startCanvasX: -1
        property real startCanvasY: -1

        onPressed: {
            if(mouse.button === Qt.RightButton) {
                colorOther = Qt.rgba(colorLeft.r, colorLeft.g, colorLeft.b, colorLeft.a)
                linesTool.currentColorLeft = Qt.rgba(colorRight.r, colorRight.g, colorRight.b, colorRight.a)
                console.log(colorLeft, colorRight, colorOther)
            }

            startCanvasX = mouseX
            startCanvasY = mouseY
            previousCanvasX = startCanvasX
            previousCanvasY = startCanvasY
            var z = imageManager.getImageZoom()
            startX = (startCanvasX - image.x) / z
            startY = (startCanvasY - image.y) / z
            previousX = startX
            previousY = startY
            imageManager.toolPressed(startX, startY, item, mouse.button === Qt.RightButton)
            mycanvas.requestPaint()
        }

        onPositionChanged: {

            if(previousX>=0 && previousY>=0) {
                var z = imageManager.getImageZoom()
                var x = (mouseX - image.x) / z
                var y = (mouseY - image.y) / z
                imageManager.toolDragged(previousX, previousY, x, y, item, pressedButtons & Qt.RightButton)
                previousCanvasX = mouseX
                previousCanvasY = mouseY
                previousX = (mouseX - image.x) / z
                previousY = (mouseY - image.y) / z
            }
            mycanvas.requestPaint()

        }

        onReleased: {

            var z = imageManager.getImageZoom()
            var x = (mouseX - image.x) / z
            var y = (mouseY - image.y) / z
            imageManager.toolReleased(startX, startY, x, y, item, mouse.button === Qt.RightButton)
            startCanvasX = -1
            startCanvasY = -1
            previousCanvasX = -1
            previousCanvasY = -1
            startX = -1
            startY = -1
            previousX = -1
            previousY = -1
            mycanvas.requestPaint()

            if(mouse.button === Qt.RightButton) {
                linesTool.currentColorLeft = Qt.rgba(colorOther.r, colorOther.g, colorOther.b, colorOther.a)
                colorOther = "#00000000"
                console.log(colorLeft, colorRight, colorOther)
            }
        }

        onWheel: {
            if(item== "brush" || item == "eraser" || item=="whiteOut"){
                if(wheel.angleDelta.y >0){
                    linesTool.painterPalet.currentSize++
                } else if((wheel.angleDelta.y<0 && size>=1)){
                    linesTool.painterPalet.currentSize--
                }
                mycanvas.requestPaint()
            }
            else if (item=="select"){
                if(wheel.angleDelta.y >0){
                   imageManager.zoomIn()
                } else if((wheel.angleDelta.y<0)){
                    imageManager.zoomOut()
                }
            }
        }
        onExited: mycanvas.requestPaint()

        Keys.onPressed: {
            if (event.key === Qt.Key_Control) {
                if(item == "eraser") {
                    linesTool.itemPalet.currentItem = "brush"
                }
                else if (item == "brush") {
                    linesTool.itemPalet.currentItem = "eraser"
                }
                mycanvas.requestPaint()
                event.accepted = true;
            } else if(event.key === Qt.Key_Alt) {
                var tmp = Qt.rgba(colorLeft.r, colorLeft.g, colorLeft.b,1)
                linesTool.currentColorLeft = linesTool.currentColorRight
                linesTool.currentColorRight = tmp
                mycanvas.requestPaint()
                event.accepted = true;
            } else if(event.key === Qt.Key_A) {
                imageManager.zoomIn()
                mycanvas.requestPaint()
            } else if(event.key === Qt.Key_Z) {
                imageManager.zoomOut()
                mycanvas.requestPaint()
            }
        }
        Keys.onReleased: {
            if (event.key === Qt.Key_Control) {
                if(item == "eraser"){
                    linesTool.itemPalet.currentItem = "brush"
                }
                else if (item == "brush"){
                    linesTool.itemPalet.currentItem = "eraser"
                }
                mycanvas.requestPaint()
                event.accepted = true;
            } else if(event.key === Qt.Key_Alt) {
                var tmp = Qt.rgba(colorLeft.r, colorLeft.g, colorLeft.b,1)
                linesTool.currentColorLeft = linesTool.currentColorRight
                linesTool.currentColorRight = tmp
                mycanvas.requestPaint()
                event.accepted = true;
            }
        }
    }

    Item {
        id: properties

        Item {
            id: noParameters
            objectName: "noToolParameters"
            property color color: colorLeft
        }

        Item {
            id: selectParameters
            objectName: "selectParameters"
            property color color: colorLeft
        }

        Item {
            id: brushParameters
            objectName: "brushParameters"
            property color color: colorLeft
            property int radius: size
        }

        Item {
            id: rectangleParameters
            objectName: "rectangleParameters"
            property color color: colorLeft
        }

        Item {
            id: eraserParameters
            objectName: "eraserParameters"
            property color color: colorLeft
            property int radius: size
        }

        Item {
            id: whiteOutParameters
            objectName: "whiteOutParameters"
            property color color: colorLeft
            property int radius: size
        }

        Item {
            id: whiteInParameters
            objectName: "whiteInParameters"
            property color color: colorLeft
            property int radius: size
        }

    }
}

