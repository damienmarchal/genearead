import QtQuick 2.0

Item {
    property real valueX: 0.5
    property real valueY: 0.5
    width: 200
    height: 200

    MouseArea {
        z:1
        width: parent.width - 20
        height: parent.height - 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        onPressed: update()
        onPositionChanged: update()
        Rectangle {
            anchors.fill: parent
            color: "#FFFFFF"
        }

        function update() {
            valueX =   Math.min(Math.max(0, mouseX/width), 1)
            valueY = 1-Math.min(Math.max(0, mouseY/height), 1)
            parent.children[2].requestPaint()
            imageManager.applyPreview(imageManager.getSelectedAlgorithmID())
        }

        function realX(normalX) {
            return x + normalX* width
        }

        function realY(normalY) {
            return y + normalY * height
        }
    }
    Image {
        z: 2
        anchors.fill: parent
        fillMode: Image.Stretch
        source: "axes.png"
    }
    Canvas {
        z: 3
        anchors.fill: parent
        onPaint : {
            var ctx = getContext("2d");
            ctx.reset()
            ctx.fillStyle = Qt.rgba(0, 0, 255, 1)
            ctx.beginPath()
            ctx.arc(
                        parent.children[0].realX(valueX),
                        parent.children[0].realY(1-valueY),
                        4, 0, Math.PI*2, true)
            ctx.closePath()
            ctx.fill()
        }
    }
}
