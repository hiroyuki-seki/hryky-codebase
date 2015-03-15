/**
  @file     test_shader.cpp
  @brief    tests hryky::shader module.
  @author   HRYKY
  @version  $Id: test_shader.cpp 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/shader.h"
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

		/// tests hryky::shader module.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "shader";

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
  @brief tests hryky::shader module.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << hryky_stream_denote(random);

	/**
	  in vec4 position;
	  uniform mat4 view, projection;
	  void main()
	  {
	    gl_Position = projection * view * position;
	  }
	 */
	{
		shader::Vshader source;
		auto const position = shader::vec4("position");
		auto const view = shader::mat4("view");
		auto const projection = shader::mat4("projection");
		source.inputs() << position;
		source.uniforms() << view << projection;
		{
			auto main = shader::function("main");
			main << (source.position() = projection * view * position);
			source << main;
		}
		shader::Coder coder;
		coder << source;
		(log.writer()
		 << "code" << coder
		 << "hierarchy" << source);
	}

#if 0
	/**
	  out vec4 color;
	  void main()
	  {
	    color = vec4(1.0, 0.0, 0.0, 1.0);
	  }
	 */
	{
		shader::Fshader source;
		auto const color = shader::vec4("color");
		{
			auto main = shader::function("main");
			main << (color = shader::vec4(1.0f, 0.0f, 0.0f, 1.0f));
			source << main;
		}
		shader::Coder coder;
		coder << source;
		(log.writer()
		 << "code" << coder
		 << "hierarchy" << source);
	}
#endif

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
