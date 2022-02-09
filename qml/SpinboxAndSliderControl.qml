import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls 1.4 as C1


Rectangle {
	id: root

	property string name
	property string unit
	property real valueFrom
	property real valueTo
	property real sliderStep
	property real spinboxStep
	property int spinboxDecimals

	signal valueChanged(real value)

	SystemPalette { id: palette; colorGroup: SystemPalette.Active }

	width: 320
	height: 80
	border.color: palette.mid 
	color: palette.window

	Text {
		id: label
		width: parent.width
		height: 20
		anchors.top: parent.top
		anchors.topMargin: 2
		horizontalAlignment: Text.AlignHCenter
		text: name
		color: palette.windowText
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