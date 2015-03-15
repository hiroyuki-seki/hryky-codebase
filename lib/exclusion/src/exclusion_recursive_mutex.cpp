/**
  @file         exclusion_recursive_mutex.cpp
  @brief        exclusion object : mutex which can be called recursively.
  @author       HRYKY
  @version      $Id: exclusion_recursive_mutex.cpp 331 2014-03-09 06:44:48Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/exclusion/exclusion_recursive_mutex.h"
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
hryky::exclusion::RecursiveMutex::RecursiveMutex()
	: raw_()
{
}
/**
  @brief suspends the current thread until the ownership is obtained.
 */
void hryky::exclusion::RecursiveMutex::lock()
{
	this->raw_.lock();
}
/**
  @brief release the ownership.
 */
void hryky::exclusion::RecursiveMutex::unlock()
{
	this->raw_.unlock();
}
/**
  @brief retrieves the mutable raw object.
 */
hryky::exclusion::RecursiveMutex::raw_type &
hryky::exclusion::RecursiveMutex::raw()
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
