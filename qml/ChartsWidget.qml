import QtQuick 2.11
import QtCharts 2.2
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.4


Item {
	id: root
	anchors.fill: parent

	property real updateFreq: appSettings.value("charts/updateFreq")
	property real axisUpdateFreq: appSettings.value("charts/axisUpdateFreq")
	property real timeWindow: appSettings.value("charts/timeWindow")
	property real timeNow: 0

	property bool openGL: appSettings.value("charts/openGL")

	ColumnLayout {
		anchors.fill: root
		spacing:0
		
		Item {
			id: item0
			height: item1.height
			Layout.fillWidth: true
			Layout.fillHeight: true
			Layout.alignment: Qt.AlignLeft | Qt.AlignTop

			ComboBox {
				id: chart0Selector
				z: 1
				width: 200
				height: 30
				anchors.top: chartview0.top
				anchors.right: chartview0.right
				anchors.topMargin: 4
				anchors.rightMargin: 32
				model: chartPlotter.channelList()
			}

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
					minorTickCount: 1
				}

				LineSeries {
					id: lineSeries0
					name: "signal 1"
					axisX: axisX0
					axisY: axisY0
					useOpenGL: root.openGL
				}
			}
		}

		Item {
			id: item1
			height: item2.height
			Layout.fillWidth: true
			Layout.fillHeight: true
			Layout.alignment: Qt.AlignLeft | Qt.AlignTop
			
			ComboBox {
				id: chart1Selector
				z: 1
				width: 200
				height: 30
				anchors.top: chartview1.top
				anchors.right: chartview1.right
				anchors.topMargin: 4
				anchors.rightMargin: 32
				model: chartPlotter.channelList()
			}

			ChartView {
				id: chartview1
				
				anchors.fill: parent
				animationOptions: ChartView.NoAnimation
				theme: ChartView.ChartThemeDark	
				legend.visible: false

				ValueAxis {
					id: axisX1
					min: axisX0.min
					max: axisX0.max
					labelFormat: "%d"
					tickCount: timeWindow / 10 + 1
					minorTickCount: 4
				}

				ValueAxis {
					id: axisY1
					min: -100
					max: 100
					minorTickCount: 1
				}

				LineSeries {
					id: lineSeries1
					name: "signal 2"
					axisX: axisX1
					axisY: axisY1
					useOpenGL: root.openGL
				}
			}
		}

		Item {
			id: item2
			Layout.fillWidth: true
			Layout.fillHeight: true
			Layout.alignment: Qt.AlignLeft | Qt.AlignTop
			
			ComboBox {
				id: chart2Selector
				z: 1
				width: 200
				height: 30
				anchors.top: chartview2.top
				anchors.right: chartview2.right
				anchors.topMargin: 4
				anchors.rightMargin: 32
				model: chartPlotter.channelList()
			}

			ChartView {
				id: chartview2
				
				anchors.fill: parent
				animationOptions: ChartView.NoAnimation
				theme: ChartView.ChartThemeDark	
				legend.visible: false

				ValueAxis {
					id: axisX2
					min: axisX0.min
					max: axisX0.max
					labelFormat: "%d"
					tickCount: timeWindow / 10 + 1
					minorTickCount: 4
				}

				ValueAxis {
					id: axisY2
					min: -100
					max: 100
					minorTickCount: 1
				}

				LineSeries {
					id: lineSeries2
					name: "signal 3"
					axisX: axisX2
					axisY: axisY2
					useOpenGL: root.openGL
				}
			}
		}
	}


	Timer {
		id: updateTimer
		interval: 1000 / updateFreq
		running: true
		repeat: true
		onTriggered: {
			chartPlotter.update(chart0Selector.currentText, lineSeries0);
			chartPlotter.update(chart1Selector.currentText, lineSeries1);
			chartPlotter.update(chart2Selector.currentText, lineSeries2);
			timeNow = chartPlotter.timeSec();
		}
	}

	Timer {
		id: axisUpdateTimer
		interval: 1000 / axisUpdateFreq
		running: true
		repeat: true
		onTriggered: {
			axisY0.min = chartPlotter.minValue(chart0Selector.currentText) - 5;
			axisY0.max = chartPlotter.maxValue(chart0Selector.currentText) + 5;
			axisY0.applyNiceNumbers();

			axisY1.min = chartPlotter.minValue(chart1Selector.currentText) - 5;
			axisY1.max = chartPlotter.maxValue(chart1Selector.currentText) + 5;
			axisY1.applyNiceNumbers();

			axisY2.min = chartPlotter.minValue(chart2Selector.currentText) - 5;
			axisY2.max = chartPlotter.maxValue(chart2Selector.currentText) + 5;
			axisY2.applyNiceNumbers();
		}
	}
	
}




	
	
