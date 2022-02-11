import QtQuick 2.11
import QtCharts 2.2
import QtQuick.Layouts 1.11


Item {
	id: root
	anchors.fill: parent

	property real timeWindow: 60
	property real timeNow: 0

	ColumnLayout {
		anchors.fill: root
		spacing:0
		
		Item {
			id: item0
			height: item1.height
			Layout.fillWidth: true
			Layout.fillHeight: true
			Layout.alignment: Qt.AlignLeft | Qt.AlignTop

			ChartView {
				id: chartview0
				
				anchors.fill: parent
				animationOptions: ChartView.NoAnimation
				theme: ChartView.ChartThemeDark	
				legend.visible: false

				ValueAxis {
					id: axisX0
					min: (timeNow > timeWindow) ? timeNow - timeWindow : 0
					max: (timeNow > timeWindow) ? timeNow : timeWindow
					labelFormat: "%d"
					tickCount: timeWindow / 10 + 1
					minorTickCount: 4
				}

				ValueAxis {
					id: axisY0
					min: -100
					max: 100
				}

				LineSeries {
					id: lineSeries0
					name: "signal 1"
					axisX: axisX0
					axisY: axisY0
				}
			}
		}

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
					labelFormat: "%d"
					tickCount: timeWindow / 10 + 1
					minorTickCount: 4
				}

				ValueAxis {
					id: axisY1
					min: -100
					max: 100
				}

				LineSeries {
					id: lineSeries1
					name: "signal 2"
					axisX: axisX1
					axisY: axisY1
				}
			}
		}

		Item {
			id: item2
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
					labelFormat: "%d"
					tickCount: timeWindow / 10 + 1
					minorTickCount: 4
				}

				ValueAxis {
					id: axisY2
					min: -100
					max: 100
				}

				LineSeries {
					id: lineSeries2
					name: "signal 3"
					axisX: axisX2
					axisY: axisY2
				}
			}
		}
	}


	Timer {
		id: refreshTimer
		interval: 1000 / 60
		running: true
		repeat: true
		onTriggered: {
			chartPlotter.update(0, lineSeries0);
			axisY0.min = chartPlotter.minValue(0) - 20;
			axisY0.max = chartPlotter.maxValue(0) + 20;
			axisY0.applyNiceNumbers();

			chartPlotter.update(1, lineSeries1);
			axisY1.min = chartPlotter.minValue(1) - 20;
			axisY1.max = chartPlotter.maxValue(1) + 20;
			axisY1.applyNiceNumbers();

			chartPlotter.update(2, lineSeries2);
			axisY2.min = chartPlotter.minValue(2) - 20;
			axisY2.max = chartPlotter.maxValue(2) + 20;
			axisY2.applyNiceNumbers();			
			
			timeNow = chartPlotter.timeSec();
		}
	}
	
}




	
	
