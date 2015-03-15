/**
  @file         http_header_cache_directive_dispatcher_base.h
  @brief        base class to be dispatched the implementation derived
                from http::header::cache::directive::Base.
  @author       HRYKY
  @version      $Id: http_header_cache_directive_dispatcher_base.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_CACHE_DIRECTIVE_DISPATCHER_BASE_H_20130107211144549
#define HTTP_HEADER_CACHE_DIRECTIVE_DISPATCHER_BASE_H_20130107211144549
#include "hryky/http/http_header_cache_directive_specifier.h"
#include "hryky/http/http_header_cache_directive_second.h"
#include "hryky/http/http_header_cache_directive_field.h"
#include "hryky/without_new.h"
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
	/// base class to be dispatched the implementation derived from
	/// http::header::cache::directive::Base.
	class Base;

} // namespace dispatcher

typedef dispatcher::Base dispatcher_type;

} // namespace directive
} // namespace cache
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief base class to be dispatched the implementation derived from
    http::header::cache::directive::Base.
 */
class hryky::http::header::cache::directive::dispatcher::Base :
	private WithoutNew
{
public :

	typedef Base this_type;

	bool operator()(specifier_type & src)
	{
		return this->on_specifier(src);
	}

	bool operator()(seconds_type & src)
	{
		return this->on_seconds(src);
	}

	bool operator()(field_type & src)
	{
		return this->on_field(src);
	}

protected :

	/// default constructor.
	Base();

	/// copy constructor.
	Base(this_type const &);

	/// move constructor.
	Base(this_type && rhs);

	/// destructor.
	~Base();

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

private :

	virtual bool on_specifier(specifier_type &) {
		return true;
	}

	virtual bool on_seconds(seconds_type &) {
		return true;
	}

	virtual bool on_field(field_type &) {
		return true;
	}

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
hryky::http::header::cache::directive::dispatcher::Base::write_to(
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
#endif // HTTP_HEADER_CACHE_DIRECTIVE_DISPATCHER_BASE_H_20130107211144549
// end of file
