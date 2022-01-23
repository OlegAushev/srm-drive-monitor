#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlApplicationEngine>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setWindowIcon(QIcon(":/resources/icons/app.png"));
	QQmlApplicationEngine engine;
	engine.load(QStringLiteral("qrc:/src/qml/main.qml"));
	QObject::connect(&engine, &QQmlEngine::quit, &app, &QApplication::quit);

	return app.exec();
}
