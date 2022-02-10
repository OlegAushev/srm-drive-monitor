import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11

Item{

	TabBar {
		id: tabbar
		TabButton {
			text: "Control"
			width: implicitWidth
		}

		TabButton {
			text: "Configuration"
			width: implicitWidth
		}
	}

	StackLayout {
		anchors.top: tabbar.bottom
		currentIndex: tabbar.currentIndex
		Item {
			id: tabControl
			Column {
				padding : 4
				spacing: 4

				SliderAndTextInput {
					name: "Speed"
					unit: "rpm"
					valueFrom: -8000
					valueTo: 8000
					sliderStep: 100
					onValueChanged: driveController.setSpeed(value)
				}

				SliderAndTextInput {
					name: "Torque"
					unit: "%"
					valueFrom: -100
					valueTo: 100
					sliderStep: 1
					decimals: 2
					onValueChanged: driveController.setTorque(value)
				}

				SliderAndTextInput {
					name: "Field Current"
					unit: "A"
					valueFrom: 0
					valueTo: 35
					sliderStep: 0.1
					decimals: 1
					onValueChanged: driveController.setFieldCurrent(value)
				}

				SliderAndTextInput {
					name: "Gamma Correction"
					unit: "°"
					valueFrom: -180
					valueTo: 180
					sliderStep: 1
					onValueChanged: driveController.setGammaCorrection(value)
				}
			}
		}

		Item {
			id: tabConfiguration
			Column {
				padding : 4
				DriveConfigurationTool {}
			}
		}
	}
}

