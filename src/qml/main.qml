import QtQuick 2.5
import QtQuick.Controls 2.15


ApplicationWindow {
	id: appWindow
	visible: true
	width: 1200
	height: 600
	title: qsTr("EVD Monitor")

	menuBar: AppMenuBar {
		id: menuBar
	}

	header: AppToolBar {
		id: toolBar
	}

	MainTabView {
		id: mainTabView
	}







	Button {
		text: "Click!"
		anchors.centerIn: parent
		onClicked: {
			appWindow.color = Qt.rgba(Math.random(), Math.random(), Math.random(), Math.random());
		}
	}
} 
