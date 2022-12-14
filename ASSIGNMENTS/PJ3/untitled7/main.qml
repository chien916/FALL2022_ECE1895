import QtQuick 2.15
import QtQuick.Window 2.3
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

//import QtSensors 5.15
//import QtBluetooth 5.15
ApplicationWindow {
	id: applicationwindow_applicationwindow
	width: 640
	height: 480
	visible: true
	//	onAfterRendering: PropertyAnimation{
	//		target:
	//	}
	MyBase {
		anchors.fill: parent
		Component.onCompleted: reconfigureMyStyle()
	}
	onHeightChanged: reconfigureMyStyle()
	onWidthChanged: reconfigureMyStyle()

	function reconfigureMyStyle() {
		MyStyle.baseValue = Math.min(width, height) * 0.03
		MyServer.disp("reconfigued base value" + MyStyle.baseValue)
	}
}
