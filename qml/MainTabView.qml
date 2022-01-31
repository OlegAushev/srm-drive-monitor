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
				tableWidth: 220
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
						tableWidth: 220
					}
					
					BasicDataTable {
						id: tpdo2DataTable
						name: "TPDO2 Data"
						sourceTable: driveCanDataPrinter.tpdo2Table()
						tableWidth: 220
					}

					Q2.Column {
						spacing: 8

						BasicDataTable {
							id: tpdo3DataTable
							name: "TPDO3 Data"
							sourceTable: driveCanDataPrinter.tpdo3Table()
							tableWidth: 220
						}

						BasicDataTable {
							id: tpdo4DataTable
							name: "TPDO4 Data"
							sourceTable: driveCanDataPrinter.tpdo4Table()
							tableWidth: 220
						}
					}
				}

				Q2.Rectangle {
					id: canTextAreaRect
					width: columnTableText.width
					height: watchDataTable.height - tpdo1DataTable.height - 8
					border.color: "lightgrey"
					Q2.Text {
						id: canTextArea
						anchors.fill: parent

						Q2.Connections {
							target: driveCanDataPrinter
							function onTextMessageAvailable(message) {
								canTextArea.text = canTextArea.text + message;
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

