import QtQuick.Controls 2.15 as C2


C2.MenuBar {
	C2.Menu {
		title: qsTr("App")

		C2.Action { text: qsTr("Device Name") }

		C2.Action { text: qsTr("Software Version") }

		C2.Action { text: qsTr("Software Build Configuration") }

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

		C2.Action { text: qsTr("Reset Faults") }

		C2.Action { text: qsTr("Calibrate Position Sensor") }
		
		C2.Action { text: qsTr("Invert Rotation Direction") }
	}
}
