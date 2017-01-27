
import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2



Rectangle {
    id: page
    width: 420; height:400
    color: "lightgray"
    radius: 1
    property alias rightAlgo: rightAlgo
    property alias rightClick: rightClick
    property alias algo3: algo3
    property alias algo2: algo2
    property alias algo1: algo1
    property alias leftClick: leftClick
    property alias leftAlgo: leftAlgo
    property alias algoPicker: algoPicker
    property string currentAlgo

    Column {
        id: column
        width: 420
        height: 400

        Row {
            id: algoPicker
            width: 420
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
                        if(currentAlgo == "algo1"){
                            currentAlgo  = "algo3"
                        }
                        else if (currentAlgo =="algo2"){
                            currentAlgo  = "algo1"
                        }
                        else if (currentAlgo =="algo3"){
                            currentAlgo  = "algo2"
                        }
                    }
                }
            }
            Rectangle {
                id: rectSelectAlgo1
                x: 0
                width: 110
                height: 160
                color: "#00000000"
                radius: 1
                z: 2
                border.width: 60
                border.color: currentAlgo == "algo1" ? "#ffffff" : "#00000000"

                Image {
                    id: algo1
                    width: 100
                    height: 160
                    anchors.horizontalCenter: parent.horizontalCenter
                    fillMode: Image.PreserveAspectFit
                    source: "Livret F.jpg"

                    MouseArea {
                        id: algo1Click
                        anchors.fill: parent
                        onClicked: {
                            currentAlgo = "algo1"
                        }
                    }
                }
            }

            Rectangle {
                id: rectSelectAlgo2
                x: 0
                width: 110
                height: 160
                color: "#00000000"
                radius: 1
                z: 2
                border.width: 60
                border.color: currentAlgo == "algo2" ? "#ffffff" : "#00000000"

                Image {
                    id: algo2
                    x: 0
                    y: 0
                    width: 100
                    height: 160
                    anchors.horizontalCenter: parent.horizontalCenter
                    fillMode: Image.PreserveAspectFit
                    source: "Livret Lucien.jpg"
                    MouseArea {
                        id: algo2Click
                        anchors.fill: parent
                        onClicked: {
                            currentAlgo = "algo2"
                        }
                    }
                }
            }
            Rectangle {
                id: rectSelectAlgo3
                x: 0
                width: 110
                height: 160
                color: "#00000000"
                radius: 1
                z: 2
                border.width: 60
                border.color: currentAlgo == "algo3" ? "#ffffff" : "#00000000"
                Image {
                    id: algo3
                    width: 100
                    height: 160
                    anchors.horizontalCenter: parent.horizontalCenter
                    fillMode: Image.PreserveAspectFit
                    source: "Livret.jpg"

                    MouseArea {
                        id: algo3Click
                        anchors.fill: parent
                        onClicked:{
                            currentAlgo = "algo3"
                        }
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
                        if(currentAlgo == "algo1"){
                            currentAlgo  = "algo2"
                        }
                        else if (currentAlgo =="algo2"){
                            currentAlgo  = "algo3"
                        }
                        else if (currentAlgo =="algo3"){
                            currentAlgo  = "algo1"
                        }
                    }
                }
            }
        }
        Item{
            id : parameters
            width: 420
            height: 240
            Item{
            id: algo1parameters
            width: 420
            height: 240

            visible: currentAlgo =="algo1"
            Slider {
                id: sliderVertical
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                stepSize: 0.05
                value: 0.5
                orientation: Qt.Vertical

            }
        }
        Item{
            id: algo2parameters
            width: 420
            height: 240

            visible: currentAlgo =="algo2"

            Slider {
                id: sliderHorizontal
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                stepSize: 0.05
                value: 0.5

            }
        }
        Item{
            id: algo3parameters
            width: 420
            height: 240

            visible: currentAlgo =="algo3"

            Image {
                property int currentX
                property int currentY
                id: graph
                width: 200
                height: 200
                fillMode: Image.PreserveAspectFit
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                source: "plus.png"
                Canvas {
                    id: graphCanvas
                    z: 1
                    anchors.fill: parent
                    onPaint : {
                        var ctx = getContext("2d");
                        ctx.reset()
                        ctx.fillStyle = Qt.rgba(255, 0, 0, 1)
                        ctx.beginPath()
                        ctx.arc(graph.currentX, graph.currentY, 4, 0, Math.PI*2, true)
                        ctx.closePath()
                        ctx.fill()
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            graph.currentX = mouseX
                            graph.currentY = mouseY
                            graphCanvas.requestPaint()
                        }
                        onPositionChanged: {
                            graph.currentX = mouseX
                            graph.currentY = mouseY
                            graphCanvas.requestPaint()
                        }
                    }
                }
            }
}
        }
    }
}
