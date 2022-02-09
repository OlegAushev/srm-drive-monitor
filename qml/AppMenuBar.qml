import QtQuick 2.11
import QtQuick.Controls 2.4


MenuBar {
	background: Rectangle { color: palette.window }

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
				onTriggered: mcoClient.connectCanDevice("can0");
			}
			MenuItem {
				text: "vcan0"
				onTriggered: mcoClient.connectCanDevice("vcan0");
			}
		}

		MenuItem {
			text: "Disconnect CAN Device"
			onTriggered: mcoClient.disconnectCanDevice();
		}

		Menu {
			title: "Watch Requests"

			MenuItem {
				implicitWidth: 100
				text: "Enable"
				checked: true
				checkable: true
				onTriggered: checked ? driveCanDataPrinter.startWatch() : driveCanDataPrinter.stopWatch()
			}

			MenuItem {
				implicitWidth: 100
				text: "Set Period"
				onTriggered: {
					watchSettingsWindow.show()
				}
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

	WatchSettingsWindow {
		id: watchSettingsWindow
		width: 300;
		height: 300;
	}
}
