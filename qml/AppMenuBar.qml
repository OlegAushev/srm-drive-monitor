import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQml 2.15


MenuBar {
	//width: parent.width
	Menu {
		title: "App"

		MenuItem { 
			text: "Device Name"
			onTriggered: driveController.getDeviceName() 
		}

		MenuItem { 
			text: "Software Version"
			onTriggered: driveController.getSoftwareVersion() 
		}

		MenuItem { 
			text: "Software Build Configuration"
			onTriggered: driveController.getBuildConfiguration() 
		}

		MenuSeparator { }

		MenuItem {
			text: "Quit"
			onTriggered: Qt.quit();
		}
	}

	Menu {
		title: "Network"
		
		Menu {
			title: "Connect CAN Device"
			
			MenuItem {
				text: "can0"
				onTriggered: mcoClient.connectCanDevice("socketcan", "can0");
			}
			MenuItem {
				text: "vcan0"
				onTriggered: mcoClient.connectCanDevice("socketcan", "vcan0");
			}
		}

		MenuItem {
			text: "Disconnect CAN Device"
			onTriggered: mcoClient.disconnectCanDevice();
		}

		Menu {
			title: "Watch Requests"

			MenuItem {
				text: "Enable"
				checked: true
				checkable: true
				onTriggered: checked ? driveCanDataPrinter.startWatch() : driveCanDataPrinter.stopWatch()
			}

			MenuItem {
				text: "Set Period"
				//onTriggered: 
			}
		}
	}

	Menu {
		title: "Drive Control"

		MenuItem {
			text: "Reset Faults"
			onTriggered: driveController.resetFaults() 
		}

		MenuItem {
			text: "Calibrate Position Sensor"
			onTriggered: driveController.calibratePositionSensor() 
		}
		
		MenuItem {
			text: "Invert Rotation Direction"
			onTriggered: driveController.invertRotationDirection() 
		}

		MenuSeparator { }

		MenuItem {
			text: "Reset Device"
			onTriggered: driveController.resetDevice()
		}
	}
}
