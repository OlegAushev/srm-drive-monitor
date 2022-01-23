import QtQuick 2.5
import QtQuick.Controls 2.15




ToolBar {
	anchors.left: parent.left
	anchors.right: parent.right

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

