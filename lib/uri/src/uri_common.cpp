/**
  @file         uri_common.cpp
  @brief        common definitions for hryky::uri.
  @author       HRYKY
  @version      $Id: uri_common.cpp 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/uri/uri_common.h"
#include "hryky/ascii.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace uri
{
namespace
{
} // namespace "anonymous"
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief confirms that an octet is a gen-delim of URI.
 */
bool hryky::uri::is_gen_delim(octet_type const octet)
{
	switch (octet) {
	case hryky_case_uri_gen_delim:
		return true;
	default:
		return false;
	}
}
/**
  @brief confirms that an octet is a sub-delim of URI.
 */
bool hryky::uri::is_sub_delim(octet_type const octet)
{
	switch (octet) {
	case hryky_case_uri_sub_delim:
		return true;
	default:
		return false;
	}
}
/**
  @brief confirms that an octet is reserved in URI.
 */
bool hryky::uri::is_reserved(octet_type const octet)
{
	switch (octet) {
	case hryky_case_uri_sub_delim:
	case hryky_case_uri_gen_delim:
		return true;
	default:
		return false;
	}
}
/**
  @brief confirms that an octet is unreserved in URI.
 */
bool hryky::uri::is_unreserved(octet_type const octet)
{
	switch (octet) {
	case hryky_case_uri_unreserved:
		return true;
	default:
		return false;
	}
}
/**
  @brief confirms whether this octet is one of the characters of segment in URI.
 */
bool hryky::uri::is_segment(octet_type const octet)
{
	switch (octet) {
	case hryky_case_uri_segment:
		return true;
	default:
		return false;
	}
}
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace uri
{
namespace
{
} // namespace "anonymous"
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
