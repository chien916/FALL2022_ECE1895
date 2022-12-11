#ifndef CURSORCONTROLLER_H
#define CURSORCONTROLLER_H
#include <QObject>
#include <QCursor>
#include <QKeyEvent>
#include <QEvent>
#include <QDebug>
class CursorController: public QObject {
	Q_OBJECT
	// QObject interface
  protected:
	void timerEvent(QTimerEvent *event) override final;

	// QObject interface
  public:
	bool eventFilter(QObject *watched, QEvent *event) override final;
};

inline void CursorController::timerEvent(QTimerEvent *event) {
//	QCursor::setPos(0, 0);
}

inline bool CursorController::eventFilter(QObject *watched, QEvent *event) {
	// Check if the event is a keyboard event
	if (event->type() == QEvent::KeyPress) {
		// The event is a keyboard event
		// Cast the event to a QKeyEvent
		QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

		// Check if the Alt+Tab key combination was pressed
		if (keyEvent->modifiers() == Qt::AltModifier) {
			// The Alt+Tab key combination was pressed
			// Ignore the event and return false to prevent it from being processed further
			qInfo() << "HEY";
			return false;
		}
	}
}
#endif // CURSORCONTROLLER_H
