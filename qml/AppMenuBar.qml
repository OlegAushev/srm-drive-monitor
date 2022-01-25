import QtQuick 2.5
import QtQuick.Controls 2.15


MenuBar {
	Menu {
		title: qsTr("App")

		Action { text: qsTr("Device Name") }

		Action { text: qsTr("Software Version") }

		Action { text: qsTr("Software Build Configuration") }

		MenuSeparator { }

		Action {
			text: qsTr("Quit")
			onTriggered: Qt.quit();
		}
	}

	Menu {
		title: qsTr("Network")

		Menu {
			title: qsTr("Connect CAN Device")
			Action {
				text: qsTr("can0")
				onTriggered: canBusDevice.connectDevice("socketcan", "can0");
			}
			Action {
				text: qsTr("vcan0")
				onTriggered: canBusDevice.connectDevice("socketcan", "vcan0");
			}
		}

		Action {
			text: qsTr("Disconnect CAN Device")
			onTriggered: canBusDevice.disconnectDevice();
		}
	}

	Menu {
		title: qsTr("Drive Control")

		Action { text: qsTr("Reset Faults") }

		Action { text: qsTr("Calibrate Position Sensor") }
		
		Action { text: qsTr("Invert Rotation Direction") }
	}
}
