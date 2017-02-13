import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 900
    height: 600
    title: qsTr("Hello World")

    menuBar : MenuBar {
        Menu {
            title: qsTr("Project")
            MenuItem {
                text: qsTr("Open...")
                onTriggered: imageManager.open()
                //fileDialog.visible = true
            }
            MenuItem {
                text: qsTr("Fast open")
                onTriggered: imageManager.loadFile("C:/Users/corentin/Pictures/test.png");
            }
            MenuItem {
                text: qsTr("Close")
                onTriggered: imageManager.loadFile("C:/Users/corentin/Pictures/gfx/Antolach.PNG");
            }
        }

        Menu {
            title: qsTr("Edit")
            MenuItem { text: qsTr("Cut") }
            MenuItem { text: qsTr("Copy") }
            MenuItem { text: qsTr("Paste") }
            MenuSeparator {}
            MenuItem {
                text: qsTr("Color RED")
                onTriggered: pinceauParam.color = "red"
            }
            MenuItem {
                text: qsTr("Color GREEN")
                onTriggered: pinceauParam.color = "green"
            }
            MenuItem {
                text: qsTr("Color BLUE")
                onTriggered: pinceauParam.color = "blue"
            }
        }

        Menu {
            title: qsTr("Document")

            MenuItem {
                text: qsTr("Isolate text - ADAPTIVE")
                onTriggered: {
                    imageManager.applyText(adaptiveThreshold)
                }
            }

            MenuItem {
                text: qsTr("Isolate text - THRESHOLD")
                onTriggered: {
                    imageManager.applyText(threshold)
                }
            }

            MenuItem {
                text: qsTr("Isolate text - NIBLACK")
                onTriggered: {
                    imageManager.applyText(niblack)
                }
            }

            MenuItem {
                text: qsTr("Isolate text - SAUVOLA")
                onTriggered: {
                    imageManager.applyText(sauvola)
                }
            }

            MenuItem {
                text: qsTr("Reset")
                onTriggered: {
                    imageManager.resetDisplay()
                }
            }

            MenuSeparator {}

            MenuItem {
                text: qsTr("Isolate lines")
                shortcut: "Ctrl+Y"
            }

            MenuSeparator {}

            MenuItem {
                text: qsTr("Isolate all")
                shortcut: "Ctrl+U"
            }
        }

        Menu {

            title: qsTr("Layers")

            MenuItem {
                text: qsTr("Clear all")
                onTriggered: {
                    imageManager.resetLayers()
                }
            }
        }

        Menu {

            title: qsTr("Refine")

            MenuItem {
                text: qsTr("Erode")
                onTriggered: {
                    refineAlgo.name = "erode"
                    imageManager.applyRefine(refineAlgo)
                }
            }

            MenuItem {
                text: qsTr("Dilate")
                onTriggered: {
                    refineAlgo.name = "dilate"
                    imageManager.applyRefine(refineAlgo)
                }
            }

            MenuSeparator {}

            MenuItem {
                text: qsTr("Blur")
                onTriggered: {
                    refineAlgo.name = "blur"
                    imageManager.applyRefine(refineAlgo)
                }
            }

            MenuItem {
                text: qsTr("Denoise")
                onTriggered: {
                    refineAlgo.name = "denoise"
                    imageManager.applyRefine(refineAlgo)
                }
            }
        }
    }


    /*Slider {
        x: 10
        y: 20
        height: 80
        id: sliderV
        value: 0.5
        orientation: Qt.Vertical
        maximumValue: mainImage.height
        minimumValue: 0
        updateValueWhileDragging: true
    }

    Slider {
        x: 20
        y: 10
        width: 80
        id: sliderH
        value: 0.5
        orientation: Qt.Horizontal
        maximumValue: mainImage.width
        minimumValue: 0
        updateValueWhileDragging: true
    }*/

    Item {
        id: pinceauParam
        property color color: Qt.rgba(255, 0, 0, 255)
        property int radius: 25
    }

    Item {
        id : previews
        objectName: "previews"

        function refresh() {
            for(var i = 0; i < children.length; ++i) {
                refreshOne(i)
            }
        }

        function refreshOne(i) {
            if(i>-1 && i<children.length) {
                console.log("hi")
                var image = children[i]
                var oldSource = image.source;
                image.source = "";
                image.source = oldSource;
            }
        }

        Image {
            x: 600
            y: 10
            id: preview0
            source: "image://imageProvider/preview0"
            width: 80
            height: 120
            horizontalAlignment: Image.AlignHCenter
            verticalAlignment: Image.AlignVCenter
            cache: false
            clip: true
        }

        Image {
            x: 700
            y: 10
            id: preview1
            source: "image://imageProvider/preview1"
            width: 80
            height: 120
            horizontalAlignment: Image.AlignHCenter
            verticalAlignment: Image.AlignVCenter
            cache: false
            clip: true
        }

        Image {
            x: 800
            y: 10
            id: preview2
            source: "image://imageProvider/preview2"
            width: 80
            height: 120
            horizontalAlignment: Image.AlignHCenter
            verticalAlignment: Image.AlignVCenter
            cache: false
            clip: true
        }

    }


    Item {
        id: textAlgo
        objectName: "textAlgorithmManager"
        property string algorithmName: "niblack"

        Item {
            id: niblack
            objectName: "niblack"

        }

        Item {
            id: sauvola
            objectName: "sauvola"
        }

        Item {
            id: adaptiveThreshold
            objectName: "adaptiveThreshold"
        }

        Item {
            id: threshold
            objectName: "threshold"
        }

        //property string name: "sauvola"
    }

    Item {
        id: refineAlgo
        property string name: "denoise"
    }

    Item {
        id: lineWidgets
    }

    /*MainForm {
        anchors.fill: parent
        mouseArea.onClicked: {
            console.log(qsTr('Clicked on background. Text: "' + textEdit.text + '"'))
        }
    }*/



    Image {
        x: 10
        y: 10
        id: mainImage
        source: "image://imageProvider/main"
        //width: 200
        //height: 300
        fillMode: Image.PreserveAspectCrop
        horizontalAlignment: Image.AlignLeft
        cache: false
        clip: true
        function refresh() {
            var oldSource = source;
            source = "";
            source = oldSource;
        }

        MouseArea{
            id: buttonMouseArea

            anchors.fill: parent //anchor all sides of the mouse area to the rectangle's anchors
            //onClicked handles valid mouse button clicks
            onClicked:
                imageManager.mouseDown(
                    150,
                    200,
                    mouseX,
                    mouseY,
                    "pinceau",
                    pinceauParam.color,
                    pinceauParam)

        }
    }

    Slider {
        id : previewX;
        x: 520
        y: 420
        orientation: Qt.Horizontal
        width: 100
        minimumValue: 0.0
        maximumValue: 1.0
        value: 0.0

        onValueChanged:
            imageManager.movePreviews(
                value,
                previewY.value
                );

    }

    Slider {
        id : previewY;
        x: 500
        y: 440
        orientation: Qt.Vertical
        height: 100
        minimumValue: 0.0
        maximumValue: 1.0
        value: 0.0

        onValueChanged:
            imageManager.movePreviews(
                previewX.value,
                value
                );

    }

    Rectangle {
        x: 500
        y: 300
        width: 100
        height: 100
        color: "red"

        MouseArea{
            id: isolate

            anchors.fill: parent //anchor all sides of the mouse area to the rectangle's anchors
            //onClicked handles valid mouse button clicks
            onClicked:
                imageManager.isolateLines();

        }

    }

    Rectangle {
        x: 700
        y: 300
        width: 100
        height: 100
        color: "blue"
        MouseArea{
            id: leftArrow
            anchors.fill: parent
            onClicked: imageManager.shiftPreviewsLeft();
        }
    }

    Rectangle {
        x: 800
        y: 300
        width: 100
        height: 100
        color: "green"
        MouseArea{
            id: rightArrow
            anchors.fill: parent
            onClicked: imageManager.shiftPreviewsRight();
        }
    }

    Connections {
        target: imageManager
        onImageUpdate: {
            mainImage.refresh();
        }
        onPreviewUpdate: {
            previews.refreshOne(imageManager.getSelectedPreviewID())
        }
        onPreviewsUpdate: {
            previews.refresh();
        }
    }

    /*Rectangle {
        id: imageContainer
        visible: true
        objectName: "image"
        width: 100
        height: 100
        x: 2
        y: 2
        color: "blue"
    }*/

    /*FileDialog {
        id: fileDialog
        visible: false
        modality: Qt.WindowModal
        title: qsTr("Choose a folder")
        selectExisting: true
        selectMultiple: true
        selectFolder: false
        nameFilters: [ "Image files (*.png *.jpg)", "All files (*)" ]
        selectedNameFilter: "All files (*)"
        sidebarVisible: true
        onAccepted: {
            console.log("Accepted: " + fileUrls)
            for (var i = 0; i < fileUrls.length; ++i) {
                var image2 = Qt.createComponent("GeneaImage.qml")
                if (image2.status === Component.Ready) {
                    //Qt.openUrlExternally(fileUrls[i])
                    images.add(image2, fileUrls[i]);
                } else {
                    console.log("Not ready ! " + fileUrls)
                }
            }
        }
        onRejected: { console.log("Rejected") }
    }*/
}
