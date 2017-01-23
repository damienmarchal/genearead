
import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2


Rectangle {
    id: page
    width: 400; height:400
    color: "lightgray"
    radius: 1
    property alias rectSelect: rectSelect
    property alias rightAlgo: rightAlgo
    property alias rightClick: rightClick
    property alias algo3: algo3
    property alias algo2: algo2
    property alias algo1: algo1
    property alias leftClick: leftClick
    property alias leftAlgo: leftAlgo
    property alias algoPicker: algoPicker
    property string currentAlgo : "Livret Lucien.jpg"
    property bool validation : false

    Column {
        id: column
        width: 400
        height: 400

        Row {
            id: algoPicker
            width: 400
            height: 160
            spacing: 10

            Image {
                id: leftAlgo
                width: 25
                height: 25
                anchors.verticalCenter: parent.verticalCenter
                fillMode: Image.PreserveAspectFit
                source: "flechegauche.png"

                MouseArea {
                    id: leftClick
                    anchors.fill: parent
                    onClicked: {
                        algo2.source = algo3.source
                        algo3.source = algo1.source
                        algo1.source = currentAlgo
                        currentAlgo = algo2.source
                    }
                }
            }

            Image {
                id: algo1
                width: 100
                height: 160
                fillMode: Image.PreserveAspectFit
                source: "Livret F.jpg"

                MouseArea {
                    id: algo1Click
                    anchors.fill: parent
                    onClicked: {
                        algo2.source = algo1.source
                        algo1.source = algo3.source
                        algo3.source = currentAlgo
                        currentAlgo = algo2.source

                    }
                }
            }

            Rectangle {
                id: rectSelect
                x: 0
                width: 110
                height: 160
                color: "#00000000"
                radius: 1
                z: 2
                border.width: 60
                border.color: "#ffffff"

                Image {
                    id: algo2
                    x: 0
                    y: 0
                    width: 100
                    height: 160
                    anchors.horizontalCenter: parent.horizontalCenter
                    fillMode: Image.PreserveAspectFit
                    source: "Livret Lucien.jpg"
                }
            }

            Image {
                id: algo3
                width: 100
                height: 160
                fillMode: Image.PreserveAspectFit
                source: "Livret.jpg"

                MouseArea {
                    id: algo2Click
                    anchors.fill: parent
                    onClicked:{
                        algo2.source = algo3.source
                        algo3.source = algo1.source
                        algo1.source = currentAlgo
                        currentAlgo = algo2.source
                    }
                }
            }

            Image {
                id: rightAlgo
                width: 25
                height: 25
                anchors.verticalCenter: parent.verticalCenter
                fillMode: Image.PreserveAspectFit
                source: "flechedroite.png"

                MouseArea {
                    id: rightClick
                    anchors.fill: parent
                    onClicked: {
                        algo2.source = algo1.source
                        algo1.source = algo3.source
                        algo3.source = currentAlgo
                        currentAlgo = algo2.source

                    }
                }
            }
        }

        Row {
            id: parameters
            width: 400
            height: 200
            spacing: 10

            Slider {
                id: sliderVertical
                stepSize: 0.05
                value: 0.5
                orientation: Qt.Vertical
                visible: false
            }

            Slider {
                id: sliderHorizontal
                stepSize: 0.05
                value: 0.5
                visible: false
            }
        }

        Button {
            id: validationFond
            text: qsTr("Ok ! ")
            tooltip: "Appliquer l'algorithme"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                clickedTool = false
                //validation = true
            }
        }
    }
}


