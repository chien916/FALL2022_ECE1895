#ifndef MYGAMESERVER_H
#define MYGAMESERVER_H

#include <QObject>
#include <qtplayable.h>

class MyGameServer:public QObject
{
Q_OBJECT
private:

public:

	MyGameServer(QObject *parent = nullptr):QObject(parent){};
};


#endif // MYGAMESERVER_H
