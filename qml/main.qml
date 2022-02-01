import QtQuick 2.15 as Q2
import QtQuick.Controls 2.15 as C2
import QtQuick.Layouts 1.15// as Layouts


C2.ApplicationWindow {
	id: appWindow
	visible: true
	minimumWidth: 1390
	minimumHeight: 620
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

		MainTabView {
			id: mainTabView
			Layout.alignment: Qt.AlignLeft | Qt.AlignTop 
			Layout.minimumWidth: 800
			Layout.minimumHeight: 500
			Layout.fillWidth: true
			Layout.fillHeight: true
		}
		
		ControlTabView {
			id: controlTabView
			Layout.alignment: Qt.AlignLeft | Qt.AlignTop 
			Layout.preferredWidth: 332
			Layout.preferredHeight: 400
			Layout.fillWidth: false
			Layout.fillHeight: true
		}
	}

	

} 
