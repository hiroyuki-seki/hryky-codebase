/*
  @file         test_main.cpp
  @brief        the entry point of all tests.
  @author       HRYKY
  @version      $Id: test_main.cpp 375 2014-07-29 04:27:53Z hryky.private@gmail.com $
 */
#include <precompiled.h>
#include <codecvt>
#include <locale>
#include "hryky/log.h"
#include "hryky/main.h"
#include "hryky/memory.h"
#include "hryky/path.h"
#include "hryky/scoped_registry.h"
#include "hryky/string.h"
#include "hryky/testing.h"
#include "hryky/windows.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
#if !defined(HRYKY_TEST_MEMORY_SIZE)
#   define HRYKY_TEST_MEMORY_SIZE (0x400u * 0x400u * 0x100u)
#endif
// overloads global new/delete.
// HRYKY_DEFINE_GLOBAL_NEW_DELETE();
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace
{
	// This function is invoked when ::operator new() cannot allocate memory.
	void handle_bad_alloc();

}
//------------------------------------------------------------------------------
// prototypes
//------------------------------------------------------------------------------
// the entry point of all tests.
int main(int argc, char * argv[]);

namespace hryky
{
namespace test
{
	// picks a test by command-line options.
	int main_impl(int const argc, char const * const argv[]);

	// call ::std::set_new_handler() the beggining of this instantiation
	struct SetNewHandler
	{
		SetNewHandler(::std::new_handler handler)
		{
			::std::set_new_handler(handler);
		}
	};
	SetNewHandler const set_new_handler(handle_bad_alloc);

}
}
//------------------------------------------------------------------------------
// global functions
//------------------------------------------------------------------------------
/*
  @brief the entry point of all tests.
 */
int main(int argc, char * argv[])
{
	return (hryky::main)(argc, argv, hryky::test::main_impl);
}
/*
  @brief picks a test by command-line options.
 */
int hryky::test::main_impl(int const argc, char const * const argv[])
{
	if (1 > argc) {
		(::std::cerr <<
		 "The name of test has to be specified in the commandline." <<
		 ::std::endl);
		return 1;
	}

	size_t const buffer_size = HRYKY_TEST_MEMORY_SIZE;
	::std::vector<char> buffer_vec(buffer_size);
	void * buffer = buffer_vec.data();
	if (hryky_is_null(buffer)) {
		hryky_log_alert("failed to allocate the primary buffer.");
		return 1;
	}
	mempool::Adapter<mempool::Lock<mempool::Arbitrary<> > >
		mempool;
	if (!mempool.get()->get()->reset(buffer, buffer_size)) {
		::std::cerr << "initialization of global mempool failed." << ::std::endl;
		return 1;
	}

	{
		/**
		  enregisters a mempool as the common mempool.
		 */
		mempool::global::Registry const global_mempool(&mempool);

		String<> const testname(argv[1]);

		// instantiates writer to output log into a file
		log::writer::File log_writer;
		{
			path_type const application = (
				path::application()
				<< "hryky-codebase"
				<< ("test_" + testname).c_str());

			if (!application.exists()) {
				if (!application.mkdir()) {
					hryky_log_emerg(
						"failed to create a new directory to store the log:"
						<< application);
					return 1;
				}
			}

			path_type const log_path =
				(application + ("test_" + testname + "_log.txt").c_str());

			log_writer.path(log_path);
		}

		/**
		  enregisters the writer here and unregisters the writer
		  at the end of this scope.
		 */
		ScopedRegistry<log::writer_type> const
			enregister_log_writer(&log_writer);

		// retrieves the associative array of unit tests as singleton.
		testing::Registry & registry = testing::Registry::instance();

		// retrieves the corresponding unit test by name.
		testing::Registry::unit_type const & unit =
			registry[testname.c_str()];

		if (hryky_nullptr == unit) {
			// output the information as the "emergency" level
			hryky_log_emerg(
				"invalid testname "
				<< (json::writer()
				<< stream::denote("testname") << testname.c_str()));
			return 1;
		}

		// invokes the unit test.
		if (!unit->run()) {
			// output the information as the "alert" level
			hryky_log_alert(
				"failed "
				<< (json::writer()
					<< "testname" << testname.c_str()));
			return 1;
		}
	}

	if (1 != mempool.get()->get()->free_nodes_size()) {
		::std::cerr << "memory leak" << ::std::endl;
		return 1;
	}

	hryky_log_debug("debug" << mempool);
	
	return 0;
}
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace
{
/*
  @brief This function is invoked when ::operator new() cannot allocate memory.
 */
void handle_bad_alloc()
{
	throw ::std::bad_alloc();
}
}
//------------------------------------------------------------------------------
// Registry public functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
