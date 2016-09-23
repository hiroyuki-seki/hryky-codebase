/**
  @file     test_v8.cpp
  @brief    tests V8 JavaScript Engine.
  @author   HRYKY
  @version  $Id: test_v8.cpp 364 2014-07-12 01:03:03Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#pragma hryky_pragma_push_warning
#   pragma hryky_pragma_disable_warning_base_assign_operator
#   pragma hryky_pragma_disable_warning_base_copy_constructor
#   pragma hryky_pragma_disable_warning_base_default_constructor
#   pragma hryky_pragma_disable_warning_constant_condition
#   pragma hryky_pragma_disable_warning_create_assign_operator
#   pragma hryky_pragma_disable_warning_sign_conversion
#   pragma hryky_pragma_disable_warning_undef
#   pragma hryky_pragma_disable_warning_unused_variable
#   pragma hryky_pragma_disable_warning_deleted_move_constructor
#   include "v8/v8.h"
#pragma hryky_pragma_pop_warning
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
		
		/// tests V8 JavaScript Engine.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "v8";

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
  @brief tests V8 JavaScript Engine.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	{
		Vector<char> buffer;
		if (!buffer.resize(0x400 * 0x400 * 0x40)) {
			hryky_log_alert("failed to allocate a buffer.");
			return false;
		}
		
		/**
		  isolates the allocation in V8.
		  V8 can leak an instance for DefaultPlatform in v8::Context::New.
		 */
		mempool::Adapter<mempool::Lock<mempool::Arbitrary<> > >
			mempool;
		mempool.get()->get()->reset(&buffer[0], buffer.size());
		mempool::global::Registry const global_mempool(&mempool);

		// Get the default Isolate created at startup.
		// v8::Isolate * const isolate = v8::Isolate::GetCurrent();
		v8::Isolate * const isolate = v8::Isolate::New();
		auto const dispose_isolate = auto_call([isolate]() {
			isolate->Dispose();
		});
		v8::Isolate::Scope const isolate_scope(isolate);

		{
			// Create a stack-allocated handle scope.
			v8::HandleScope const handle_scope(isolate);

			// Create a new context.
			v8::Handle<v8::Context> context = v8::Context::New(isolate);

			// Enter the created context for compiling and
			// running the hello world script.
			v8::Context::Scope const context_scope(context);

			// Here's how you could create a Persistent handle to the
			// context, if needed.
			v8::Persistent<v8::Context> persistent_context(isolate, context);

			// Create a string containing the JavaScript source code.
			v8::Handle<v8::String> const source =
				v8::String::NewFromUtf8(isolate, "'Hello' + ', World!'");

			// Compile the source code.
			v8::Handle<v8::Script> script = v8::Script::Compile(source);

			// Run the script to get the result.
			v8::Handle<v8::Value> result = script->Run();

			// The persistent handle needs to be eventually disposed.
			persistent_context.Reset();

			// Convert the result to an ASCII string and print it.
			v8::String::Utf8Value const result_str(result);
			log.writer() << "result" << *result_str;
		}
	}

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
