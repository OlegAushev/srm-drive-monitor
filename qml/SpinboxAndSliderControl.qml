import QtQuick 2.15
import QtQuick.Controls 2.15


Rectangle {
	property string name
	//property real valueFrom
	//property real valueTo

	width: 300
	height: 50
	border.color: "black"

	Text {
		id: label
		width: parent.width
		height: 20
		anchors.top: parent.top
		horizontalAlignment: Text.AlignHCenter
		verticalAlignment: Text.AlignVCenter
		text: name
	}
}