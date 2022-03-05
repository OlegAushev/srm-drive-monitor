import QtQuick 2.11
import QtQuick.Controls 2.4


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

		Column{
			id: column
			padding: 16
			spacing: 16

			Label {
				id: label
				width: 200
				horizontalAlignment: Text.AlignHCenter
				text: "Watch request period (0..999ms)"
			}

			Rectangle {
				width: 200
				height: valueInput.implicitHeight
				anchors.horizontalCenter: parent.horizontalCenter
				color: "transparent"

				TextField {
					id: valueInput
					anchors.fill: parent
					horizontalAlignment: Qt.AlignHCenter
					verticalAlignment: Qt.AlignVCenter
					//placeholderText: "Watch request period (ms)"
					text: driveCanDataProcessor.watchPeriod()
					validator: IntValidator{ bottom: 0; top: 999; }
				}
			}

			Row {
				spacing: 16
				anchors.horizontalCenter: parent.horizontalCenter

				Button {
					text: "Ok"
					onClicked: {
						driveCanDataProcessor.setWatchPeriod(Number.fromLocaleString(Qt.locale("en_EN"), valueInput.text))
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