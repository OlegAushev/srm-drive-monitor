import QtQuick.Controls 1.4 as C1
import QtQuick 2.15  as Q2
import QtQuick.Controls 2.15 as C2

import CanDataTableModel 1.0



C1.TabView {
	C1.Tab {
		id: tabCanData
		title: "CAN Data"
		C2.Frame {
			C1.TableView {
				//width: 300
				//height: 600
				//anchors.fill: parent
				
				contentHeader: Q2.Text {
					text: "Watch Data"
					font.bold: true
				}

				model : CanDataTableModel {
					table: table1
				}
				
				C1.TableViewColumn {
					role: "name"
					title: "Name"
					width: 100
					resizable: false
					movable: false
				}

				C1.TableViewColumn {
					role: "value"
					title: "Value"
					width: 100
					resizable: false
					movable: false
				}

				C1.TableViewColumn {
					role: "unit"
					title: "Unit"
					width: 100
					resizable: false
					movable: false
				}


			}
		}
	}
	
	C1.Tab {
		id: tabCharts
		title: "Charts"
	}
}

