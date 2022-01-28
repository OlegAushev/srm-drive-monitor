import QtQuick.Controls 1.4 as C1


C1.TabView {
	C1.Tab {
		id: tabControl
		title: "Control"
		SpinboxAndSliderControl {
			name: "Speed"
		}
	}
	
	C1.Tab {
		id: tabConfiguration
		title: "Configuration"
	}
}
