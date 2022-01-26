#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include "canbusdevice/canbusdevice.h"
#include "models/candatatable/candatatablemodel.h"
#include "models/candatatable/candatatable.h"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setWindowIcon(QIcon(":/images/app.png"));
		
	qmlRegisterType<CanDataTableModel>("CanDataTableModel", 1, 0, "CanDataTableModel");
	qmlRegisterUncreatableType<CanDataTable>("CanDataTable", 1, 0, "CanDataTable", QStringLiteral("TESTTEST"));
	
	CanDataTable table1({{"A","B"},{"C","D"},{"E","F"},{"G","H"}});
	CanBusDevice canBusDevice;

	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("canBusDevice", &canBusDevice);
	engine.rootContext()->setContextProperty("table1", &table1);
	engine.load(QStringLiteral("qrc:/qml/main.qml"));

	QObject::connect(&engine, &QQmlEngine::quit, &app, &QApplication::quit);
	return app.exec();
}


