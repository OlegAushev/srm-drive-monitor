import QtQuick 2.11
import QtCharts 2.2
import QtQuick.Layouts 1.11


Item {
	id: root
	anchors.fill: parent

	ColumnLayout {
		anchors.fill: root
		spacing:0
		
		Item {
			id: item1
			height: item2.height
			Layout.fillWidth: true
			Layout.fillHeight: true
			Layout.alignment: Qt.AlignLeft | Qt.AlignTop

			ChartView {
				id: chartview1
				
				anchors.fill: parent
				animationOptions: ChartView.NoAnimation
				theme: ChartView.ChartThemeDark	
				legend.visible: false

				ValueAxis {
					id: axisY1
					min: -100
					max: 100
				}

				ValueAxis {
					id: axisX1
					min: 0
					max: 60
				}

				LineSeries {
					id: lineSeries1
					name: "signal 1"
					axisX: axisX1
					axisY: axisY1
				}
			}
		}





		Item {
			id: item2
			height: item3.height
			Layout.fillWidth: true
			Layout.fillHeight: true
			Layout.alignment: Qt.AlignLeft | Qt.AlignTop
			
			ChartView {
				id: chartview2
				
				anchors.fill: parent
				animationOptions: ChartView.NoAnimation
				theme: ChartView.ChartThemeDark	
				legend.visible: false

				ValueAxis {
					id: axisY2
					min: -100
					max: 100
				}

				ValueAxis {
					id: axisX2
					min: 0
					max: 60
				}

				LineSeries {
					id: lineSeries2
					name: "signal 2"
					axisX: axisX2
					axisY: axisY2
				}
			}
		}



		Item {
			id: item3
			Layout.fillWidth: true
			Layout.fillHeight: true
			Layout.alignment: Qt.AlignLeft | Qt.AlignTop
			
			ChartView {
				id: chartview3
				
				anchors.fill: parent
				animationOptions: ChartView.NoAnimation
				theme: ChartView.ChartThemeDark	
				legend.visible: false

				ValueAxis {
					id: axisY3
					min: -100
					max: 100
				}

				ValueAxis {
					id: axisX3
					min: 0
					max: 60
				}

				LineSeries {
					id: lineSeries3
					name: "signal 3"
					axisX: axisX3
					axisY: axisY3
				}
			}
		}



		



	}


	Timer {
		id: refreshTimer
		interval: 1000 / 60 	// 60 Hz
		running: true
		repeat: true
		onTriggered: {
			chartPlotter.update(0, lineSeries1);
			chartPlotter.update(1, lineSeries2);
			chartPlotter.update(2, lineSeries3);
		}
	}


}




	
	
