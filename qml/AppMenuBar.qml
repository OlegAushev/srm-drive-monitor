import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Dialogs 1.3
import "settings"


MenuBar {
	id: root

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

		MenuSeparator {}
		
		MenuItem {
			text: "Settings"
			onTriggered: {
				var component = Qt.createComponent("settings/MainSettingsWindow.qml");
				var window = component.createObject(root);
				window.show();
			}
		}
		
		MenuSeparator {}

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
				onTriggered: checked ? driveCanDataProcessor.startWatch() : driveCanDataProcessor.stopWatch()
			}

			MenuItem {
				implicitWidth: 100
				text: "Set Period"
				onTriggered: {
					var component = Qt.createComponent("settings/WatchSettingsWindow.qml");
					var window = component.createObject(root);
					window.show();
				}
			}
		}
	}

	Menu {
		title: "Drive"
		width: menu3LongItem.width

		MenuItem {
			text: "Reset Faults"
			onTriggered: driveController.resetFaults() 
		}

		MenuItem {
			id: menu3LongItem
			text: "Calibrate Position Sensor"
			onTriggered: calibrateDialog.open()

			MessageDialog {
				id: calibrateDialog
				icon: StandardIcon.Warning
				title: "Warning!"
				text: "The calibration procedure is about to begin.\nMake sure that the driving wheels DO NOT touch the ground!\nContinue?"
				standardButtons: StandardButton.Yes | StandardButton.No
				onYes: driveController.calibratePositionSensor();
			}
		}
		
		MenuItem {
			text: "Invert Rotation Direction"
			onTriggered: invertDialog.open()

			MessageDialog {
				id: invertDialog
				icon: StandardIcon.Warning
				title: "Warning!"
				text: "The default direction of rotation will be changed.\nContinue?"
				standardButtons: StandardButton.Yes | StandardButton.No
				onYes: driveController.invertRotationDirection()
			}
		}

		Menu {
			title: "Set Reference"
			
			MenuItem {
				text: "Speed"
				onTriggered: {
					driveConfigEditor.writeParameter("MODEL", "REFERENCE", 0);
					driveConfigEditor.applyParameters();
				}
			}

			MenuItem {
				text: "Torque"
				onTriggered: {
					driveConfigEditor.writeParameter("MODEL", "REFERENCE", 1);
					driveConfigEditor.applyParameters();
				}
			}
		}

		MenuSeparator { }

		MenuItem {
			text: "Reset Device"
			onTriggered: driveController.resetDevice()
		}
	}
}
