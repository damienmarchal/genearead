
import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2



Rectangle {
    id: page
    anchors.fill: parent
    color: "lightgray"
    radius: 1
    property alias backItems: backItems
    property alias rightAlgo: rightAlgo
    property alias rightClick: rightClick
    property alias leftClick: leftClick
    property alias leftAlgo: leftAlgo
    property alias algoPicker: algoPicker
    property string currentAlgo
    width: 420
    height: 430

    Connections {
        target: imageManager
        onPreviewUpdate: {
            algoPicker.refreshOne(imageManager.getSelectedPreviewID())
        }
        onPreviewsUpdate: {
            algoPicker.refresh();
        }
        onPreviewDeselection: {
            deselectPreview()
        }
        onPreviewSelection: {
            imageManager.showSelectionLayers();
            selectPreview()
        }
    }

    function deselectPreview() {
        var select = imageManager.getSelectedPreviewID()+1;
        algoPicker.setBorder(select, "#00000000")
        algoColumn.children[imageManager.getSelectedAlgorithmID()+1].visible = false;
    }

    function selectPreview() {
        var select = imageManager.getSelectedPreviewID()+1
        algoPicker.setBorder(select, "#FF00FF")
        algoColumn.children[imageManager.getSelectedAlgorithmID()+1].visible = true;
    }

    Column {
        id: algoColumn
        objectName: "algoColumn"
        width: 420
        height: 430

        Row {
            id: algoPicker
            spacing: 10
            objectName: "previews"

            function refresh() {
                for(var i = 0; i < children.length-2; ++i) {
                    refreshOne(i)
                }
            }

            function refreshOne(i) {
                if(i>-1 && i<children.length-1) {
                    var rect = children[i+1]
                    var image = rect.children[0];
                    var oldSource = image.source;
                    image.source = "";
                    image.source = oldSource;
                }
            }

            function setBorder(id, color) {
                if(id>0 && id<children.length-1)
                    children[id].border.color = color
            }

            function selectRectangle(id) {
                setBorder(imageManager.getSelectedPreviewID()+1, "#00000000")
                imageManager.selectPreviewID(id)
                setBorder(imageManager.getSelectedPreviewID()+1, "#FF00FF")
            }

            function previousRectangle() {
                setBorder(imageManager.getSelectedPreviewID()+1, "#00000000")
                imageManager.shiftPreviewsRight()
                setBorder(imageManager.getSelectedPreviewID()+1, "#FF00FF")
            }

            function nextRectangle() {
                setBorder(imageManager.getSelectedPreviewID()+1, "#00000000")
                imageManager.shiftPreviewsLeft()
                setBorder(imageManager.getSelectedPreviewID()+1, "#FF00FF")
            }

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
                        algoPicker.previousRectangle()
                    }
                }
            }


            Rectangle {
                id: rectSelectAlgo0
                x: 0
                width: 110
                height: 160
                color: "#00000000"
                radius: 1
                z: 2
                border.width: 60
                border.color: "#00000000"
                Image {
                    id: preview0
                    width: 100
                    height: 150
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "image://imageProvider/preview0"
                    cache: false
                    clip: true

                    MouseArea {
                        id: algo0Click
                        anchors.fill: parent
                        onClicked: imageManager.selectPreview(0)
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
                        onClicked: imageManager.selectPreview(1)
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
                border.color: "#00000000"
                Image {
                    id: preview2
                    width: 100
                    height: 150
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "image://imageProvider/preview2"
                    cache: false
                    clip: true

                    MouseArea {
                        id: algo2Click
                        anchors.fill: parent
                        onClicked: imageManager.selectPreview(2)
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
                        algoPicker.nextRectangle()
                    }
                }
            }
        }

        AlgorithmParameter {
            id: algoParameters0
            Item {
                Item {
                }
            }
        }

        AlgorithmParameter {
            id: algoParameters1
            Item {
                Item {
                    property string textAlgoName: "niblack"
                    property real k: algoParameters1_0.valueX
                }
            }
            AlgorithmSliders {
                NormalSlider2D {id: algoParameters1_0}
            }
        }

        AlgorithmParameter {
            id: algoParameters2
            Item {
                Item {
                    property string textAlgoName: "sauvola"
                    property real k: algoParameters2_0.valueX
                    property real r: algoParameters2_0.valueY
                }
            }
            AlgorithmSliders {
                NormalSlider2D {id: algoParameters2_0}
            }
        }

        AlgorithmParameter {
            id: algoParameters3
            Item {
                Item {
                    property string textAlgoName: "threshold"
                    property real t: algoParameters3_0.valueX
                    property real inv: algoParameters3_0.valueY
                }
            }
            AlgorithmSliders {
                NormalSlider2D {id: algoParameters3_0}
            }
        }

        AlgorithmParameter {
            id: algoParameters4
            Item {
                Item {
                    property string textAlgoName: "adaptiveThreshold"
                    property real w: algoParameters4_0.valueX
                    property real inv_mean: algoParameters4_0.valueY
                }
            }
            AlgorithmSliders {
                NormalSlider2D {id: algoParameters4_0}
            }
        }

        AlgorithmParameter {
            id: algoParameters5
            Item {
                Item {
                    property string textAlgoName: "niblack"
                    property real k: algoParameters5_0.valueX
                }
                Item {
                    property string refineAlgoName: "erode"
                    property real iterations: algoParameters5_0.valueY
                }
                Item {
                    property string refineAlgoName: "dilate"
                    property real iterations: algoParameters5_0.valueY
                }
            }
            AlgorithmSliders {
                NormalSlider2D {id: algoParameters5_0}
            }
        }

        AlgorithmParameter {
            id: algoParameters6
            Item {
                Item {
                    property string textAlgoName: "threshold"
                    property real t: algoParameters6_0.value
                }
            }
            AlgorithmSliders {
                NormalSlider {id: algoParameters6_0}
            }
        }

        AlgorithmParameter {
            id: algoParameters7
            Item {
                Item {
                    property string textAlgoName: "threshold"
                    property real t: algoParameters7_0.value
                }
            }
            AlgorithmSliders {
                NormalSlider {id: algoParameters7_0}
            }
        }

        AlgorithmParameter {
            id: algoParameters8
            Item {
                Item {
                    property string textAlgoName: "threshold"
                    property real t: algoParameters8_0.value
                }
            }
            AlgorithmSliders {
                NormalSlider {id: algoParameters8_0}
            }
        }

        AlgorithmParameter {
            id: algoParameters9
            Item {
                Item {
                    property string textAlgoName: "threshold"
                    property real t: algoParameters9_0.value
                }
            }
            AlgorithmSliders {
                NormalSlider {id: algoParameters9_0}
            }
        }


        Item{
            id: item1
            width: 420
            height: 20
            BackItems {
                id: backItems
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
                anchors.right: parent.right
                anchors.rightMargin: 20

            }
        }

    }
}
