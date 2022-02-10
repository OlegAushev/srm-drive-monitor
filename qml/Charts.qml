import QtQuick 2.11
import QtCharts 2.2
import QtQuick.Layouts 1.11


Item {
	id: root
	anchors.fill: parent

	property real timeWindow: 25
	property real timeNow: 0

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
					id: axisX1
					min: (timeNow > timeWindow) ? timeNow - timeWindow : 0
					max: (timeNow > timeWindow) ? timeNow : timeWindow
				}

				ValueAxis {
					id: axisY1
					min: -100
					max: 100
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
					id: axisX2
					min: (timeNow > timeWindow) ? timeNow - timeWindow : 0
					max: (timeNow > timeWindow) ? timeNow : timeWindow
				}

				ValueAxis {
					id: axisY2
					min: -100
					max: 100
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
					id: axisX3
					min: (timeNow > timeWindow) ? timeNow - timeWindow : 0
					max: (timeNow > timeWindow) ? timeNow : timeWindow
				}

				ValueAxis {
					id: axisY3
					min: -100
					max: 100
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
		property real timeSec: 0
		running: true
		repeat: true
		onTriggered: {
			timeSec += interval/1000;
			chartPlotter.update(0, lineSeries1);
			chartPlotter.update(1, lineSeries2);
			chartPlotter.update(2, lineSeries3);
			timeNow = chartPlotter.timeSec();
		}
	}
	
}




	
	
