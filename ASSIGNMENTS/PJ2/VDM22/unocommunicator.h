#include "HardwareSerial.h"
#include "Arduino.h"
#ifndef UNOCOMMUNICATOR_H
#define UNOCOMMUNICATOR_H

#include "qt_lib/communicator.h"

#define UNO_TEMPALTE_B 8
#define UNO_TEMPALTE_T int16_t
#define UNO_TEMPALTE_D int16_t
#define UNO_TEMPALTE_A float
#define UNO_TEMPALTE_PARAM UNO_TEMPALTE_B,UNO_TEMPALTE_T,UNO_TEMPALTE_D,UNO_TEMPALTE_A
//数字针脚和模式


/**
 * 数字模拟转换器需要转换的数字信号的每一位代表的针脚索引
 * 注意！DB0是最右面的位 DB7是最左面的位
 * @brief DIGITALOUTPUT_DAC_DB[*]
 */
#define DIGITALOUTPUT_DAC_DB0 23
#define DIGITALOUTPUT_DAC_DB1 24
#define DIGITALOUTPUT_DAC_DB2 25
#define DIGITALOUTPUT_DAC_DB3 26
#define DIGITALOUTPUT_DAC_DB4 6
#define DIGITALOUTPUT_DAC_DB5 11
#define DIGITALOUTPUT_DAC_DB6 12
#define DIGITALOUTPUT_DAC_DB7 13

/**
 * 数字模拟转换器需要转换的模拟信号输出通道控制
 * 注意！低电平输出到通道A；高电平输出到通道B
 */
#define DIGITALOUTPUT_DAC_AB 14

/**
 * 数字模拟转换器需要转换的模拟信号更新控制组
 * 注意！低电平时会触发
 * 注意！如果低电平被保持，那么WR的高电平会更新输出模拟信号
 */
#define DIGITALOUTPUT_DAC_LDAC 15
#define DIGITALOUTPUT_DAC_WR 16

/**
 * 数字信号输出针脚，包含蜂鸣器和发光二极管
 * @brief DIGITALOUTPUT_[*]
 */
#define DIGITALOUTPUT_BUZZER 15
#define DIGITALOUTPUT_RWR1 2
#define DIGITALOUTPUT_RWR2 3

/**
 * 数字信号输入针脚，包含所有按钮
 * @brief DIGITALINPUT_[*]
 */
#define DIGITALINPUT_LAUNCHBUTTON 4
#define DIGITALINPUT_COUNTERMEASURE 17
#define DIGITALINPUT_PIPERUP 18
#define DIGITALINPUT_PIPERDOWN 19

/**
 * 串行接口针脚
 * 注意！串行针脚被用于发光二极管显示，谨慎使用
 */
#define DIGITALOUTPUT_RX 2
#define DIGITALOUTPUT_TX 3


//模拟针脚和模式
#define ANALOGINPUT_STICKXAXIS 27
#define ANALOGINPUT_STICKYAXIS 28

class UnoCommunicator:public Communicator<UNO_TEMPALTE_PARAM> {

  public:
	bool serialUsage{ false };
  private:
	void platformSpecificPrint(char *messageText) override final;
	void platformSpecificExit() override final ;
  public:
	UnoCommunicator(bool serialUsage);
	bool platformSpecificUpdateBufferToPins() override final ;
	bool platformSpecificUpdatePinsToBuffer() override final ;
	bool platformSpecificFlashPixelToScreen(const UNO_TEMPALTE_T x, const UNO_TEMPALTE_T y) override final;
	bool platformSpecificClearScreen() override final;
	UNO_TEMPALTE_T platformSpecificRandomGenerator(const UNO_TEMPALTE_T lowerLimit, const UNO_TEMPALTE_T upperLimit) override final;
};


inline UnoCommunicator::UnoCommunicator(bool serialUsage) {

	this->serialUsage = serialUsage;
	pinMode(DIGITALOUTPUT_DAC_DB0, OUTPUT);
	pinMode(DIGITALOUTPUT_DAC_DB1, OUTPUT);
	pinMode(DIGITALOUTPUT_DAC_DB2, OUTPUT);
	pinMode(DIGITALOUTPUT_DAC_DB3, OUTPUT);
	pinMode(DIGITALOUTPUT_DAC_DB4, OUTPUT);
	pinMode(DIGITALOUTPUT_DAC_DB5, OUTPUT);
	pinMode(DIGITALOUTPUT_DAC_DB6, OUTPUT);
	pinMode(DIGITALOUTPUT_DAC_DB7, OUTPUT);
	pinMode(DIGITALOUTPUT_DAC_AB, OUTPUT);
	pinMode(DIGITALOUTPUT_DAC_LDAC, OUTPUT);
	pinMode(DIGITALOUTPUT_DAC_WR, OUTPUT);
	pinMode(DIGITALOUTPUT_BUZZER, OUTPUT);
	if (this->serialUsage) {
		Serial.begin(9600);
	} else {
		pinMode(DIGITALOUTPUT_RWR1, OUTPUT);
		pinMode(DIGITALOUTPUT_RWR2, OUTPUT);
	}
	pinMode(DIGITALINPUT_LAUNCHBUTTON, INPUT);
	pinMode(DIGITALINPUT_COUNTERMEASURE, INPUT);
	pinMode(DIGITALINPUT_PIPERUP, INPUT);
	pinMode(DIGITALINPUT_PIPERDOWN, INPUT);

}

inline bool UnoCommunicator::platformSpecificUpdateBufferToPins()
{

}

inline bool UnoCommunicator::platformSpecificUpdatePinsToBuffer()
{

}

inline bool UnoCommunicator::platformSpecificFlashPixelToScreen(const UNO_TEMPALTE_T x, const UNO_TEMPALTE_T y)
{

}

inline bool UnoCommunicator::platformSpecificClearScreen()
{

}

inline UNO_TEMPALTE_T UnoCommunicator::platformSpecificRandomGenerator(const UNO_TEMPALTE_T lowerLimit, const UNO_TEMPALTE_T upperLimit)
{
	return static_cast<UNO_TEMPALTE_T>(random(lowerLimit,upperLimit));
}

inline void UnoCommunicator::platformSpecificPrint(char *messageText)
{
	Serial.print(messageText);
}

inline void UnoCommunicator::platformSpecificExit()
{
	exit(1);
}

#endif
