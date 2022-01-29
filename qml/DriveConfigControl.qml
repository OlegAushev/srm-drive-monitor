import QtQuick 2.15
import QtQuick.Controls 2.15


Rectangle {
	id: root

	width: 320
	height: 400
	border.color: "black"

	Column {
		anchors.fill: root
		anchors.topMargin: 16
		padding: 16
		spacing: 16
		ComboBox {
			id: parameterCategory
			anchors.horizontalCenter: parent.horizontalCenter
			model: ["First", "Second", "Third"]
		}

		ComboBox {
			id: parameterName
			anchors.horizontalCenter: parent.horizontalCenter
			model: listlist
		}

		Row {
			anchors.horizontalCenter: parameterName.horizontalCenter
			spacing: 16
			Button {
				id: readButton
				text: "Read"
			}

			Button {
				id: writeButton
				text: "Write"
			}
		}

		Button {
			id: applyButton
			text: "Apply"
			width: 160
			anchors.horizontalCenter: parent.horizontalCenter
		}

		Button {
			id: resetButton
			text: "Reset To Default"
			width: 160
			anchors.horizontalCenter: parent.horizontalCenter
		}
	}
}