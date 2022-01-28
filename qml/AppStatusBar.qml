import QtQuick.Controls 2.15


Label {
	text: "No CAN bus connection"
	function print(message) {
		text = message;
	}
}

