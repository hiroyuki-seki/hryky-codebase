/*
  @file         test_window.cpp
  @brief        tests a creation of GUI Window.
  @author       HRYKY
  @version      $Id: test_window.cpp 375 2014-07-29 04:27:53Z hryky.private@gmail.com $
 */
#include <precompiled.h>
#include "hryky/testing.h"
#include "hryky/geometry.h"
#include "hryky/window.h"
#include "hryky/log.h"
#include "hryky/opengl.h"
#include "hryky/array.h"
#include "hryky/display.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
#define HRYKY_ENABLE_FULLSCREEN     (0)
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace
{
	char const * const g_test_name = "window";

	// enregisters a test
	class Test : testing::unit::Base
	{
	public :
		typedef testing::unit::Base base_type;
		typedef Test this_type;
		
		Test()
			: testing::unit::Base(g_test_name)
		{
		}
	private :
		Test(this_type const &);
		this_type & operator=(this_type const &);
		
		// tests a creation of GUI Window.
		virtual bool run_impl();
	};
	Test const g_test;

}
}
//------------------------------------------------------------------------------
// global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace
{
/**
  @brief tests a creation of GUI Window.
 */
bool Test::run_impl()
{
	// initializes the output of log
	testing::Log log(*this);
	
	// creates window
	window::Context const window_context;
	if (hryky_is_null(window_context)) {
		hryky_log_alert("failed to create window");
		return false;
	}

	window_context.update();

	return true;
}
}
}
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
