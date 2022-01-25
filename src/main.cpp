#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlApplicationEngine>

#include "canbusdevice/canbusdevice.h"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setWindowIcon(QIcon(":/images/app.png"));
	QQmlApplicationEngine engine;
	engine.load(QStringLiteral("qrc:/qml/main.qml"));
	QObject::connect(&engine, &QQmlEngine::quit, &app, &QApplication::quit);

	


	return app.exec();
}


