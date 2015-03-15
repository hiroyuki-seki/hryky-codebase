/**
  @file         http_header_product_entity.h
  @brief        retains the information of HTTP Product Token.
  @author       HRYKY
  @version      $Id: http_header_product_entity.h 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_PRODUCT_ENTITY_H_20121121220250585
#define HTTP_HEADER_PRODUCT_ENTITY_H_20121121220250585
#include "hryky/mempool/mempool_base.h"
#include "hryky/http/http_header_common.h"
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
namespace product
{
	/// retains the information of HTTP Product Token.
	class Entity;

} // namespace product

typedef product::Entity product_type;

} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information of HTTP Product Token.
 */
class hryky::http::header::product::Entity :
	public WithStreamOut<Entity>,
	public WithSwap<Entity>
{
public :

	typedef Entity              this_type;
	typedef token_type          name_type;
	typedef token_type          version_type;

	/// default constructor.
	Entity();

	/// copy constructor.
	Entity(this_type const &);

	/// move constructor.
	Entity(this_type && rhs);

	/// constructor.
	Entity(mempool_type const mempool);

	/// constructor with product name.
	Entity(name_type const & name);

	/// constructor with name and version of product.
	Entity(name_type const & name, version_type const & version);

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

	/// retrieves the mutable instance of the name.
	name_type & name();

	/// retrieves the mutable instance of the version.
	version_type & version();

	/// retrieves the immutable instance of the name.
	name_type const & name() const;

	/// retrieves the immutable instance of the version.
	version_type const & version() const;

protected :

private :

	name_type       name_;
	version_type    version_;

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
namespace product
{
} // namespace product
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
hryky::http::header::product::Entity::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(name);
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
namespace header
{
namespace product
{
} // namespace product
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_PRODUCT_ENTITY_H_20121121220250585
// end of file
