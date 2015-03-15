/**
  @file         http_method_common.cpp
  @brief        common definitions for hryky::http::method.
  @author       HRYKY
  @version      $Id: http_method_common.cpp 350 2014-04-24 10:10:31Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_method_common.h"
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
namespace method
{
	LiteralString<> const g_tokens[Kind::num] = {
		LiteralString<>("OPTIONS"),
		LiteralString<>("GET"),
		LiteralString<>("HEAD"),
		LiteralString<>("POST"),
		LiteralString<>("PUT"),
		LiteralString<>("DELETE"),
		LiteralString<>("TRACE"),
		LiteralString<>("CONNECT"),
	};

namespace
{
} // namespace "anonymous"
} // namespace method
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace http
{
namespace method
{
namespace
{
} // namespace "anonymous"
} // namespace method
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
