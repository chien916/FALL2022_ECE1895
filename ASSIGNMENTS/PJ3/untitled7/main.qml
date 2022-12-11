import QtQuick 2.15
import QtQuick.Window 2.15

//import QtSensors 5.15
//import QtBluetooth 5.15
Window {
	width: 640
	height: 480
	visible: true
	Loader {
		anchors.fill: parent
		objectName: "loader_loader"
		source: "qrc:/debugger.qml"
	}

	//	title: qsTr("Hello World")

	//	// The tilt sensor
	//	TiltSensor {
	//		id: tiltSensor

	//		// This signal is emitted when new data is available from the sensor
	//		onDataChanged: {
	//			// Update the value of the tilt sensor data attribute on the Bluetooth server
	//			bluetoothServer.updateAttributeValue(1, data)
	//		}
	//	}
}
