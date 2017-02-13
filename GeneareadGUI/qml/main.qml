import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2


ApplicationWindow {
    visible: true
    width: 1200
    height: 900
    title: qsTr("GeneaRead")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: project.open();
            }
            MenuItem {
                text: qsTr("&Save")
                onTriggered: project.saveAs();
            }
            MenuItem {
                text: qsTr("&Close Image")
                onTriggered: project.close();
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    MainForm {
        anchors.fill: parent
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
