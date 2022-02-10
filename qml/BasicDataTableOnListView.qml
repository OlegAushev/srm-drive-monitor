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

	property real defaultColumnWidth: tableWidth/3;

	width: tableWidth
	height: tableHeader.height + columnHeader.height + table.count * 24

	Rectangle {
		id: tableHeader
		width: tableWidth
		anchors.top: root.top
		anchors.horizontalCenter: root.horizontalCenter
		anchors.topMargin: 0
		height: 20
		color: Material.color(Material.DeepOrange)

		Text {
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
		height: 20
		anchors.top: tableHeader.bottom
		anchors.horizontalCenter: root.horizontalCenter
		anchors.topMargin: 0
		spacing: 0

		Repeater {
			model: 3

			Rectangle {
				width: defaultColumnWidth
				height: columnHeader.height
				color: Material.color(Material.Blue)

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

	ListView {
		id: table
		orientation: Qt.Vertical
		anchors.top: columnHeader.bottom
		anchors.bottom: root.bottom
		
		model: BasicDataTableModel {
			table: sourceTable
		}

		spacing: -1
		delegate: RowLayout {
			spacing: -1

			Label {
				Layout.fillHeight: true
				Layout.fillWidth: true
				Layout.preferredHeight: 24
				Layout.preferredWidth: defaultColumnWidth+1
				background: Rectangle { color: "transparent"; border.color: Material.color(Material.Grey) }
				horizontalAlignment: Text.AlignHCenter
				verticalAlignment: Text.AlignVCenter
				text: name
			}

			Label {
				Layout.fillHeight: true
				Layout.fillWidth: true
				Layout.preferredHeight: 24
				Layout.preferredWidth: defaultColumnWidth+1
				background: Rectangle { color: "transparent"; border.color: Material.color(Material.Grey) }
				horizontalAlignment: Text.AlignHCenter
				verticalAlignment: Text.AlignVCenter
				text: value
			}

			Label {
				Layout.fillHeight: true
				Layout.fillWidth: true
				Layout.preferredHeight: 24
				Layout.preferredWidth: defaultColumnWidth
				background: Rectangle { color: "transparent"; border.color: Material.color(Material.Grey) }
				horizontalAlignment: Text.AlignHCenter
				verticalAlignment: Text.AlignVCenter
				text: unit
			}
		}
	}












}