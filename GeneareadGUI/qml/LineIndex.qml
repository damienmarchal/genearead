import QtQuick 2.0

Image {

    x: 50
    y: 0
    z: 10
    width: 100
    height: 100
    source: "image://imageProvider/lineIndex"
    fillMode: Image.PreserveAspectFit
    clip: false
    cache: false

    function refresh() {
        var oldSource = source;
        source = "";
        source = oldSource;
    }

    Component.onCompleted: refresh()

    Rectangle {
        x: 0
        y: 0
        z: 11
        color: "blue"
        width: 10
        height: 10
    }
}
