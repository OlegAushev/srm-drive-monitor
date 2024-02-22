#include <QtWidgets/QApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QIcon>

#include "appsettings/appsettings.h"
#include "mcoclient/mcoclient.h"
#include "drive/drivecontroller/drivecontroller.h"
#include "drive/configeditor/configeditor.h"
#include "drive/candataprocessor/candataprocessor.h"
#include "drive/syslog/syslog.h"
#include "models/basicdatatable/basicdatatablemodel.h"
#include "models/basicdatatable/basicdatatable.h"
#include "chartplotter/chartplotter.h"

#include <iostream>
#include <sstream>


int main(int argc, char *argv[])
{
    unsigned int client_canid = 0x14;
    unsigned int server_canid = 0x01;

    if (argc == 3) {
        std::istringstream s1(argv[1]);
        std::istringstream s2(argv[2]);
        unsigned int id1, id2;
        if ((s1 >> std::hex >> id1) && (s2 >> std::hex >> id2)) {     
            client_canid = id1;
            server_canid = id2;
        }

    } 

    std::cout << "Client CAN ID: 0x" << std::hex << client_canid << "\n"; 
    std::cout << "Server CAN ID: 0x" << std::hex << server_canid << std::dec << "\n"; 

	QCoreApplication::setOrganizationName("ECAO");
	QCoreApplication::setApplicationName("srm-drive-monitor");
	AppSettings settings;

#ifdef EDGE_COMPUTER
	system("sh ../scripts/connect_can_edge.sh");
#endif

	QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication app(argc, argv);
	app.setWindowIcon(QIcon(":/images/app.png"));

	qRegisterMetaType<CanBusFrame>("CanBusFrame");
	qmlRegisterType<BasicDataTableModel>("BasicDataTableModel", 1, 0, "BasicDataTableModel");
	qmlRegisterUncreatableType<BasicDataTable>("BasicDataTable", 1, 0, "BasicDataTable", QStringLiteral("BasicDataTable"));
	
	microcanopen::McoClient mcoClient(microcanopen::NodeId{client_canid}, microcanopen::NodeId{server_canid});
	mcoClient.setTpdoPeriod(microcanopen::TpdoNum::NUM1, 250);
	mcoClient.setTpdoPeriod(microcanopen::TpdoNum::NUM2, 100);

	drive::DriveController driveController(&mcoClient);
	drive::ConfigEditor driveConfigEditor(&mcoClient);
	drive::Syslog syslog;
	ChartPlotter chartPlotter(microcanopen::watchEntriesList());
	drive::CanDataProcessor driveCanDataProcessor(&mcoClient, &chartPlotter, &syslog);

	// START QML ENGINE
	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("appSettings", &settings);
	engine.rootContext()->setContextProperty("mcoClient", &mcoClient);
	engine.rootContext()->setContextProperty("driveController", &driveController);
	engine.rootContext()->setContextProperty("driveConfigEditor", &driveConfigEditor);
	engine.rootContext()->setContextProperty("driveCanDataProcessor", &driveCanDataProcessor);
	engine.rootContext()->setContextProperty("syslog", &syslog);
	engine.rootContext()->setContextProperty("chartPlotter", &chartPlotter);


	engine.load(QStringLiteral("qrc:/qml/main.qml"));
	return app.exec();
}


