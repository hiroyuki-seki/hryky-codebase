/**
  @file         uri_entity.cpp
  @brief        retains the information of URI.
  @author       HRYKY
  @version      $Id: uri_entity.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/clear.h"
#include "hryky/uri/uri_entity.h"
#include "hryky/swap.h"
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
hryky::uri::Entity::Entity()
	: scheme_()
	  , hierarchy_()
	  , query_()
	  , fragment_()
{
	return;
}
/**
  @brief copy constructor.
 */
hryky::uri::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(scheme)
	  , hryky_copy_member(hierarchy)
	  , hryky_copy_member(query)
	  , hryky_copy_member(fragment)
{
}
/**
  @brief move constructor.
 */
hryky::uri::Entity::Entity(this_type && rhs)
	: hryky_move_member(scheme)
	  , hryky_move_member(hierarchy)
	  , hryky_move_member(query)
	  , hryky_move_member(fragment)
{
}
/**
  @brief constructor with the memory pool.
 */
hryky::uri::Entity::Entity(mempool_type mempool)
	: scheme_(mempool)
	  , hierarchy_(mempool)
	  , query_(mempool)
	  , fragment_(mempool)
{
	return;
}
/**
  @brief destructor.
 */
hryky::uri::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::uri::Entity::clear()
{
	hryky::clear(this->fragment_);
	hryky::clear(this->query_);
	hryky::clear(this->hierarchy_);
	hryky::clear(this->scheme_);
}
/**
  @brief assigns a URI Scheme.
 */
void hryky::uri::Entity::scheme(scheme_type const & src)
{
	this->scheme_ = src;
}
/**
  @brief assigns a new hierarchy part of URI.
 */
void hryky::uri::Entity::hierarchy(hierarchy_type const & src)
{
	this->hierarchy_ = src;
}
/**
  @brief assigns a query of URI.
 */
void hryky::uri::Entity::query(query_type const & src)
{
	this->query_ = src;
}
/**
  @brief assigns a fragment of URI.
 */
void hryky::uri::Entity::fragment(fragment_type const & src)
{
	this->fragment_ = src;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::uri::Entity::swap(this_type & src)
{
	hryky_swap_member(scheme);
	hryky_swap_member(hierarchy);
	hryky_swap_member(query);
	hryky_swap_member(fragment);
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
