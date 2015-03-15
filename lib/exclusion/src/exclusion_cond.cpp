/**
  @file         exclusion_cond.cpp
  @brief        exclusion object : condition variable.
  @author       HRYKY
  @version      $Id: exclusion_cond.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/exclusion/exclusion_cond.h"
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
hryky::exclusion::Cond::Cond()
	: raw_()
	  , waiting_()
{
}
/**
  @brief destructor.
 */
hryky::exclusion::Cond::~Cond()
{
	this->clear();
}
/**
  @brief invokes the waiting threads which has called wait.
 */
void hryky::exclusion::Cond::notify()
{
	this->notify_all();
}
/**
  @brief releases the internal resources.
 */
void hryky::exclusion::Cond::clear()
{
	if (0u < this->waiting_) {
		hryky_log_warning(
			"Some sequences are waiting this condition.");
		this->notify();
	}
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief invokes the all waiting threads which have called join().
 */
void hryky::exclusion::Cond::notify_all()
{
	this->raw_.notify_all();
}
/**
  @brief invokes the one waiting thread which has called join().
 */
void hryky::exclusion::Cond::notify_one()
{
	this->raw_.notify_one();
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
