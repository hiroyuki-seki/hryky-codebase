/**
  @file     path_win32_special.cpp
  @brief    retrieves the special path on Windows Platform.
  @author   HRYKY
  @version  $Id: path_win32_special.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/json.h"
#include "hryky/log.h"
#include "hryky/nullptr.h"
#include "hryky/path/path_win32_special.h"
#include "hryky/stream.h"
#include "hryky/utf8.h"
#include "hryky/utf16.h"
#include "hryky/win32.h"
#include "hryky/windows.h"
#include "hryky/ascii.h"
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
#if NTDDI_VISTA > NTDDI_VERSION
	typedef int const known_folder_type;
	known_folder_type g_application_folder = ::CSIDL_APPDATA;
#else
	typedef REFKNOWNFOLDERID known_folder_type;
	known_folder_type g_application_folder = ::FOLDERID_RoamingAppData;
#endif
	/// retrieves the path to the special folder.
	path_type known_folder_path(known_folder_type known_folder);

} // namespace "anonymous"
} // namespace win32
} // namespace path
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the directory for this application.
 */
hryky::path_type
hryky::path::win32::application()
{
	return known_folder_path(g_application_folder);
}
/**
  @brief retrieves the path to executable.
 */
hryky::path_type
hryky::path::win32::executable()
{
	::HMODULE const module = NULL;
	::DWORD const buffer_size = MAX_PATH;
	::WCHAR buffer[buffer_size + 1u] = {0, };
	::DWORD const result = ::GetModuleFileNameW(
		module,
		buffer,
		buffer_size);

	if (result == buffer_size) {
		hryky_log_alert(
			"The path to this executable is too long.");
		return path_type();
	}

	return path_type(buffer);
}
/**
  @brief creates a temporary path.
 */
hryky::path_type hryky::path::win32::tempfile()
{
	DWORD const dir_buffer_size = MAX_PATH;
	::WCHAR dir_buffer[MAX_PATH + 1] = {0, };

	DWORD const dir_length
		= ::GetTempPathW(dir_buffer_size, dir_buffer);
	if (0 == dir_length) {
		hryky_log_alert(
			"failed to retrieves the path to "
			"the temporary directory: "
			<< (json::writer()
				<< "error" << hryky::win32::last_error()));
		return path_type();
	}

	String<> encoded;
	auto encoder = utf8::encoder(ostream::back_inserter(encoded));
	if (!utf16::decode(encoder, dir_buffer)) {
		hryky_log_alert(
			"failed to decode the path to the "
			"temporary directry");
		return path_type();
	}

	::GUID guid;
	::HRESULT const guid_result = ::CoCreateGuid(&guid);
	if (S_OK != guid_result) {
		hryky_log_alert("failed to create a GUID");
		return path_type();
	}

	char const guid_c_str[36] = {
		ascii::to_hexchar(static_cast<char>((guid.Data1 >> 28) & 0xF)),
		ascii::to_hexchar(static_cast<char>((guid.Data1 >> 24) & 0xF)),
		ascii::to_hexchar(static_cast<char>((guid.Data1 >> 20) & 0xF)),
		ascii::to_hexchar(static_cast<char>((guid.Data1 >> 16) & 0xF)),
		ascii::to_hexchar(static_cast<char>((guid.Data1 >> 12) & 0xF)),
		ascii::to_hexchar(static_cast<char>((guid.Data1 >> 8) & 0xF)),
		ascii::to_hexchar(static_cast<char>((guid.Data1 >> 4) & 0xF)),
		ascii::to_hexchar(static_cast<char>(guid.Data1 & 0xF)),
		'-',
		ascii::to_hexchar(static_cast<char>((guid.Data2 >> 12) & 0xF)),
		ascii::to_hexchar(static_cast<char>((guid.Data2 >> 8) & 0xF)),
		ascii::to_hexchar(static_cast<char>((guid.Data2 >> 4) & 0xF)),
		ascii::to_hexchar(static_cast<char>(guid.Data2 & 0xF)),
		'-',
		ascii::to_hexchar(static_cast<char>((guid.Data3 >> 12) & 0xF)),
		ascii::to_hexchar(static_cast<char>((guid.Data3 >> 8) & 0xF)),
		ascii::to_hexchar(static_cast<char>((guid.Data3 >> 4) & 0xF)),
		ascii::to_hexchar(static_cast<char>(guid.Data3 & 0xF)),
		'-',
		ascii::to_hexchar(static_cast<char>((guid.Data4[0] >> 4) & 0xF)),
		ascii::to_hexchar(static_cast<char>(guid.Data4[0] & 0xF)),
		ascii::to_hexchar(static_cast<char>((guid.Data4[1] >> 4) & 0xF)),
		ascii::to_hexchar(static_cast<char>(guid.Data4[1] & 0xF)),
		ascii::to_hexchar(static_cast<char>((guid.Data4[2] >> 4) & 0xF)),
		ascii::to_hexchar(static_cast<char>(guid.Data4[2] & 0xF)),
		ascii::to_hexchar(static_cast<char>((guid.Data4[3] >> 4) & 0xF)),
		ascii::to_hexchar(static_cast<char>(guid.Data4[3] & 0xF)),
		ascii::to_hexchar(static_cast<char>((guid.Data4[4] >> 4) & 0xF)),
		ascii::to_hexchar(static_cast<char>(guid.Data4[4] & 0xF)),
		ascii::to_hexchar(static_cast<char>((guid.Data4[5] >> 4) & 0xF)),
		ascii::to_hexchar(static_cast<char>(guid.Data4[5] & 0xF)),
		ascii::to_hexchar(static_cast<char>((guid.Data4[6] >> 4) & 0xF)),
		ascii::to_hexchar(static_cast<char>(guid.Data4[6] & 0xF)),
		ascii::to_hexchar(static_cast<char>((guid.Data4[7] >> 4) & 0xF)),
		ascii::to_hexchar(static_cast<char>(guid.Data4[7] & 0xF)),
		0,
	};

	path_type path(encoded.c_str());
	path << guid_c_str;
	
	return path;
}
//------------------------------------------------------------------------------
// defines static functions
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
  @brief retrieves the path to the special folder.
 */
path_type known_folder_path(known_folder_type known_folder)
{
#if NTDDI_VISTA > NTDDI_VERSION
	::HWND const owner = 0;
	::HANDLE const token = NULL;
	::DWORD const flags = ::SHGFP_TYPE_DEFAULT;
	::WCHAR raw_path[::MAX_PATH] = {0,};
	::HRESULT const result = ::SHGetFolderPathW(
		owner,
		known_folder,
		token,
		flags,
		raw_path);

	if (S_OK != result) {
		return path_type();
	}

	return path_type(&raw_path[0]);
#else // NTDDI_VISTA > NTDDI_VERSION
	::PWSTR raw_path = hryky_nullptr;
	::DWORD const flags = (
		::KF_FLAG_NOT_PARENT_RELATIVE
		| ::KF_FLAG_DEFAULT_PATH
		| ::KF_FLAG_DONT_VERIFY
		| ::KF_FLAG_DONT_UNEXPAND);
	::HANDLE const token = NULL;
	::HRESULT const result = ::SHGetKnownFolderPath(
		known_folder,
		flags,
		token,
		&raw_path);

	if (S_OK != result) {
		return path_type();
	}

	return path_type(raw_path);
#endif // NTDDI_VISTA > NTDDI_VERSION
}
} // namespace "anonymous"
} // namespace win32
} // namespace path
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
