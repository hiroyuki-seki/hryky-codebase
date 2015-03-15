/*
  @file         test_display.cpp
  @brief        tests an initialization of video display.
  @author       HRYKY
  @version      $Id: test_display.cpp 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/log.h"
#include "hryky/display.h"
#include "hryky/range.h"
#include "hryky/window.h"
#include "hryky/testing.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace test
{
namespace
{
	// enregisters a test
	class Test : hryky::testing::unit::Base
	{
	public :
		typedef testing::unit::Base base_type;
		typedef Test this_type;
		
		Test()
			: hryky::testing::unit::Base("display")
		{
		}
		
	private :
		Test(this_type const &);
		this_type & operator=(this_type const &);
		
		// tests an initialization of video display.
		virtual bool run_impl();
	};
	Test const g_test;

	typedef display::config_type config_type;
	typedef Vector<config_type> configs_type;

}
} // namespace test
} // namespace hryky
//------------------------------------------------------------------------------
// global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace test
{
namespace
{
/**
  @brief tests an initialization of video display.
 */
bool Test::run_impl()
{
	// initializes the output of log
	testing::Log log(*this);

	// collects the information of the available displaies
	display::Environment display;
	if (!display.reset()) {
		hryky_log_alert(
			"failed to reset display "
			<< (json::writer()));
		return false;
	}

	log.writer() << "display environment" << display;

	configs_type configs;

	display.traverse([&configs](config_type const & config) {
		configs.push_back(config);
		return true;
	});

	configs_type::iterator begin = configs.begin();
	configs_type::iterator end = configs.end();

	end = ::std::partition(begin, end, [](config_type const & config) {
		return (
			60 <= config.refresh_rate()
			&& 3 <= config.format().traits().bytes()
			&& (config.size().x() / 16) == (config.size().y() / 9)
			&& 1024 <= config.size().x());
	});

	log.writer() << "candidates of display configs" << range(begin, end);

	::std::sort(begin, end, [](
		config_type const & lhs, config_type const & rhs) {
		return lhs.size().x() > rhs.size().x();
	});

	log.writer() << "sorted candidates of display configs" << range(begin, end);

	return true;
}
}
} // namespace test
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
