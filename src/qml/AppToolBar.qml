import QtQuick 2.5
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15


ToolBar {
	Action {
		id: actionConnectCanDevice
		text: qsTr("&Connect CAN")
		icon.name: "qrc:/resources/icons/link-variant.png"
	}

	Action {
		id: actionDisconnectCanDevice
		text: qsTr("&Disconnect CAN")
		icon.name: "qrc:/resources/icons/link-variant-off.png"
	}

	Action {
		id: actionQuit
		text: qsTr("&Quit")
		icon.name: "qrc:/resources/icons/exit-to-app.png"
	}

	 
	RowLayout {
		ToolButton {
		id: buttonConnectCanDevice
		action: actionConnectCanDevice
		}

		ToolButton {
			id: buttonDisconnectCanDevice
			action: actionDisconnectCanDevice
		}

		ToolButton {
			id: buttonQuit
			action: actionQuit
		}
	}

}

