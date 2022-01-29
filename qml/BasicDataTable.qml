import QtQuick 2.15
import QtQuick.Controls 2.15

import BasicDataTableModel 1.0


Rectangle {
	property string name
	property QtObject sourceTable

	width: 308
	height: 200
	border.color: "black"

	Rectangle {
		id: tableName
		width: parent.width
		height: 30
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
		width: 300
		height: 20
		anchors.top: tableName.bottom
		anchors.topMargin: 4
		spacing: 4

		Repeater {
			model: 3

			Rectangle {
				width: 100
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
		anchors.topMargin: tableName.height + header.height + 4 + 4
		columnSpacing: 4
		rowSpacing: 4

		model : BasicDataTableModel {
			table: sourceTable
		}
		
		delegate: Rectangle {
			color: "#EEE"
			implicitWidth: 100
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