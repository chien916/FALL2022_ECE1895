#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

template <unsigned int B>
class Communicator {
  private:
	bool digitalOutputBuzzerBuffer{false};
	bool digitalOutputRwr1LedBuffer{false};
	bool digitalOutputRwr2LedBuffer{false};
	bool digitalOutputStickXAxisSliderVoltageBuffer[B] {false};
	bool digitalOutputStickYAxisSliderVoltageBuffer[B] {false};
	void digitalToAnalog(const bool (&digitalSignal)[B], int& analogSignal);
	void analogToDigital(const int& analogSignal, bool (&digitalSignal)[B]);
  public:
	bool getDigitalOutputBuzzerBuffer() const;
	void setDigitalOutputBuzzerBuffer(bool newDigitalOutputBuzzerBuffer);
	bool getDigitalOutputRwr1LedBuffer() const;
	void setDigitalOutputRwr1LedBuffer(bool newDigitalOutputRwr1LedBuffer);
	bool getDigitalOutputRwr2LedBuffer() const;
	void setDigitalOutputRwr2LedBuffer(bool newDigitalOutputRwr2LedBuffer);
	bool getDigitalOutputStickXAxisSliderVoltageBuffer(unsigned int ind) const;
	void setDigitalOutputStickXAxisSliderVoltageBuffer(unsigned int ind, bool digitalOutput);
	void setDigitalOutputStickXAxisSliderVoltageBuffer(int analogOutput);
	bool getDigitalOutputStickYAxisSliderVoltageBuffer(unsigned int ind) const;
	void setDigitalOutputStickYAxisSliderVoltageBuffer(unsigned int ind, bool digitalOutput);
	void setDigitalOutputStickYAxisSliderVoltageBuffer(int analogOutput);

	virtual void platformSpecificUpdateDigitalOutputBufferToPins();
	virtual void platformSpecificOnDigitalInputLaunchButtonEvent(const bool digitalInput);
	virtual void platformSpecificOnDigitalInputCounterMeasureButtonEvent(const bool digitalInput);
	virtual void platformSpecificOnDigitalInputPiperUpButtonEvent(const bool digitalInput);
	virtual void platformSpecificOnDigitalInputPiperDownButtonEvent(const bool digitalInput);
	virtual void platformSpecificOnAnalogInputStickXAxisSliderEvent(const int analogInput);
	virtual void platformSpecificOnAnalogInputStickYAxisSliderEvent(const int analogInput);
};





/**
 * 将B位宽的数字信号转换成模拟信号
 * @brief Communicator::digitalToAnalog
 * @param analogSignal 模拟信号
 */
template <unsigned int B>
inline void Communicator<B>::digitalToAnalog(const bool (&digitalSignal)[B], int& analogSignal) {
	analogSignal = 0;
	for(int i = 0; i < B; ++i) {
		analogSignal += digitalSignal[i] ? 1 << i : 0;

	}
}

/**
 * 将模拟信号转换成B位宽的数字信号
 * @brief Communicator::analogToDigital
 * @param analogSignal
 */
template <unsigned int B>
inline void Communicator<B>::analogToDigital(const int &analogSignal, bool (&digitalSignal)[B]) {
	int i = 0;
	short analogSignalCopy = analogSignal;
	for(bool& it : digitalSignal) {
		it = 0;
	}
	while(analogSignalCopy != 0 ) {
		if(analogSignalCopy % 2 != 0) {
			digitalSignal[i];
		}
		++i;
		analogSignalCopy >>= 1;
	}
}

/**
 * 获取——缓冲区中等待输出的蜂鸣器电平值
 * @brief Communicator::getDigitalOutputBuzzerBuffer
 * @return 电平值；是为高电平，非为低电平
 */
template<unsigned int B>
inline bool Communicator<B>::getDigitalOutputBuzzerBuffer() const {

}

/**
 * @brief Communicator::setDigitalOutputBuzzerBuffer
 * @param newDigitalOutputBuzzerBuffer 电平值；是为高电平，非为低电平
 */
template<unsigned int B>
inline void Communicator<B>::setDigitalOutputBuzzerBuffer(bool newDigitalOutputBuzzerBuffer) {

}

/**
 * 获取——缓冲区中等待输出的第一指示灯电平值
 * @brief Communicator::getDigitalOutputRwr1LedBuffer
 * @return 电平值；是为高电平，非为低电平
 */
template<unsigned int B>
inline bool Communicator<B>::getDigitalOutputRwr1LedBuffer() const {

}
/**
 * @brief Communicator::setDigitalOutputRwr1LedBuffer
 * @param newDigitalOutputRwr1LedBuffer 电平值；是为高电平，非为低电平
 */
template<unsigned int B>
inline void Communicator<B>::setDigitalOutputRwr1LedBuffer(bool newDigitalOutputRwr1LedBuffer) {

}

/**
 * 获取——缓冲区中等待输出的第二指示灯电平值
 * @brief Communicator::getDigitalOutputRwr2LedBuffer
 * @return 电平值；是为高电平，非为低电平
 */
template<unsigned int B>
inline bool Communicator<B>::getDigitalOutputRwr2LedBuffer() const {

}

/**
 *
 * @brief Communicator::setDigitalOutputRwr2LedBuffer
 * @param newDigitalOutputRwr2LedBuffer 电平值；是为高电平，非为低电平
 */
template<unsigned int B>
inline void Communicator<B>::setDigitalOutputRwr2LedBuffer(bool newDigitalOutputRwr2LedBuffer) {

}

/**
 * 获取——缓冲区中等待输出的蜂鸣器电平值
 * @brief Communicator::getDigitalOutputStickXAxisSliderVoltageBuffer
 * @param ind
 * @return 电平值；是为高电平，非为低电平
 */
template<unsigned int B>
inline bool Communicator<B>::getDigitalOutputStickXAxisSliderVoltageBuffer(unsigned int ind) const {

}

/**
 * @brief Communicator::setDigitalOutputStickXAxisSliderVoltageBuffer
 * @param ind
 * @param digitalOutput 电平值；是为高电平，非为低电平
 */
template<unsigned int B>
inline void Communicator<B>::setDigitalOutputStickXAxisSliderVoltageBuffer(unsigned int ind, bool digitalOutput) {

}

/**
 *
 * @brief Communicator::setDigitalOutputStickXAxisSliderVoltageBuffer
 * @param analogOutput 电平值
 */
template<unsigned int B>
inline void Communicator<B>::setDigitalOutputStickXAxisSliderVoltageBuffer(int analogOutput) {

}

/**
 * 获取——缓冲区中等待输出的蜂鸣器电平值
 * @brief Communicator::getDigitalOutputStickYAxisSliderVoltageBuffer
 * @param ind
 * @return 电平值；是为高电平，非为低电平
 */
template<unsigned int B>
inline bool Communicator<B>::getDigitalOutputStickYAxisSliderVoltageBuffer(unsigned int ind) const {

}

/**
 * @brief Communicator::setDigitalOutputStickYAxisSliderVoltageBuffer
 * @param ind
 * @param digitalOutput 电平值；是为高电平，非为低电平
 */
template<unsigned int B>
inline void Communicator<B>::setDigitalOutputStickYAxisSliderVoltageBuffer(unsigned int ind, bool digitalOutput) {

}

/**
 * @brief Communicator::setDigitalOutputStickYAxisSliderVoltageBuffer
 * @param analogOutput 电平值
 */
template<unsigned int B>
inline void Communicator<B>::setDigitalOutputStickYAxisSliderVoltageBuffer(int analogOutput) {

}

/**
 * @brief Communicator::platformSpecificUpdateDigitalOutputBufferToPins
 */
template<unsigned int B>
inline void Communicator<B>::platformSpecificUpdateDigitalOutputBufferToPins() {}

/**
 * @brief Communicator::platformSpecificOnDigitalInputLaunchButtonEvent
 * @param digitalInput 电平值；是为高电平，非为低电平
 */
template<unsigned int B>
inline void Communicator<B>::platformSpecificOnDigitalInputLaunchButtonEvent(const bool digitalInput) {}

/**
 * @brief Communicator::platformSpecificOnDigitalInputCounterMeasureButtonEvent
 * @param digitalInput 电平值；是为高电平，非为低电平
 */
template<unsigned int B>
inline void Communicator<B>::platformSpecificOnDigitalInputCounterMeasureButtonEvent(const bool digitalInput) {}

/**
 * @brief Communicator::platformSpecificOnDigitalInputPiperUpButtonEvent
 * @param digitalInput 电平值；是为高电平，非为低电平
 */
template<unsigned int B>
inline void Communicator<B>::platformSpecificOnDigitalInputPiperUpButtonEvent(const bool digitalInput) {}

/**
 * @brief Communicator::platformSpecificOnDigitalInputPiperDownButtonEvent
 * @param digitalInput 电平值；是为高电平，非为低电平
 */
template<unsigned int B>
inline void Communicator<B>::platformSpecificOnDigitalInputPiperDownButtonEvent(const bool digitalInput) {}

/**
 * @brief Communicator::platformSpecificOnAnalogInputStickXAxisSliderEvent
 * @param analogInput 电平值；是为高电平，非为低电平
 */
template<unsigned int B>
inline void Communicator<B>::platformSpecificOnAnalogInputStickXAxisSliderEvent(const int analogInput) {}

/**
 * @brief Communicator::platformSpecificOnAnalogInputStickYAxisSliderEvent
 * @param analogInput 电平值
 */
template<unsigned int B>
inline void Communicator<B>::platformSpecificOnAnalogInputStickYAxisSliderEvent(const int analogInput) {}
#endif // COMMUNICATOR_H
