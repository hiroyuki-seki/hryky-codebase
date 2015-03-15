/**
  @file         http_header_connection_entity.cpp
  @brief        retains the information about 'Connection' field of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_connection_entity.cpp 328 2014-02-24 02:40:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_connection_entity.h"
#include "hryky/http/http_header_connection_common.h"
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
namespace connection
{
namespace
{
} // namespace "anonymous"
} // namespace connection
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
hryky::http::header::connection::Entity::Entity()
	: keep_alive_()
	  , close_()
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::connection::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(keep_alive)
	  , hryky_copy_member(close)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::connection::Entity::Entity(this_type && rhs)
	: hryky_move_member(keep_alive)
	  , hryky_move_member(close)
{
}
/**
  @brief destructor.
 */
hryky::http::header::connection::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::connection::Entity::clear()
{
	hryky::clear(this->keep_alive_);
	hryky::clear(this->close_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::connection::Entity::swap(this_type & src)
{
	hryky_swap_member(keep_alive);
	hryky_swap_member(close);
}
/**
  @brief appends the value of 'Connection' field by string.
 */
bool hryky::http::header::connection::Entity::append(token_type const & token)
{
	kind_type const kind(token.begin(), token.end());

	switch (kind.raw()) {
	case Kind::keep_alive:
		this->keep_alive_ = true;
		break;
	case Kind::close:
		this->close_ = true;
		break;
	default:
		hryky_log_debug(
			"unsupported value for 'Connection' field " << token);
		return false;
	}
	
	return true;
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
namespace connection
{
namespace
{
} // namespace "anonymous"
} // namespace connection
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
