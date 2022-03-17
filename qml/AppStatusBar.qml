import QtQuick 2.11
import QtQuick.Controls 2.4


Label {
	id: statusLabel
	padding: 2
	text: "No CAN bus connection"

	Connections {
		target: mcoClient
		/*function onInfoMessageAvailable(message) {
			text = message;		// new syntax
		}*/
		onInfoMessageAvailable: {
			statusLabel.text = message;		// deprecated syntax for 5.11 compatibility
		}
	}
}

