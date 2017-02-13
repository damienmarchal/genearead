import QtQuick 2.0

Rectangle {
    id: rectSelectAlgo1
    x: 0
    width: 110
    height: 160
    color: "#00000000"
    radius: 1
    z: 2
    border.width: 60
    border.color: "#00000000"

    Image {
        id: preview1
        width: 100
        height: 150
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        horizontalAlignment: Image.AlignHCenter
        verticalAlignment: Image.AlignVCenter
        source: "image://imageProvider/preview1"
        cache: false
        clip: true

        MouseArea {
            id: algo1Click
            anchors.fill: parent
            onClicked:{
                page.selectPreview(1);
            }
        }
    }
}
