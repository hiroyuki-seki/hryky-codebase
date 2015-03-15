/**
  @file         main.h
  @brief        facilitates the entry-point.
  @author       HRYKY
  @version      $Id: main.h 375 2014-07-29 04:27:53Z hryky.private@gmail.com $
 */
#ifndef MAIN_H_20120226102124098
#define MAIN_H_20120226102124098
#include "hryky/boost.h"
#include "hryky/common.h"
#include "hryky/debug/debug_common.h"
#include "hryky/type_traits/as_parameter.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_catch_variadic
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/**
	  @brief    wrapper function to catch exception.
	  @param    argc is the first argument of entry point (almost always, main()).
	  @param    argv is the second argument of entry point.
	  @param    func is called in this function.
	  @retval   0 is success.
	  @retval   otherwise failure.
	  @attention
	  - @a func must be able to be called as the function with two arguments, argc and argv.
	  - @a func must return 0 if it completed successfully.
	 */
	template < typename MainFuncT >
	int main(
		int argc,
		char const * const argv[],
		typename AsParameter<MainFuncT>::type func);

	/// utility type to pass a function pointer to hryky::main().
	typedef int (*main_func_pointer)(int, char const * const []);

	/**
	  @brief    wrapper function to catch exception.
	  @param    argc is the first argument of entry point (almost always, main()).
	  @param    argv is the second argument of entry point.
	  @param    func is called in this function.
	  @retval   0 is success.
	  @retval   otherwise failure.
	 */
	int main(int argc, char const * const argv[], main_func_pointer func);

}
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// define global functions
//------------------------------------------------------------------------------
/**
  @brief wrapper function to catch exception.
 */
template < typename MainFuncT >
int hryky::main(
	int const argc,
	char const * const argv[],
	typename AsParameter<MainFuncT>::type func)
{
#if defined(_WIN32)
	/**
	  _CRTDBG_LEAK_CHECK_DF cause termination in locale library
	  without the execution from Visual Studio 2013.
	 */
	{
		// int const flag = _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF;
		int const flag = _CRTDBG_ALLOC_MEM_DF;
		_CrtSetDbgFlag (flag);
		// 	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_WNDW);
		// 	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
		//	_CrtSetBreakAlloc(455);
	}
#endif // defined(_WIN32)

#if HRYKY_USE_EXCEPTION
	try
#endif // HRYKY_USE_EXCEPTION
	{
		return func(argc, argv);
	}
#if HRYKY_USE_EXCEPTION
	catch (boost::exception const & exception) {
		::std::ostringstream os;
		os << boost::diagnostic_information(exception);
		hryky_debug_output(os.str().c_str());
	}
	catch (::std::string const & msg) {
		::std::ostringstream os;
		os << "exception as string : " << msg;
		hryky_debug_output(msg.c_str());
	}
	catch (::std::out_of_range const & exception) {
		::std::ostringstream os;
		os << "::std::out_of_range : " << exception.what();
		hryky_debug_output(os.str().c_str());
	}
	catch (::std::bad_alloc const & exception) {
		::std::ostringstream os;
		os << "::std::bad_alloc : " << exception.what();
		hryky_debug_output(os.str().c_str());
	}
	catch (::std::exception const & exception) {
		::std::ostringstream os;
		os << "::std::exception : " << exception.what();
		hryky_debug_output(os.str().c_str());
	}
	catch (...) {
		::std::ostringstream os;
		os << "unexpected exception";
		hryky_debug_output(os.str().c_str());
	}
	hryky_debug_output("\n");
	
	return 1;
#endif // HRYKY_USE_EXCEPTION
}
/**
  @brief wrapper function to catch exception.
 */
inline int hryky::main(int argc, char const * const argv[], main_func_pointer func)
{
	return hryky::main<main_func_pointer>(argc, argv, func);
}
//------------------------------------------------------------------------------
// revokes macro definition
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // MAIN_H_20120226102124098
// end of file
