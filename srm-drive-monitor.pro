QT += qml quick charts widgets

QMAKE_CXXFLAGS += -std=c++17

DEFINES += EDGE_COMPUTER

SOURCES += \
	src/main.cpp							\
	src/appsettings/appsettings.cpp					\
	src/cansocketdevice/cansocketdevice.cpp				\
	src/mcoclient/mcoclient.cpp					\
	src/mcoclient/objectdictionary/objectdictionary.cpp		\
	src/drive/candataprinter/candataprinter.cpp			\
	src/drive/configeditor/configeditor.cpp				\
	src/drive/drivecontroller/drivecontroller.cpp			\
	src/chartplotter/chartplotter.cpp				\
	src/models/basicdatatable/basicdatatable.cpp			\
	src/models/basicdatatable/basicdatatablemodel.cpp		\

HEADERS += \
	src/appsettings/appsettings.h					\
	src/cansocketdevice/cansocketdevice.h				\
	src/mcoclient/mcoclient.h					\
	src/mcoclient/mcodef.h						\
	src/mcoclient/rpdodef.h						\
	src/mcoclient/tpdodef.h						\
	src/mcoclient/objectdictionary/objectdictionary.h		\
	src/drive/candataprinter/candataprinter.h			\
	src/drive/configeditor/configeditor.h				\
	src/drive/drivecontroller/drivecontroller.h			\
	src/chartplotter/chartplotter.h					\
	src/models/basicdatatable/basicdatatable.h			\
	src/models/basicdatatable/basicdatatablemodel.h			\

INCLUDEPATH = src/

RESOURCES += \
	resources.qrc

TARGET = srm-drive-monitor

DESTDIR = bin


