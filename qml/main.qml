import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import QtQuick.Controls.Material 2.1


ApplicationWindow {
	id: appWindow

	Material.primary: Material.color(Material.BlueGrey)			// used for EVOCARGO build
	Material.accent: Material.color(Material.DeepOrange, Material.Shade700)	// used for EVOCARGO build
	
	visible: true
	minimumWidth: 1340
	minimumHeight: 700
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

		MainWidget {
			id: dataTabView
			Layout.alignment: Qt.AlignLeft | Qt.AlignTop 
			Layout.minimumWidth: 800
			Layout.minimumHeight: 500
			Layout.fillWidth: true
			Layout.fillHeight: true
		}
		
		ControlAndConfigurationWidget {
			id: controlTabView
			Layout.alignment: Qt.AlignLeft | Qt.AlignTop 
			Layout.preferredWidth: 332
			Layout.preferredHeight: 400
			Layout.fillWidth: false
			Layout.fillHeight: true
		}
	}

	

} 
