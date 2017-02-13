#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QDebug>
#include <QQmlContext>
#include <QQuickView>
#include <QCommandLineParser>

#include <header/algorithm/algorithmManager.h>
#include <header/io/projectReader.h>
#include <header/io/projectWriter.h>
#include <header/image/imageManager.h>
#include <header/image/imageProvider.h>

#include <header/io/project.h>

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

void cvTest1() {
    cv::Mat img(2, 2, CV_8UC3, Scalar(126, 0, 255));
    cout << "img = \n" << img << "\n\n" << endl;
}

void cvTest2() {
    Mat mat;
    mat = imread("foo");
    namedWindow("hello", WINDOW_AUTOSIZE);
    imshow("hello", mat);

    waitKey(0);


}

void cvTest3() {

    Layer mat = imread("foo");
    int width = mat.cols;
    int height = mat.rows;

    Layer l = Layer(height, width, CV_8UC1);
    cv::cvtColor(mat, l, CV_RGB2GRAY);
    Layer l2 = Layer(height, width, CV_16U);
    int n = cv::connectedComponents(l, l2, 4, CV_16U);

    ushort* prt = l2.ptr<ushort>();
    assert(l2.isContinuous());

    for(int i=0; i<width*height; ++i) {
        prt[i] = (prt[i] * (0xFFFF/(n-1)));
    }

    cv::namedWindow("hello", WINDOW_AUTOSIZE);
    cv::imshow("hello", l2);
    std::cout << l2 << std::endl;

    cv::waitKey(0);
}


int start(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QQmlApplicationEngine* engine = new QQmlApplicationEngine();


    ImageManager* im = new ImageManager(engine);
    engine->rootContext()->setContextProperty("imageManager", im);

    ImageProvider* ip = new ImageProvider(im);
    engine->addImageProvider("imageProvider", ip);

    PROJECT = new Project(
                engine,
                new ProjectReader(),
                new ProjectWriter(),
                im
                );

    engine->rootContext()->setContextProperty("project", PROJECT);

    engine->load(QUrl(QStringLiteral("qrc:/main.qml")));

    im->init();

    QCommandLineParser commandLineParser;
    commandLineParser.addHelpOption();
    commandLineParser.addPositionalArgument(QObject::tr("[file]"), QObject::tr("Image file to open."));
    commandLineParser.process(QCoreApplication::arguments());

    //PROJECT->close();

    return app.exec();
}

int main(int argc, char *argv[]) {

    return start(argc, argv);
}

