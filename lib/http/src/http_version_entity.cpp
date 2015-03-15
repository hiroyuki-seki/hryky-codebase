/**
  @file         http_version_entity.cpp
  @brief        retains HTTP-Version.
  @author       HRYKY
  @version      $Id: http_version_entity.cpp 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_version_entity.h"
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
  @brief default constructor.
 */
hryky::http::version::Entity::Entity()
	: major_(1)
	  , minor_(0)
{
	return;
}
/**
  @brief constructor with version number.
 */
hryky::http::version::Entity::Entity(
	major_type const major, minor_type const minor)
	: major_(major)
	  , minor_(minor)
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::version::Entity::clear()
{
	this->minor_ = 0;
	this->major_ = 1;
}
/**
  @brief reinitializes the instance.
 */
void hryky::http::version::Entity::assign(
	major_type const major, minor_type const minor)
{
	this->major_ = major;
	this->minor_ = minor;
}
/**
  @brief retrieves the major number of HTTP-Version.
 */
hryky::http::version::Entity::major_type
hryky::http::version::Entity::major() const
{
	return this->major_;
}
/**
  @brief retrieves the minor number of HTTP-Version.
 */
hryky::http::version::Entity::minor_type
hryky::http::version::Entity::minor() const
{
	return this->minor_;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::version::Entity::swap(
	this_type & src)
{
	hryky_swap_member(major);
	hryky_swap_member(minor);
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
} // namespace "anonymous"
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
