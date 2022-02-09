import QtQuick 2.11
import QtQuick.Controls 2.4 as C2
import QtQuick.Controls 1.4 as C1


C1.TabView {

	SystemPalette { id: palette; colorGroup: SystemPalette.Active }

	C1.Tab {
		id: tabCanData
		title: "CAN Data"

		Row {
			padding: 2
			spacing: 8
			
			BasicDataTable_v11 {
				id: watchDataTable
				name: "Watch Data"
				sourceTable: driveCanDataPrinter.watchTable()
				tableWidth: 250
				tableHeight: 620
			}

			Column {
				id: columnTableText
				spacing: 8

				Row {
					spacing: 8
					BasicDataTable_v11 {
						id: tpdo1DataTable
						name: "TPDO1 Data"
						sourceTable: driveCanDataPrinter.tpdo1Table()
						tableWidth: 250
						tableHeight: 328
					}
					
					BasicDataTable_v11 {
						id: tpdo2DataTable
						name: "TPDO2 Data"
						sourceTable: driveCanDataPrinter.tpdo2Table()
						tableWidth: 250
						tableHeight: 328
					}

					Column {
						spacing: 8

						BasicDataTable_v11 {
							id: tpdo3DataTable
							name: "TPDO3 Data"
							sourceTable: driveCanDataPrinter.tpdo3Table()
							tableWidth: 250
							tableHeight: 160
						}

						BasicDataTable_v11 {
							id: tpdo4DataTable
							name: "TPDO4 Data"
							sourceTable: driveCanDataPrinter.tpdo4Table()
							tableWidth: 250
							tableHeight: 160
						}
					}
				}

				Rectangle {
					id: canMsgTextRect
					width: columnTableText.width
					height: watchDataTable.height - tpdo1DataTable.height - 8
					border.color: palette.mid

					C2.ScrollView {
						width: canMsgTextRect.width - 2
						height: canMsgTextRect.height - 2
						anchors.centerIn: parent
						C2.ScrollBar.vertical.policy: C2.ScrollBar.AlwaysOn
						background: Rectangle { color: palette.base }

						ListView {
							id: canMsgListView
							anchors.fill: parent
							model: driveCanDataPrinter.textMessages

							delegate: Rectangle {
								width: canMsgListView.width
								height: msg.height
								color: "transparent"

								Text {
									id: msg
									text: modelData
									horizontalAlignment: Qt.AlignLeft
									leftPadding: 4
									color: palette.text
								}
							}

							onCountChanged: {
								Qt.callLater( canMsgListView.positionViewAtEnd )
								
							}
						}
					}

					C2.Button {
						text: "Clear"
						width: text.implicitWidth
						height: text.implicitHeight
						anchors.bottom: parent.bottom
						anchors.right: parent.right
						anchors.bottomMargin: 4
						anchors.rightMargin: 24
						onClicked: driveCanDataPrinter.clearTextMessages()
					}
				}
			}
		}
	}
	
	C1.Tab {
		id: tabCharts
		title: "Charts"

		Charts {}
	}
}

