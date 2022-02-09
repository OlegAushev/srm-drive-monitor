import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11

Item{

	TabBar {
		id: tabbar
		TabButton {
			text: "Control"
		}

		TabButton {
			text: "Configuration"
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

				SpinboxAndSliderControl {
					name: "Speed"
					unit: " rpm"
					valueFrom: -8000
					valueTo: 8000
					sliderStep: 100
					spinboxStep: 100
					onValueChanged: driveController.setSpeed(value)
				}

				SpinboxAndSliderControl {
					name: "Torque"
					unit: " %"
					valueFrom: -100
					valueTo: 100
					sliderStep: 1
					spinboxStep: 1
					spinboxDecimals: 2
					onValueChanged: driveController.setTorque(value)
				}

				SpinboxAndSliderControl {
					name: "Field Current"
					unit: " A"
					valueFrom: 0
					valueTo: 35
					sliderStep: 1
					spinboxStep: 1
					spinboxDecimals: 1
					onValueChanged: driveController.setFieldCurrent(value)
				}

				SpinboxAndSliderControl {
					name: "Gamma Correction"
					unit: " °"
					valueFrom: -180
					valueTo: 180
					sliderStep: 1
					spinboxStep: 1
					onValueChanged: driveController.setGammaCorrection(value)
				}
			}
		}

		Item {
			id: tabConfiguration
			Column {
				padding : 4
				DriveConfigurationTool {
					
				}
			}
		}
	}
}

