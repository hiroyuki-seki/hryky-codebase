/**
  @file         http_header_common.h
  @brief        common definitions of http::header module.
  @author       HRYKY
  @version      $Id: http_header_common.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_COMMON_H_20120719002159681
#define HTTP_HEADER_COMMON_H_20120719002159681
#include "hryky/kind.h"
#include "hryky/vector.h"
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
	typedef Vector<octet_type> token_type;
	typedef Vector<octet_type> quoted_string_type;
	typedef Vector<octet_type> charset_type;
	typedef float qvalue_type;

	qvalue_type const default_qvalue_ = 1.0f;
	
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
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_COMMON_H_20120719002159681
// end of file
