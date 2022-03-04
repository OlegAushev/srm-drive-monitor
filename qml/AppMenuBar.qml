import QtQuick 2.11
import QtQuick.Controls 2.4


MenuBar {

	Menu {
		title: "App"
		width: menu1LongItem.width

		MenuItem {
			text: "Device Name"
			onTriggered: driveController.getDeviceName() 
		}

		MenuItem { 
			text: "Software Version"
			onTriggered: driveController.getSoftwareVersion() 
		}

		MenuItem {
			id: menu1LongItem
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
		width: menu2LongItem.width
		
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
			id: menu2LongItem
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
		width: menu3LongItem.width

		MenuItem {
			text: "Reset Faults"
			onTriggered: driveController.resetFaults() 
		}

		MenuItem {
			id: menu3LongItem
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
