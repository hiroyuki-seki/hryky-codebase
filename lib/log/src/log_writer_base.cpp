/**
  @file         log_writer_base.cpp
  @brief        the interface to output logs.
  @author       HRYKY
  @version      $Id: log_writer_base.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/log/log_writer_base.h"
#include "hryky/debug/debug_common.h"
#include "hryky/mempool.h"
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
  @brief writes out a string.
 */
bool hryky::log::writer::Base::operator()(
	char const * const str, size_t const size)
{
	mempool::Adapter<mempool::Standard> mempool;
	
	hryky_debug_output(String<>(str, size, &mempool).c_str());
	
	return this->write_impl(str, size);
}
/**
  @brief assigns the level than which the output of log is ignored less than.
 */
hryky::log::writer::Base &
hryky::log::writer::Base::lower(level_type const & src)
{
	this->lower_ = src;
	return *this;
}
/**
  @brief assigns the level than which the output of log is ignored more than.
 */
hryky::log::writer::Base &
hryky::log::writer::Base::upper(level_type const & src)
{
	this->upper_ = src;
	return *this;
}
/**
  @brief confirms whether the log level is in the available range.
 */
bool hryky::log::writer::Base::available(level_type const & level) const
{
	if (level < this->lower_ || level > this->upper_) {
		return false;
	}
	return true;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
/**
  @brief constructor.
 */
hryky::log::writer::Base::Base()
	: lower_(level::Kind::debug)
	  , upper_(level::Kind::emerg)
{
}
/**
  @brief destructor.
 */
hryky::log::writer::Base::~Base()
{
}
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
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
