/**
  @file         exclusion_mutex.cpp
  @brief        exclusion object : mutex.
  @author       HRYKY
  @version      $Id: exclusion_mutex.cpp 331 2014-03-09 06:44:48Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/exclusion/exclusion_mutex.h"
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
hryky::exclusion::Mutex::Mutex()
	: raw_()
{
}
/**
  @brief suspends the current thread until the ownership is obtained.
 */
void hryky::exclusion::Mutex::lock()
{
	this->raw_.lock();
}
/**
  @brief releases the ownership.
 */
void hryky::exclusion::Mutex::unlock()
{
	this->raw_.unlock();
}
/**
  @brief retrieves the mutable raw object.
 */
hryky::exclusion::Mutex::raw_type &
hryky::exclusion::Mutex::raw()
{
	return this->raw_;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
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
}
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
