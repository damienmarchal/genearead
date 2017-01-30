TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

HEADERS += \
    header/algorithm/algorithm.h \
    header/algorithm/algorithmManager.h \
    header/algorithm/line/lineAlgorithm.h \
    header/algorithm/refine/blur.h \
    header/algorithm/refine/denoise.h \
    header/algorithm/refine/dilate.h \
    header/algorithm/refine/erode.h \
    header/algorithm/refine/kernelFilter.h \
    header/algorithm/refine/refineAlgorithm.h \
    header/algorithm/text/adaptiveThreshold.h \
    header/algorithm/text/niblack.h \
    header/algorithm/text/niblackDerivedAlgorithm.h \
    header/algorithm/text/sauvola.h \
    header/algorithm/text/textAlgorithm.h \
    header/algorithm/text/threshold.h \
    header/image/imageManager.h \
    header/image/imageProvider.h \
    header/tool/circleTool.h \
    header/tool/drawingTool.h

SOURCES += \
    src/algorithm/algorithmManager.cpp \
    src/algorithm/line/lineAlgorithm.cpp \
    src/algorithm/refine/blur.cpp \
    src/algorithm/refine/denoise.cpp \
    src/algorithm/refine/dilate.cpp \
    src/algorithm/refine/erode.cpp \
    src/algorithm/refine/kernelFilter.cpp \
    src/algorithm/text/adaptiveThreshold.cpp \
    src/algorithm/text/niblack.cpp \
    src/algorithm/text/niblackDerivedAlgorithm.cpp \
    src/algorithm/text/sauvola.cpp \
    src/algorithm/text/textAlgorithm.cpp \
    src/algorithm/text/threshold.cpp \
    src/image/imageManager.cpp \
    src/image/imageProvider.cpp \
    src/tool/circleTool.cpp \
    src/main.cpp

RESOURCES += qml/qml.qrc


# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/imageviewer
INSTALLS += target

wince {
   DEPLOYMENT_PLUGIN += qjpeg qgif
}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = qml

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=


INCLUDEPATH += "C:/opencv/opencv/modules/core/include"
INCLUDEPATH += "C:/opencv/opencv/modules/highgui/include"
INCLUDEPATH += "C:/opencv/opencv/modules/imgcodecs/include"
INCLUDEPATH += "C:/opencv/opencv/modules/imgproc/include"
INCLUDEPATH += "C:/opencv/opencv/modules/videoio/include"
INCLUDEPATH += "C:/opencv/opencv/modules/photo/include"
INCLUDEPATH += "C:/opencv/build-opencv-Desktop_Qt_5_8_0_MinGW_32bit-Release"
INCLUDEPATH += "C:/opencv/build-opencv-Desktop_Qt_5_8_0_MinGW_32bit-Release/include"

LIBS +=-LC:\opencv\build-opencv-Desktop_Qt_5_8_0_MinGW_32bit-Release\bin\
-llibopencv_core320\
-llibopencv_highgui320\
-llibopencv_imgcodecs320\
-llibopencv_imgproc320\
-llibopencv_videoio320\
-llibopencv_photo320\
