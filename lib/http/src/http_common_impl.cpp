/**
  @file         http_common_impl.cpp
  @brief        internal common definitions of http.
  @author       HRYKY
  @version      $Id: http_common_impl.cpp 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "./http_common_impl.h"
#include "hryky/ascii.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace http
{
namespace
{
} // namespace "anonymous"
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief confirms that an octet is a separator of HTTP.
 */
bool hryky::http::is_separator(octet_type const octet)
{
	switch (octet) {
	case hryky_case_http_separator:
		return true;
	default:
		return false;
	}
}
/**
  @brief confirms that an octet belongs to the character of token.
 */
bool hryky::http::is_token_char(octet_type const octet)
{
	switch (octet) {
	case hryky_case_http_token:
		return true;
	default:
		return false;
	}
}
/**
  @brief confirms that an octet belongs to the characters of TEXT.
 */
bool hryky::http::is_text_char(octet_type const octet)
{
	switch (octet) {
	case hryky_case_http_not_text:
		return false;
	default:
		return true;
	}
}
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace http
{
namespace
{
} // namespace "anonymous"
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
