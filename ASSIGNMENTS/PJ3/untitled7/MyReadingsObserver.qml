import QtQuick 2.15
import QtQuick.Window 2.3
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Rectangle {
	id: rootRectangle_myReadingsObserver
	implicitHeight: 100
	implicitWidth: 400
	color: MyStyle.color_neutral900
	radius: MyStyle.param_radius
	property double xVal: -0
	property double yVal: -0
	property color readingsColor: MyStyle.color_neutral600
	Rectangle {
		id: rightGauge
		x: {
			let xMinimum = rootRectangle_myReadingsObserver.x
				+ rootRectangle_myReadingsObserver.width / 2
			let xMaximum = rootRectangle_myReadingsObserver.x
				+ rootRectangle_myReadingsObserver.width
				- rootRectangle_myReadingsObserver.radius * 2
			let xMiddle = (xMaximum + xMinimum) / 2
			return xMiddle + (xMaximum - xMinimum) / 2 * xVal
		}
		Behavior on x {
			SpringAnimation {
				spring: 1
				damping: 0.2
			}
		}
		color: readingsColor
		anchors.top: rootRectangle_myReadingsObserver.top
		anchors.bottom: rootRectangle_myReadingsObserver.bottom
		radius: MyStyle.param_radius
		width: MyStyle.param_radius * 2
	}
	Rectangle {
		id: rectangle_leftGauge
		x: {
			let xMinimum = rootRectangle_myReadingsObserver.x
			let xMaximum = rootRectangle_myReadingsObserver.x
				+ rootRectangle_myReadingsObserver.width / 2
				- rootRectangle_myReadingsObserver.radius * 2
			let xMiddle = (xMaximum + xMinimum) / 2
			return xMiddle + (xMaximum - xMinimum) / 2 * yVal
		}
		Behavior on x {
			SpringAnimation {
				spring: 1
				damping: 0.2
			}
		}
		color: readingsColor
		anchors.top: rootRectangle_myReadingsObserver.top
		anchors.bottom: rootRectangle_myReadingsObserver.bottom
		radius: MyStyle.param_radius
		width: MyStyle.param_radius * 2
	}
}
