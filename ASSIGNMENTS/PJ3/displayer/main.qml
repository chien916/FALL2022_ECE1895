import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQml 2.15

Window {
	id: appwindow
	width: 640
	height: 480
	visible: true
	//	visibility: "FullScreen"
	title: qsTr("Hello World")
	Text {
		font.pixelSize: 100
	}

	Loader {
		anchors.fill: parent
		source: "qrc:/filechooser.qml"
	}

	Button {
		x: 16
		y: 72
		text: "Close"
		onClicked: SequentialAnimation {
			// Use a PropertyAnimation to resize the window width to maximum
			PropertyAnimation {
				target: appwindow
				property: "width"
				to: 1000
				duration: 500
			}

			// Use a PropertyAnimation to resize the window height to maximum
			PropertyAnimation {
				target: appwindow
				property: "height"
				to: 200
				duration: 500
			}
		}
	}

	//	// Page for the spinning loading bar
	//	StackView {
	//		id: stackview_main
	//		anchors.fill: parent
	//		initialItem: "qrc:/main.qml"
	//	}
}
