import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Rectangle {
	objectName: "root_myBase"
	Rectangle {
		id: rectangle_header
		anchors {
			top: parent.top
			left: parent.left
			right: parent.right
		}
		height: parent.height * 0.1
		Rectangle {
			id: rectangle_control
			anchors {
				left: parent.left
				right: rectangle_debug.left
				top: parent.top
				bottom: parent.bottom
				//				margins: parent.height * marg
			}
			color: swipeview_swipeview.currentIndex
				   == 0 ? MyStyle.color_neutral900 : MyStyle.color_neutralWhite
			width: parent.width * 0.5
			Text {
				anchors {
					fill: parent
					margins: MyStyle.param_lineWidth * 5
				}
				color: swipeview_swipeview.currentIndex
					   == 0 ? MyStyle.color_neutralWhite : MyStyle.color_neutral900
				font.family: "STHeiti TC"
				font.pixelSize: MyStyle.param_largeFontSize
				text: "主页/Main Page"
				horizontalAlignment: Text.AlignHCenter
				verticalAlignment: Text.AlignVCenter
				fontSizeMode: Text.Fit
			}

			Button {
				id: button_control
				objectName: "button_control"
				anchors.fill: parent
				onPressed: swipeview_swipeview.currentIndex = 0
			}
		}
		Rectangle {
			id: rectangle_debug
			anchors {
				right: parent.right
				top: parent.top
				bottom: parent.bottom
				//				margins: parent.height * marg
			}
			color: swipeview_swipeview.currentIndex
				   == 1 ? MyStyle.color_neutral900 : MyStyle.color_neutralWhite
			width: parent.width * 0.5

			Text {
				anchors {
					fill: parent
					margins: MyStyle.param_lineWidth * 5
				}
				color: swipeview_swipeview.currentIndex
					   == 1 ? MyStyle.color_neutralWhite : MyStyle.color_neutral900
				font.family: "STHeiti TC"
				font.pixelSize: MyStyle.param_largeFontSize
				text: "调试/Debug"
				horizontalAlignment: Text.AlignHCenter
				verticalAlignment: Text.AlignVCenter
				fontSizeMode: Text.Fit
			}

			Button {
				id: button_debug
				objectName: "button_debug"
				anchors {
					fill: parent
				}
				onPressed: swipeview_swipeview.currentIndex = 1
			}
		}
	}
	SwipeView {
		id: swipeview_swipeview
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.top: rectangle_header.bottom
		anchors.bottom: parent.bottom
		interactive: false
		currentIndex: 0

		MyInterface {}
		MyDebugger {}

		//		Loader {
		//			source: "qrc:/interface.qml"
		//		}
		//		Loader {
		//			source: "qrc:/debugger.qml"
		//		}
	}
}

/*##^##
Designer {
	D{i:0;autoSize:true;formeditorZoom:0.5;height:480;width:640}
}
##^##*/

