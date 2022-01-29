import QtQuick 2.15 as Q2
import QtQuick.Controls 1.4 as C1


C1.TabView {
	C1.Tab {
		id: tabControl
		title: "Control"
		Q2.Column {
			padding : 4
			spacing: 4

			SpinboxAndSliderControl {
				name: "Speed"
				unit: " rpm"
				valueFrom: -8000
				valueTo: 8000
				sliderStep: 1000
				spinboxStep: 100
				onValueChanged: driveController.setSpeed(value)
			}

			SpinboxAndSliderControl {
				name: "Torque"
				unit: " %"
				valueFrom: -100
				valueTo: 100
				sliderStep: 20
				spinboxStep: 1
				spinboxDecimals: 2
				onValueChanged: driveController.setTorque(value)
			}

			SpinboxAndSliderControl {
				name: "Field Current"
				unit: " A"
				valueFrom: 0
				valueTo: 35
				sliderStep: 5
				spinboxStep: 1
				spinboxDecimals: 1
				onValueChanged: driveController.setFieldCurrent(value)
			}

			SpinboxAndSliderControl {
				name: "Gamma Correction"
				unit: " °"
				valueFrom: -180
				valueTo: 180
				sliderStep: 30
				spinboxStep: 1
				onValueChanged: driveController.setGammaCorrection(value)
			}
		}
		
	}
	
	C1.Tab {
		id: tabConfiguration
		title: "Configuration"
		Q2.Column {
			padding : 4
			DriveConfigControl {
				
			}
		}
	}
}
