/**
  @file         http_seconds_entity.cpp
  @brief        retains the information of delta-seconds of HTTP.
  @author       HRYKY
  @version      $Id: http_seconds_entity.cpp 328 2014-02-24 02:40:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_seconds_entity.h"
#include "hryky/clear.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace http
{
namespace seconds
{
namespace
{
} // namespace "anonymous"
} // namespace seconds
} // namespace http
} // namespace hryky
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
hryky::http::seconds::Entity::Entity()
	: raw_()
{
}
/**
  @brief constructor.
 */
hryky::http::seconds::Entity::Entity(raw_type const raw)
	: raw_(raw)
{
}
/**
  @brief copy constructor.
 */
hryky::http::seconds::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(raw)
{
}
/**
  @brief move constructor.
 */
hryky::http::seconds::Entity::Entity(this_type && rhs)
	: hryky_move_member(raw)
{
}
/**
  @brief destructor.
 */
hryky::http::seconds::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::seconds::Entity::clear()
{
	hryky::clear(this->raw_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::seconds::Entity::swap(this_type & src)
{
	hryky_swap_member(raw);
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
namespace hryky
{
namespace http
{
namespace seconds
{
namespace
{
} // namespace "anonymous"
} // namespace seconds
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
