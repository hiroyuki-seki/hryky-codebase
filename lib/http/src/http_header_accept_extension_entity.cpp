/**
  @file         http_header_accept_extension_entity.cpp
  @brief        retains the information for 'accept-extension' of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_accept_extension_entity.cpp 328 2014-02-24 02:40:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_accept_extension_entity.h"
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
namespace header
{
namespace accept
{
namespace extension
{
namespace
{
} // namespace "anonymous"
} // namespace extension
} // namespace accept
} // namespace header
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
hryky::http::header::accept::extension::Entity::Entity()
	: key_()
	  , value_()
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::accept::extension::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(key)
	  , hryky_copy_member(value)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::accept::extension::Entity::Entity(this_type && rhs)
	: hryky_move_member(key)
	  , hryky_move_member(value)
{
}
/**
  @brief constructor.
 */
hryky::http::header::accept::extension::Entity::Entity(
	key_type const & key, value_type const & value)
	: key_(key)
	  , value_(value)
{
}
/**
  @brief destructor.
 */
hryky::http::header::accept::extension::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::accept::extension::Entity::clear()
{
	hryky::clear(this->value_);
	hryky::clear(this->key_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::accept::extension::Entity::swap(this_type & src)
{
	hryky_swap_member(key);
	hryky_swap_member(value);
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
namespace header
{
namespace accept
{
namespace extension
{
namespace
{
} // namespace "anonymous"
} // namespace extension
} // namespace accept
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
