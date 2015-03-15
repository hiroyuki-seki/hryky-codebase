/**
  @file         file_reader_entity.win32.cpp
  @brief        retains a file descripter for Win32.
  @author       HRYKY
  @version      $Id: file_reader_win32_entity.cpp 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/file/file_reader_win32_entity.h"
#include "hryky/file/file_common.h"
#include "hryky/win32.h"
#include "hryky/log.h"
#include "hryky/json/json_writer.h"
#include "hryky/utf8.h"
#include "hryky/utf16.h"
#include "hryky/stream.h"
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
hryky::file::reader::win32::Entity::Entity()
	: handle_()
{
}
/**
  @brief creates an instance with opening a file.
 */
hryky::file::reader::win32::Entity::Entity(
	path_type const & path)
	: handle_()
{
	if (!this->open(path)) {
		hryky_log_err(
			"failed to open file "
			<< (json::writer() << hryky_stream_denote(path)));
		return;
	}
}
/**
  @brief move constructor.
 */
hryky::file::reader::win32::Entity::Entity(this_type && rhs)
	: hryky_move_member(handle)
{
}
/**
  @brief destructor.
 */
hryky::file::reader::win32::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::file::reader::win32::Entity::clear()
{
	hryky::clear(this->handle_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::file::reader::win32::Entity::swap(this_type & src)
{
	hryky_swap_member(handle);
}
/**
  @brief reads out data.
 */
hryky::size_t
hryky::file::reader::win32::Entity::read(
	void * const dest, size_t const size)
{
	::DWORD read_size = 0u;
	::OVERLAPPED * const overlapped = NULL;
	if (!::ReadFile(
		this->handle_.raw(),
		dest,
		static_cast< ::DWORD>(size),
		&read_size,
		overlapped)) {
		hryky_log_err(
			"failed to read file: "
			<< (json::writer()
				<< "error" << hryky::win32::last_error()));
		return 0u;
	}

	return static_cast<size_t>(read_size);
}
/**
  @brief opens a file.
 */
bool hryky::file::reader::win32::Entity::open(path_type const & path)
{
	if (!mkdir(path)) {
		hryky_log_err(
			"failed to create a directory for "
			<< (json::writer() << hryky_stream_denote(path)));
		return false;
	}
	
	String<wchar_t> encoded;
	auto encoder = utf16::encoder(ostream::back_inserter(encoded));
	if (!utf8::decode(encoder, path.impl().absolute().c_str())) {
		hryky_log_err(
			"failed to decode the string of the path.\n");
		return false;
	}

	::DWORD const access = GENERIC_READ;
	::DWORD const share = FILE_SHARE_READ;
	::LPSECURITY_ATTRIBUTES const security = NULL;
	::DWORD const disposition = OPEN_EXISTING;
	::DWORD const attributes = FILE_ATTRIBUTE_NORMAL;
	::HANDLE const temp = NULL;

	handle_type handle = ::CreateFileW(
		encoded.c_str(),
		access,
		share,
		security,
		disposition,
		attributes,
		temp);
	if (hryky_is_null(handle)) {
		hryky_log_err(
			"failed to open file: "
			<< (json::writer()
				<< hryky_stream_denote(path)
				<< "error" << hryky::win32::last_error()));
		return false;
	}

	hryky::swap(this->handle_, handle);

	return true;
}
/**
  @brief confirms whether this instance is regarded as null.
 */
bool hryky::file::reader::win32::Entity::is_null() const
{
	return hryky_is_null(this->handle_);
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
