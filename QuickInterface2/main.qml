import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2


ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("&Save")
                onTriggered: console.log("Save action triggered");
            }
            MenuItem {
                text: qsTr("&Close Image")
                onTriggered: console.log("Close image action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    MainForm {
        anchors.fill: parent

        /*Text {
            id: colorText
            text: qsTr("Surlignez les lignes ! ")
            style: Text.Raised
            font.capitalization: Font.AllUppercase
            font.family: "Arial"
            fontSizeMode: Text.HorizontalFit
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 25
            color: colorPalet.currentColor

        }*/
    }

    MessageDialog {
        id: messageDialog
        title: qsTr("May I have your attention, please?")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }
}
