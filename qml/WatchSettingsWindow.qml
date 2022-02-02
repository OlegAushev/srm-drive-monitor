import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15


ApplicationWindow {
	id: root
	minimumWidth: 240
	minimumHeight: 160
	maximumHeight: minimumHeight
	maximumWidth: minimumWidth
	Rectangle {
		id: frame
		width: root.width - 2
		height: root.height - 2
		anchors.centerIn: parent
		color: "#eff0f1"
		border.color: "lightgrey"

		Column{
			id: column
			anchors.fill: root
			padding: 16
			spacing: 16

			Text {
				id: label
				width: 200
				height: 20
				horizontalAlignment: Text.AlignHCenter
				text: "Watch request period (0..999ms)"
			}

			Rectangle {
				width: 200
				height: 32
				anchors.horizontalCenter: parent.horizontalCenter
				TextField {
					id: valueInput
					anchors.fill: parent
					horizontalAlignment: Qt.AlignHCenter
					verticalAlignment: Qt.AlignVCenter
					//placeholderText: "Watch request period (ms)"
					text: driveCanDataPrinter.watchPeriod()
					validator: IntValidator{ bottom: 0; top: 999; }
				}
			}

			Row {
				spacing: 16
				anchors.horizontalCenter: parent.horizontalCenter

				Button {
					text: "Ok"
					onClicked: {
						driveCanDataPrinter.setWatchPeriod(Number.fromLocaleString(Qt.locale("en_EN"), valueInput.text))
						root.close()
					}
				}

				Button {
					text: "Cancel"
					onClicked: root.close()
				}
			}
		}
	}
}