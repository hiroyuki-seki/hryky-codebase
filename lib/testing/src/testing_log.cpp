/**
  @file         testing_log.cpp
  @brief        outputs the log of the unit test at the end of scope.
  @author       HRYKY
  @version      $Id: testing_log.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing/testing_log.h"
#include "hryky/testing/testing_unit_base.h"
#include "hryky/log/log_writer_base.h"
#include "hryky/stream.h"
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
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
/**
  @brief constructor.
 */
hryky::testing::Log::Log(unit_type unit)
	: writer_()
	  , name_(unit.name().c_str())
{
}
/**
  @brief destructor.
 */
hryky::testing::Log::~Log()
{
	ostream::String<String<> > os;
	os << stream::denote(this->name_) << this->writer_ << hryky::endl;

	log::write(
		log::level::Kind::debug,
		os.str().c_str(),
		os.str().size());
}
/**
  @brief retrieves the collection of the log.
 */
hryky::testing::Log::writer_type &
hryky::testing::Log::writer()
{
	return this->writer_;
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
