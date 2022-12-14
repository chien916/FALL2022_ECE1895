import QtQuick 2.15
import QtQuick.Window 2.3
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Rectangle {
	//	color: MyStyle.color_neutral300
	//	border.color: "#ffffff"
	objectName: "root_myDebugger"
	function disp(str) {
		if (listmodel_terminalText.count >= 100) {
			listmodel_terminalText.remove(0)
		}
		listmodel_terminalText.append({
										  "t": str.toString()
									  })
	}

	TextField {
		id: textField_textField
		anchors.left: parent.left
		anchors.right: button_send.left
		anchors.top: parent.top
		anchors.margins: MyStyle.param_lineWidth * 10
		height: parent.height * 0.1
		font.family: "YaHei Fira Icon Hybrid"
		placeholderText: "命令/Command"
		font.pixelSize: MyStyle.param_largeFontSize
		//		horizontalAlignment: Text.AlignHCenter
		//		verticalAlignment: Text.AlignVCenter
		//		fontSizeMode: Text.Fit
	}
	Button {
		id: button_send
		anchors.right: parent.right
		anchors.top: parent.top
		anchors.margins: MyStyle.param_lineWidth * 10
		width: parent.width * 0.2
		height: parent.height * 0.1
		Text {
			anchors.fill: parent
			anchors.margins: MyStyle.param_lineWidth * 10
			color: MyStyle.color_neutral900
			font.family: "STHeiti TC"
			font.pixelSize: MyStyle.param_largeFontSize
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter
			fontSizeMode: Text.Fit
			text: "发送/Send"
		}
	}

	Rectangle {
		id: rectangle_mouseArea
		color: MyStyle.color_neutral900
		anchors.top: textField_textField.bottom
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.bottom: parent.bottom
		anchors.margins: MyStyle.param_lineWidth * 10
		ListView {
			anchors.fill: parent
			anchors.margins: MyStyle.param_lineWidth * 10
			id: listview_terminalText
			model: listmodel_terminalText
			delegate: Text {
				text: t
				wrapMode: Text.Wrap
				color: MyStyle.color_neutralWhite
				font.family: "YaHei Fira Icon Hybrid"
				font.pixelSize: MyStyle.param_fontSize
			}
		}
	}

	ListModel {
		id: listmodel_terminalText
		ListElement {
			t: "-> TILE MOUSE VERSION 1.0 ALPHA"
		}
		ListElement {
			t: "-> MADE BY YINHAO SPECIALLY FOR YOU"
		}
		ListElement {
			t: "-> ENJOY :)"
		}
	}
}
/*##^##
Designer {
	D{i:0;autoSize:true;formeditorZoom:0.75;height:480;width:640}
}
##^##*/

