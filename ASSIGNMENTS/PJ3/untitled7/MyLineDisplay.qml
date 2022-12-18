import QtQuick 2.15

Rectangle {
	id: rootRectangle_myLineDisplay
	property string dispText: "!!!NOT!IN!SERVICE!!!"
	color: "transparent"
	implicitHeight: text_backgroundText.paintedHeight
	implicitWidth: 200
	Text {
		id: text_backgroundText
		anchors.fill: parent
		font.family: "DSEG14 Classic"
		font.pixelSize: MyStyle.param_largeFontSize * 4
		horizontalAlignment: Text.AlignHCenter
		verticalAlignment: Text.AlignVCenter
		styleColor: "#ffffff"
		font.letterSpacing: MyStyle.param_lineWidth
		fontSizeMode: Text.Fit
		text: "~~~~~~~~~~~~~~~~~~~~"
		opacity: 0.15
		color: "#ffffff"
	}
	Text {
		id: text_foregroundText
		anchors.fill: parent
		font.family: "DSEG14 Classic"
		font.pixelSize: MyStyle.param_largeFontSize * 4
		horizontalAlignment: Text.AlignHCenter
		verticalAlignment: Text.AlignVCenter
		font.letterSpacing: MyStyle.param_lineWidth
		fontSizeMode: Text.Fit
		text: {
			let toDisplay = parent.dispText
			if (toDisplay.length < 20)
				toDisplay = toDisplay.padEnd(20, '!')
			else if (toDisplay.length > 20)
				toDisplay = toDisplay.substring(0, 20)
			return toDisplay.replace(/\W/g, '!').replace(' ', '!')
		}
		color: MyStyle.color_neutralWhite
	}
}

/*##^##
Designer {
	D{i:0;autoSize:true;formeditorZoom:0.75;height:480;width:640}
}
##^##*/
