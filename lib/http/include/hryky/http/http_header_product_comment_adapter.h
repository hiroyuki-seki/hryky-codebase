/**
  @file         http_header_product_comment_adapter.h
  @brief        creates the class derived from http::header::product_comment::Base with existing class.
  @author       HRYKY
  @version      $Id: http_header_product_comment_adapter.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_PRODUCT_COMMENT_ADAPTER_H_20130112010103709
#define HTTP_HEADER_PRODUCT_COMMENT_ADAPTER_H_20130112010103709
#include "hryky/http/http_header_product_comment_base.h"
#include "hryky/adapter.h"
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
namespace product_comment
{
	/// creates the class derived from http::header::product_comment::Base with existing class.
	template <typename ClientT>
	class Adapter;

} // namespace product_comment
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief creates the class derived from http::header::product_comment::Base with existing class.
 */
template <typename ClientT>
class hryky::http::header::product_comment::Adapter :
	public hryky::Adapter<Base, ClientT>
{
public :

	/// base class of inheritance.
	typedef hryky::Adapter<Base, ClientT> base_type;

	typedef Adapter<ClientT> this_type;

	/// constructor.
	Adapter(const_reference value);

protected :

private :

	/// dispatches the implementation.
	virtual bool dispatch_impl(dispatcher_type & dispatcher);
	
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
namespace product_comment
{
} // namespace product_comment
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief constructor.
 */
template <typename ClientT>
hryky::http::header::product_comment::Adapter<ClientT>::Adapter(
	const_reference value)
	: base_type(value)
{
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief dispatches the implementation.
 */
template <typename ClientT>
bool
hryky::http::header::product_comment::Adapter<ClientT>::dispatch_impl(
	dispatcher_type & dispatcher)
{
	return dispatcher(*this->get());
}
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace http
{
namespace header
{
namespace product_comment
{

} // namespace product
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_PRODUCT_COMMENT_ADAPTER_H_20130112010103709
// end of file
