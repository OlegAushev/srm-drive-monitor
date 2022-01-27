import QtQuick.Controls 1.4 as C1
import QtQuick 2.15  as Q2
import QtQuick.Controls 2.15 as C2
import QtQuick.Layouts 1.15


C1.TabView {
	C1.Tab {
		id: tabCanData
		title: "CAN Data"
		GridLayout {
			anchors.fill: parent
			anchors.leftMargin: 2
			anchors.topMargin: 2
			anchors.rightMargin: 2
			anchors.bottomMargin: 2
			rows: 1
			columns: 2
			columnSpacing: 2
			BasicDataTable { name: "Watch Data"; sourceTable: table1 }
		}
	}
	
	C1.Tab {
		id: tabCharts
		title: "Charts"
	}
}

