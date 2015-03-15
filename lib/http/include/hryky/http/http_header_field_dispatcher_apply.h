/**
  @file         http_header_field_dispatcher_apply.h
  @brief        applies the implementation of field to HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_field_dispatcher_apply.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_FIELD_DISPATCHER_APPLY_H_20130106151705303
#define HTTP_HEADER_FIELD_DISPATCHER_APPLY_H_20130106151705303
#include "hryky/http/http_header_field_dispatcher_base.h"
#include "hryky/http/http_header_accept_entity.h"
#include "hryky/http/http_header_entity.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_virtual_destructor
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
namespace dispatcher
{
	/// applies the implementation of field to HTTP Header.
	class Apply;

} // namespace dispatcher
} // namespace field
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief applies the implementation of field to HTTP Header.
 */
class hryky::http::header::field::dispatcher::Apply :
	public Base,
	public WithStreamOut<Apply>,
	public WithSwap<Apply>
{
public :

	/// base class of inheritance.
	typedef Base base_type;

	typedef Apply this_type;

	/// constructor.
	Apply(header_type & header);

	/// destructor.
	~Apply();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

protected :

private :

	hryky_delete_default_constructor(Apply);
	hryky_delete_this_copy_constructor(Apply);
	hryky_delete_this_copy_assign_op(Apply);

	/// dispatches http::header::accept_type.
	virtual bool on_accept(accept_type & src);

	header_type & header_;

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
namespace dispatcher
{
} // namespace dispatcher
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
hryky::http::header::field::dispatcher::Apply::write_to(
	StreamT & out) const
{
	out << static_cast<base_type const>(*this);
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
namespace dispatcher
{
} // namespace dispatcher
} // namespace field
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// restores warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // HTTP_HEADER_FIELD_DISPATCHER_APPLY_H_20130106151705303
// end of file
