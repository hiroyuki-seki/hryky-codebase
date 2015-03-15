/**
  @file         log_level_entity.cpp
  @brief        the level of logging depending on the severity and purpose.
  @author       HRYKY
  @version      $Id: log_level_entity.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include <precompiled.h>
#include "hryky/common.h"
#include "hryky/swap.h"
#include "hryky/log/log_level_entity.h"
#include "hryky/literal_string.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace log
{
namespace level
{
namespace
{

	hryky::LiteralString<> const g_dummy = LiteralString<>("N/A");
}
} // namespace level
} // namespace log
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
  @brief constructor.
 */
hryky::log::level::Entity::Entity()
	: kind_(Kind::debug)
{
}
/**
  @brief constructor with a level.
 */
hryky::log::level::Entity::Entity(Kind::Raw const kind)
	: kind_(kind)
{
	return;
}
/**
  @brief destructor.
 */
hryky::log::level::Entity::~Entity()
{
}
/**
  @brief copy constructor.
 */
hryky::log::level::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(kind)
{
	return;
}
/**
  @brief move constructor.
 */
hryky::log::level::Entity::Entity(this_type && rhs)
	: hryky_move_member(kind)
{
}
/**
  @brief retrieves the null terminated string which represents the log level.
 */
hryky::LiteralString<> const &
hryky::log::level::Entity::str() const
{
	if (Kind::num <= this->kind_) {
		return g_dummy;
	}

	return level::g_tokens[this->kind_];
}
/**
  @brief confirms that this level is less than the other level.
 */
bool hryky::log::level::Entity::operator<(this_type const & rhs) const
{
	return this->kind_ < rhs.kind_;
}
/**
  @brief confirms that this level is more than the other level.
 */
bool hryky::log::level::Entity::operator>(this_type const & rhs) const
{
	return this->kind_ > rhs.kind_;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::log::level::Entity::swap(this_type & src)
{
	hryky_swap_member(kind);
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
}
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
