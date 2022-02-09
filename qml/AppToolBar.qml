import QtQuick 2.11
import QtQuick.Controls 2.4


ToolBar {
	SystemPalette { id: palette; colorGroup: SystemPalette.Active }
	background: Rectangle { color: palette.window }

	Row {
		ToolButton {
			id: buttonTlcEmulation
			checkable: true
			icon.source: "qrc:/images/desktop-classic.png"
			ToolTip.visible: hovered
			ToolTip.text: "TLC Emulation On/Off"
			onClicked: checked ? mcoClient.startTpdoSending() : mcoClient.stopTpdoSending()
		}

		ToolButton {
			id: buttonPower
			checkable: true
			icon.source: "qrc:/images/car-electric-outline.png"
			ToolTip.visible: hovered
			ToolTip.text: "Power On/Off"
			onClicked: checked ? driveController.powerUpDrive() : driveController.powerDownDrive()
		}

		ToolButton {
			id: buttonMotorRun
			checkable: true
			icon.source: "qrc:/images/power.png"
			ToolTip.visible: hovered
			ToolTip.text: "Motor Run On/Off"
			onClicked: checked ? driveController.startMotor() : driveController.stopMotor()
		}

		ToolButton {
			id: buttonEmergency
			checkable: true
			icon.source: "qrc:/images/alert-octagon-outline.png"
			ToolTip.visible: hovered
			ToolTip.text: "Emergency On/Off"
			onClicked: checked ? driveController.setEmergencyOn() : driveController.setEmergencyOff() 
		}
	}

}

