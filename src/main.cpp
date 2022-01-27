#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include "canbusdevice/canbusdevice.h"
#include "models/basicdatatable/basicdatatablemodel.h"
#include "models/basicdatatable/basicdatatable.h"
#include "mcoclient/mcoclient.h"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setWindowIcon(QIcon(":/images/app.png"));
		
	qmlRegisterType<BasicDataTableModel>("BasicDataTableModel", 1, 0, "BasicDataTableModel");
	qmlRegisterUncreatableType<BasicDataTable>("BasicDataTable", 1, 0, "BasicDataTable", QStringLiteral("BasicDataTable"));
	
	BasicDataTable table1({{"A","B"},{"C","D"},{"E","F"},{"G","H"}});
	CanBusDevice canBusDevice;
	microcanopen::McoClient mcoClient(microcanopen::NodeId(0x14), microcanopen::NodeId(0x01));

	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("canBusDevice", &canBusDevice);
	engine.rootContext()->setContextProperty("table1", &table1);
	engine.load(QStringLiteral("qrc:/qml/main.qml"));

	QObject::connect(&engine, &QQmlEngine::quit, &app, &QApplication::quit);
	return app.exec();
}


