/**
  @file         http_header_server_entity.cpp
  @brief        retains the information for 'Server' field of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_server_entity.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_server_entity.h"
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
namespace server
{
namespace
{
} // namespace "anonymous"
} // namespace server
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
hryky::http::header::server::Entity::Entity()
	: products_()
	  , comments_()
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::server::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(products)
	  , hryky_copy_member(comments)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::server::Entity::Entity(this_type && rhs)
	: hryky_move_member(products)
	  , hryky_move_member(comments)
{
}
/**
  @brief constructor.
 */
hryky::http::header::server::Entity::Entity(mempool_type const mempool)
	: products_(mempool)
	  , comments_(mempool)
{
}
/**
  @brief destructor.
 */
hryky::http::header::server::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::server::Entity::clear()
{
	hryky::clear(this->comments_);
	hryky::clear(this->products_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::server::Entity::swap(this_type & src)
{
	hryky_swap_member(products);
	hryky_swap_member(comments);
}
/**
  @brief appends a new 'product'.
 */
bool hryky::http::header::server::Entity::append(product_type const & src)
{
	return this->products_.push_back(src);
}
/**
  @brief appends a new 'comment'.
 */
bool hryky::http::header::server::Entity::append(comment_type const & src)
{
	return this->comments_.push_back(src);
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
namespace server
{
namespace
{
} // namespace "anonymous"
} // namespace server
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
