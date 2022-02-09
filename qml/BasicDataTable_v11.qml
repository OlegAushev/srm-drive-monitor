import QtQuick 2.11
import QtQuick.Controls 1.4 as  C1
import QtQuick.Controls 2.4 as  C2

import BasicDataTableModel 1.0


Rectangle {
	id: root

	property string name
	property QtObject sourceTable
	property real tableWidth
	property real tableHeight
	property real cellSpacing: 1

	property real defaultColumnWidth: (tableWidth-2)/3;

	width: tableWidth
	height: tableHeight
	color: "transparent"
		
	Rectangle {
		id: tableName
		width: tableWidth
		anchors.top: parent.top
		anchors.horizontalCenter: parent.horizontalCenter
		height: 20
		color: "#3daee9"
		border.color: palette.mid

		Text {
			anchors.fill: parent			
			anchors.top: parent.top
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter
			text: name
		}
	}

	C1.TableView {
		id: table
		width: tableWidth
		//height: 30 + rowCount * 24
		anchors.top: tableName.bottom
		anchors.bottom: parent.bottom
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.topMargin: -1
		horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
		verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff

		model: BasicDataTableModel {
			table: sourceTable
		}

		C1.TableViewColumn {
			role: "name"
			title: "Name"
			width: defaultColumnWidth
			horizontalAlignment: Text.AlignHCenter
			resizable: false
			movable: false
		}

		C1.TableViewColumn {
			role: "value"
			title: "Value"
			width: defaultColumnWidth
			horizontalAlignment: Text.AlignHCenter
			resizable: false
			movable: false
		}

		C1.TableViewColumn {
			role: "unit"
			title: "Unit"
			width: defaultColumnWidth
			horizontalAlignment: Text.AlignHCenter
			resizable: false
			movable: false
		}


	}






	



}