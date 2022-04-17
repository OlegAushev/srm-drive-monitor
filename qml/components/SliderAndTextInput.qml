import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.1
import QtQuick.Extras 1.4


Rectangle {
	id: root

	property string name
	property string unit
	property real valueFrom
	property real valueTo
	property real sliderStep
	property int decimals
	property bool active: false

	signal valueChanged(real value)

	width: 280
	height: 100
	color: "transparent"
	border.color: Material.color(Material.Grey)

	StatusIndicator {
		id: statusIndicator
		active: root.active
		color: "green"
		anchors.top: root.top
		anchors.right: root.right
		anchors.topMargin: -6
		anchors.rightMargin: 4
		width: 16
	}

	Rectangle {
		width: label.implicitWidth
		height: label.implicitHeight
		anchors.horizontalCenter: root.horizontalCenter
		anchors.top: root.top
		anchors.topMargin: 4
		color: "transparent"

		Label {
			id: label
			width: parent.width
			height: 20
			horizontalAlignment: Text.AlignHCenter
			text: name + ", " + unit
		}
	}

	Slider {
		id: slider
		width: 160
		anchors.right: root.right
		anchors.verticalCenter: root.verticalCenter
		anchors.rightMargin: 4

		from: valueFrom
		to: valueTo
		stepSize: sliderStep
		snapMode: Slider.NoSnap

		onMoved: { root.valueChanged(value) }		
	}

	Rectangle {
		width: 100
		height: valueInput.implicitHeight
		anchors.left: root.left
		anchors.verticalCenter: root.verticalCenter
		anchors.leftMargin: 4
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

			text: slider.value.toLocaleString(Qt.locale("en_EN"), 'f', decimals)

			onAccepted: {
				slider.value = parseFloat(text);
				root.valueChanged(slider.value)
				selectAll();
			}
		}
	}
}