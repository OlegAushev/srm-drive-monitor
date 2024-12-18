import QtQuick 2.11
import QtQuick.Controls 2.4
import "components"


Item {
	Row {
		padding: 2
		spacing: 8
		
		CanDataTable {
			id: watchDataTable
			name: "Watch"
			sourceTable: driveCanDataProcessor.watchTable()
			tableWidth: 240
		}

		Column {
			id: columnTableText
			spacing: 8

			Row {
				spacing: 8
				CanDataTable {
					id: tpdo1DataTable
					name: "TPDO1"
					sourceTable: driveCanDataProcessor.tpdo1Table()
					tableWidth: 240
				}
				
				CanDataTable {
					id: tpdo2DataTable
					name: "TPDO2"
					sourceTable: driveCanDataProcessor.tpdo2Table()
					tableWidth: 240
				}

				Column {
					spacing: 8

					CanDataTable {
						id: tpdo3DataTable
						name: "TPDO3"
						sourceTable: driveCanDataProcessor.tpdo3Table()
						tableWidth: 240
					}

					CanDataTable {
						id: tpdo4DataTable
						name: "TPDO4"
						sourceTable: driveCanDataProcessor.tpdo4Table()
						tableWidth: 240
					}
				}
			}

			Frame {
				padding: 0
				implicitWidth: columnTableText.width//canMsgTextRect.width
				implicitHeight: watchDataTable.height - tpdo1DataTable.height - 8//canMsgTextRect.height

				Item {
					anchors.fill: parent
												
					ScrollView {
						anchors.fill: parent
						anchors.margins: 1
						ScrollBar.vertical.policy: ScrollBar.AlwaysOn
						
						ListView {
							id: canMsgListView
							anchors.fill: parent
							anchors.margins: 8
							model: driveCanDataProcessor.textMessages

							delegate: Rectangle {
								width: canMsgListView.width
								height: msg.height
								color: "transparent"

								Text {
									id: msg
									text: modelData
									horizontalAlignment: Qt.AlignLeft
									leftPadding: 4
									font.family: "Monospace"
								}
							}

							onCountChanged: {
								Qt.callLater( canMsgListView.positionViewAtEnd )
							}
						}
					}

					Button {
						text: "Clear"
						width: text.implicitWidth
						height: text.implicitHeight
						anchors.bottom: parent.bottom
						anchors.right: parent.right
						anchors.bottomMargin: 4
						anchors.rightMargin: 24
						onClicked: driveCanDataProcessor.clearTextMessages()
					}
				}
			}
		}
	}
}