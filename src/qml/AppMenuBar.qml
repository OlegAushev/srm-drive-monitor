import QtQuick 2.5
import QtQuick.Controls 2.15

MenuBar {
        Menu {
            title: qsTr("Actions")
            Action { text: qsTr("Reset faults") }
            Action { text: qsTr("&Calibrate position sensor") }
            Action { text: qsTr("&Invert rotation direction") }
            MenuSeparator { }
            Action { text: qsTr("&Quit") }
        }
        Menu {
            title: qsTr("&Help")
            Action { text: qsTr("&Device name") }
            Action { text: qsTr("&Software version") }
            Action { text: qsTr("&Software build configuration") }
        }
}
