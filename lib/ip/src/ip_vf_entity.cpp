/**
  @file         ip_vf_entity.cpp
  @brief        retains the information about IP Address of future version.
  @author       HRYKY
  @version      $Id: ip_vf_entity.cpp 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/ip/ip_vf_entity.h"
#include "hryky/clear.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace ip
{
namespace vf
{
namespace
{
} // namespace "anonymous"
} // namespace vf
} // namespace ip
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
hryky::ip::vf::Entity::Entity()
	: minor_()
{
}
/**
  @brief copy constructor.
 */
hryky::ip::vf::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(minor)
{
}
/**
  @brief move constructor.
 */
hryky::ip::vf::Entity::Entity(this_type && rhs)
	: hryky_move_member(minor)
{
}
/**
  @brief constructor.
 */
hryky::ip::vf::Entity::Entity(mempool_type const mempool)
	: minor_(mempool)
{
}
/**
  @brief constructor with a major version and a minor version.
 */
hryky::ip::vf::Entity::Entity(
	major_type const major, minor_type const & minor)
	: major_(major)
	  , minor_(minor)
{
}
/**
  @brief destructor.
 */
hryky::ip::vf::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::ip::vf::Entity::clear()
{
	hryky::clear(this->minor_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::ip::vf::Entity::swap(this_type & src)
{
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
namespace hryky
{
namespace ip
{
namespace vf
{
namespace
{
} // namespace "anonymous"
} // namespace vf
} // namespace ip
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
