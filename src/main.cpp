#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include "canbusdevice/canbusdevice.h"
#include "models/watchdatatablemodel/watchdatatablemodel.h"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setWindowIcon(QIcon(":/images/app.png"));
	QQmlApplicationEngine engine;
	
	
	CanBusDevice canBusDevice;
	engine.rootContext()->setContextProperty("canBusDevice", &canBusDevice);

	
	engine.load(QStringLiteral("qrc:/qml/main.qml"));
	QObject::connect(&engine, &QQmlEngine::quit, &app, &QApplication::quit);

	return app.exec();
}


