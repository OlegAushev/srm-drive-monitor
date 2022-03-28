import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import QtQuick.Controls.Material 2.1


ApplicationWindow {
	id: root

	Material.primary: Material.color(Material.BlueGrey)			// used for EVOCARGO build
	Material.accent: Material.color(Material.DeepOrange, Material.Shade700)	// used for EVOCARGO build

	title: "SRM Drive Monitor Settings"
	minimumWidth: 400
	minimumHeight: 300
	maximumHeight: minimumHeight
	maximumWidth: minimumWidth

	TabBar {
		id: tabbar
		TabButton {
			text: "Charts"
			width: implicitWidth
		}
	}

	StackLayout {
		anchors.top: tabbar.bottom
		anchors.bottom: root.bottom
		anchors.left: root.left
		anchors.right: root.right
		currentIndex: tabbar.currentIndex
		
		Item {
			id: tabData
			ChartsSettings {}
			
		}
	}
}