import QtQuick 2.15
import QtQuick.Controls 2.15

import BasicDataTableModel 1.0


Rectangle {
	property string name
	property QtObject sourceTable
	property real tableWidth
	property real cellSpacing: 1

	width: tableWidth
	height: tableName.height + header.height + cellSpacing + table.contentHeight

	border.color: "lightgrey"
	color: "lightgrey"

	Rectangle {
		id: tableName
		width: parent.width
		height: 20
		color: "#268bd2"

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
		anchors.topMargin: 0
		spacing: cellSpacing

		Repeater {
			model: 3

			Rectangle {
				width: (tableWidth - 2*cellSpacing)/3
				height: header.height
				color: "#cb4b16"

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
		anchors.fill: parent
		anchors.topMargin: tableName.height + header.height + cellSpacing
		columnSpacing: cellSpacing
		rowSpacing: cellSpacing
		interactive: false

		model : BasicDataTableModel {
			table: sourceTable
		}
		
		delegate: Rectangle {
			color: model.row % 2 == 0 ? "white" : "lightgrey"
			implicitWidth: (tableWidth - 2*cellSpacing)/3
			implicitHeight: text.implicitHeight

			Text{
				id: text
				text: model.display
				width: parent.width
				horizontalAlignment: Text.AlignHCenter
			}
		}
	}
}