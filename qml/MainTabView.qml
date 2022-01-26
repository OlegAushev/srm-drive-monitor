import QtQuick.Controls 1.4 as C1
import QtQuick 2.15  as Q2
import QtQuick.Controls 2.15 as C2

import WatchDataTableModel 0.1


C1.TabView {
	C1.Tab {
		id: tabCanData
		title: "CAN Data"
		C2.Frame {
			width: 300
			//height: 500
			C1.TableView {
				//width: 300
				//height: 600
				contentHeader: Q2.Text {
					text: "Watch Data"
					font.bold: true
				}
				anchors.fill: parent
				//columnSpacing: 1
				//rowSpacing: 1

				model : WatchDataTableModel {}
				
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

