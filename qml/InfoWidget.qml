import QtQuick 2.11
import "components"

Item {
	Row {
		padding: 2
		spacing: 8

		DataTableOnListView2Col {
			id: faultsTable
			name: "Faults"
			sourceTable: syslog.faultsTable()
			tableWidth: 360
		}

		DataTableOnListView2Col {
			id: warningsTable
			name: "Warnings"
			sourceTable: syslog.warningsTable()
			tableWidth: 360
		}



	}
}