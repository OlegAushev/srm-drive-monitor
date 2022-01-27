import QtQuick.Controls 1.4 as C1
import QtQuick 2.15  as Q2
import QtQuick.Controls 2.15 as C2


C1.TabView {
	C1.Tab {
		id: tabCanData
		title: "CAN Data"
		BasicDataTable {}
	}
	
	C1.Tab {
		id: tabCharts
		title: "Charts"
	}
}

