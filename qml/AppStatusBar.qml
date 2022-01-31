import QtQuick 2.15
import QtQuick.Controls 2.15


Label {
	text: "No CAN bus connection"
		Connections {
		target: mcoClient
		function onInfoMessageAvailable(message) {
			text = message;
		}
	}
}

