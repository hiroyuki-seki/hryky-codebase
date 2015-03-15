/**
  @file         http_header_accept_entity.h
  @brief        retains the information of a 'Accept' field of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_accept_entity.h 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_ACCEPT_ENTITY_H_20130104125733206
#define HTTP_HEADER_ACCEPT_ENTITY_H_20130104125733206
#include "hryky/http/http_header_accept_content_entity.h"
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
namespace accept
{
	/// retains the information of a 'Accept' field of HTTP Header.
	class Entity;

} // namespace accept

typedef accept::Entity accept_type;

} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information of a 'Accept' field of HTTP Header.
 */
class hryky::http::header::accept::Entity :
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

	/// appends a 'Accept' field-content.
	bool append(content_type const & src);

protected :

private :

	typedef Vector<content_type> contents_type;

	contents_type contents_;

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
namespace accept
{
} // namespace accept
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
hryky::http::header::accept::Entity::write_to(
	StreamT & out) const
{
	out << this->contents_;
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
namespace accept
{
} // namespace accept
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_ACCEPT_ENTITY_H_20130104125733206
// end of file
