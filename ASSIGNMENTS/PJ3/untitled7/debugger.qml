import QtQuick 2.15

Rectangle {
	objectName: "root_debugger"
	function disp(str) {
		if (listmodel_terminalText.count >= 100) {
			listmodel_terminalText.remove(0)
		}
		listmodel_terminalText.append({
										  "t": str.toString()
									  })
	}

	ListModel {
		id: listmodel_terminalText
		ListElement {
			t: "Debug Window"
		}
		ListElement {
			t: "Version 1.0"
		}
	}

	ListView {
		anchors.fill: parent
		id: listview_terminalText
		model: listmodel_terminalText
		delegate: Text {
			text: t
		}
	}
}
/*##^##
Designer {
	D{i:0;autoSize:true;formeditorZoom:0.66;height:480;width:640}
}
##^##*/

