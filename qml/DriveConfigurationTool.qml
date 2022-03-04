import QtQuick 2.11
import QtQuick.Controls 2.4


Frame {
	id: root

	width: 320
	height: 400

	Column {
		anchors.horizontalCenter: parent.horizontalCenter
		padding: 16
		spacing: 16
		
		ComboBox {
			id: parameterCategory
			width: 200
			anchors.horizontalCenter: parent.horizontalCenter
			model: driveConfigEditor.parameterCategories()
		}

		ComboBox {
			id: parameterName
			width: 200
			anchors.horizontalCenter: parent.horizontalCenter
			model: driveConfigEditor.parameterNames(parameterCategory.currentText)
		}

		Rectangle {
			width: 200
			height: valueInput.implicitHeight
			anchors.horizontalCenter: parent.horizontalCenter
			color: "transparent"

			TextField {
				id: valueInput
				anchors.fill: parent
				horizontalAlignment: Qt.AlignHCenter
				verticalAlignment: Qt.AlignVCenter
				placeholderText: "Enter value"
				validator: DoubleValidator { locale: "en_EN"}
			}
		}

		Row {
			anchors.horizontalCenter: parameterName.horizontalCenter
			spacing: 16
			Button {
				id: readButton
				width: 92
				text: "Read"
				onClicked: {
					valueInput.clear();
					driveConfigEditor.readParameter(parameterCategory.currentText, parameterName.currentText);
				}
			}

			Button {
				id: writeButton
				width: 92
				text: "Write"
				onClicked: {
					driveConfigEditor.writeParameter(parameterCategory.currentText, parameterName.currentText, valueInput.displayText);
					valueInput.clear();
				}
			}
		}

		Button {
			id: applyButton
			text: "Apply"
			width: 200
			anchors.horizontalCenter: parent.horizontalCenter
			onClicked: {
				valueInput.clear();
				driveConfigEditor.applyParameters();
			}
		}

		Button {
			id: resetButton
			text: "Reset To Default"
			width: 200
			anchors.horizontalCenter: parent.horizontalCenter
			onClicked: {
				valueInput.clear();
				driveConfigEditor.resetParameters();
			}
		}
	}
}