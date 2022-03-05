#include <QtWidgets/QApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QIcon>

#include "mcoclient/mcoclient.h"
#include "drive/drivecontroller/drivecontroller.h"
#include "drive/configeditor/configeditor.h"
#include "drive/candataprocessor/candataprocessor.h"
#include "drive/syslog/syslog.h"
#include "models/basicdatatable/basicdatatablemodel.h"
#include "models/basicdatatable/basicdatatable.h"
#include "chartplotter/chartplotter.h"



int main(int argc, char *argv[])
{
#ifdef EDGE_COMPUTER
	system("sh ../scripts/connect_can_edge.sh");
#endif

	QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication app(argc, argv);
	app.setWindowIcon(QIcon(":/images/app.png"));

	qRegisterMetaType<CanBusFrame>("CanBusFrame");
	qmlRegisterType<BasicDataTableModel>("BasicDataTableModel", 1, 0, "BasicDataTableModel");
	qmlRegisterUncreatableType<BasicDataTable>("BasicDataTable", 1, 0, "BasicDataTable", QStringLiteral("BasicDataTable"));
	
	microcanopen::McoClient mcoClient(microcanopen::NodeId(0x14), microcanopen::NodeId(0x01));
	mcoClient.setTpdoPeriod(microcanopen::TpdoNum::NUM1, 250);
	mcoClient.setTpdoPeriod(microcanopen::TpdoNum::NUM2, 100);

	drive::DriveController driveController(&mcoClient);
	drive::ConfigEditor driveConfigEditor(&mcoClient);
	drive::Syslog syslog;
	ChartPlotter chartPlotter;
	drive::CanDataProcessor driveCanDataProcessor(&mcoClient, &chartPlotter, &syslog);

	// START QML ENGINE
	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("mcoClient", &mcoClient);
	engine.rootContext()->setContextProperty("driveController", &driveController);
	engine.rootContext()->setContextProperty("driveConfigEditor", &driveConfigEditor);
	engine.rootContext()->setContextProperty("driveCanDataProcessor", &driveCanDataProcessor);
	engine.rootContext()->setContextProperty("chartPlotter", &chartPlotter);


	engine.load(QStringLiteral("qrc:/qml/main.qml"));
	return app.exec();
}


