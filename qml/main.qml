import QtQuick 2.5
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15


ApplicationWindow {
	id: appWindow
	visible: true
	minimumWidth: 1000
	minimumHeight: 550
	title: qsTr("SRM Drive Monitor")

	menuBar: AppMenuBar {
		id: menuBar
	}

	header: AppToolBar {
		id: toolBar
		anchors.left: parent.left
		anchors.right: parent.right
	}

	footer : AppStatusBar {
		id: statusBar
	}

	GridLayout {
		anchors.fill: parent
		anchors.leftMargin: 2
		anchors.topMargin: 2
		anchors.rightMargin: 2
		anchors.bottomMargin: 2
		rows: 1
		columns: 2
		columnSpacing: 2

		MainTabView {
			id: mainTabView
			Layout.minimumWidth: 850
			Layout.minimumHeight: 550
			Layout.fillWidth: true
			Layout.fillHeight: true
		}
		
		ControlTabView {
			id: controlTabView
			anchors.right: parent.right
			anchors.top: parent.top
			Layout.preferredWidth: 350
			Layout.preferredHeight: 400
			Layout.fillWidth: false
			Layout.fillHeight: true
		}
	}

	Connections {
		target: canBusDevice
		onStatusMessageAvailable: {
			statusBar.print(message);
		}
	}






	Button {
		text: "Click!"
		anchors.centerIn: parent
		onClicked: {
			appWindow.color = Qt.rgba(Math.random(), Math.random(), Math.random(), Math.random());
		}
	}
} 
