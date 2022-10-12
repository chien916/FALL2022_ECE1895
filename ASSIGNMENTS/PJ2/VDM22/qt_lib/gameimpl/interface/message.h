#ifndef MESSAGE_H
#define MESSAGE_H
class Message {
  private:
	void info(char* messageText);
	void verbose(char* messageText);
	void debug(char* messageText);
	void critical(char* messageText);
	virtual void platformSpecificPrint(char* messageText);
	virtual void platformSpecificDisplay(char* messageText);
	virtual void platformSpecificExit();
  public:
	Message(char messageType, char* messageText);
};

/**
 * 显示消息到应用
 * @brief Message::info
 * @param messageText 消息
 */
inline void Message::info(char *messageText) {
	platformSpecificPrint((char*)("$INFO$"));
	platformSpecificPrint(messageText);
	platformSpecificDisplay(messageText);
}

/**
 * 显示消息到屏幕
 * @brief Message::verbose
 * @param messageText 消息
 */
inline void Message::verbose(char *messageText)
{
	platformSpecificPrint((char*)("$VERBOSE$"));
	platformSpecificPrint(messageText);
}

/**
 * 如果检测到在调试，显示消息
 * @brief Message::debug
 * @param messageText 消息
 */
inline void Message::debug(char *messageText) {
#ifdef DEBUG
	platformSpecificPrint((char*)("$DEBUG$"));
	platformSpecificPrint(messageText);
#endif
}

/**
 * 显示消息并且结束程序运行
 * @brief Message::critical
 * @param messageText 消息
 */
inline void Message::critical(char *messageText) {
	platformSpecificPrint((char*)("$CRITICAL$"));
	platformSpecificPrint(messageText);
	platformSpecificExit();
}

/**
 * 接口
 * 利用平台特定的方式显示消息到屏幕
 * @brief Message::platformSpecificPrint
 * @param messageText
 */
inline void Message::platformSpecificPrint(char *messageText) {}

/**
 * 接口
 * 利用平台特定的方式显示消息到应用
 * @brief Message::platformSpecificPrint
 * @param messageText
 */
inline void Message::platformSpecificDisplay(char *messageText){}

/**
 * 接口
 * 利用平台特定的方式结束程序运行
 * @brief Message::platformSpecificExit
 */
inline void Message::platformSpecificExit() {}

/**
 * 构造
 * 抛出一个带有消息提示的异常
 * @brief Message::Message
 * @param errorMessage 异常消息提示
 */
inline Message::Message(char messageType, char* messageText) {
	switch(messageType) {
	case 'i':
		info(messageText);
		break;
	case 'd':
		debug(messageText);
		break;
	case 'c':
		critical(messageText);
		break;
	default:
		break;
	}
}

#endif // MESSAGE_H
