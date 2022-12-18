import QtQuick 2.15
import QtQuick.Window 2.3
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

//import QtSensors 5.15
//import QtBluetooth 5.15
ApplicationWindow {
	id: applicationwindow_applicationwindow
	objectName: "root_main"
	width: 640
	height: 480
	visible: true
	//	onAfterRendering: PropertyAnimation{
	//		target:
	//	//	}
	MyBase {
		anchors.fill: parent
		Component.onCompleted: MyStyle.baseValue = Math.min(width,
															height) * 0.03
	}
	//	onHeightChanged: MyStyle.baseValue = Math.min(width, height) * 0.03
	//	onWidthChanged: MyStyle.baseValue = Math.min(width, height) * 0.03
}
