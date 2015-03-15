/**
  @file         uri_hierarchy_entity.cpp
  @brief        retains the information about the 'hier-part' of URI.
  @author       HRYKY
  @version      $Id: uri_hierarchy_entity.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/clear.h"
#include "hryky/uri/uri_hierarchy_entity.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace uri
{
namespace hierarchy
{
namespace
{
} // namespace "anonymous"
} // namespace hierarchy
} // namespace uri
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
hryky::uri::hierarchy::Entity::Entity()
	: authority_()
	  , path_()
{
}
/**
  @brief copy constructor.
 */
hryky::uri::hierarchy::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(authority)
	  , hryky_copy_member(path)
{
}
/**
  @brief move constructor.
 */
hryky::uri::hierarchy::Entity::Entity(this_type && rhs)
	: hryky_move_member(authority)
	  , hryky_move_member(path)
{
}
/**
  @brief constructor.
 */
hryky::uri::hierarchy::Entity::Entity(mempool_type const mempool)
	: authority_(mempool)
	  , path_(mempool)
{
}
/**
  @brief destructor.
 */
hryky::uri::hierarchy::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::uri::hierarchy::Entity::clear()
{
	hryky::clear(this->path_);
	hryky::clear(this->authority_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::uri::hierarchy::Entity::swap(this_type & src)
{
	hryky_swap_member(authority);
	hryky_swap_member(path);
}
/**
  @brief assigns a new authority.
 */
void hryky::uri::hierarchy::Entity::authority(authority_type const & src)
{
	this->authority_ = src;
}
/**
  @brief assigns a new path.
 */
void hryky::uri::hierarchy::Entity::path(path_type const & src)
{
	this->path_ = src;
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
namespace uri
{
namespace hierarchy
{
namespace
{
} // namespace "anonymous"
} // namespace hierarchy
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
