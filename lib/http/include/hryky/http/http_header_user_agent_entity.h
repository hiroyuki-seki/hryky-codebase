/**
  @file         http_header_user_agent_entity.h
  @brief        retains the information about HTTP 'User-Agent' field.
  @author       HRYKY
  @version      $Id: http_header_user_agent_entity.h 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_USER_AGENT_ENTITY_H_20130112013513732
#define HTTP_HEADER_USER_AGENT_ENTITY_H_20130112013513732
#include "hryky/vector.h"
#include "hryky/http/http_header_product_entity.h"
#include "hryky/http/http_header_comment_sequence.h"
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
namespace user_agent
{
	/// retains the information about HTTP 'User-Agent' field.
	class Entity;

} // namespace user_agent

typedef user_agent::Entity user_agent_type;

} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information about HTTP 'User-Agent' field.
 */
class hryky::http::header::user_agent::Entity :
	public WithStreamOut<Entity>,
	public WithSwap<Entity>
{
public :

	typedef Entity this_type;
	typedef comment::sequence_type comment_type;

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

	/// appends a new 'product'.
	bool append(product_type const & src);

	/// appends a new 'comment'.
	bool append(comment_type const & src);

protected :

private :

	typedef Vector<product_type> products_type;
	typedef Vector<comment_type> comments_type;

	products_type products_;
	comments_type comments_;

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
namespace user_agent
{
} // namespace user_agent
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
hryky::http::header::user_agent::Entity::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(products);
	hryky_write_member(comments);

	
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
namespace user_agent
{
} // namespace user_agent
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_USER_AGENT_ENTITY_H_20130112013513732
// end of file
