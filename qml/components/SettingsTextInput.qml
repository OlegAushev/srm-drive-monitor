import QtQuick 2.11
import QtQuick.Controls 2.4


Item {
	id: root

	property string name
	property string unit
	property string parameterKey
	property real valueFrom
	property real valueTo
	property int decimals



	Label {
		id: label
		width: text.implicitWidth
		//height: 20
		anchors.left: root.left
		anchors.verticalCenter: root.verticalCenter
		anchors.margins: 4
		horizontalAlignment: Text.AlignHCenter
		text: unit ? name + ", " + unit : name
	}

	Rectangle {
		width: 100
		height: valueInput.implicitHeight
		anchors.right: root.right
		anchors.verticalCenter: root.verticalCenter
		anchors.margins: 4
		color: "transparent"

		TextField {
			id: valueInput
			anchors.fill: parent
			horizontalAlignment: Qt.AlignHCenter
			verticalAlignment: Qt.AlignVCenter
			placeholderText: "Enter value"
			validator: DoubleValidator {
				locale: "en_EN"
				bottom: valueFrom
				top: valueTo
			}

			text: appSettings.value(parameterKey)
			onAccepted: {
				appSettings.setValue(parameterKey, parseFloat(text));
				selectAll();
			}
		}
	}

}