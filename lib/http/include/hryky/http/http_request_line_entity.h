/**
  @file         http_request_line_entity.h
  @brief        retains the information of the first line of HTTP Request Message.
  @author       HRYKY
  @version      $Id: http_request_line_entity.h 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#ifndef HTTP_REQUEST_LINE_ENTITY_H_20130104115233161
#define HTTP_REQUEST_LINE_ENTITY_H_20130104115233161
#include "hryky/http/http_method_entity.h"
#include "hryky/http/http_version_entity.h"
#include "hryky/mempool/mempool_base.h"
#include "hryky/uri.h"
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
namespace request
{
namespace line
{
	/// retains the information of the first line of HTTP Request Message.
	class Entity;

} // namespace line

typedef line::Entity line_type;

} // namespace request
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information of the first line of HTTP Request Message.
 */
class hryky::http::request::line::Entity :
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

	/// constructor with components.
	Entity(
		method_type const & method,
		uri_type const & uri,
		version_type const & version);

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

protected :

private :

	method_type method_;
	uri_type uri_;
	version_type version_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace http
{
namespace request
{
namespace line
{
} // namespace line
} // namespace request
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
hryky::http::request::line::Entity::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(method);
	hryky_write_member(uri);
	hryky_write_member(version);
	
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
namespace request
{
namespace line
{
} // namespace line
} // namespace request
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_REQUEST_LINE_ENTITY_H_20130104115233161
// end of file
