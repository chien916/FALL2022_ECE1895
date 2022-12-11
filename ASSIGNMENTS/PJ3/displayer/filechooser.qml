import QtQuick 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Controls 2.15
import QtQuick.Window 2.1
import QtQuick.Layouts 1.15
import Qt.labs.folderlistmodel 2.15
import QtWebView 1.15

Rectangle {
	id: root_fileChooser
	objectName: "root_fileChooser"
	property string htmlContent: ""
	onHtmlContentChanged: webview_htmlViewer.loadHtml(htmlContent)
	Button {
		id: testButton
		text: "上传/Upload"
		onClicked: fileDialog.open()
	}

	FileDialog {
		id: fileDialog
		title: "Choose File"
		selectExisting: true
		selectMultiple: false
		onAccepted: {
			var file = new File(fileDialog.fileUrl)
			file.open(Qt.ReadOnly)
			var fileData = file.readAll()
			// Use the fileData variable to access the contents of the file as a byte array
		}
	}

	WebView {
		id: webview_htmlViewer
		anchors.fill: parent
		anchors.topMargin: 64
	}
}

/*##^##
Designer {
	D{i:0;autoSize:true;formeditorZoom:0.33;height:480;width:640}
}
##^##*/

