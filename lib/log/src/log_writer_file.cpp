/**
  @file         log_writer_file.cpp
  @brief        output log message.
  @author       HRYKY
  @version      $Id: log_writer_file.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/log/log_writer_file.h"
#include "hryky/log/log_definition.h"
#include "hryky/exclusion/exclusion_lock.h"
#include "hryky/file.h"
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
hryky::log::writer::File::File()
	: mempool_()
	  , log_(&mempool_)
	  , path_(&mempool_)
	  , lockable_()
{
}
/**
  @brief creates an instance with the path to the logged file.
 */
hryky::log::writer::File::File(path_type const & path)
	: mempool_()
	  , log_(&mempool_)
	  , path_(path.c_str(), &mempool_)
	  , lockable_()
{
}
/**
  @brief destrunctor.
 */
hryky::log::writer::File::~File()
{
	this->flush();
}
/**
  @brief assign a new path.
 */
void hryky::log::writer::File::path(path_type const & src)
{
	this->path_ = src;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief writes out a string.
 */
bool hryky::log::writer::File::write_impl(
	char const * const str, size_t const size)
{
	lock_type const lock(this->lockable_);

	this->log_.append(str, size);

	return true;
}
/**
  @brief write out bufferred messages.
 */
void hryky::log::writer::File::flush_impl()
{
	lock_type const lock(this->lockable_);

	if (this->log_.empty()) {
		return;
	}
	
	file::writer_type writer(this->path_);
	if (hryky_is_null(writer)) {
		hryky_log_warning(
			"failed to open the file for logging.");
		return;
	}
	writer.write(this->log_.data(), this->log_.size());

	this->log_.clear();
}
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
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
