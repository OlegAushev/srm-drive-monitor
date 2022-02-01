import QtQuick.Controls 1.4 as C1
import QtQuick 2.15  as Q2
import QtQuick.Controls 2.15 as C2
import QtQuick.Layouts 1.15


C1.TabView {
	C1.Tab {
		id: tabCanData
		title: "CAN Data"

		Q2.Row {
			padding: 2
			spacing: 8
			
			BasicDataTable {
				id: watchDataTable
				name: "Watch Data"
				sourceTable: driveCanDataPrinter.watchTable()
				tableWidth: 250
			}

			Q2.Column {
				id: columnTableText
				spacing: 8

				Q2.Row {
					spacing: 8
					BasicDataTable {
						id: tpdo1DataTable
						name: "TPDO1 Data"
						sourceTable: driveCanDataPrinter.tpdo1Table()
						tableWidth: 250
					}
					
					BasicDataTable {
						id: tpdo2DataTable
						name: "TPDO2 Data"
						sourceTable: driveCanDataPrinter.tpdo2Table()
						tableWidth: 250
					}

					Q2.Column {
						spacing: 8

						BasicDataTable {
							id: tpdo3DataTable
							name: "TPDO3 Data"
							sourceTable: driveCanDataPrinter.tpdo3Table()
							tableWidth: 250
						}

						BasicDataTable {
							id: tpdo4DataTable
							name: "TPDO4 Data"
							sourceTable: driveCanDataPrinter.tpdo4Table()
							tableWidth: 250
						}
					}
				}

				Q2.Rectangle {
					id: canMsgTextRect
					width: columnTableText.width
					height: watchDataTable.height - tpdo1DataTable.height - 8
					border.color: "lightgrey"

					C2.ScrollView {
						anchors.fill: parent
						C2.ScrollBar.vertical.policy: C2.ScrollBar.AlwaysOn

						Q2.ListView {
							id: canMsgListView
							anchors.fill: parent
							model: driveCanDataPrinter.textMessages

							delegate: Q2.Rectangle {
								width: canMsgListView.width
								height: msg.height

								Q2.Text {
									id: msg
									text: modelData
									horizontalAlignment: Qt.AlignLeft
									leftPadding: 2
								}
							}
						}
					}
				}
			}
		}
	}
	
	C1.Tab {
		id: tabCharts
		title: "Charts"
	}
}

