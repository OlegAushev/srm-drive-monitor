import QtQuick.Controls 2.15


MenuBar {
	width: parent.width
	Menu {
		title: qsTr("App")

		MenuItem { 
			text: qsTr("Device Name")
			onTriggered: driveController.getDeviceName() 
		}

		MenuItem { 
			text: qsTr("Software Version")
			onTriggered: driveController.getSoftwareVersion() 
		}

		MenuItem { 
			text: qsTr("Software Build Configuration")
			onTriggered: driveController.getBuildConfiguration() 
		}

		MenuSeparator { }

		MenuItem {
			text: qsTr("Quit")
			onTriggered: Qt.quit();
		}
	}

	Menu {
		title: qsTr("Network")

		Menu {
			title: qsTr("Connect CAN Device")
			
			MenuItem {
				text: qsTr("can0")
				onTriggered: mcoClient.connectCanDevice("socketcan", "can0");
			}
			MenuItem {
				text: qsTr("vcan0")
				onTriggered: mcoClient.connectCanDevice("socketcan", "vcan0");
			}
		}

		MenuItem {
			text: qsTr("Disconnect CAN Device")
			onTriggered: mcoClient.disconnectCanDevice();
		}
	}

	Menu {
		title: qsTr("Drive Control")

		MenuItem {
			text: qsTr("Reset Faults")
			onTriggered: driveController.resetFaults() 
		}

		MenuItem {
			text: qsTr("Calibrate Position Sensor")
			onTriggered: driveController.calibratePositionSensor() 
		}
		
		MenuItem {
			text: qsTr("Invert Rotation Direction")
			onTriggered: driveController.invertRotationDirection() 
		}
	}
}
