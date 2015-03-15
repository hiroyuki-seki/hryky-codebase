/**
  @file         http_header_accept_extension_entity.h
  @brief        retains the information for 'accept-extension' of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_accept_extension_entity.h 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_ACCEPT_EXTENSION_ENTITY_H_20130112123940194
#define HTTP_HEADER_ACCEPT_EXTENSION_ENTITY_H_20130112123940194
#include "hryky/http/http_header_accept_extension_common.h"
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
namespace extension
{
	/// retains the information for 'accept-extension' of HTTP Header.
	class Entity;

} // namespace extension

typedef extension::Entity extension_type;

} // namespace accept
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information for 'accept-extension' of HTTP Header.
 */
class hryky::http::header::accept::extension::Entity :
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
	Entity(key_type const & key, value_type const & value);

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

	key_type key_;
	value_type value_;

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
namespace extension
{
} // namespace extension
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
hryky::http::header::accept::extension::Entity::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(key);
	hryky_write_member(value);
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
namespace extension
{
} // namespace extension
} // namespace accept
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_ACCEPT_EXTENSION_ENTITY_H_20130112123940194
// end of file
