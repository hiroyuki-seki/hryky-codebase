/**
  @file     file_writer_win32_entity.cpp
  @brief    writes out data from a file on Windows Platform.
  @author   HRYKY
  @version  $Id: file_writer_win32_entity.cpp 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/file/file_writer_win32_entity.h"
#include "hryky/file/file_common.h"
#include "hryky/json/json_writer.h"
#include "hryky/log.h"
#include "hryky/utf16.h"
#include "hryky/utf8.h"
#include "hryky/win32.h"
#include "hryky/stream.h"
#include "hryky/raii.h"
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
namespace win32
{
namespace
{
	uint64_t const g_buffer_size = 0x400u * 0x100u;
	
} // namespace "anonymous"
} // namespace win32
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
hryky::file::writer::win32::Entity::Entity()
	: temp_handle_()
	  , path_()
	  , temp_path_()
	  , written_size_()
{
}
/**
  @brief creates an instance with the path.
 */
hryky::file::writer::win32::Entity::Entity(path_type const & path)
	: temp_handle_()
	  , path_()
	  , temp_path_()
	  , written_size_()
{
	if (!this->open(path)) {
		hryky_log_err(
			"failed to open a writer: "
			<< (json::writer() << hryky_stream_denote(path)));
		return;
	}
}
/**
  @brief move constructor.
 */
hryky::file::writer::win32::Entity::Entity(this_type && rhs)
	: hryky_move_member(temp_handle)
	  , hryky_move_member(path)
	  , hryky_move_member(temp_path)
	  , hryky_move_member(written_size)
{
}
/**
  @brief destructor.
 */
hryky::file::writer::win32::Entity::~Entity()
{
	this->materialize();
}
/**
  @brief releases the internal resources.
 */
void hryky::file::writer::win32::Entity::clear()
{
	this->materialize();

	hryky::clear(this->written_size_);
	hryky::clear(this->temp_path_);
	hryky::clear(this->path_);
	hryky::clear(this->temp_handle_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::file::writer::win32::Entity::swap(this_type & src)
{
	hryky_swap_member(temp_handle);
	hryky_swap_member(path);
	hryky_swap_member(temp_path);
	hryky_swap_member(written_size);
}
/**
  @brief writes out data.
 */
hryky::size_t
hryky::file::writer::win32::Entity::write(
	void const * const src, size_t const size)
{
	::DWORD written_size = 0u;
	::OVERLAPPED * const overlapped = NULL;
	if (!::WriteFile(
		this->temp_handle_.raw(),
		src,
		static_cast< ::DWORD>(size),
		&written_size,
		overlapped)) {
		hryky_log_err(
			"failed to write file: "
			<< hryky::win32::last_error());
		return 0u;
	}

	this->written_size_ += written_size;
	
	return static_cast<size_t>(written_size);
}
/**
  @brief opens a file.
 */
bool hryky::file::writer::win32::Entity::open(path_type const & path)
{
	if (!mkdir(path)) {
		hryky_log_err(
			"failed to create a directory for "
			<< (json::writer() << hryky_stream_denote(path)));
		return false;
	}

	path_type const temp_path = path::tempfile();

	if (!mkdir(temp_path)) {
		hryky_log_err(
			"failed to create a temporary directory for "
			<< (json::writer() << hryky_stream_denote(temp_path)));
		return false;
	}
	
	String<wchar_t> encoded;
	auto encoder = utf16::encoder(ostream::back_inserter(encoded));
	if (!utf8::decode(encoder, temp_path.impl().absolute().c_str())) {
		hryky_log_err(
			"failed to decode the string of the path.\n");
		return false;
	}

	::DWORD const access = GENERIC_WRITE | GENERIC_READ;
	::DWORD const share = 0;
	::LPSECURITY_ATTRIBUTES const security = NULL;
	::DWORD const disposition = CREATE_ALWAYS;
	::DWORD const attributes = FILE_ATTRIBUTE_TEMPORARY;
	::HANDLE const template_file = NULL;

	handle_type temp_handle = ::CreateFileW(
		encoded.c_str(),
		access,
		share,
		security,
		disposition,
		attributes,
		template_file);
	if (hryky_is_null(temp_handle)) {
		hryky_log_err(
			"failed to open file: "
			<< (json::writer()
				<< hryky_stream_denote(path)
				<< "error" << hryky::win32::last_error()));
		return false;
	}

	this->clear();

	hryky::swap(this->temp_handle_, temp_handle);
	this->path_ = path;
	this->temp_path_ = temp_path;
	this->written_size_ = 0u;

	return true;
}
/**
  @brief confirms whether this instance is regarded as null.
 */
bool hryky::file::writer::win32::Entity::is_null() const
{
	return hryky_is_null(this->temp_handle_);
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief saves the temporary data to the target file.
 */
void hryky::file::writer::win32::Entity::materialize()
{
	if (hryky_is_null(this->temp_handle_)) {
		return;
	}

	auto const remove_temp_file = auto_call([this]() {
		hryky::clear(this->temp_handle_);
		this->temp_path_.rm();
	});

	String<wchar_t> encoded;
	auto encoder = utf16::encoder(ostream::back_inserter(encoded));
	if (!utf8::decode(encoder, this->path_.impl().absolute().c_str())) {
		hryky_log_err(
			"failed to decode the string of the path.\n");
		return;
	}

	::DWORD const access = GENERIC_WRITE;
	::DWORD const share = 0;
	::LPSECURITY_ATTRIBUTES const security = NULL;
	::DWORD const disposition = CREATE_ALWAYS;
	::DWORD const attributes = FILE_ATTRIBUTE_NORMAL;
	::HANDLE const template_file = NULL;

	handle_type const handle = ::CreateFileW(
		encoded.c_str(),
		access,
		share,
		security,
		disposition,
		attributes,
		template_file);
	if (hryky_is_null(handle)) {
		hryky_log_err(
			"failed to open the written file: "
			<< (json::writer()
				<< hryky_stream_denote(this->path_)
				<< "error" << hryky::win32::last_error()));
		return;
	}

	if (!::LockFile(
		handle.raw(),
		0,
		0,
		this->written_size_ & 0xFFFFFFFF,
		this->written_size_ >> 32)) {
		hryky_log_err(
			"failed to lock the written file: "
			<< (json::writer()
				<< "error" << hryky::win32::last_error()));
		return;
	}
	auto unlock_handle = auto_call([&handle, this]() {
		::UnlockFile(
			handle.raw(),
			0,
			0,
			this->written_size_ & 0xFFFFFFFF,
			this->written_size_ >> 32);
	});

	::LARGE_INTEGER const distance = { 0, };

	if (0 == ::SetFilePointerEx(
		this->temp_handle_.raw(),
		distance,
		NULL,
		FILE_BEGIN)) {
		hryky_log_err(
			"failed to move the pointer of the temporary file "
			"to the beginning:"
			<< (json::writer()
				<< "error" << hryky::win32::last_error()));
		return;
	}

	Vector<uint8_t> buffer;
	uint64_t const buffer_size
		= (::std::min)(g_buffer_size, this->written_size_);
	buffer.resize(buffer_size);

	uint64_t rest = this->written_size_;
	while (0 < rest) {
		uint64_t const size = (::std::min)(rest, buffer_size);
		::DWORD read_size = 0;
		if (!::ReadFile(
			this->temp_handle_.raw(),
			&buffer[0],
			static_cast< ::DWORD>(size),
			&read_size,
			NULL) || size != read_size) {
			hryky_log_err(
				"failed to read data from the temporary file: "
				<< (json::writer()
					<< "size" << size
					<< "read_size" << read_size
					<< "error" << hryky::win32::last_error()));
			return;
		}
		::DWORD written_size = 0;
		if (!::WriteFile(
			handle.raw(),
			&buffer[0],
			static_cast< ::DWORD>(size),
			&written_size,
			NULL) || size != written_size) {
			hryky_log_err(
				"failed to write data to the file: "
				<< (json::writer()
					<< "size" << size
					<< "written_size" << written_size
					<< "error" << hryky::win32::last_error()));
			return;
		}
		rest -= size;
	}

	return;
}
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
namespace win32
{
namespace
{
} // namespace "anonymous"
} // namespace win32
} // namespace writer
} // namespace file
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
