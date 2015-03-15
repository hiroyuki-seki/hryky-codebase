/**
  @file         http_header_entity.h
  @brief        retains message-headers of HTTP Message.
  @author       HRYKY
  @version      $Id: http_header_entity.h 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_ENTITY_H_20120908100329085
#define HTTP_HEADER_ENTITY_H_20120908100329085
#include "hryky/mempool/mempool_base.h"
#include "hryky/uri.h"
#include "hryky/http/http_header_connection_common.h"
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
	/// retains message-headers of HTTP Message.
	class Entity;

} // namespace header

typedef header::Entity header_type;

} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains message-headers of HTTP Message.
 */
class hryky::http::header::Entity :
	public WithStreamOut<Entity>,
	public WithSwap<Entity>
{
public :

	typedef Entity this_type;
	typedef uri::authority::Entity host_type;

	/// default constructor.
	Entity();

	/// constructor.
	explicit Entity(mempool_type const mempool);

	/// copy constructor.
	Entity(this_type const &);

	/// move constructor.
	Entity(this_type && rhs);

	/// destructor.
	~Entity();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// outputs the information formatted as string.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// retrieves the mutable reference to Host field.
	host_type & host();

	/// retrieves the immutable reference to Host field.
	host_type const & host() const;

	/// assigns the kind of 'Connection' field.
	void connection(connection::kind_type const & src);

protected :

private :

	host_type               host_;
	connection::kind_type   connection_;

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
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information formatted as string.
 */
template <typename StreamT>
StreamT &
hryky::http::header::Entity::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(host);
	hryky_write_member(connection);

	
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
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_ENTITY_H_20120908100329085
// end of file
