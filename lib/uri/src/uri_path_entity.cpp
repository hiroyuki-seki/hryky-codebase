/**
  @file         uri_path_entity.cpp
  @brief        retains the information of the 'Path' part of URI.
  @author       HRYKY
  @version      $Id: uri_path_entity.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/clear.h"
#include "hryky/uri/uri_path_entity.h"
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
namespace path
{
namespace
{
} // namespace "anonymous"
} // namespace path
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
hryky::uri::path::Entity::Entity()
	: segments_()
{
}
/**
  @brief copy constructor.
 */
hryky::uri::path::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(segments)
{
}
/**
  @brief move constructor.
 */
hryky::uri::path::Entity::Entity(this_type && rhs)
	: hryky_move_member(segments)
{
}
/**
  @brief constructor.
 */
hryky::uri::path::Entity::Entity(mempool_type const mempool)
	: segments_(mempool)
{
}
/**
  @brief destructor.
 */
hryky::uri::path::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::uri::path::Entity::clear()
{
	hryky::clear(this->segments_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::uri::path::Entity::swap(this_type & src)
{
	hryky_swap_member(segments);
}
/**
  @brief appends a segment to this instance.
 */
bool hryky::uri::path::Entity::append(segment_type const & src)
{
	return this->segments_.push_back(src);
}
/**
  @brief appends an other entity.
 */
bool hryky::uri::path::Entity::append(this_type const & src)
{
	return this->segments_.insert(
		this->segments_.end(), src.segments_.begin(), src.segments_.end());
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
namespace path
{
namespace
{
} // namespace "anonymous"
} // namespace path
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
