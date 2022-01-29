import QtQuick 2.15 as Q2
import QtQuick.Controls 1.4 as C1


C1.TabView {
	C1.Tab {
		id: tabControl
		title: "Control"
		Q2.Column {
			SpinboxAndSliderControl {
				name: "Speed"
			}

			SpinboxAndSliderControl {
				name: "Torque"
			}
		}
		
	}
	
	C1.Tab {
		id: tabConfiguration
		title: "Configuration"
	}
}
