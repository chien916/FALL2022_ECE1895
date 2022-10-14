#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H
/**
 * @brief The Communicator class
 * @tparam B 数字信号位宽
 */
template <unsigned char B>
class Communicator {
  private:
	///**
	// * 接口
	// * 利用平台特定的方式显示消息到屏幕
	// * @brief Communicator::platformSpecificPrint
	// * @param messageText
	// */
	virtual void platformSpecificPrint(char* messageText) = 0;

	///**
	// * 接口
	// * 利用平台特定的方式结束程序运行
	// * @brief Communicator::platformSpecificExit
	// */
	virtual void platformSpecificExit() = 0;
  public:

	/**
	 * 显示消息到屏幕
	 * @brief Communicator::verbose
	 * @param messageText 消息
	 */
	void buildVerboseMessage(char* messageText);

	/**
	 * 显示消息并且结束程序运行
	 * @brief Communicator::critical
	 * @param messageText 消息
	 */
	void buildCriticalMessage(char* messageText);

	bool digitalInputLaunchButtonBuffer{false};
	bool digitalInputCounterMeasureBuffer{false};
	bool digitalInputPiperUpButtonBuffer{false};
	bool digitalInputPiperDownButtonBuffer{false};
	char analogInputStickXAxisBuffer{0};
	char analogInputStickYAxisBuffer{0};

	/**
	 * 属性——即将要发送到针脚的数字信号电平缓冲区
	 * @brief Communicator::digitalOutput[*]Buffer
	 */
	bool digitalOutputBuzzerBuffer{false};
	bool digitalOutputRwr1LedBuffer{false};
	bool digitalOutputRwr2LedBuffer{false};
	char analogOutputStickXAxisSliderVoltageBuffer {0};
	char analogOutputStickYAxisSliderVoltageBuffer {0};

	/**
	 * 将B位宽的数字信号转换成模拟信号
	 * @brief Communicator::digitalToAnalog
	 * @param analogSignal 模拟信号
	 */
	void digitalToAnalog(const bool (&digitalSignal)[B], char& analogSignal);

	/**
	 * 将模拟信号转换成B位宽的数字信号
	 * @brief Communicator::analogToDigital
	 * @param analogSignal
	 */
	void analogToDigital(const char& analogSignal, bool (&digitalSignal)[B]);

	/**
	 * 平台差异化接口
	 * 将缓冲器中的输出针脚电平更新到针脚上
	 * @brief platformSpecificUpdateBufferToPins
	 */
	virtual void platformSpecificUpdateBufferToPins() = 0;

	/**
	 * 平台差异化接口
	 * 将针脚上的电平更新到缓冲器中
	 * @brief platformSpecificUpdateBufferToPins
	 */
	virtual void platformSpecificUpdatePinsToBuffer() = 0;
};

template <unsigned char B>
inline void Communicator<B>::buildVerboseMessage(char *messageText) {
	platformSpecificPrint(messageText);
}

template <unsigned char B>
inline void Communicator<B>::buildCriticalMessage(char *messageText) {
	this->buildVerboseMessage(messageText);
	platformSpecificExit();
}


template <unsigned char B>
inline void Communicator<B>::digitalToAnalog(const bool (&digitalSignal)[B], char& analogSignal) {
	analogSignal = 0;
	for(int i = 0; i < B; ++i) {
		analogSignal += digitalSignal[i] ? 1 << i : 0;
	}
}


template <unsigned char B>
inline void Communicator<B>::analogToDigital(const char &analogSignal, bool (&digitalSignal)[B]) {
	char i = 0;
	char analogSignalCopy = analogSignal;
	for(bool& it : digitalSignal)
		it = 0;
	while(analogSignalCopy != 0 ) {
		if(analogSignalCopy % 2 != 0)
			digitalSignal[i];
		++i;
		analogSignalCopy >>= 1;
	}
}

#endif // COMMUNICATOR_H
