import QtQuick.Controls 2.15


Label {
	text: "Read Only"
	function print(message) {
		text = message;
	}
}

