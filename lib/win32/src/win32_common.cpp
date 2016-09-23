/**
  @file         win32_common.cpp
  @brief        common utilities for win32.
  @author       HRYKY
  @version      $Id: win32_common.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/json/json_writer.h"
#include "hryky/log/log_definition.h"
#include "hryky/scoped_registry.h"
#include "hryky/std/std_codecvt.h"
#include "hryky/std/std_locale.h"
#include "hryky/stream/ostream_iterator.h"
#include "hryky/utf16/utf16_decoder.h"
#include "hryky/utf8/utf8_encoder.h"
#include "hryky/win32/win32_common.h"
#include "hryky/stream.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace win32
{
namespace
{
	size_t const g_description_size = 0x400u;
	
} // namespace "anonymous"
} // namespace win32
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the string representing the last error of Win32 API.
 */
hryky::String<>
hryky::win32::last_error()
{
	DWORD const code = ::GetLastError();

	return format_error(code);
}
/**
  @brief converts the ID of error to string.
 */
hryky::String<>
hryky::win32::format_error(DWORD const id)
{
	wchar_t description[g_description_size] = {0, };
	
	DWORD const size = ::FormatMessageW(
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, // _In_opt_ LPCVOID lpSource
		id,
		LANG_USER_DEFAULT,
		description,
		g_description_size,
		NULL);
	if (0u == size) {
		hryky_log_err(
			"failed to format an error-message: "
			<< static_cast<uint32_t>(id));
		return String<>();
	}

	String<> dest;
	auto encoder = utf8::encoder(ostream::back_inserter(dest));
	auto src = literal_string(description, size);
	if (!utf16::decode(encoder, src.begin(), src.end())) {
		hryky_log_err(
			"failed to convert wide characters: "
			<< (json::writer()
				<< "id" << static_cast<uint32_t>(id)));
		return String<>();
	}

	return dest;
}
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace win32
{
namespace
{
} // namespace "anonymous"
} // namespace win32
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
