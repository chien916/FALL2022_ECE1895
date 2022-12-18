import QtQuick 2.15
import QtQuick.Window 2.3
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Rectangle {
	id: rootRectangle_myDisplay
	implicitHeight: 400
	implicitWidth: 500
	color: MyStyle.color_neutral900
	radius: MyStyle.param_radius
	property int numberOfLines: 5
	property string dispText: "t\ne\ngeeg"
	onDispTextChanged: passDispTextToLines()
	Column {
		id: column_linesOfDisplay
		anchors.fill: parent
		anchors.margins: MyStyle.param_lineWidth * 10
		spacing: MyStyle.param_lineWidth * 10
		clip: true
		Repeater {
			id: repeater_linesOfDisplay
			model: numberOfLines
			delegate: MyLineDisplay {
				anchors.left: column_linesOfDisplay.left
				anchors.right: column_linesOfDisplay.right
				height: (column_linesOfDisplay.height
						 - (column_linesOfDisplay.spacing
							* (rootRectangle_myDisplay.numberOfLines - 1)))
						/ rootRectangle_myDisplay.numberOfLines
			}
			Component.onCompleted: passDispTextToLines()
		}
	}

	function passDispTextToLines() {
		let splittedDispText = rootRectangle_myDisplay.dispText.split('\n')
		let smallerIndex = Math.min(rootRectangle_myDisplay.numberOfLines,
									splittedDispText.length)
		for (var i = 0; i < smallerIndex; ++i) {
			if (repeater_linesOfDisplay.itemAt(i) !== null)
				repeater_linesOfDisplay.itemAt(i).dispText = i
						< splittedDispText.length ? splittedDispText[i] : "!!!!-!!!!!-!!!!!-!!!"
		}
	}
}

/*##^##
Designer {
	D{i:0;formeditorZoom:1.1}
}
##^##*/
