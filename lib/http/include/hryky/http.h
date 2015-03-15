/**
  @file         http.h
  @brief        modules to manage HTTP.
  @author       HRYKY
  @version      $Id: http.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef HTTP_H_20120602152935312
#define HTTP_H_20120602152935312

#include "hryky/http/http_body_entity.h"
#include "hryky/http/http_entity.h"
#include "hryky/http/http_header_accept_charset_content_entity.h"
#include "hryky/http/http_header_accept_charset_entity.h"
#include "hryky/http/http_header_accept_content_entity.h"
#include "hryky/http/http_header_accept_encoding_content_entity.h"
#include "hryky/http/http_header_accept_encoding_entity.h"
#include "hryky/http/http_header_accept_entity.h"
#include "hryky/http/http_header_accept_extension_common.h"
#include "hryky/http/http_header_accept_extension_entity.h"
#include "hryky/http/http_header_accept_language_content_entity.h"
#include "hryky/http/http_header_accept_language_entity.h"
#include "hryky/http/http_header_accept_params_entity.h"
#include "hryky/http/http_header_cache_common.h"
#include "hryky/http/http_header_cache_control_common.h"
#include "hryky/http/http_header_cache_control_entity.h"
#include "hryky/http/http_header_cache_directive_adapter.h"
#include "hryky/http/http_header_cache_directive_base.h"
#include "hryky/http/http_header_cache_directive_common.h"
#include "hryky/http/http_header_cache_directive_dispatcher_apply.h"
#include "hryky/http/http_header_cache_directive_dispatcher_base.h"
#include "hryky/http/http_header_cache_directive_field.h"
#include "hryky/http/http_header_cache_directive_second.h"
#include "hryky/http/http_header_cache_directive_specifier.h"
#include "hryky/http/http_header_comment_base.h"
#include "hryky/http/http_header_comment_adapter.h"
#include "hryky/http/http_header_comment_sequence.h"
#include "hryky/http/http_header_comment_string.h"
#include "hryky/http/http_header_common.h"
#include "hryky/http/http_header_connection_common.h"
#include "hryky/http/http_header_connection_entity.h"
#include "hryky/http/http_header_content_common.h"
#include "hryky/http/http_header_content_length_entity.h"
#include "hryky/http/http_header_content_type_entity.h"
#include "hryky/http/http_header_date_entity.h"
#include "hryky/http/http_header_entity.h"
#include "hryky/http/http_header_expires_entity.h"
#include "hryky/http/http_header_field_adapter.h"
#include "hryky/http/http_header_field_base.h"
#include "hryky/http/http_header_field_common.h"
#include "hryky/http/http_header_field_dispatcher_apply.h"
#include "hryky/http/http_header_field_dispatcher_base.h"
#include "hryky/http/http_header_field_extension_common.h"
#include "hryky/http/http_header_field_extension_entity.h"
#include "hryky/http/http_header_host_entity.h"
#include "hryky/http/http_header_language_common.h"
#include "hryky/http/http_header_language_entity.h"
#include "hryky/http/http_header_location_entity.h"
#include "hryky/http/http_header_media_type_common.h"
#include "hryky/http/http_header_media_type_entity.h"
#include "hryky/http/http_header_parameter_common.h"
#include "hryky/http/http_header_parameter_entity.h"
#include "hryky/http/http_header_product_comment_adapter.h"
#include "hryky/http/http_header_product_comment_base.h"
#include "hryky/http/http_header_product_comment_dispatcher_base.h"
#include "hryky/http/http_header_product_comment_dispatcher_apply.h"
#include "hryky/http/http_header_product_entity.h"
#include "hryky/http/http_header_server_entity.h"
#include "hryky/http/http_header_user_agent_entity.h"
#include "hryky/http/http_method_common.h"
#include "hryky/http/http_method_entity.h"
#include "hryky/http/http_parser_common.h"
#include "hryky/http/http_request_entity.h"
#include "hryky/http/http_request_line_entity.h"
#include "hryky/http/http_seconds_common.h"
#include "hryky/http/http_seconds_entity.h"
#include "hryky/http/http_server.h"
#include "hryky/http/http_stream.h"
#include "hryky/http/http_version_entity.h"
#include "hryky/http/http_parser.h"


//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
/// modules to manage HTTP.
namespace http
{
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// define global functions
//------------------------------------------------------------------------------
#endif // HTTP_H_20120602152935312
// end of file
