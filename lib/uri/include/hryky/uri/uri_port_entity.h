/**
  @file         uri_port_entity.h
  @brief        retains the information about the 'port' of URI.
  @author       HRYKY
  @version      $Id: uri_port_entity.h 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#ifndef URI_PORT_ENTITY_H_20130104095125077
#define URI_PORT_ENTITY_H_20130104095125077
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
namespace port
{
	/// retains the information about the 'port' of URI.
	class Entity;

} // namespace port

typedef port::Entity port_type;

} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information about the 'port' of URI.
 */
class hryky::uri::port::Entity :
	public WithStreamOut<Entity>,
	public WithSwap<Entity>
{
public :

	typedef Entity this_type;
	typedef uint16_t number_type;

	/// default constructor.
	Entity();

	/// copy constructor.
	Entity(this_type const &);

	/// move constructor.
	Entity(this_type && rhs);

	/// constructor.
	Entity(number_type number);

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

	number_type number_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace uri
{
namespace port
{
} // namespace port
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
hryky::uri::port::Entity::write_to(
	StreamT & out) const
{
	out << this->number_;
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
namespace port
{
} // namespace port
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // URI_PORT_ENTITY_H_20130104095125077
// end of file
