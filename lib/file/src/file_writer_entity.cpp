/**
  @file     file_writer_entity.cpp
  @brief    writes out data from a file.
  @author   HRYKY
  @version  $Id: file_writer_entity.cpp 363 2014-07-10 10:46:29Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/file/file_writer_entity.h"
#include "hryky/swap.h"
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
namespace writer
{
namespace
{
} // namespace "anonymous"
} // namespace writer
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
hryky::file::writer::Entity::Entity()
	: impl_()
{
}
/**
  @brief move constructor.
 */
hryky::file::writer::Entity::Entity(this_type && rhs)
	: hryky_move_member(impl)
{
}
/**
  @brief creates an instance with the path.
 */
hryky::file::writer::Entity::Entity(path_type const & path)
	: impl_(path)
{
}
/**
  @brief destructor.
 */
hryky::file::writer::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::file::writer::Entity::clear()
{
	hryky::clear(this->impl_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::file::writer::Entity::swap(this_type & src)
{
	hryky_swap_member(impl);
}
/**
  @brief retrieves the platform-specific implementation as mutable.
 */
hryky::file::writer::Entity::impl_type &
hryky::file::writer::Entity::impl()
{
	return this->impl_;
}
/**
  @brief retrieves the platform-specific implementation as immutable.
 */
hryky::file::writer::Entity::impl_type const &
hryky::file::writer::Entity::impl() const
{
	return this->impl_;
}
/**
  @brief writes out data to the file.
 */
hryky::size_t hryky::file::writer::Entity::write(
	void const * const src, size_t const size)
{
	return this->impl_.write(src, size);
}
/**
  @brief confirms whether this instance is regarded as null.
 */
bool hryky::file::writer::Entity::is_null() const
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
namespace writer
{
namespace
{
} // namespace "anonymous"
} // namespace writer
} // namespace file
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
