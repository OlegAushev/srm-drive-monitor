import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11


Item {
	id: root

	property string name
	property string unit
	property string parameterKey
	property real valueFrom
	property real valueTo
	property int decimals

	RowLayout {
		anchors.fill: root
		
		Label {
			id: label
			Layout.alignment: Qt.AlignLeft
			Layout.preferredWidth: root.width * 0.75
			horizontalAlignment: Text.AlignLeft
			text: unit ? name + ", " + unit : name
		}

		TextField {
			id: field
			Layout.alignment: Qt.AlignRight
			Layout.preferredWidth: root.width * 0.25
			horizontalAlignment: Qt.AlignHCenter
			verticalAlignment: Qt.AlignVCenter
			placeholderText: "Enter value"
			validator: DoubleValidator {
				locale: "en_EN"
				bottom: valueFrom
				top: valueTo
			}

			text:  appSettings.value(parameterKey)
			onAccepted: {
				appSettings.setValue(parameterKey, parseFloat(text));
				selectAll();
			}
		}
	}
}