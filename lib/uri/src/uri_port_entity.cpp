/**
  @file         uri_port_entity.cpp
  @brief        retains the information about the 'port' of URI.
  @author       HRYKY
  @version      $Id: uri_port_entity.cpp 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/clear.h"
#include "hryky/uri/uri_port_entity.h"
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
namespace port
{
namespace
{
} // namespace "anonymous"
} // namespace port
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
hryky::uri::port::Entity::Entity()
	: number_()
{
}
/**
  @brief copy constructor.
 */
hryky::uri::port::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(number)
{
}
/**
  @brief move constructor.
 */
hryky::uri::port::Entity::Entity(this_type && rhs)
	: hryky_move_member(number)
{
}
/**
  @brief constructor with port number.
 */
hryky::uri::port::Entity::Entity(number_type number)
	: number_(number)
{
}
/**
  @brief destructor.
 */
hryky::uri::port::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::uri::port::Entity::clear()
{
	hryky::clear(this->number_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::uri::port::Entity::swap(this_type & src)
{
	hryky_swap_member(number);
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
namespace port
{
namespace
{
} // namespace "anonymous"
} // namespace port
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
