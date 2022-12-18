import QtQuick 2.15
import QtQuick.Window 2.3
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Rectangle {
	implicitHeight: 480
	implicitWidth: 400
	id: rootRectangle_myDebugger
	objectName: "rootRectangle_myDebugger"
	color: "transparent"
	//	border.color: "#ffffff"
	clip: true
	Text {
		anchors.fill: parent
		text: MyServer ? MyServer.debuggerMessages_q : "-> Debugger Initializing..."
		color: MyStyle.color_neutral900
		font.family: "YaHei Fira Icon Hybrid"
		font.pixelSize: MyStyle.param_fontSize
		wrapMode: Text.Wrap
		fontSizeMode: Text.VerticalFit
	}
}
/*##^##
Designer {
	D{i:0;autoSize:true;formeditorZoom:0.75;height:480;width:640}
}
##^##*/

