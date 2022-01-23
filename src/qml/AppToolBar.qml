import QtQuick 2.5
import QtQuick.Controls 2.15


ToolBar {
	Action {
		id: actionExit
		text: qsTr("&Exit")
		icon.name: "qrc:/resources/icons/exit-to-app.png"
	}

	ToolButton {
		id: buttonExit
		action: actionExit
	}
}

