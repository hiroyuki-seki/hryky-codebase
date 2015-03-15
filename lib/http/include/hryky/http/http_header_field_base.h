/**
  @file         http_header_field_base.h
  @brief        base class for each field of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_field_base.h 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_FIELD_BASE_H_20130104124031194
#define HTTP_HEADER_FIELD_BASE_H_20130104124031194
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
namespace field
{
	/// base class for each field of HTTP Header.
	class Base;

namespace dispatcher
{
	class Base;
} // namespace dispatcher

typedef dispatcher::Base dispatcher_type;

} // namespace field

typedef field::Base field_type;

} // namespace header

} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief base class for each field of HTTP Header.
 */
class hryky::http::header::field::Base :
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

	/**
	  dispatches the implementation by derived class.
	 */
	virtual bool dispatch_impl(dispatcher_type & dispatcher) = 0;

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
namespace field
{
} // namespace field
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
hryky::http::header::field::Base::write_to(
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
namespace field
{
} // namespace field
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_FIELD_BASE_H_20130104124031194
// end of file
