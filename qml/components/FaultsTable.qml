import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import QtQuick.Controls.Material 2.1

import BasicDataTableModel 1.0


Item {
	id: root

	property string name
	property QtObject sourceTable
	property real tableWidth
	property real cellSpacing: 1
	property real rowHeight: 20

	property real defaultColumnWidth: tableWidth/2;

	property color tableHeaderColor: Material.accent
	property color columnHeaderColor: Material.primary
	property color rowAlternateColor: { Material.theme == Material.Light ? 
			Material.color(Material.Grey, Material.Shade300) : Material.color(Material.Grey, Material.Shade800) }
	

	function getColumnWidth(col)
	{
		switch (col) {
		case 0:
			return defaultColumnWidth+120+1;
		case 1:
			return defaultColumnWidth-120;
		default:
			return 0;
		}
	}


	width: tableWidth
	height: tableHeader.height + columnHeader.height + table.count * rowHeight - (table.count - 1)  

	Rectangle {
		id: tableHeader
		width: tableWidth
		anchors.top: root.top
		anchors.horizontalCenter: root.horizontalCenter
		anchors.topMargin: 0
		height: rowHeight
		color: tableHeaderColor

		Label {
			anchors.fill: parent			
			anchors.top: parent.top
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter
			text: name
		}
	}
	
	Row {
		id: columnHeader
		width: tableWidth
		height: rowHeight
		anchors.top: tableHeader.bottom
		anchors.horizontalCenter: root.horizontalCenter
		anchors.topMargin: 0
		spacing: -1

		Repeater {
			model: 2

			Rectangle {
				width: getColumnWidth(index)
				height: columnHeader.height
				color: columnHeaderColor
				border.color: Material.color(Material.Grey)

				Label {
					width: parent.width
					height: parent.height
					horizontalAlignment: Text.AlignHCenter
					verticalAlignment: Text.AlignVCenter
					text: table.model.headerData(index, Qt.Horizontal)
				}
			}
		}
	}

	ListView {
		id: table
		orientation: Qt.Vertical
		anchors.top: columnHeader.bottom
		anchors.bottom: root.bottom
		anchors.topMargin: -1
		
		model: BasicDataTableModel {
			table: sourceTable
		}

		spacing: -1
		delegate: RowLayout {
			spacing: -1

			Label {
				Layout.fillHeight: true
				Layout.fillWidth: true
				Layout.preferredHeight: rowHeight
				Layout.preferredWidth: getColumnWidth(0)
				background: Rectangle { 
					color: index % 2 == 0 ? "transparent" : rowAlternateColor
					border.color: Material.color(Material.Grey)
				}
				horizontalAlignment: Text.AlignHCenter
				verticalAlignment: Text.AlignVCenter
				text: model.Name
			}

			Label {
				Layout.fillHeight: true
				Layout.fillWidth: true
				Layout.preferredHeight: rowHeight
				Layout.preferredWidth: getColumnWidth(1)
				background: Rectangle {
					color: parent.text ? Material.color(Material.Red) : Material.color(Material.Green)
					border.color: Material.color(Material.Grey)
				}
				horizontalAlignment: Text.AlignHCenter
				verticalAlignment: Text.AlignVCenter
				text: model.State
			}
		}
	}












}