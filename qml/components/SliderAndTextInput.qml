import QtQuick 2.11
import QtQuick.Controls 2.4


Frame {
	id: root

	property string name
	property string unit
	property real valueFrom
	property real valueTo
	property real sliderStep
	property int decimals

	signal valueChanged(real value)

	padding: 0

	Item {
		width: 320
		height: 80
		implicitWidth: 320
		implicitHeight: 80
		anchors.fill: parent

		Item {
			width: parent.width
			height: label.implicitHeight
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.top: parent.top
			anchors.topMargin: 4

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
			width: 200
			anchors.right: parent.right
			anchors.verticalCenter: parent.verticalCenter
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
			anchors.left: parent.left
			anchors.verticalCenter: parent.verticalCenter
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
                		}
			}
		}
	}
}