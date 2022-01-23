import QtQuick.Controls 1.4


TabView {
	anchors.left: parent.left
	anchors.top: parent.top
	width: 800
	height: 500
	Tab {
		id: tabCanData
		title: "CAN Data"	
	}
	Tab {
		id: tabCharts
		title: "Charts"
	}
}
