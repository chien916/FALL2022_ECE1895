#ifndef QCONTROL_H
#define QCONTROL_H
#include <QObject>
#include "control.h"

class QControl: public Control, QObject{


	// Control interface
public:


	// Control interface
public:
	void onLaunchButtonPressed() Q_DECL_OVERRIDE;
	void onCounterMeasureButtonPressed() Q_DECL_OVERRIDE;
	void onPiperUpButtonPressed() Q_DECL_OVERRIDE;
	void onPiperDownButtonPressed() Q_DECL_OVERRIDE;
	void onArmSwitchToggled() Q_DECL_OVERRIDE;
	void onStickXAxisSliderChanged() Q_DECL_OVERRIDE;
	void onStickYAxisSliderChanged() Q_DECL_OVERRIDE;
};

#endif // QCONTROL_H
