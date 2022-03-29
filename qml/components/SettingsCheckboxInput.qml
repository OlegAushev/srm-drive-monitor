import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11


Item {
	id: root

	property string name
	property string parameterKey

	RowLayout {
		anchors.fill: root
		
		Label {
			id: label
			width: text.implicitWidth
			Layout.alignment: Qt.AlignLeft
			Layout.preferredWidth: root.width * 0.75
			horizontalAlignment: Text.AlignLeft
			text: name
		}

		CheckBox {
			id: checkbox
			Layout.alignment: Qt.AlignHCenter
			Layout.preferredWidth: root.width * 0.25
			checked: appSettings.value(parameterKey)

			onClicked: {
				appSettings.setValue(parameterKey, checked)
			}
		}
	}



}
