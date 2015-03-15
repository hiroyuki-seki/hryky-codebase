/**
  @file     path_entity.cpp
  @brief    represents a path of filesystem.
  @author   HRYKY
  @version  $Id: path_entity.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/path/path_entity.h"
#include "hryky/clear.h"
#include "hryky/utf8.h"
#include "hryky/utf16.h"
#include "hryky/stream.h"
#include "hryky/log.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace path
{
namespace
{
} // namespace "anonymous"
} // namespace path
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
hryky::path::Entity::Entity()
	: impl_()
{
}
/**
  @brief creates an instance with memory pool.
 */
hryky::path::Entity::Entity(mempool::Ptr const & mempool)
	: impl_(mempool)
{
}
/**
  @brief creates a path from a null-terminated character encoded by UTF-8.
 */
hryky::path::Entity::Entity(
	char const * const c_str, mempool::Ptr const & mempool)
	: impl_(c_str, mempool)
{
}
/**
  @brief creates a path from a null-terminated wide character.
 */
hryky::path::Entity::Entity(
	wchar_t const * const c_str, mempool::Ptr const & mempool)
	: impl_(mempool)
{
	String<> encoded(this->impl_.mempool());
	auto encoder = utf8::encoder(ostream::back_inserter(encoded));

	if (!utf16::decode(encoder, c_str)) {
		hryky_log_warning(
			"failed to decode the name of "
			"application-specific directory.");
		return;
	}

	this->impl_ = encoded.c_str();
}
/**
  @brief copy constructor.
 */
hryky::path::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(impl)
{
}
/**
  @brief move constructor.
 */
hryky::path::Entity::Entity(this_type && rhs)
	: hryky_move_member(impl)
{
}
/**
  @brief destructor.
 */
hryky::path::Entity::~Entity()
{
}
/**
  @brief appends components by operator.
 */
hryky::path::Entity &
hryky::path::Entity::operator<<(char const * const c_str)
{
	this->append(c_str);
	return *this;
}
/**
  @brief creates a new path to which a component is appended.
 */
hryky::path::Entity hryky::path::Entity::operator+(
	char const * const c_str) const
{
	this_type ret(*this);
	return (ret << c_str);
}
/**
  @brief releases the internal resources.
 */
void hryky::path::Entity::clear()
{
	hryky::clear(this->impl_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::path::Entity::swap(this_type & src)
{
	hryky_swap_member(impl);
}
/**
  @brief appends components.
 */
bool hryky::path::Entity::append(char const * const c_str)
{
	return this->impl_.append(c_str);
}
/**
  @brief confirms whether the path exists.
 */
bool hryky::path::Entity::exists() const
{
	return this->impl_.exists();
}
/**
  @brief creates a directory.
 */
bool hryky::path::Entity::mkdir() const
{
	return this->impl_.mkdir();
}
/**
  @brief removes the component described by this path.
 */
bool hryky::path::Entity::rm() const
{
	return this->impl_.rm();
}
/**
  @brief retrieves the platform-specific implementation as immutable.
 */
hryky::path::Entity::impl_type const &
hryky::path::Entity::impl() const
{
	return this->impl_;
}
/**
  @brief retrieves the representation of path as null-terminated character.
 */
char const * hryky::path::Entity::c_str() const
{
	return this->impl_.c_str();
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
// defines functions used in this file
//------------------------------------------------------------------------------
namespace hryky
{
namespace path
{
namespace
{
} // namespace "anonymous"
} // namespace path
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
