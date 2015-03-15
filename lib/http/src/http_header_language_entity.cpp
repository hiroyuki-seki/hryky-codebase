/**
  @file         http_header_language_entity.cpp
  @brief        retains the information for 'language-tag' of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_language_entity.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_language_entity.h"
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
namespace language
{
namespace
{
} // namespace "anonymous"
} // namespace language
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
hryky::http::header::language::Entity::Entity()
	: primary_()
	  , subs_()
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::language::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(primary)
	  , hryky_copy_member(subs)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::language::Entity::Entity(this_type && rhs)
	: hryky_move_member(primary)
	  , hryky_move_member(subs)
{
}
/**
  @brief constructor.
 */
hryky::http::header::language::Entity::Entity(mempool_type const mempool)
	: primary_()
	  , subs_(mempool)
{
}
/**
  @brief destructor.
 */
hryky::http::header::language::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::language::Entity::clear()
{
	hryky::clear(this->subs_);
	hryky::clear(this->primary_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::language::Entity::swap(this_type & src)
{
	hryky_swap_member(primary);
	hryky_swap_member(subs);
}
/**
  @brief assign a new 'primary-tag'.
 */
void hryky::http::header::language::Entity::primary(tag_type const & src)
{
	this->primary_ = src;
}
/**
  @brief appends a new 'sub-tag'.
 */
bool hryky::http::header::language::Entity::append(tag_type const & src)
{
	return this->subs_.push_back(src);
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
namespace language
{
namespace
{
} // namespace "anonymous"
} // namespace language
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
