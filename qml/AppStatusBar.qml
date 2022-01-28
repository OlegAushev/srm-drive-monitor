import QtQuick.Controls 2.15


Label {
	text: "No CAN bus connection"
	function printMessage(message) {
		text = message;
	}
}

