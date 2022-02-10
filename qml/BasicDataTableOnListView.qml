import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11

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





	ListModel {
		id: listModel
		ListElement { name: 'item1'; code: "alpha"; language: "english" }
		ListElement { name: 'item2'; code: "beta"; language: "french" }
		ListElement { name: 'item3'; code: "long-code"; language: "long-language" }
	}

	ListView {
	
		orientation: Qt.Vertical
		anchors.fill: parent
		model: BasicDataTableModel {
			table: sourceTable
		}

		delegate: RowLayout {
			spacing: 0

			Label {
				Layout.fillHeight: true
				Layout.fillWidth: true
				Layout.preferredHeight: implicitHeight
				Layout.preferredWidth: defaultColumnWidth
				background: Rectangle { border.color: "red" }
				text: name
			}

			Label {
				Layout.fillHeight: true
				Layout.fillWidth: true
				Layout.preferredHeight: implicitHeight
				Layout.preferredWidth: defaultColumnWidth
				background: Rectangle { border.color: "green" }
				text: value
			}

			Label {
				Layout.fillHeight: true
				Layout.fillWidth: true
				Layout.preferredHeight: implicitHeight
				Layout.preferredWidth: defaultColumnWidth
				background: Rectangle { border.color: "blue" }
				text: unit
			}
		}
	}












}