import QtQuick 2.11
import QtCharts 2.2


ChartView {
	id: chartview
	anchors.fill: parent
	animationOptions: ChartView.NoAnimation
	theme: ChartView.ChartThemeDark	

	ValueAxis {
		id: axisY1
		min: 35
		max: 45
	}

	ValueAxis {
		id: axisY2
		min: -10
		max: 5
	}

	ValueAxis {
		id: axisX
		min: 0
		max: 60
	}

	LineSeries {
		id: lineSeries1
		name: "signal 1"
		axisX: axisX
		axisY: axisY1
	}

	LineSeries {
		id: lineSeries2
		name: "signal 2"
		axisX: axisX
		axisYRight: axisY2
	}

	Timer {
		id: refreshTimer
		interval: 1000 / 60 	// 60 Hz
		running: true
		repeat: true
		onTriggered: {
			chartPlotter.update(lineSeries1);
        		//chartPlotter.update(lineSeries2);
		}
	}
	

}