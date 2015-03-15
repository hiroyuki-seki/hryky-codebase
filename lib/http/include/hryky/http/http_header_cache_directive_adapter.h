/**
  @file         http_header_cache_directive_adapter.h
  @brief        creates the class derived from http::header::cache::directive::Base with existing class.
  @author       HRYKY
  @version      $Id: http_header_cache_directive_adapter.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_CACHE_DIRECTIVE_ADAPTER_H_20130112023356773
#define HTTP_HEADER_CACHE_DIRECTIVE_ADAPTER_H_20130112023356773
#include "hryky/http/http_header_cache_directive_base.h"
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
namespace cache
{
namespace directive
{
	/// creates the class derived from http::header::cache::directive::Base with existing class.
	template <typename ClientT>
	class Adapter;

} // namespace directive
} // namespace cache
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief creates the class derived from http::header::cache::directive::Base with existing class.
 */
template <typename ClientT>
class hryky::http::header::cache::directive::Adapter
	: public hryky::Adapter<Base, ClientT>
{
public :

	/// base class of inheritance.
	typedef hryky::Adapter<Base, ClientT> base_type;

	typedef Adapter<ClientT> this_type;

	/// constructor with the implementation.
	Adapter(const_reference value);

protected :

private :

	/// dispatches the implementation of http::header::cache::directive::Base.
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
namespace cache
{
namespace directive
{
} // namespace directive
} // namespace cache
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
hryky::http::header::cache::directive::Adapter<ClientT>::Adapter(
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
  @brief dispatches the implementation of http::header::cache::directive::Base.
 */
template <typename ClientT>
bool
hryky::http::header::cache::directive::Adapter<ClientT>::dispatch_impl(
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
namespace cache
{
namespace directive
{

} // namespace directive
} // namespace cache
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_CACHE_DIRECTIVE_ADAPTER_H_20130112023356773
// end of file
