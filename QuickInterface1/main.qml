import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 330
    height:0330
    title: qsTr("Transitions")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    MainForm {
        anchors.fill: parent
        id: page
        //button1.onClicked: messageDialog.show(qsTr("Button 1 pressed"))
        //button2.onClicked: messageDialog.show(qsTr("Button 2 pressed"))
        mouseArea1 {
            onClicked: stateGroup.state = ''
        }
        mouseArea2 {
            onClicked: stateGroup.state = 'State1'
            //onClicked: messageDialog.show(qsTr("Button 1 pressed"))
        }
        mouseArea3 {
            onClicked: stateGroup.state = 'State2'
            //onClicked: messageDialog.show(qsTr("Button 2 pressed"))
        }
    }
    StateGroup {
        id: stateGroup
        states: [
            State {
                name: "State1"

                PropertyChanges {
                    target: page.icon
                    x: page.middleRightRect.x
                    y: page.middleRightRect.y
                }
            },
            State {
                name: "State2"

                PropertyChanges {
                    target: page.icon
                    x: page.bottomLeftRect.x
                    y: page.bottomLeftRect.y
                }
            }
        ]
        transitions: [
            Transition {
                from: "*"; to: "State1"
                NumberAnimation {
                    easing.amplitude: 2
                    easing.type: Easing.OutBounce
                    properties: "x,y";
                    duration: 1000
                }
            },
            Transition {
                from: "*"; to: "State2"
                NumberAnimation {
                    easing.period: 0.25
                    easing.amplitude: 1
                    properties: "x,y";
                    easing.type: Easing.InElastic
                    duration: 2000
                }
            },

            Transition {
                NumberAnimation {
                    properties: "x,y";
                    duration: 200
                }
            }
        ]

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
