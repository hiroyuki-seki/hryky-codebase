/**
  @file         http_header_cache_directive_base.h
  @brief        base class for cache directive of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_cache_directive_base.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_CACHE_DIRECTIVE_BASE_H_20130107210619546
#define HTTP_HEADER_CACHE_DIRECTIVE_BASE_H_20130107210619546
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
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
	/// base class for cache directive of HTTP Header.
	class Base;

namespace dispatcher
{
	class Base;
}
typedef dispatcher::Base dispatcher_type;

} // namespace directive

typedef directive::Base directive_type;

} // namespace cache
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief base class for cache directive of HTTP Header.
 */
class hryky::http::header::cache::directive::Base :
	public WithStreamOut<Base>,
	public WithSwap<Base>
{
public :

	typedef Base this_type;

	/// destructor.
	virtual ~Base();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// dispatches the implementation.
	bool dispatch(dispatcher_type & dispatcher);

protected :

	/// default constructor.
	Base();

	/// copy constructor.
	Base(this_type const &);

	/// move constructor.
	Base(this_type && rhs);

	/// assignment operator.
	hryky_assign_op;

	/// releases the internal resources.
	void clear();

private :

	virtual bool dispatch_impl(dispatcher_type &) = 0;

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
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::http::header::cache::directive::Base::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	return out;
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
#endif // HTTP_HEADER_CACHE_DIRECTIVE_BASE_H_20130107210619546
// end of file
