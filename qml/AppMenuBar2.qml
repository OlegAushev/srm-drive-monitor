import QtQuick 2.15
import QtQuick.Controls 1.4

Item{
MenuBar {
	//width: parent.width
	Menu {
		title: "App"

		/*MenuItem { 
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
		}*/
	}

	Menu {
		title: "Network"
		
		/*Menu {
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
		}*/

		//MenuItem {
			//CheckBox {
			//text: qsTr("Watch Requests")
			//}
		//}
	}

	Menu {
		title: "Drive Control"

		/*MenuItem {
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
		}*/
	}

	Menu {
		title: "Test"

		/*CheckBox {
			text: "aaa"
		}*/
		/*MenuItem {
			text: "Test menu"
			checkable: true
		}*/
		
	}
}
}