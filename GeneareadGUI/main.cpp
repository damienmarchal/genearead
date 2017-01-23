#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QDebug>
#include <QQmlContext>
#include <QQuickView>
#include <QCommandLineParser>

#include "algorithm/algorithmManager.h"
#include "imageManager.h"
#include "imageProvider.h"
#include "interaction.h"

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
    mat = imread("C:/Users/corentin/Pictures/gfx/Antolach.PNG");
    namedWindow("hello", WINDOW_AUTOSIZE);
    imshow("hello", mat);

    waitKey(0);

    //cout << "Hello World!" << endl;

    //QQmlComponent component(&engine,
    //        QUrl::fromLocalFile("MyItem.qml"));
    //QObject *window = component.create();
    //QObject *image = window-> findChild<QObject*>("image");
    //*image->setProperty("color")

    //qmlRegisterType<algorithm>("QMLObjects", 1, 0, "algorithm");

}

int start(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    /*AlgorithmManager a;
    engine.rootContext()->setContextProperty("algor", &a);*/

    ImageManager im;
    engine.rootContext()->setContextProperty("imageManager", &im);

    ImageProvider ip = ImageProvider(&im);
    engine.addImageProvider("imageProvider", &ip);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QGuiApplication::setApplicationDisplayName(QObject::tr("Genearead"));

    QCommandLineParser commandLineParser;
    commandLineParser.addHelpOption();
    commandLineParser.addPositionalArgument(QObject::tr("[file]"), QObject::tr("Image file to open."));
    commandLineParser.process(QCoreApplication::arguments());

    return app.exec();
}

int main(int argc, char *argv[]) {

    return start(argc, argv);

    //return start(argc, *argv[]);

    /*Interaction interaction;
    if (!commandLineParser.positionalArguments().isEmpty()
        && !interaction.loadFile(commandLineParser.positionalArguments().front())) {
        return -1;
    }*/
    //interaction.show();
}

/*void createLanguageMenu()
{
    QActionGroup* langGroup = new QActionGroup(ui.menuLanguage);
    langGroup->setExclusive(true);

    connect(langGroup, SIGNAL (triggered(QAction *)), this, SLOT (slotLanguageChanged(QAction *)));

    // format systems language
    QString defaultLocale = QLocale::system().name(); // e.g. "de_DE"
    defaultLocale.truncate(defaultLocale.lastIndexOf('_')); // e.g. "de"

    m_langPath = QApplication::applicationDirPath();
    m_langPath.append("/languages");
    QDir dir(m_langPath);
    QStringList fileNames = dir.entryList(QStringList("TranslationExample_*.qm"));

    for (int i = 0; i < fileNames.size(); ++i) {
        // get locale extracted by filename
        QString locale;
        locale = fileNames[i]; // "TranslationExample_de.qm"
        locale.truncate(locale.lastIndexOf('.')); // "TranslationExample_de"
        locale.remove(0, locale.indexOf('_') + 1); // "de"

        QString lang = QLocale::languageToString(QLocale(locale).language());
        QIcon ico(QString("%1/%2.png").arg(m_langPath).arg(locale));

        QAction *action = new QAction(ico, lang, this);
        action->setCheckable(true);
        action->setData(locale);

        ui.menuLanguage->addAction(action);
        langGroup->addAction(action);

        // set default translators and language checked
        if (defaultLocale == locale)
        {
            action->setChecked(true);
        }
    }
}*/

/*void call() {
    QQmlEngine engine;
    QQmlComponent component(&engine, "Algorithm.qml");
    QObject *object = component.create();

    QVariant returnedValue;
    QVariant msg = "Hello from C++";
    QMetaObject::invokeMethod(object, "call",
                              Q_RETURN_ARG(QVariant, returnedValue),
                              Q_ARG(QVariant, msg));

    qDebug() << "QML function returned:" << returnedValue.toString();
    delete object;
}*/
