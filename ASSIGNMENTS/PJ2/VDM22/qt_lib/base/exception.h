#ifndef EXCEPTION_H
#define EXCEPTION_H
class Exception {
  protected:
	virtual void showMessageAndExitProgram(char* errorMessage);
  public:
	Exception(char* errorMessage);
};

inline Exception::Exception(char* errorMessage) {
	this->showMessageAndExitProgram(errorMessage);
}

#endif // EXCEPTIONHANDLER_H
