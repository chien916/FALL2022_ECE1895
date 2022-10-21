#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H


/**
 * 接口——交流器
 * @brief The Communicator class
 * @tparam B 数字信号位宽
 * @tparam D 用于代表数字信号的数据类型
 * @tparam A 用于代表模拟信号的数据类型
 * @tparam T 存储像素坐标的基本数据类型
 */
template <unsigned char B, typename T, typename D, typename A>
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
	A analogInputStickXAxisBuffer{0};
	A analogInputStickYAxisBuffer{0};

	/**
	 * 属性——即将要发送到针脚的数字信号电平缓冲区
	 * @brief Communicator::digitalOutput[*]Buffer
	 */
	bool digitalOutputBuzzerBuffer{false};
	bool digitalOutputRwr1LedBuffer{false};
	bool digitalOutputRwr2LedBuffer{false};
	A analogOutputStickXAxisSliderVoltageBuffer {0};
	A analogOutputStickYAxisSliderVoltageBuffer {0};

	/**
	 * 将B位宽的数字信号转换成模拟信号
	 * @brief digitalToAnalog
	 * @param analogSignal 模拟信号
	 * @return 数字信号
	 */
	A digitalToAnalog (const D& analogSignal);

	/**
	 * 将模拟信号转换成B位宽的数字信号
	 * @brief analogToDigital
	 * @param analogSignal 模拟信号
	 * @return 数字信号
	 */
	D analogToDigital(const A& analogSignal);



	/**
	 * 平台差异化接口
	 * 将缓冲器中的输出针脚电平更新到针脚上
	 * @brief platformSpecificUpdateBufferToPins
	 */
	virtual bool platformSpecificUpdateBufferToPins() = 0;

	/**
	 * 平台差异化接口
	 * 将针脚上的电平更新到缓冲器中
	 * @brief platformSpecificUpdateBufferToPins
	 */
	virtual bool platformSpecificUpdatePinsToBuffer() = 0;

	/**
	 * 平台差异化接口
	 * 将某个像素点亮
	 * @brief platformSpecificFlashPixelToScreen
	 */
	virtual bool platformSpecificFlashPixelToScreen(const T x,const T y) = 0;
};

template <unsigned char B, typename T, typename D, typename A>
inline void Communicator<B, T, D, A>::buildVerboseMessage(char *messageText) {
	platformSpecificPrint(messageText);
}

template <unsigned char B, typename T, typename D, typename A>
inline void Communicator<B, T, D, A>::buildCriticalMessage(char *messageText) {
	this->buildVerboseMessage(messageText);
	platformSpecificExit();
}


template <unsigned char B, typename T, typename D, typename A>
inline A Communicator<B, T, D, A>::digitalToAnalog(const D &digitalSignal) {
	A analogSignal = 0;
	for(unsigned char ind = 0; ind < B; ++ind) {
		analogSignal += digitalSignal & (1 << ind) ? (1 << ind) : 0;
	}
	return analogSignal;
}


template <unsigned char B, typename T, typename D, typename A>
inline D Communicator<B, T, D, A>::analogToDigital(const A &analogSignal) {
	D digitalSignal = 0;
	A analogSignalCopy = analogSignal;
	for(unsigned char ind = 0; ind < B; ++ind) {
		digitalSignal |= static_cast<bool>(analogSignalCopy % 2);
		analogSignalCopy >>= 1;
	}
}

#endif // COMMUNICATOR_H
