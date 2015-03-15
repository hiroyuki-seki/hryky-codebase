/**
  @file         debug_common.cpp
  @brief        common definitions of debug module.
  @author       HRYKY
  @version      $Id: debug_common.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/debug/debug_common.h"
#include "hryky/log.h"
#include "hryky/stream.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace
{
}
#if defined(BOOST_ENABLE_ASSERT_HANDLER)
namespace boost
{
	/// the definition of the handler for assertions with message by boost.
	void assertion_failed_msg(
		char const * expr,
		char const * msg,
		char const * function,
		char const * file,
		long line);

	// the definition of the handler for assertions by boost.
	void assertion_failed(
		char const * expr,
		char const * function,
		char const * file,
		long line);
		
}
#endif // defined(BOOST_ENABLE_ASSERT_HANDLER)
//------------------------------------------------------------------------------
// defines public member functions of hryky::debug::Source
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#if defined(BOOST_ENABLE_ASSERT_HANDLER)
/**
  @brief the definition of the handler for assertions with message by boost.
 */
void boost::assertion_failed_msg(
	char const * expr,
	char const * msg,
	char const * function,
	char const * file,
	long line)
{
	hryky::ostream::String<hryky::String<> > os;
	os << expr << " : " << msg << hryky::endl;

	hryky::log::write(
		hryky::debug::Source(file, function, static_cast<size_t>(line)),
		hryky::log::level::Kind::alert,
		os.str());

	hryky_debug_output(os.str().c_str());
	hryky_debug_break();
	hryky_throw(
		::std::exception,
		os.str().c_str(),
		return);
}
/**
  @brief the definition of the handler for assertions by boost.
 */
void boost::assertion_failed(
	char const * expr, char const * function, char const * file, long line)
{
	hryky::ostream::String<hryky::String<> > os;
	os << expr << hryky::endl;

	hryky::log::write(
		hryky::debug::Source(file, function, static_cast<size_t>(line)),
		hryky::log::level::Kind::alert,
		os.str());

	hryky_debug_output(os.str().c_str());
	hryky_debug_break();
	hryky_throw(::std::exception, os.str().c_str(), return);
}
#endif // defined(BOOST_ENABLE_ASSERT_HANDLER)
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace
{
}
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
