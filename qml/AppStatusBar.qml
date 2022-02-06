import QtQuick 2.11
import QtQuick.Controls 2.4


Label {
	text: "No CAN bus connection"
		Connections {
		target: mcoClient
		function onInfoMessageAvailable(message) {
			text = message;
		}
	}
}

