import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import QtQuick.Shapes 1.15

Rectangle {
	implicitHeight: 500
	implicitWidth: 640

	objectName: "rootRectangle_myInterface"
	id: rootRectangle_myInterface
	property bool isClient: MyServer ? MyServer.role_q === 1 : true
	property bool isServer: !isClient
	property double x_m: MyServer ? MyServer.xRatio_m_q : 0
	property double y_m: MyServer ? MyServer.yRatio_m_q : 0
	property bool debuggerShow: mouseArea_debuggerShow.pressed
	property string dispText: MyServer ? MyServer.currentMessage_q : "NOT IN SERVCE\nNOT IN SERVICE"
	Rectangle {
		id: rectangle_blurFrame
		anchors.fill: parent
		color: MyStyle.color_neutral800
		MyDisplay {
			id: myDisplay_myDisplay
			anchors.left: parent.left
			anchors.right: parent.right
			anchors.top: parent.top
			height: parent.height * 0.2
			anchors.margins: MyStyle.param_lineWidth * 10
			numberOfLines: 2
			dispText: rootRectangle_myInterface.dispText
		}

		MyReadingsObserver {
			id: myReadingsObserver_myReadingsObserver
			visible: isClient
			anchors.top: myDisplay_myDisplay.bottom

			height: parent.height * 0.05
			anchors.left: parent.left
			anchors.right: parent.right
			anchors.margins: MyStyle.param_lineWidth * 10
			xVal: x_m
			yVal: y_m
		}

		MyDialer {
			id: myDialer_myDialer
			anchors.top: isClient ? myReadingsObserver_myReadingsObserver.bottom : myDisplay_myDisplay.bottom
			anchors.bottom: parent.bottom
			anchors.left: parent.left
			anchors.right: parent.right
			anchors.margins: MyStyle.param_lineWidth * 10
			isClient: !isServer
			onButtonClicked: buttonText => {
								 console.log("BUTTON_" + buttonText)
								 //								 if (MyServer)
								 MyServer.execute("BUTTON_" + buttonText)
							 }
		}
	}

	FastBlur {
		opacity: debuggerShow ? 1.0 : 0.0
		Behavior on opacity {
			SpringAnimation {
				spring: 1
				damping: 0.2
			}
		}
		source: rectangle_blurFrame
		anchors.fill: parent
		radius: 40
	}

	Rectangle {
		id: rectangle_debugger
		x: myDisplay_myDisplay.x
		y: myDisplay_myDisplay.y
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.top: parent.top
		//		color: "transparent"
		height: debuggerShow ? myDialer_myDialer.height : myDisplay_myDisplay.height
		Behavior on height {
			NumberAnimation {
				easing.type: Easing.InOutQuad
			}
		}
		color: MyStyle.color_neutral300
		radius: MyStyle.param_lineWidth * 10
		anchors.margins: MyStyle.param_lineWidth * 10
		visible: true
		opacity: debuggerShow ? 0.5 : 0.0
		Behavior on opacity {
			SpringAnimation {
				spring: 1
				damping: 0.2
			}
		}
		MyDebugger {
			anchors.fill: parent
			anchors.margins: MyStyle.param_lineWidth * 10
		}
		MouseArea {
			id: mouseArea_debuggerShow
			anchors.fill: parent
		}
	}
}

/*##^##
Designer {
	D{i:0;autoSize:true;formeditorZoom:0.5;height:480;width:640}
}
##^##*/

