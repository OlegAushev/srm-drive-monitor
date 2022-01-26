import QtQuick.Controls 2.15 as C2


C2.Label {
	text: "No CAN bus connection"
	function print(message) {
		text = message;
	}
}

