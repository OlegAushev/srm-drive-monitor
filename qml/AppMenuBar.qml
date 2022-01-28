import QtQuick.Controls 2.15 as C2


C2.MenuBar {
	C2.Menu {
		title: qsTr("App")

		C2.Action { 
			text: qsTr("Device Name")
			onTriggered: driveController.getDeviceName() 
		}

		C2.Action { 
			text: qsTr("Software Version")
			onTriggered: driveController.getSoftwareVersion() 
		}

		C2.Action { 
			text: qsTr("Software Build Configuration")
			onTriggered: driveController.getBuildConfiguration() 
		}

		C2.MenuSeparator { }

		C2.Action {
			text: qsTr("Quit")
			onTriggered: Qt.quit();
		}
	}

	C2.Menu {
		title: qsTr("Network")

		C2.Menu {
			title: qsTr("Connect CAN Device")
			C2.Action {
				text: qsTr("can0")
				onTriggered: mcoClient.connectCanDevice("socketcan", "can0");
			}
			C2.Action {
				text: qsTr("vcan0")
				onTriggered: mcoClient.connectCanDevice("socketcan", "vcan0");
			}
		}

		C2.Action {
			text: qsTr("Disconnect CAN Device")
			onTriggered: mcoClient.disconnectCanDevice();
		}
	}

	C2.Menu {
		title: qsTr("Drive Control")

		C2.Action {
			text: qsTr("Reset Faults")
			onTriggered: driveController.resetFaults() 
		}

		C2.Action {
			text: qsTr("Calibrate Position Sensor")
			onTriggered: driveController.calibratePositionSensor() 
		}
		
		C2.Action {
			text: qsTr("Invert Rotation Direction")
			onTriggered: driveController.invertRotationDirection() 
		}
	}
}
