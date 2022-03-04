import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11


Item {
	id: root

	TabBar {
		id: tabbar
		TabButton {
			text: "Data"
			width: implicitWidth
		}

		TabButton {
			text: "Info"
			width: implicitWidth
		}

		/*TabButton {
			text: "Charts"
			width: implicitWidth
		}*/
	}

	StackLayout {
		anchors.top: tabbar.bottom
		anchors.bottom: root.bottom
		anchors.left: root.left
		anchors.right: root.right
		currentIndex: tabbar.currentIndex
		
		Item {
			id: tabData
			CanDataWidget {}
			
		}

		Item {
			id: tabInfo
			InfoWidget {}
		}

		/*Item {
			id: tabCharts
			Layout.alignment: Qt.AlignLeft | Qt.AlignTop | Qt.AlignRight | Qt.AlignBottom
			ChartsWidget {}
		}*/


	}





}

























/*

C1.TabView {

	C1.Tab {
		id: tabCanData
		title: "CAN Data"

		
	}
	
	C1.Tab {
		id: tabCharts
		title: "Charts"

		Charts {}
	}
}

*/