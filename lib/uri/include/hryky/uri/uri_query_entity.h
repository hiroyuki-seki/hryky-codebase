/**
  @file         uri_query_entity.h
  @brief        retains the information about the query part of URI.
  @author       HRYKY
  @version      $Id: uri_query_entity.h 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#ifndef URI_QUERY_ENTITY_H_20130102134543240
#define URI_QUERY_ENTITY_H_20130102134543240
#include "hryky/vector.h"
#include "hryky/mempool/mempool_base.h"
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
namespace uri
{
namespace query
{
	/// retains the information about the query part of URI.
	class Entity;

} // namespace query

typedef query::Entity query_type;

} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information about the query part of URI.
 */
class hryky::uri::query::Entity :
	public WithStreamOut<Entity>,
	public WithSwap<Entity>
{
public :

	typedef Entity this_type;
	typedef mempool_type mempool_type;
	typedef Vector<octet_type> octets_type;

	/// default constructor.
	Entity();

	/// constructor.
	Entity(mempool_type const mempool);

	/// copy constructor.
	Entity(this_type const &);

	/// move constructor.
	Entity(this_type && rhs);

	/// constructor with octets.
	Entity(octets_type const & octets);

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

	/// appends an octet.
	bool append(octet_type const src);

protected :

private :

	octets_type octets_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace uri
{
namespace query
{
} // namespace query
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::uri::query::Entity::write_to(
	StreamT & out) const
{
	out << this->octets_;
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
namespace uri
{
namespace query
{
} // namespace query
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // URI_QUERY_ENTITY_H_20130102134543240
// end of file
