/**
  @file         http_header_product_comment_base.h
  @brief        base class for holding 'comment' and 'product' representation polymorphically.
  @author       HRYKY
  @version      $Id: http_header_product_comment_base.h 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_PRODUCT_COMMENT_BASE_H_20130112005749706
#define HTTP_HEADER_PRODUCT_COMMENT_BASE_H_20130112005749706
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
namespace product_comment
{
	/// base class for holding 'comment' and 'product' representation polymorphically.
	class Base;

namespace dispatcher
{
	class Base;
}
typedef dispatcher::Base dispatcher_type;

} // namespace product_comment

typedef product_comment::Base product_comment_type;

} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief base class for holding 'comment' and 'product' representation polymorphically.
 */
class hryky::http::header::product_comment::Base :
	public WithStreamOut<Base>,
	public WithSwap<Base>
{
public :

	typedef Base this_type;

	/// default constructor.
	Base();

	/// copy constructor.
	Base(this_type const &);

	/// move constructor.
	Base(this_type && rhs);

	/// destructor.
	virtual ~Base();

	/// assignment operator.
	hryky_assign_op;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// dispatches the implementation.
	bool dispatch(dispatcher_type & dispatcher);

protected :

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
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::http::header::product_comment::Base::write_to(
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
namespace product_comment
{
} // namespace product_comment
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_PRODUCT_COMMENT_BASE_H_20130112005749706
// end of file
