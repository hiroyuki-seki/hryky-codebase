/**
  @file         http_header_product_entity.cpp
  @brief        retains the information of HTTP Product Tokens.
  @author       HRYKY
  @version      $Id: http_header_product_entity.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_product_entity.h"
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
namespace product
{
namespace
{
} // namespace "anonymous"
} // namespace product
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
hryky::http::header::product::Entity::Entity()
	: name_()
	  , version_()
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::product::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(name)
	  , hryky_copy_member(version)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::product::Entity::Entity(this_type && rhs)
	: hryky_move_member(name)
	  , hryky_move_member(version)
{
}
/**
  @brief constructor.
 */
hryky::http::header::product::Entity::Entity(mempool_type const mempool)
	: name_(mempool)
	  , version_(mempool)
{
}
/**
  @brief constructor with product name.
 */
hryky::http::header::product::Entity::Entity(name_type const & name)
	: name_(name)
	  , version_()
{
}
/**
  @brief constructor with name and version of product.
 */
hryky::http::header::product::Entity::Entity(
	name_type const & name, version_type const & version)
	: name_(name)
	  , version_(version)
{
}
/**
  @brief destructor.
 */
hryky::http::header::product::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::product::Entity::clear()
{
	hryky::clear(this->version_);
	hryky::clear(this->name_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::product::Entity::swap(this_type & src)
{
	hryky_swap_member(name);
	hryky_swap_member(version);
}
/**
  @brief retrieves the mutable instance of the name.
 */
hryky::http::header::product::Entity::name_type & 
hryky::http::header::product::Entity::name()
{
	return this->name_;
}
/**
  @brief retrieves the mutable instance of the version.
 */
hryky::http::header::product::Entity::version_type & 
hryky::http::header::product::Entity::version()
{
	return this->version_;
}
/**
  @brief retrieves the immutable instance of the name.
 */
hryky::http::header::product::Entity::name_type const & 
hryky::http::header::product::Entity::name() const
{
	return this->name_;
}
/**
  @brief retrieves the immutable instance of the version.
 */
hryky::http::header::product::Entity::version_type const & 
hryky::http::header::product::Entity::version() const
{
	return this->version_;
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
namespace product
{
namespace
{
} // namespace "anonymous"
} // namespace product
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
