import QtQuick 2.15

import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Rectangle {
	objectName: "root_myInterface"
	id: rectangle_root
	property double marg: 0.2
	property real opac: 0.8
	color: "#ffffff"
	border.color: "#ffffff"

	Text {
		font.family: "STHeiti TC"
		font.pixelSize: MyStyle.param_largeFontSize * 2
		horizontalAlignment: Text.AlignHCenter
		verticalAlignment: Text.AlignVCenter
		fontSizeMode: Text.Fit
		text: "已连接/Connected"
		anchors.top: parent.top
		anchors.bottom: row_buttons.top
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.margins: MyStyle.param_lineWidth * 10


	}
	//	ProgressBar {
	//		x: 137
	//		y: 30
	//		width: 165
	//		height: 32
	//		indeterminate: true
	//		focusPolicy: Qt.StrongFocus
	//		wheelEnabled: false
	//	}
	ListModel {
		id: listModel_gauges
		ListElement {
			reversed: true
		}
		ListElement {
			reversed: false
		}
		ListElement {
			reversed: true
		}
		ListElement {
			reversed: false
		}
		ListElement {
			reversed: true
		}
		ListElement {
			reversed: false
		}
	}
	Row {
		id: row_gauges
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.bottom: button_mouseArea.top
		anchors.margins: MyStyle.param_lineWidth * 10
		Repeater {
			id: repeater_gauges
			model: listModel_gauges
			delegate: ProgressBar {
				id: progessBar_gauge
				width: row_gauges.width / listModel_gauges.count
				height: rectangle_root.height * 0.02
				rotation: reversed * 180
				clip: true
				value: 0.5
			}
		}
	}

	ListModel {
		id: listModel_buttons

		ListElement {
			buttonText: "校正/Calibrate"
			highlight: false
		}
		ListElement {
			buttonText: "连接/Connect"
			highlight: true
		}
		ListElement {
			buttonText: "调参/Parameters"
			highlight: false
		}
	}

	Row {
		id: row_buttons
		anchors.bottom: row_gauges.top
		anchors.margins: MyStyle.param_lineWidth * 10
		anchors.left: parent.left
		anchors.right: parent.right
		Repeater {
			model: listModel_buttons
			delegate: Rectangle {
				width: row_buttons.width / listModel_buttons.count
				height: rectangle_root.height * 0.1
				color: highlight ? MyStyle.color_neutral900 : MyStyle.color_neutralWhite
				Text {
					anchors.fill: parent
					anchors.margins: MyStyle.param_lineWidth * 10
					font.family: "STHeiti TC"
					font.pixelSize: MyStyle.param_fontSize
					horizontalAlignment: Text.AlignHCenter
					verticalAlignment: Text.AlignVCenter
					fontSizeMode: Text.Fit
					text: buttonText
					color: highlight ? MyStyle.color_neutralWhite : MyStyle.color_neutral900
				}
				Button {
					anchors.fill: parent
				}
			}


			/*Button {

				Rectangle {
					anchors.fill: parent
					color: highlight ? MyStyle.color_neutral900 : MyStyle.color_neutral300
				}
				Text {
					anchors.fill: parent
					font.family: "STHeiti TC"
					font.pixelSize: MyStyle.param_fontSize
					horizontalAlignment: Text.AlignHCenter
					verticalAlignment: Text.AlignVCenter
					fontSizeMode: Text.Fit
					text: buttonText
					color: highlight ? MyStyle.color_neutralWhite : MyStyle.color_neutral900
				}*/
			//			}
		}
	}

	Button {
		id: button_mouseArea
		height: parent.height * 0.5
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.bottom: parent.bottom
		anchors.margins: MyStyle.param_lineWidth * 10
	}
}

/*##^##
Designer {
	D{i:0;autoSize:true;formeditorZoom:0.75;height:480;width:640}
}
##^##*/

