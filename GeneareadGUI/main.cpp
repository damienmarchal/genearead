#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QDebug>
#include <QQmlContext>
#include <QQuickView>

#include "algorithm.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    algorithm a;
    engine.rootContext()->setContextProperty("algor", &a);

    //QQmlComponent component(&engine,
    //        QUrl::fromLocalFile("MyItem.qml"));
    //QObject *window = component.create();
    //QObject *image = window-> findChild<QObject*>("image");
    //*image->setProperty("color")

    //qmlRegisterType<algorithm>("QMLObjects", 1, 0, "algorithm");

    return app.exec();
}

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
