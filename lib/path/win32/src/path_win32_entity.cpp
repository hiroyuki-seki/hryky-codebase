/**
  @file     path_win32_entity.cpp
  @brief    represents a path of filesystem on Windows Platform..
  @author   HRYKY
  @version  $Id: path_win32_entity.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/clear.h"
#include "hryky/log.h"
#include "hryky/path/path_win32_entity.h"
#include "hryky/stream.h"
#include "hryky/swap.h"
#include "hryky/utf16.h"
#include "hryky/utf8.h"
#include "hryky/windows.h"
#include "hryky/win32.h"
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
namespace win32
{
namespace
{
	char const g_platform_delimiter = '\\';

	/// confirms whether a character can be regarded as delimiter of path.
	bool is_delimiter(char const chara);

	/// confirms whether a character is null.
	bool at_end(char const chara);
	
	/// skips delimiters.
	char const * skip_delimiter(char const * ptr);

	/// creates a directory with the intermediate directories recursively.
	bool mkdir(String<wchar_t> const & dir);

} // namespace "anonymous"
} // namespace win32
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
hryky::path::win32::Entity::Entity()
	: server_()
	  , components_()
	  , absolute_()
	  , cached_absolute_()
	  , drive_()
{
}
/**
  @brief creates an instance with memory pool.
 */
hryky::path::win32::Entity::Entity(mempool::Ptr const & mempool)
	: server_(mempool)
	  , components_(mempool)
	  , absolute_(mempool)
	  , cached_absolute_()
	  , drive_()
{
}
/**
  @brief creates an instance from a null-terminated characters.
 */
hryky::path::win32::Entity::Entity(
	char const * const c_str,
	mempool::Ptr const & mempool)
	: server_(mempool)
	  , components_(mempool)
	  , absolute_(mempool)
	  , cached_absolute_()
	  , drive_()
{
	if (!this->reset(c_str)) {
		hryky_log_warning("invalid path: " << c_str);
	}
}
/**
  @brief copy constructor.
 */
hryky::path::win32::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(server)
	  , hryky_copy_member(components)
	  , hryky_copy_member(absolute)
	  , hryky_copy_member(cached_absolute)
	  , hryky_copy_member(drive)
{
}
/**
  @brief move constructor.
 */
hryky::path::win32::Entity::Entity(this_type && rhs)
	: hryky_move_member(server)
	  , hryky_move_member(components)
	  , hryky_move_member(absolute)
	  , hryky_move_member(cached_absolute)
	  , hryky_move_member(drive)
{
}
/**
  @brief destructor.
 */
hryky::path::win32::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::path::win32::Entity::clear()
{
	hryky::clear(this->drive_);
	hryky::clear(this->cached_absolute_);
	hryky::clear(this->absolute_);
	hryky::clear(this->components_);
	hryky::clear(this->server_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::path::win32::Entity::swap(this_type & src)
{
	hryky_swap_member(server);
	hryky_swap_member(components);
	hryky_swap_member(absolute);
	hryky_swap_member(cached_absolute)
	hryky_swap_member(drive);
}
/**
  @brief appends components.
 */
bool hryky::path::win32::Entity::append(
	char const * const c_str)
{
	if (hryky_is_null(c_str)) {
		return true;
	}

	mempool_type const mempool = this->mempool();

	components_type components = this->components_;

	char const * ptr = c_str;

	// skips delimiters at the beginning.
	ptr = skip_delimiter(ptr);

	char const * component = ptr;

	while (!at_end(*ptr)) {
		if (ptr != component) {
			if (!is_delimiter(ptr[0])) {
				++ptr;
				continue;
			}
			// appends a new component.
			components.push_back(
				component_type(
					component,
					static_cast<size_t>(ptr - component),
					mempool));
			ptr = skip_delimiter(ptr);
			component = ptr;
			continue;
		}

		if ('.' != ptr[0]) {
			++ptr;
			continue;
		}

		// skips the specifier for current directory
		if (is_delimiter(ptr[1])) {
			ptr += 2;
			ptr = skip_delimiter(ptr);
			component = ptr;
			continue;
		}

		if ('.' == ptr[1]) {
			if (!is_delimiter(ptr[2])) {
				ptr += 2;
				continue;
			}

			// ascends to the parent directory.
			if (components.empty()) {
				hryky_log_warning("No parent component.");
				return false;
			}
			components.pop_back();
			ptr += 3;
			ptr = skip_delimiter(ptr);
			component = ptr;
			continue;
		}

		ptr += 2;
	}

	if (ptr != component) {
		components.push_back(component_type(
			component,
			static_cast<size_t>(ptr - component),
			mempool));
	}

	hryky::swap(this->components_, components);

	this->cached_absolute_ = false;

	return true;
}
/**
  @brief retrieves the absolute path.
 */
hryky::path::win32::Entity::string_type const & 
hryky::path::win32::Entity::absolute() const
{
	if (this->cached_absolute_) {
		return this->absolute_;
	}

	string_type absolute(this->mempool());

	if (!this->server_.empty()) {
		absolute += "\\\\?\\";
		absolute += this->server_;
		absolute += g_platform_delimiter;
	}
	else if (0 != this->drive_) {
		absolute += "\\\\?\\";
		absolute += this->drive_;
		absolute += ":\\";
	}

	{
		components_type::const_iterator itr = this->components_.begin();
		components_type::const_iterator const end = this->components_.end();
		if (end != itr) {
			absolute += *itr;
			++itr;
		}
		range(itr, end).foreach([&absolute](string_type const & component) {
			absolute += g_platform_delimiter;
			absolute += component;
		});
	}

	hryky::swap(absolute, this->absolute_);
	this->cached_absolute_ = true;
	
	return this->absolute_;
}
/**
  @brief confirms whether the path exists.
 */
bool hryky::path::win32::Entity::exists() const
{
	String<wchar_t> encoded(this->mempool());
	auto encoder = utf16::encoder(ostream::back_inserter(encoded));

	if (!utf8::decode(encoder, this->absolute().c_str())) {
		hryky_log_warning("failed to decode the path.");
		return false;
	}
	
	return TRUE == ::PathFileExistsW(encoded.c_str());
}
/**
  @brief creates a directory.
 */
bool hryky::path::win32::Entity::mkdir() const
{
	String<wchar_t> encoded(this->mempool());
	auto encoder = utf16::encoder(ostream::back_inserter(encoded));

	if (!utf8::decode(encoder, this->absolute().c_str())) {
		hryky_log_warning("failed to decode the path.");
		return false;
	}

	if (::PathFileExistsW(encoded.c_str())) {
		return true;
	}

	if (!win32::mkdir(encoded)) {
		hryky_log_err(
			"failed to create directory: "
			<< (json::writer()
				<< "path" << *this
				<< "encoded" << encoded));
		return false;
	}

	return true;
}
/**
  @brief removes the component described by this path.
 */
bool hryky::path::win32::Entity::rm() const
{
	String<wchar_t> encoded(this->mempool());
	auto encoder = utf16::encoder(ostream::back_inserter(encoded));
	if (!utf8::decode(encoder, this->absolute().c_str())) {
		hryky_log_warning("failed to decode the path.");
		return false;
	}

	if (0 == ::DeleteFileW(encoded.c_str())) {
		hryky_log_err(
			"failed to delete the component: "
			<< (json::writer()
				<< "path" << *this
				<< "error" << hryky::win32::last_error()));
		return false;
	}

	return true;
}
/**
  @brief retrieves the memory pool.
 */
hryky::mempool_type
hryky::path::win32::Entity::mempool() const
{
	return this->server_.get_allocator().mempool();
}
/**
  @brief retrieves the representation of path as null-terminated character.
 */
char const * hryky::path::win32::Entity::c_str() const
{
	return this->absolute().c_str();
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief configures resources.
 */
bool hryky::path::win32::Entity::reset(char const * const c_str)
{
	if (hryky_is_null(c_str)) {
		this->clear();
		return true;
	}

	mempool_type const mempool = this->mempool();

	size_t const size = ::std::strlen(c_str);
	char const * const end = c_str + size;
	char const * ptr = c_str;

	string_type server(mempool);
	drive_type drive = 0;
	
	if (is_delimiter(ptr[0])
		&& is_delimiter(ptr[1])) {
		ptr += 2;
		char const * const begin = ptr;
		while (!at_end(*ptr) && !is_delimiter(*ptr)) {
			++ptr;
		}
		if (begin == ptr) {
			hryky_log_warning("server component is not found.");
			return false;
		}
		server.assign(begin, static_cast<size_t>(ptr - begin));
	}
	else if (':' == ptr[1]
			 && is_delimiter(ptr[2])) {
		drive = ptr[0];
		// remains a delimiter for the following loop.
		ptr = ptr + 2;
	}
	else {
		hryky_log_warning("The relative path is not supported.");
		return false;
	}

	string_type normalized(mempool);
	normalized.reserve(static_cast<size_t>(end - ptr));

	while (!at_end(*ptr)) {
		if (is_delimiter(*ptr)) {
			// skips duplicated delimiters.
			ptr = skip_delimiter(ptr);
			if ('.' == ptr[0u]
				&& is_delimiter(ptr[1u])) {
				// skips the specifier for the current component.
				++ptr;
			}
			else if ('.' == ptr[0u]
					 && '.' == ptr[1u]
					 && is_delimiter(ptr[2u])) {
				// ascends to the parent component.
				size_type const parent
					= normalized.rfind(g_platform_delimiter);
				if (string_type::npos == parent) {
					hryky_log_warning(
						"invalid path: " << c_str);
					return false;
				}
				normalized.resize(parent);
				ptr += 2u;
			}
			else {
				normalized.push_back(g_platform_delimiter);
			}
		}
		else {
			normalized.push_back(*ptr);
			++ptr;
		}
	}

	// removes the delimiter at the end.
	if (!normalized.empty()
		&& (g_platform_delimiter == normalized.back())) {
		size_type const first = normalized.find(g_platform_delimiter);
		if (first != normalized.size() - 1) {
			normalized.resize(normalized.size() - 1);
		}
	}

	size_type index = 0u;
	size_type const normalized_size = normalized.size();

	components_type components(mempool);
	while (normalized_size > index) {
		size_type const found
			= normalized.find(g_platform_delimiter, index);
		if (string_type::npos != found) {
			components.push_back(
				component_type(
					&normalized[index],
					found - index,
					mempool));
			index = found + 1u;
		}
		else {
			components.push_back(component_type(
				&normalized[index],
				normalized_size - index,
				mempool));
			break;
		}
	}

	this->cached_absolute_ = false;
	hryky::swap(this->server_, server);
	hryky::swap(this->components_, components);
	this->drive_ = drive;
	
	return true;
}
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
namespace win32
{
namespace
{
/**
  @brief confirms whether a character can be regarded as delimiter of path.
 */
bool is_delimiter(char const chara)
{
	return '/' == chara || '\\' == chara;
}
/**
  @brief confirms whether a character is null.
 */
bool at_end(char const chara)
{
	return 0 == chara;
}
/**
  @brief skips delimiters.
 */
char const * skip_delimiter(char const * ptr)
{
	while (is_delimiter(*ptr)) {
		++ptr;
	}
	return ptr;
}
/**
  @brief creates a directory with the intermediate directories recursively.
 */
bool mkdir(String<wchar_t> const & dir)
{
	String<wchar_t>::size_type const dir_size = dir.size();
	
	if (2u > dir_size) {
		hryky_log_err("directory is too short.");
		return false;
	}
	
	String<wchar_t>::size_type const pos
		= dir.rfind(L'\\', dir_size - 2u);
	if (String<wchar_t>::npos == pos) {
		hryky_log_warning(
			"A delimiter is not found.");
		return false;
	}

	String<wchar_t> const intermediate(
		dir.begin(),
		(dir.begin()
		 + static_cast<String<wchar_t>::difference_type>(pos)),
		dir.get_allocator());

	if (!::PathFileExistsW(intermediate.c_str())) {
		if (!mkdir(intermediate)) {
			return false;
		}
	}

	if (!::CreateDirectoryW(dir.c_str(), NULL)) {
		hryky_log_err(
			"failed to create directory:"
			<< (json::writer()
				<< "error" << hryky::win32::last_error()));
		return false;
	}

	return true;
}
} // namespace "anonymous"
} // namespace win32
} // namespace path
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
