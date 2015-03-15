/**
  @file         http_header_comment_adapter.h
  @brief        provides the interface derived from http::header::comment::Base.
  @author       HRYKY
  @version      $Id: http_header_comment_adapter.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_COMMENT_ADAPTER_H_20130113170003375
#define HTTP_HEADER_COMMENT_ADAPTER_H_20130113170003375
#include "hryky/adapter.h"
#include "hryky/http/http_header_comment_base.h"
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
namespace comment
{
	/// provides the interface derived from http::header::comment::Base.
	template <typename ClientT>
	class Adapter;

} // namespace comment

} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief provides the interface derived from http::header::comment::Base.
 */
template <typename ClientT>
class hryky::http::header::comment::Adapter :
	public hryky::Adapter<Base, ClientT>
{
public :

	typedef hryky::Adapter<Base, ClientT> base_type;

	/// constructor with the implementation.
	Adapter(const_reference src);

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace http
{
namespace header
{
namespace comment
{
} // namespace comment
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief constructor with the implementation.
 */
template <typename ClientT>
hryky::http::header::comment::Adapter<ClientT>::Adapter(
	const_reference src)
	: base_type(src)
{
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
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
namespace comment
{
} // namespace comment
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_COMMENT_ADAPTER_H_20130113170003375
// end of file

