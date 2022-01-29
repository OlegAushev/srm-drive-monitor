import QtQuick.Controls 1.4 as C1
import QtQuick 2.15  as Q2
import QtQuick.Controls 2.15 as C2
import QtQuick.Layouts 1.15


C1.TabView {
	C1.Tab {
		id: tabCanData
		title: "CAN Data"
		Q2.Row {
			/*width: 500
			//anchors.fill: parent
			anchors.leftMargin: 2
			anchors.topMargin: 2
			anchors.rightMargin: 2
			anchors.bottomMargin: 2
			rows: 2
			columns: 4
			columnSpacing: 2*/

			BasicDataTable {
				id: watchDataTable
				name: "Watch Data"
				sourceTable: table1
				//Layout.alignment: Qt.AlignLeft | Qt.AlignTop 
			}

			Q2.Column {
				Q2.Row {
					BasicDataTable {
						id: tpdo1DataTable
						name: "TPDO1 Data"
						sourceTable: table1
						//Layout.alignment: Qt.AlignLeft | Qt.AlignTop
					}
					
					BasicDataTable {
						id: tpdo2DataTable
						name: "TPDO2 Data"
						sourceTable: table1
						//Layout.alignment: Qt.AlignLeft | Qt.AlignTop
					}

					Q2.Column {
						BasicDataTable {
						id: tpdo3DataTable
						name: "TPDO3 Data"
						sourceTable: table1
						//Layout.alignment: Qt.AlignLeft | Qt.AlignTop
						}

						BasicDataTable {
						id: tpdo4DataTable
						name: "TPDO4 Data"
						sourceTable: table1
						//Layout.alignment: Qt.AlignLeft | Qt.AlignTop
						}
					}
				}

				BasicDataTable {
				id: test
				name: "test Data"
				sourceTable: table1
				//Layout.alignment: Qt.AlignLeft | Qt.AlignTop
				}
			}
		}
	}
	
	C1.Tab {
		id: tabCharts
		title: "Charts"
	}
}

