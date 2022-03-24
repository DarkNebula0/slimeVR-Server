#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Defines.h"

#include "TrackerServer.h"
#include "Gui.h"

#if defined(Q_OS_WIN)
#include <Windows.h>
#include "Logger.h"
#endif

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    if (AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()) {
            freopen("CONOUT$", "w", stdout);
            freopen("CONOUT$", "w", stderr);
        }

    Logger::SetTitle(CONSOLE_TITLE);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    CGui oGuiClass;
    engine.rootContext()->setContextProperty("_gui", &oGuiClass);

    // Load server
    TrackerServerInstance->initialize(QHostAddress::Any, UDP_PORT);

    return app.exec();
}
