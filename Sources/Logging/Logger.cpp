#include <boost/log/utility/setup/from_stream.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>
#include <boost/log/utility/setup/filter_parser.hpp>
#include <boost/log/attributes/clock.hpp>
#include <boost/log/trivial.hpp>

#include <fstream>

#include <Headers/Logging/Logger.h>

namespace pan {
	void Logger::trace(const char* message) {
		BOOST_LOG_TRIVIAL(trace) << message;
	}

	void Logger::debug(const char* message) {
		BOOST_LOG_TRIVIAL(debug) << message;
	}

	void Logger::info(const char* message) {
		BOOST_LOG_TRIVIAL(info) << message;
	}

	void Logger::warning(const char* message) {
		BOOST_LOG_TRIVIAL(warning) << message;
	}

	void Logger::error(const char* message) {
		BOOST_LOG_TRIVIAL(error) << message;
	}

	void Logger::fatal(const char* message) {
		BOOST_LOG_TRIVIAL(fatal) << message;
	}

	Logger::Logger() {
		initialize();
	}

	Logger::~Logger() {
	}

	void Logger::initialize() {
		boost::log::register_simple_formatter_factory< boost::log::trivial::severity_level, char >("Severity");
		boost::log::register_simple_filter_factory<boost::log::trivial::severity_level>("Severity");
		boost::log::core::get()->add_global_attribute("TimeStamp", boost::log::attributes::local_clock());

		std::ifstream file("logging.ini");
		boost::log::init_from_stream(file);
	}
}