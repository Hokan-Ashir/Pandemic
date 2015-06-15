#include <boost/log/utility/setup/from_stream.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>
#include <boost/log/utility/setup/filter_parser.hpp>
#include <boost/log/attributes/clock.hpp>
#include <boost/log/trivial.hpp>
#include <fstream>
#include <Headers/Auto.h>

void InitPre()
{
	EE_INIT();
	App.flag = APP_MS_EXCLUSIVE;	
	
	boost::log::register_simple_formatter_factory< boost::log::trivial::severity_level, char >("Severity");
	boost::log::register_simple_filter_factory<boost::log::trivial::severity_level>("Severity");
	boost::log::core::get()->add_global_attribute("TimeStamp", boost::log::attributes::local_clock());

	std::ifstream file("logging.ini");
	boost::log::init_from_stream(file);	

	BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
	BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
	BOOST_LOG_TRIVIAL(info) << "An informational severity message";
	BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
	BOOST_LOG_TRIVIAL(error) << "An error severity message";
	BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";
}

Bool Init()
{	
	return true;
}

void Shut()
{
}

Bool Update()
{	
	return true;
}

void Render()
{
}

void Draw()
{
}
