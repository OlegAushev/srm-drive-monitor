import QtQuick 2.15
import QtQuick.Controls 2.15

import BasicDataTableModel 1.0


Rectangle {
	width: 500
	height: 500
	anchors.top: parent.top
	anchors.right: parent.right
	border.color: "black"

	Row {
		id: header
		width: 300
		height: 20
		spacing: 4
		Repeater {
			model: 3
			Rectangle {
				width: 100
				height: header.height
				color: "#007acc"
				Text {
					width: parent.width
					height: parent.height
					horizontalAlignment: Text.AlignHCenter
					text: table.model.headerData(index, Qt.Horizontal)
				}
			}
		}
	}

	TableView {
		id: table
		anchors.fill: parent
		anchors.topMargin: header.height + 4
		columnSpacing: 4
		rowSpacing: 4

		model : BasicDataTableModel {
			table: table1
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