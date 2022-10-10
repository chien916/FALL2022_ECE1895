#ifndef QPIXELOBJECT_H
#define QPIXELOBJECT_H

#include <QObject>

#include "lib/pixelobject.h"
class QPixelObject: public PixelObject, QObject{
	Q_OBJECT
public:
	QPixelObject(QObject *parent):QObject(parent){}
signals:

public slots:

private:
};

#endif // QPIXELOBJECT_H
