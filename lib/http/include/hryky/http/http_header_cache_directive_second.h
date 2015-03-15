/**
  @file         http_header_cache_directive_second.h
  @brief        retains delta-seconds of cache-directive in HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_cache_directive_second.h 328 2014-02-24 02:40:42Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_CACHE_DIRECTIVE_SECOND_H_20130108174031403
#define HTTP_HEADER_CACHE_DIRECTIVE_SECOND_H_20130108174031403
#include "hryky/http/http_header_cache_common.h"
#include "hryky/http/http_header_cache_directive_common.h"
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
	/// retains delta-seconds of cache-directive in HTTP Header.
	class Second;

	typedef Second seconds_type;

} // namespace directive

} // namespace cache
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains delta-seconds of cache-directive in HTTP Header.
 */
class hryky::http::header::cache::directive::Second :
	public WithStreamOut<Second>,
	public WithSwap<Second>
{
public :

	typedef Second this_type;

	/// default constructor.
	Second();

	/// copy constructor.
	Second(this_type const &);

	/// move constructor.
	Second(this_type && rhs);

	/// constructor.
	Second(
		Kind::Raw const kind,
		cache::seconds_type const & second);

	/// destructor.
	~Second();

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

	/// retrieves the kind of cache-directive.
	kind_type const & kind() const;

	/// retrieves the delta seconds.
	cache::seconds_type const & second() const;

protected :

private :

	kind_type               kind_;
	cache::seconds_type     seconds_;

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
hryky::http::header::cache::directive::Second::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(kind);
	hryky_write_member(seconds);

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
#endif // HTTP_HEADER_CACHE_DIRECTIVE_SECOND_H_20130108174031403
// end of file
