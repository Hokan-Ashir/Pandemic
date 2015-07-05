#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <Headers/ToolClasses/Singleton.h>

namespace pan {

	/**
	 * Wrapper around boost::log root logger
	 */
	class Logger final : public Singleton<Logger> {
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
		/**
		 * Logger configuration file name  <p>
		 * Must be placed in same folder, where executable lay
		 */
		const std::string LOGGER_CONFIG_FILE = "logging.ini";

		/**
		 * Initialize logging system 
		 *		- initiazlie paramters that must be used for parsing configuration file
		 *		- load config file
		 *		- initialize root boost::log logger via loaded config file
		 */
		void initialize();
	};
}

#endif