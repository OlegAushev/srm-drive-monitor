import QtQuick 2.11
import QtQuick.Controls 2.4
import "../components"


Item {
	id: root
	anchors.fill: parent

	Column {
		anchors.fill: parent

		SettingsTextInput {
			width: 400
			height: 40
			name: "Update Frequency"
			unit: "Hz"
			parameterKey: "charts/updateFreq"
			valueFrom: 1
			valueTo: 150
			decimals: 0
		}
	
		SettingsTextInput {
			width: 400
			height: 40
			name: "Axis Update Frequency"
			unit: "Hz"
			parameterKey: "charts/axisUpdateFreq"
			valueFrom: 0.1
			valueTo: 60
			decimals: 1
		}

		SettingsTextInput {
			width: 400
			height: 40
			name: "Time Window"
			unit: "s"
			parameterKey: "charts/timeWindow"
			valueFrom: 10
			valueTo: 600
			decimals: 0
		}
	}
}