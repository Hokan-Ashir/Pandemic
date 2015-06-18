#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <Headers/ToolClasses/Singleton.h>

class Logger : public Singleton<Logger> {
	SET_SINGLETON(Logger)
public:
	void trace(const char* message);
	void debug(const char* message);
	void info(const char* message);
	void warning(const char* message);
	void error(const char* message);
	void fatal(const char* message);
	
protected:
	Logger();
	virtual ~Logger() override;

private:
	void initialize();
};

#endif