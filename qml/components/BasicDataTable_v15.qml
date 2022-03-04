import QtQuick 2.15
import QtQuick.Controls 2.15

import BasicDataTableModel 1.0


Rectangle {
	property string name
	property QtObject sourceTable
	property real tableWidth
	property real cellSpacing: 1

	property real defaultColumnWidth: (tableWidth - 2*cellSpacing)/3;

	function getColumnWidth(col)
	{
		switch (col) {
		case 0:
			return defaultColumnWidth;
		case 1:
			return defaultColumnWidth*1.2;
		case 2:
			return defaultColumnWidth/1.2;
		default:
			return 0;
		}
	}

	width: tableWidth + 2*cellSpacing
	height: tableName.height + header.height + 4*cellSpacing + table.contentHeight

	border.color: "lightgrey"
	color: "lightgrey"

	Rectangle {
		id: tableName
		width: tableWidth
		anchors.top: parent.top
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.topMargin: cellSpacing
		height: 20
		color: "#3daee9"

		Text {
			anchors.fill: parent			
			anchors.top: parent.top
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter
			text: name
		}
	}
	
	Row {
		id: header
		width: tableWidth
		height: 20
		anchors.top: tableName.bottom
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.topMargin: cellSpacing
		spacing: cellSpacing

		Repeater {
			model: 3

			Rectangle {
				width: defaultColumnWidth
				height: header.height
				color: "#93cee9"

				Text {
					width: parent.width
					height: parent.height
					horizontalAlignment: Text.AlignHCenter
					verticalAlignment: Text.AlignVCenter
					text: table.model.headerData(index, Qt.Horizontal)
				}
			}
		}
	}

	TableView {
		id: table
		width: tableWidth
		anchors.top: header.bottom
		anchors.topMargin: cellSpacing
		anchors.bottom: parent.bottom
		anchors.horizontalCenter: parent.horizontalCenter
		columnSpacing: cellSpacing
		rowSpacing: cellSpacing
		interactive: false

		model : BasicDataTableModel {
			table: sourceTable
		}
		
		delegate: Rectangle {
			color: model.row % 2 == 0 ? "white" : "#eff0f1"
			implicitWidth: defaultColumnWidth
			implicitHeight: text.implicitHeight

			Text{
				id: text
				text: model.display
				width: parent.width
				horizontalAlignment: model.column == 0 ? Text.AlignLeft : Text.AlignHCenter
				leftPadding: 8
			}
		}
	}
}