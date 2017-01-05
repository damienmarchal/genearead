import QtQuick 2.5
import QtQuick.Controls 1.4

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MainForm {
        anchors.fill: parent
        mouseArea.onClicked: {
            console.log(qsTr('Clicked on background. Text: "' + textEdit.text + '"'))
        }
    }

    Rectangle {
        id: image
        objectName: "image"
        width: 100
        height: 100
        x: 2
        y: 2
        color: "blue"
    }

    menuBar : MenuBar {
        Menu {
            title: "Project"
            MenuItem { text: "Open..." }
            MenuItem { text: "Close" }
        }

        Menu {
            title: "Edit"
            MenuItem { text: "Cut" }
            MenuItem { text: "Copy" }
            MenuItem { text: "Paste" }
        }

        Menu {
            title: "Document"

            MenuItem {
                text: "Isolate text"
                shortcut: "Ctrl+T"
                onTriggered: algor.apply(image, 0)
            }

            MenuItem {
                text: "Isolate lines"
                shortcut: "Ctrl+Y"
                onTriggered: algor.apply(image, 1)
            }

            MenuSeparator {}

            MenuItem {
                text: "Isolate all"
                shortcut: "Ctrl+U"
                onTriggered: algor.apply(image, 2)
            }
        }
    }
}
