/**
  @file         uri_scheme_entity.h
  @brief        retains the information about the 'scheme' part of URI.
  @author       HRYKY
  @version      $Id: uri_scheme_entity.h 350 2014-04-24 10:10:31Z hryky.private@gmail.com $
 */
#ifndef URI_SCHEME_ENTITY_H_20130103170425378
#define URI_SCHEME_ENTITY_H_20130103170425378
#include "hryky/uri/uri_scheme_common.h"
#include "hryky/sieve.h"
#include "hryky/foreach.h"
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
namespace scheme
{
	/// retains the information about the 'scheme' part of URI.
	class Entity;

} // namespace scheme

typedef scheme::Entity scheme_type;

} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information about the 'scheme' part of URI.
 */
class hryky::uri::scheme::Entity :
	public WithStreamOut<Entity>,
	public WithSwap<Entity>
{
public :

	typedef Entity this_type;
	typedef mempool_type mempool_type;

	/// default constructor.
	Entity();

	/// constructor.
	Entity(mempool_type const mempool);

	/// copy constructor.
	Entity(this_type const &);

	/// move constructor.
	Entity(this_type && rhs);

	/// constructor with the range of octets.
	template <typename InputIteratorT>
	Entity(InputIteratorT begin, InputIteratorT end);

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

	scheme::kind_type kind_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace uri
{
namespace scheme
{
} // namespace scheme
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief constructor with the range of octets.
 */
template <typename InputIteratorT>
hryky::uri::scheme::Entity::Entity(
	InputIteratorT begin, InputIteratorT end)
	: kind_(begin, end)
{
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::uri::scheme::Entity::write_to(
	StreamT & out) const
{
	out << this->kind_;
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
namespace scheme
{
} // namespace scheme
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // URI_SCHEME_ENTITY_H_20130103170425378
// end of file
