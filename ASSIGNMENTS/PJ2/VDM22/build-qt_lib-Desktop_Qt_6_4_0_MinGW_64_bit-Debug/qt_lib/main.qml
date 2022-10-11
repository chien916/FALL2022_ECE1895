import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
Window {
	Material.theme: Material.Light
	Material.accent: Material.BlueGrey
	Material.foreground: Material.BlueGrey
	Material.background: Material.BlueGrey
	width: 375
	height: 600
	maximumHeight: 600
	minimumHeight: 600
	maximumWidth: 375
	minimumWidth: 375
	visible: true
	title: qsTr("VDM22")
	Rectangle{
		id: rectangle_display
		width: 256
		height: 256
		anchors.top: parent.top
		anchors.left: parent.left
		anchors.margins: 15
		color: "#010101"
		border.color: "#607D8B"
		border.width: 3
		radius: width*1
		Image{
			id: image_display
			width: parent.width
			height: parent.height
		}
	}

		Text {
			id: text_stickX
			anchors.left: rectangle_display.right
			anchors.top: parent.top
			anchors.margins: 5
			text: qsTr("STICK_X")
		}
		Text {
			id: text_stickY
			text: qsTr("STICK_Y")
			anchors.left: text_stickX.right
			anchors.top: parent.top
			anchors.margins: 5
		}


	Slider{
		id: slider_stickX
		anchors.top: text_stickX.bottom
		anchors.left: text_stickX.left
		anchors.right: text_stickX.right
		anchors.bottom: rectangle_display.bottom
		anchors.margins: 15
		orientation: Qt.Vertical

	}

	Slider{
		id: slider_stickY
		anchors.top: text_stickY.bottom
		anchors.left: text_stickY.left
		anchors.right: text_stickY.right
		anchors.bottom: rectangle_display.bottom
		anchors.margins: 15
		orientation: Qt.Vertical
	}

	Button{
		id: button_ARM
		anchors.top: rectangle_display.bottom
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.margins: 15
		text: "ARM"
	}
	Button{
		id: button_BUZ
		anchors.top: button_ARM.bottom
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.margins: 15
		text: "BUZ"
	}
	Button{
		id: button_RWR
		anchors.top: button_BUZ.bottom
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.margins: 15
		text: "RWR"
	}
	Button{
		id: button_LD
		anchors.top: button_RWR.bottom
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.margins: 15
		text: "LD"
	}
}


/*##^##
Designer {
	D{i:0;formeditorZoom:0.75}
}
##^##*/
