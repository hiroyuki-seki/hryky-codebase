/**
  @file         http_header_cache_directive_dispatcher_apply.h
  @brief        applies the implementation of cache-directive to cache-control.
  @author       HRYKY
  @version      $Id: http_header_cache_directive_dispatcher_apply.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_CACHE_DIRECTIVE_DISPATCHER_APPLY_H_20130108140359252
#define HTTP_HEADER_CACHE_DIRECTIVE_DISPATCHER_APPLY_H_20130108140359252
#include "hryky/http/http_header_cache_directive_dispatcher_base.h"
#include "hryky/http/http_header_cache_control_entity.h"
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
namespace cache
{
namespace directive
{
namespace dispatcher
{
	/// applies the implementation of cache-directive to cache-control.
	class Apply;

} // namespace dispatcher

typedef dispatcher::Apply apply_type;

} // namespace directive
} // namespace cache
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief applies the implementation of cache-directive to cache-control.
 */
class hryky::http::header::cache::directive::dispatcher::Apply :
	public Base,
	public WithStreamOut<Apply>,
	public WithSwap<Apply>
{
public :

	/// base class of inheritance.
	typedef Base base_type;

	typedef Apply this_type;

	/// default constructor.
	Apply();

	/// copy constructor.
	Apply(this_type const &);

	/// move constructor.
	Apply(this_type && rhs);

	/// constructor.
	Apply(control_type & control);

	/// destructor.
	~Apply();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

protected :

private :

	/// applies http::header::cache::specifier_type to cache-control.
	virtual bool on_specifier(specifier_type & specifier);

	/// applies http::header::cache::directive::seconds_type to cache-control.
	virtual bool on_seconds(seconds_type & second);

	/// applies http::header::cache::directive::field_type to cache_control.
	virtual bool on_field(field_type & field);

	control_type & control_;

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
namespace dispatcher
{
} // namespace dispatcher
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
hryky::http::header::cache::directive::dispatcher::Apply::write_to(
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
namespace cache
{
namespace directive
{
namespace dispatcher
{
} // namespace dispatcher
} // namespace directive
} // namespace cache
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // HTTP_HEADER_CACHE_DIRECTIVE_DISPATCHER_APPLY_H_20130108140359252
// end of file
