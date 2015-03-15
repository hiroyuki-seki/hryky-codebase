/**
  @file         http_header_language_common.h
  @brief        common definitions for http::header::language.
  @author       HRYKY
  @version      $Id: http_header_language_common.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_LANGUAGE_COMMON_H_20130112225826623
#define HTTP_HEADER_LANGUAGE_COMMON_H_20130112225826623
#include "hryky/fixed_vector.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace http
{
namespace header
{
namespace language
{
	typedef FixedVector<octet_type, 8> tag_type;
	
} // namespace language
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace http
{
namespace header
{
namespace language
{
} // namespace language
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_LANGUAGE_COMMON_H_20130112225826623
// end of file
