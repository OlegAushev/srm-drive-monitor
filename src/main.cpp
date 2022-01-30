#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include "mcoclient/mcoclient.h"
#include "drive/drivecontroller/drivecontroller.h"
#include "drive/configeditor/configeditor.h"
#include "models/basicdatatable/basicdatatablemodel.h"
#include "models/basicdatatable/basicdatatable.h"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setWindowIcon(QIcon(":/images/app.png"));
		
	qmlRegisterType<BasicDataTableModel>("BasicDataTableModel", 1, 0, "BasicDataTableModel");
	qmlRegisterUncreatableType<BasicDataTable>("BasicDataTable", 1, 0, "BasicDataTable", QStringLiteral("BasicDataTable"));
	
	BasicDataTable table1({{"A","B"},{"C","D"},{"E","F"},{"G","H"}});


	microcanopen::McoClient mcoClient(microcanopen::NodeId(0x14), microcanopen::NodeId(0x01));
	mcoClient.setTpdoPeriod(microcanopen::TpdoNum::NUM1, 250);
	mcoClient.setTpdoPeriod(microcanopen::TpdoNum::NUM2, 100);

	drive::DriveController driveController(&mcoClient);
	ConfigEditor driveConfigEditor(&mcoClient);





	/* START QML ENGINE */
	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("mcoClient", &mcoClient);
	engine.rootContext()->setContextProperty("driveController", &driveController);
	engine.rootContext()->setContextProperty("driveConfigEditor", &driveConfigEditor);



	engine.rootContext()->setContextProperty("table1", &table1);




	engine.load(QStringLiteral("qrc:/qml/main.qml"));

	QObject::connect(&engine, &QQmlEngine::quit, &app, &QApplication::quit);
	return app.exec();
}


