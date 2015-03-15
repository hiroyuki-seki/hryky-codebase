/**
  @file         http_method_entity.h
  @brief        retains the HTTP Method.
  @author       HRYKY
  @version      $Id: http_method_entity.h 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#ifndef HTTP_METHOD_ENTITY_H_20130104121740178
#define HTTP_METHOD_ENTITY_H_20130104121740178
#include "hryky/http/http_method_common.h"
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
namespace method
{
	/// retains the HTTP Method.
	class Entity;

} // namespace method

typedef method::Entity method_type;

} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the HTTP Method.
 */
class hryky::http::method::Entity :
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
	Entity(kind_type const kind);

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

	kind_type kind_;
	

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace http
{
namespace method
{
} // namespace method
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
hryky::http::method::Entity::write_to(
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
namespace http
{
namespace method
{
} // namespace method
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_METHOD_ENTITY_H_20130104121740178
// end of file
