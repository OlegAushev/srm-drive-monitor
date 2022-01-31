import QtQuick 2.15
import QtQuick.Controls 2.15

import BasicDataTableModel 1.0


Rectangle {
	property string name
	property QtObject sourceTable
	property real tableWidth
	property real cellSpacing: 1

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
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.topMargin: cellSpacing
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
		width: tableWidth
		//anchors.fill: parent
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