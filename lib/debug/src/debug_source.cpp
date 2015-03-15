/**
  @file         debug_source.cpp
  @brief        retains a debugging information of source position.
  @author       HRYKY
  @version      $Id: debug_source.cpp 375 2014-07-29 04:27:53Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/debug/debug_source.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace
{
} // namespace "anonymous"
//------------------------------------------------------------------------------
// static variable
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// function prototype
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief constructor.
 */
hryky::debug::Source::Source()
	: filename_()
	  , function_()
	  , line_(0u)
{
	return;
}
/**
  @brief constructor with debug information.
 */
hryky::debug::Source::Source(
	char const * filename, char const * function, size_t line)
	: filename_(filename)
	  , function_(function)
	  , line_(line)
{
	return;
}
/**
  @brief destructor.
 */
hryky::debug::Source::~Source()
{
	return;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the name of file.
 */
hryky::debug::Source::filename_type const & 
hryky::debug::Source::filename() const
{
	return this->filename_;
}
/**
  @brief retrieves the name of function.
 */
hryky::debug::Source::function_type const & 
hryky::debug::Source::function() const
{
	return this->function_;
}
/**
  @brief retrieves the number of lines.
 */
hryky::debug::Source::line_type
hryky::debug::Source::line() const
{
	return this->line_;
}
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace
{
} // namespace "anonymous"
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
