import QtQuick 2.5
import QtQuick.Controls 2.15


ApplicationWindow {
	id: appWindow
	visible: true
	width: 1200
	height: 600
	title: qsTr("EVD Monitor")

	header: AppMenuBar {
		id: menuBar
	}

	AppToolBar {
		id: toolBar
		//anchors.top: menubar.bottom
	}








	Button {
		text: "Click!"
		anchors.centerIn: parent
		onClicked: {
			appWindow.color = Qt.rgba(Math.random(), Math.random(), Math.random(), Math.random());
		}
	}
} 
