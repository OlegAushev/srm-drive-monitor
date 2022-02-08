import QtQuick 2.11 as Q2
import QtQuick.Controls 2.4 as C2
import QtQuick.Layouts 1.11


C2.ApplicationWindow {
	id: appWindow
	visible: true
	minimumWidth: 1390
	minimumHeight: 760
	color: "#eff0f1"

	title: "SRM Drive Monitor"
	
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

		DataAndCharts {
			id: dataTabView
			Layout.alignment: Qt.AlignLeft | Qt.AlignTop 
			Layout.minimumWidth: 800
			Layout.minimumHeight: 500
			Layout.fillWidth: true
			Layout.fillHeight: true
		}
		
		ControlAndConfiguration {
			id: controlTabView
			Layout.alignment: Qt.AlignLeft | Qt.AlignTop 
			Layout.preferredWidth: 332
			Layout.preferredHeight: 400
			Layout.fillWidth: false
			Layout.fillHeight: true
		}
	}

	

} 
