import QtQuick 2.0
import QtQuick.Controls 1.5

Slider {
    minimumValue: 0.0
    maximumValue: 1.0
    orientation: Qt.Horizontal
    onValueChanged: {
        imageManager.applyPreview(imageManager.getSelectedAlgorithmID())
    }
}
