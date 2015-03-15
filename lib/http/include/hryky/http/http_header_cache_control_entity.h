/**
  @file         http_header_cache_control_entity.h
  @brief        retains 'Cache-Control' field of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_cache_control_entity.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_CACHE_CONTROL_ENTITY_H_20130108104839117
#define HTTP_HEADER_CACHE_CONTROL_ENTITY_H_20130108104839117
#include "hryky/http/http_header_cache_common.h"
#include "hryky/http/http_header_cache_directive_common.h"
#include "hryky/mempool/mempool_base.h"
#include "hryky/log/log_definition.h"
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
namespace control
{
	/// retains 'Cache-Control' field of HTTP Header.
	class Entity;

} // namespace control
typedef control::Entity control_type;

} // namespace cache
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains 'Cache-Control' field of HTTP Header.
 */
class hryky::http::header::cache::control::Entity :
	public WithStreamOut<Entity>,
	public WithSwap<Entity>
{
public :

	typedef Entity this_type;

	/// default constructor.
	Entity();

	/// copy constructor.
	Entity(this_type const &);

	/// move constructor.
	Entity(this_type && rhs);

	/// constructor.
	Entity(mempool_type const mempool);

	/// destructor.
	~Entity();

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

	/// appends a cache directive.
	bool append(directive::kind_type const directive);

	/// appends a delta seconds of cache-directive.
	bool append(
		directive::kind_type const & kind, seconds_type const & second);

	/// appends an array of field-names.
	template <typename InputIteratorT>
	bool append(
		directive::kind_type const & kind,
		InputIteratorT begin,
		InputIteratorT end);

protected :

private :

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
namespace control
{
} // namespace control
} // namespace cache
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief appends an array of field-names.
 */
template <typename InputIteratorT>
bool
hryky::http::header::cache::control::Entity::append(
	directive::kind_type const & kind,
	InputIteratorT,
	InputIteratorT)
{
	switch (kind.raw()) {
	case directive::Kind::no_cache: break;
	case directive::Kind::no_store: break;
	case directive::Kind::max_age: break;
	case directive::Kind::max_stale: break;
	case directive::Kind::min_fresh: break;
	case directive::Kind::no_transform: break;
	case directive::Kind::only_if_cached: break;
	case directive::Kind::as_public: break;
	case directive::Kind::as_private: break;
	case directive::Kind::must_revalidate: break;
	case directive::Kind::proxy_revalidate: break;
	case directive::Kind::s_maxage: break;

	default:
		hryky_log_err(
			"invalid cache directive " << kind.raw());
		return false;
	}
	return true;
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::http::header::cache::control::Entity::write_to(
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
namespace control
{
} // namespace control
} // namespace cache
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_CACHE_CONTROL_ENTITY_H_20130108104839117
// end of file
