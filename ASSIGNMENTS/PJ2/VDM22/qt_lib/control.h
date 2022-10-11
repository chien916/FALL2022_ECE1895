#ifndef CONTROL_H
#define CONTROL_H


class Control {
  public:
	void digitalToAnalog(const bool (&digitalSignal)[8], short& analogSignal);
	void analogToDigital(const short& analogSignal, bool (&digitalSignal)[8]);
	virtual void digitalOutputBuzzer(const bool digitalSignal);
	virtual void digitalOutputRwr1Led(const bool digitalSignal);
	virtual void digitalOutputRwr2Led(const bool digitalSignal);
	virtual void digitalOutputStickXAxisSliderVoltage(const bool (&digitalSignal)[8]);
	virtual void digitalOutputStickYAxisSliderVoltage(const bool (&digitalSignal)[8]);
  public:
	virtual void onLaunchButtonPressed();
	virtual void onCounterMeasureButtonPressed();
	virtual void onPiperUpButtonPressed();
	virtual void onPiperDownButtonPressed();
	virtual void onStickXAxisSliderChanged();
	virtual void onStickYAxisSliderChanged();
};

inline void Control::digitalToAnalog(const bool (&digitalSignal)[8], short& analogSignal) {
	analogSignal = 0;
	for(int i = 0; i < 8; ++i) {
		analogSignal += digitalSignal[i] ? 1 << i : 0;

	}
}

inline void Control::analogToDigital(const short &analogSignal, bool (&digitalSignal)[8]) {
	int i = 0;
	short analogSignalCopy = analogSignal;
	while(analogSignalCopy != 0 ) {

	}
}


#endif // CONTROL_H
