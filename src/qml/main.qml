import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.0

Window {
	id: win
	visible: true
	width: 600
	height: 400
	title: qsTr("Hi!")
	
	Button {
		text: "Click!"
		anchors.centerIn: parent
		onClicked: {
			win.color = Qt.rgba(Math.random(), Math.random(), Math.random(), Math.random());
		}
	}
} 
