import QtQuick 2.15 as Q2
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15// as Layouts


ToolBar {
	RowLayout {
		ToolButton {
			id: buttonTlcEmulation
			checkable: true
			icon.name: "qrc:/images/desktop-classic.png"
			ToolTip.visible: hovered
			ToolTip.text: qsTr("TLC Emulation On/Off")
		}

		ToolButton {
			id: buttonPower
			checkable: true
			icon.name: "qrc:/images/car-electric-outline.png"
			ToolTip.visible: hovered
			ToolTip.text: qsTr("Power On/Off")
		}

		ToolButton {
			id: buttonMotorRun
			checkable: true
			icon.name: "qrc:/images/power.png"
			ToolTip.visible: hovered
			ToolTip.text: qsTr("Motor Run On/Off")
		}

		ToolButton {
			id: buttonEmergency
			checkable: true
			icon.name: "qrc:/images/alert-octagon-outline.png"
			ToolTip.visible: hovered
			ToolTip.text: qsTr("Emergency On/Off")
		}
	}

}

