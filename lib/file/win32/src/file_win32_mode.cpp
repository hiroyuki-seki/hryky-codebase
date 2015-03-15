/**
  @file         file_win32_mode.cpp
  @brief        retains the access mode for file descriptor for Win32.
  @author       HRYKY
  @version      $Id: file_win32_mode.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/file/file_win32_mode.h"
#include "hryky/log.h"
#include "hryky/stream.h"
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
namespace descriptor
{
namespace
{
} // namespace "anonymous"
} // namespace descriptor
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
hryky::file::win32::Mode::Mode()
	: flags_()
{
}
/**
  @brief copy constructor.
 */
hryky::file::win32::Mode::Mode(this_type const & rhs)
	: hryky_copy_member(flags)
{
}
/**
  @brief move constructor.
 */
hryky::file::win32::Mode::Mode(this_type && rhs)
	: hryky_move_member(flags)
{
}
/**
  @brief destructor.
 */
hryky::file::win32::Mode::~Mode()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::file::win32::Mode::clear()
{
	hryky::clear(this->flags_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::file::win32::Mode::swap(this_type & src)
{
	hryky_swap_member(flags);
}
/**
  @brief retrieves the 'DesiredAccess' parameter.
 */
DWORD
hryky::file::win32::Mode::desired_access() const
{
	Flags const & flags = this->flags_.bits();
	
	return (
		(flags.read_ ? GENERIC_READ : 0)
		| (flags.write_ ? GENERIC_WRITE : 0)
		);
}
/**
  @brief retrieves the 'ShareMode' parameter.
 */
DWORD
hryky::file::win32::Mode::share_mode() const
{
	Flags const & flags = this->flags_.bits();
	return static_cast<DWORD>(
		(flags.share_read_ ? FILE_SHARE_READ : 0)
		| (flags.share_write_ ? FILE_SHARE_WRITE : 0)
		| (flags.share_delete_ ? FILE_SHARE_DELETE : 0)
		);
}
/**
  @brief retrieves the 'SecurityAttributes' parameter.
 */
SECURITY_ATTRIBUTES *
hryky::file::win32::Mode::security_attributes() const
{
	return hryky_nullptr;
}
/**
  @brief retrieves the 'CreationDisposition' parameter.
 */
DWORD
hryky::file::win32::Mode::creation_disposition() const
{
	Flags const & flags = this->flags_.bits();

	if (flags.create_new_) {
		return CREATE_NEW;
	} else if (flags.open_existing_) {
		return OPEN_EXISTING;
	} else if (flags.truncate_) {
		return TRUNCATE_EXISTING;
	} else {
		hryky_log_err(
			"There is no valid attribute for CreationDisposition.");
		return 0;
	}
}
/**
  @brief retrieves the 'FlagsAndAttributes' parameter.
 */
DWORD
hryky::file::win32::Mode::flags_and_attributes() const
{
	Flags const & flags = this->flags_.bits();
	return (
		(flags.normal_ ? FILE_ATTRIBUTE_NORMAL : 0)
		| (flags.hidden_ ? FILE_ATTRIBUTE_HIDDEN : 0)
		| (flags.read_only_ ? FILE_ATTRIBUTE_READONLY : 0)
		| (flags.no_buffering_ ? FILE_FLAG_NO_BUFFERING : 0)
		| (flags.async_ ? FILE_FLAG_OVERLAPPED : 0)
		| (flags.random_ ? FILE_FLAG_RANDOM_ACCESS : 0)
		| (flags.sequential_ ? FILE_FLAG_SEQUENTIAL_SCAN : 0)
		| (flags.write_through_ ? FILE_FLAG_WRITE_THROUGH : 0)
		);
}
/**
  @brief retrieves the 'TemplateFile' parameter.
 */
HANDLE
hryky::file::win32::Mode::template_file() const
{
	return NULL;
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
namespace file
{
namespace descriptor
{
namespace
{
} // namespace "anonymous"
} // namespace descriptor
} // namespace file
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
