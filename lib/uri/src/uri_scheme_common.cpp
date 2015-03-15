/**
  @file         uri_scheme_common.cpp
  @brief        common definitions of hryky::scheme.
  @author       HRYKY
  @version      $Id: uri_scheme_common.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/uri/uri_scheme_common.h"
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
namespace scheme
{
	LiteralString<> const g_tokens[Kind::num] = {
		LiteralString<>("unknown"),
		LiteralString<>("http"),
		LiteralString<>("https"),
		LiteralString<>("ftp"),
		LiteralString<>("ldap"),
		LiteralString<>("mailto"),
		LiteralString<>("urn"),
		LiteralString<>("ws"),
		LiteralString<>("ralative"),
	};

namespace
{
} // namespace "anonymous"
} // namespace scheme
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief confirms whether this octet is one of the characters of URI Scheme.
 */
bool hryky::uri::scheme::is_char(octet_type const octet)
{
	switch (octet) {
	case hryky_case_uri_scheme:
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
namespace scheme
{
namespace
{
} // namespace "anonymous"
} // namespace scheme
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
