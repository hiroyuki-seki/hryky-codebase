/**
  @file     test_opengl.cpp
  @brief    tests opengl module.
  @author   HRYKY
  @version  $Id: test_opengl.cpp 377 2014-08-15 02:49:04Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/opengl.h"
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
	// enretisters a test.
	class Test : testing::unit::Base
	{
	public:
		typedef testing::unit::Base base_type;
		typedef Test this_type;

		/// constructor.
		Test();

	private:
		Test(this_type const &);
		this_type & operator=(this_type const &);
		
		/// tests opengl module.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "opengl";

} // namespace "anonymous"
} // namespace test
} // namespace hryky
namespace hryky
{
namespace test
{
namespace
{
//------------------------------------------------------------------------------
// public member functions of Test
//------------------------------------------------------------------------------
/**
  @brief constructor.
 */
Test::Test()
	: base_type(g_testname)
{
}
//------------------------------------------------------------------------------
// private member functions of Test
//------------------------------------------------------------------------------
/**
  @brief tests opengl module.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	// opengl verson
	opengl::version_type const opengl_version
		= opengl::version_3_2();
	opengl_version.prefer();
	
	// creates window
	window::Context const window_context;
	if (hryky_is_null(window_context)) {
		hryky_log_alert(
			"failed to create window "
			<< (json::writer()
				<< "opengl_version" << opengl_version
			));
		return false;
	}

	// initializes OpenGL module
	opengl::Module const opengl_module(window_context);
	if (hryky_is_null(opengl_module)) {
		hryky_log_alert(
			"failed to initialize OpenGL module");
		return false;
	}

	opengl::vshader_type const vshader = opengl_module.vshader();
	if (hryky_is_null(vshader)) {
		hryky_log_alert("failed to create a Vertex Shader object.");
		return false;
	}

	opengl::fshader_type const fshader = opengl_module.fshader();
	if (hryky_is_null(fshader)) {
		hryky_log_alert("failed to create a Fragment Shader object.");
		return false;
	}

	if (!opengl_module.cleaner()(
		opengl::Cleaner::Parameter()
		.for_color(true).color(
			opengl::Cleaner::color_type().red(0.5f))
		.for_depth(true).depth(0.0f)
		.for_stencil(true).stencil(0))) {
		hryky_log_alert("failed to clear framebuffer");
		return false;
	}

	window_context.update();

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
