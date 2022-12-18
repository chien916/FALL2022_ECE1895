pragma Singleton

import QtQuick 2.15

Item {
	property int baseValue: 10
	readonly property color color_neutral900: "#1A202C"
	readonly property color color_neutral800: "#2D3648"
	//	readonly property color color_neutral700: "#4A5468"
	readonly property color color_neutral600: "#717D96"
	//	readonly property color color_neutral500: "#A0ABC0"
	//	readonly property color color_neutral400: "#CBD2E0"
	readonly property color color_neutral300: "#E2E7F0"
	//	readonly property color color_neutral200: "#EDF0F7"
	//	readonly property color color_neutral100: "#F7F9FC"
	readonly property color color_neutralWhite: "#FFFFFF"
	readonly property double param_fontSize: baseValue
	readonly property double param_largeFontSize: baseValue * 1.5
	readonly property double param_radius: baseValue
	readonly property double param_lineWidth: baseValue * 0.1
	//	readonly property double param_iconSize: param_lineWidth * 7
	//	FontLoader {
	//		id: fontloader_interbold
	//		source: "qrc:/FONTS/Inter-Bold.ttf"
	//	}
	//	FontLoader {
	//		id: fontloader_interregular
	//		source: "qrc:/FONTS/Inter-Regular.ttf"
	//	}
}
