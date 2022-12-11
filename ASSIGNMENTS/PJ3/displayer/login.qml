import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import "./"

Rectangle {
	id: root
	objectName: "login_qml_root"
	property double marg: 0.2
	property real opac: 0.8
	color: MyStyle.color_neutral300
	Rectangle {
		id: rectangle_header
		anchors {
			top: parent.top
			left: parent.left
			right: parent.right
		}
		color: MyStyle.color_neutral900
		height: parent.height * 0.1
		Text {
			anchors {
				left: parent.left
				top: parent.top
				bottom: parent.bottom
				margins: parent.height * marg
			}
			id: text_headerLeft
			text: "测试"
			color: MyStyle.color_neutralWhite
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter
			font.family: "STHeiti TC"
			font.pixelSize: MyStyle.param_fontSize
		}
		Rectangle {
			anchors {
				right: parent.right
				top: parent.top
				bottom: parent.bottom
				//				margins: parent.height * marg
			}
			color: MyStyle.color_neutral300
			width: parent.width * 0.2
			Button {
				id: button_signup
				objectName: "button_signup"
				anchors {
					fill: parent
				}
				font.family: "STHeiti TC"
				text: "注册/Sign Up"
			}
		}
	}

	Column {
		id: columnlayout_inputfields
		width: parent.width * 0.5
		height: parent.height * 0.4
		anchors.verticalCenter: parent.verticalCenter
		anchors.horizontalCenter: parent.horizontalCenter
		Text {
			text: "用户名/Username"
			font.family: "STHeiti TC"
			font.pixelSize: MyStyle.param_fontSize
			verticalAlignment: Text.AlignVCenter
		}
		TextField {
			width: parent.width
			font.family: "STHeiti TC"
			font.pixelSize: MyStyle.param_fontSize
			topInset: parent.height * 0.05
			topPadding: parent.height * 0.05
			bottomInset: parent.height * 0.05
			bottomPadding: parent.height * 0.05
		}

		Text {
			text: "密码/Password"
			font.family: "STHeiti TC"
			font.pixelSize: MyStyle.param_fontSize
			verticalAlignment: Text.AlignVCenter
		}
		TextField {
			width: parent.width
			font.family: "STHeiti TC"
			font.pixelSize: MyStyle.param_fontSize
			topInset: parent.height * 0.05
			topPadding: parent.height * 0.05
			bottomInset: parent.height * 0.05
			bottomPadding: parent.height * 0.05
		}

		Button {
			text: "登录/Log In"
			anchors.left: parent.left
			anchors.right: parent.right
			font.family: "STHeiti TC"
			font.pixelSize: MyStyle.param_fontSize
		}
	}
}

/*##^##
Designer {
	D{i:0;autoSize:true;formeditorZoom:0.66;height:480;width:640}
}
##^##*/

