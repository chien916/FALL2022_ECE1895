#ifndef EXCEPTION_H
#define EXCEPTION_H
class Exception {
  private:
	virtual void showMessageAndExitProgram(char* errorMessage);
  public:
	Exception(char* errorMessage);
};

/**
 * 平台差异化接口
 * 利用平台特定的方式显示消息并且结束程序运行
 * @brief Exception::Exception
 * @param errorMessage 异常消息提示
 */
inline void Exception::showMessageAndExitProgram(char *errorMessage) {}

/**
 * 构造
 * 抛出一个带有消息提示的异常
 * @brief Exception::Exception
 * @param errorMessage 异常消息提示
 */
inline Exception::Exception(char* errorMessage) {
	this->showMessageAndExitProgram(errorMessage);
}

#endif // EXCEPTIONHANDLER_H
