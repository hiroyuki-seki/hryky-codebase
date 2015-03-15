/**
  @file     file_reader_entity.cpp
  @brief    reads out data from a file.
  @author   HRYKY
  @version  $Id: file_reader_entity.cpp 363 2014-07-10 10:46:29Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/file/file_reader_entity.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace file
{
namespace reader
{
namespace
{
} // namespace "anonymous"
} // namespace reader
} // namespace file
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
hryky::file::reader::Entity::Entity()
	: impl_()
{
}
/**
  @brief creates an instance with opening a file.
 */
hryky::file::reader::Entity::Entity(path_type const & path)
	: impl_(path)
{
}
/**
  @brief move constructor.
 */
hryky::file::reader::Entity::Entity(this_type && rhs)
	: hryky_move_member(impl)
{
}
/**
  @brief destructor.
 */
hryky::file::reader::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::file::reader::Entity::clear()
{
	hryky::clear(this->impl_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::file::reader::Entity::swap(this_type & src)
{
	hryky_swap_member(impl);
}
/**
  @brief retrieves the platform-specific implementation.
 */
hryky::file::reader::Entity::impl_type &
hryky::file::reader::Entity::impl()
{
	return this->impl_;
}
/**
  @brief retrieves the platform-specific implementation as immutable.
 */
hryky::file::reader::Entity::impl_type const &
hryky::file::reader::Entity::impl() const
{
	return this->impl_;
}
/**
  @brief reads out data from file.
 */
hryky::size_t
hryky::file::reader::Entity::read(void * const dest, size_t const size)
{
	return this->impl_.read(dest, size);
}
/**
  @brief confirms whether this instance is regarded as null.
 */
bool hryky::file::reader::Entity::is_null() const
{
	return hryky_is_null(this->impl_);
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
namespace file
{
namespace reader
{
namespace
{
} // namespace "anonymous"
} // namespace reader
} // namespace file
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
