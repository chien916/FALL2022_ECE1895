import QtQuick 2.15

Rectangle {
	id: rootRectangle_myDialer
	implicitHeight: 500
	implicitWidth: 600
	color: MyStyle.color_neutral900
	radius: MyStyle.param_radius
	property bool isClient: true
	property color buttonsColor: MyStyle.color_neutral600
	property color buttonColor2: MyStyle.color_neutral800
	property color buttonLabelColor: MyStyle.color_neutral300
	//	property bool topButtonsEnabled: true
	//	property bool bottomButtonsEnabled: true
	signal buttonClicked(string buttonText)
	Grid {
		id: grid_buttons
		rows: isClient ? 4 : 1
		columns: isClient ? 4 : 1
		anchors.top: parent.top
		anchors.left: parent.left
		anchors.right: parent.right
		height: parent.height * 0.7
		anchors.margins: MyStyle.param_lineWidth * 10
		spacing: MyStyle.param_lineWidth * 10
		Repeater {
			id: repeater_buttons
			model: isClient ? ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"] : ["CL"]
			delegate: Rectangle {
				width: (grid_buttons.width - (grid_buttons.columns - 1)
						* grid_buttons.spacing) / grid_buttons.columns
				height: (grid_buttons.height - (grid_buttons.rows - 1)
						 * grid_buttons.spacing) / grid_buttons.rows
				radius: mouseArea_button.pressed ? MyStyle.param_radius * 4 : MyStyle.param_radius
				Behavior on radius {
					SpringAnimation {
						spring: 5
						damping: 500
					}
				}

				color: mouseArea_button.pressed ? buttonsColor : buttonColor2
				Behavior on color {
					ColorAnimation {
						duration: 200
					}
				}

				Text {
					anchors.fill: parent
					anchors.margins: mouseArea_button.pressed ? MyStyle.param_lineWidth
																* 10 : MyStyle.param_lineWidth * 5
					Behavior on anchors.margins {
						SpringAnimation {
							spring: 5
							damping: 500
						}
					}
					font.family: "STHeiti TC"
					font.pixelSize: MyStyle.param_largeFontSize * 10
					horizontalAlignment: Text.AlignHCenter
					verticalAlignment: Text.AlignVCenter
					fontSizeMode: Text.Fit
					id: text_buttonLabel
					visible: isClient
					color: buttonLabelColor
					text: modelData
				}
				MouseArea {
					id: mouseArea_button
					anchors.fill: parent
					onClicked: {
						buttonClicked(modelData)
					}

					onPressAndHold: {
						if (modelData === "CL")
							buttonClicked("HO")
					}
				}
			}
		}
	}
	Grid {
		rows: 1
		columns: isClient ? 3 : 2
		id: grid_bottomButtons
		anchors.top: grid_buttons.bottom
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.bottom: parent.bottom
		anchors.margins: MyStyle.param_lineWidth * 10
		spacing: MyStyle.param_lineWidth * 10
		Repeater {

			id: repeater_bottomButtons
			model: isClient ? ["确认/OK", "地址/AD", "开关/PO"] : ["校正/CA", "开关/PO"]
			delegate: Rectangle {
				width: (grid_bottomButtons.width - (grid_bottomButtons.columns - 1)
						* grid_bottomButtons.spacing) / grid_bottomButtons.columns
				height: (grid_bottomButtons.height - (grid_bottomButtons.rows - 1)
						 * grid_bottomButtons.spacing) / grid_bottomButtons.rows
				radius: mouseArea_buttomButton.pressed ? MyStyle.param_radius
														 * 4 : MyStyle.param_radius
				Behavior on radius {
					SpringAnimation {
						spring: 5
						damping: 500
					}
				}

				color: mouseArea_buttomButton.pressed ? buttonsColor : buttonColor2
				Behavior on color {
					ColorAnimation {
						duration: 200
					}
				}

				Text {
					anchors.fill: parent
					anchors.margins: mouseArea_buttomButton.pressed ? MyStyle.param_lineWidth * 30 : MyStyle.param_lineWidth * 10
					Behavior on anchors.margins {
						SpringAnimation {
							spring: 5
							damping: 500
						}
					}
					font.family: "STHeiti TC"
					font.pixelSize: MyStyle.param_largeFontSize * 10
					horizontalAlignment: Text.AlignHCenter
					verticalAlignment: Text.AlignVCenter
					fontSizeMode: Text.Fit
					id: text_buttomButtonLabel
					color: buttonLabelColor
					text: modelData
				}
				MouseArea {
					id: mouseArea_buttomButton
					anchors.fill: parent
					onClicked: buttonClicked(modelData.split('/')[1])
				}
			}
		}
	}
}
