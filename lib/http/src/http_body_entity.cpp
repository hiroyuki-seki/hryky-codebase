/**
  @file         http_body_entity.cpp
  @brief        retains a message-body of HTTP Message.
  @author       HRYKY
  @version      $Id: http_body_entity.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_body_entity.h"
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
hryky::http::body::Entity::Entity()
{
}
/**
  @brief constructor.
 */
hryky::http::body::Entity::Entity(mempool_type const)
{
}
/**
  @brief copy constructor.
 */
hryky::http::body::Entity::Entity(this_type const &)
{
}
/**
  @brief move constructor.
 */
hryky::http::body::Entity::Entity(this_type &&)
{
}
/**
  @brief destructor.
 */
hryky::http::body::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::body::Entity::clear()
{
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::body::Entity::swap(this_type &)
{
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
