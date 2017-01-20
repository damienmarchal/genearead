import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
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
                text: qsTr("Close")
                onTriggered: imageManager.loadFile("C:/Users/corentin/Pictures/gfx/Antolach.PNG");
            }
        }

        Menu {
            title: qsTr("Edit")
            MenuItem { text: qsTr("Cut") }
            MenuItem { text: qsTr("Copy") }
            MenuItem { text: qsTr("Paste") }
        }

        Menu {
            title: qsTr("Document")

            MenuItem {
                text: qsTr("Isolate text")
                shortcut: "Ctrl+T"
                onTriggered: imageManager.apply("Text")
            }

            MenuItem {
                text: qsTr("Isolate lines")
                shortcut: "Ctrl+Y"
                onTriggered: imageManager.apply("Line")
            }

            MenuSeparator {}

            MenuItem {
                text: qsTr("Isolate all")
                shortcut: "Ctrl+U"
                onTriggered: imageManager.apply("All")
            }
        }
    }

    /*MainForm {
        anchors.fill: parent
        mouseArea.onClicked: {
            console.log(qsTr('Clicked on background. Text: "' + textEdit.text + '"'))
        }
    }*/

    Image {
        x: 200
        y: 100
        id: mainImage
        source: "image://imageProvider/main"
        //width: 200
        //height: 300
        fillMode: Image.PreserveAspectCrop
        horizontalAlignment: Image.AlignLeft
        cache: false
        clip: true
        function reload() {
            var oldSource = source;
            source = "";
            source = oldSource;
        }
    }

    Connections {
        target: imageManager
        onImageUpdate: {
            mainImage.reload();
        }
    }

    Rectangle {
        id: imageContainer
        visible: true
        objectName: "image"
        width: 100
        height: 100
        x: 2
        y: 2
        color: "blue"
    }

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
