import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls 1.4 as C1
import QtQuick.Controls.Styles 1.4


Frame {
	id: root

	property string name
	property string unit
	property real valueFrom
	property real valueTo
	property real sliderStep
	property real spinboxStep
	property int spinboxDecimals

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
				text: name
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

		C1.SpinBox {
			id: spinbox
			//style: SpinBoxStyle {}
			width: 100
			anchors.left: parent.left
			anchors.verticalCenter: parent.verticalCenter
			anchors.leftMargin: 4

			minimumValue: valueFrom
			maximumValue: valueTo
			stepSize: spinboxStep
			decimals: spinboxDecimals
			suffix: unit

			value: slider.value
			onEditingFinished: { slider.value = value; root.valueChanged(value) }
		}
	}
}