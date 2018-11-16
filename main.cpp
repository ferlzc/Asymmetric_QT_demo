#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include "realtime.h"

#define VERSION "V1.0"



int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        // Qt Charts uses Qt Graphics View Framework for drawing, therefore QApplication must be used.

    qputenv("QMLSCENE_DEVICE", QByteArray("softwarecontext"));
    qputenv("QSG_INFO", QByteArray("1"));

    qmlRegisterType<Realtime>("Realtime", 1, 0, "Realtime");
    QApplication app(argc, argv);

    QQuickView viewer;

    QString extraImportPath(QStringLiteral("%1/../../../%2"));

    viewer.engine()->addImportPath(extraImportPath.arg(QGuiApplication::applicationDirPath(),
                                      QString::fromLatin1("qml")));
    QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer, &QWindow::close);

    QQmlContext *ctxt = viewer.engine()->rootContext();
    ctxt->setContextProperty("SOFTWARE_VERSION", VERSION);

    viewer.setTitle(QStringLiteral("QML Chart"));

    viewer.setSource(QUrl("qrc:/main.qml"));
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.showFullScreen();
 //   viewer.showMaximized()
//    viewer.show();
    return app.exec();
}
