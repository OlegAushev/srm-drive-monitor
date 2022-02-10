import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11


Item {
	id: root

	TabBar {
		id: tabbar
		TabButton {
			text: "CAN Data"
		}

		TabButton {
			text: "Charts"
		}
	}

	StackLayout {
		anchors.top: tabbar.bottom
		anchors.bottom: root.bottom
		anchors.left: root.left
		anchors.right: root.right
		currentIndex: tabbar.currentIndex
		
		Item {
			id: tabCanData

			Row {
				padding: 2
				spacing: 8
				
				BasicDataTableOnListView {
					id: watchDataTable
					name: "Watch Data"
					sourceTable: driveCanDataPrinter.watchTable()
					tableWidth: 250
					tableHeight: 620
				}

				Column {
					id: columnTableText
					spacing: 8

					Row {
						spacing: 8
						BasicDataTableOnListView {
							id: tpdo1DataTable
							name: "TPDO1 Data"
							sourceTable: driveCanDataPrinter.tpdo1Table()
							tableWidth: 250
							tableHeight: 328
						}
						
						BasicDataTableOnListView {
							id: tpdo2DataTable
							name: "TPDO2 Data"
							sourceTable: driveCanDataPrinter.tpdo2Table()
							tableWidth: 250
							tableHeight: 328
						}

						Column {
							spacing: 8

							BasicDataTableOnListView {
								id: tpdo3DataTable
								name: "TPDO3 Data"
								sourceTable: driveCanDataPrinter.tpdo3Table()
								tableWidth: 250
								tableHeight: 160
							}

							BasicDataTableOnListView {
								id: tpdo4DataTable
								name: "TPDO4 Data"
								sourceTable: driveCanDataPrinter.tpdo4Table()
								tableWidth: 250
								tableHeight: 160
							}
						}
					}

					Frame {
						padding: 0
						implicitWidth: columnTableText.width//canMsgTextRect.width
						implicitHeight: watchDataTable.height - tpdo1DataTable.height - 8//canMsgTextRect.height

						Item {
							anchors.fill: parent
														
							ScrollView {
								anchors.fill: parent
								anchors.margins: 1
								ScrollBar.vertical.policy: ScrollBar.AlwaysOn
								
								ListView {
									id: canMsgListView
									anchors.fill: parent
									anchors.margins: 4
									model: driveCanDataPrinter.textMessages

									delegate: Rectangle {
										width: canMsgListView.width
										height: msg.height
										color: "transparent"

										Text {
											id: msg
											text: modelData
											horizontalAlignment: Qt.AlignLeft
											leftPadding: 4
										}
									}

									onCountChanged: {
										Qt.callLater( canMsgListView.positionViewAtEnd )
									}
								}
							}

							Button {
								text: "Clear"
								width: text.implicitWidth
								height: text.implicitHeight
								anchors.bottom: parent.bottom
								anchors.right: parent.right
								anchors.bottomMargin: 4
								anchors.rightMargin: 24
								onClicked: driveCanDataPrinter.clearTextMessages()
							}
						}
					}
				}
			}
		}

		Item {
			id: tabCharts
			Layout.alignment: Qt.AlignLeft | Qt.AlignTop | Qt.AlignRight | Qt.AlignBottom
			Charts {}
		}


	}





}

























/*

C1.TabView {

	C1.Tab {
		id: tabCanData
		title: "CAN Data"

		
	}
	
	C1.Tab {
		id: tabCharts
		title: "Charts"

		Charts {}
	}
}

*/