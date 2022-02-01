import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15


ToolBar {
	RowLayout {
		ToolButton {
			id: buttonTlcEmulation
			checkable: true
			icon.name: "qrc:/images/desktop-classic.png"
			ToolTip.visible: hovered
			ToolTip.text: "TLC Emulation On/Off"
			onClicked: checked ? mcoClient.startTpdoSending() : mcoClient.stopTpdoSending()
		}

		ToolButton {
			id: buttonPower
			checkable: true
			icon.name: "qrc:/images/car-electric-outline.png"
			ToolTip.visible: hovered
			ToolTip.text: "Power On/Off"
			onClicked: checked ? driveController.powerUpDrive() : driveController.powerDownDrive()
		}

		ToolButton {
			id: buttonMotorRun
			checkable: true
			icon.name: "qrc:/images/power.png"
			ToolTip.visible: hovered
			ToolTip.text: "Motor Run On/Off"
			onClicked: checked ? driveController.startMotor() : driveController.stopMotor()
		}

		ToolButton {
			id: buttonEmergency
			checkable: true
			icon.name: "qrc:/images/alert-octagon-outline.png"
			ToolTip.visible: hovered
			ToolTip.text: "Emergency On/Off"
			onClicked: checked? driveController.setEmergencyOn() : driveController.setEmergencyOff() 
		}
	}

}

