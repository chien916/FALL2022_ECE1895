#ifndef CONTROL_H
#define CONTROL_H


class Control{
private:

public:
	virtual double getStickXAxis();
	virtual double getStickYAxis();
	virtual bool getLEButton();
	virtual bool getRWRButton();
	virtual bool getBUZButton();
	virtual bool getARMButton();
}

#endif // CONTROL_H
