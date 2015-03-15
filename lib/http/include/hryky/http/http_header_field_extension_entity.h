/**
  @file         http_header_field_extension_entity.h
  @brief        retains the information for 'extension-header' field of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_field_extension_entity.h 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_FIELD_EXTENSION_ENTITY_H_20130114162809352
#define HTTP_HEADER_FIELD_EXTENSION_ENTITY_H_20130114162809352
#include "hryky/http/http_header_field_extension_common.h"
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
namespace field
{
namespace extension
{
	/// retains the information for 'extension-header' field of HTTP Header.
	class Entity;

} // namespace extension

typedef extension::Entity extension_type;

} // namespace field
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information for 'extension-header' field of HTTP Header.
 */
class hryky::http::header::field::extension::Entity :
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

	/// assigns a new name of this field.
	void name(name_type const & src);

	/// appends a new content of this field.
	bool append(content_type const & src);

protected :

private :

	typedef Vector<content_type> contents_type;

	name_type name_;
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
namespace field
{
namespace extension
{
} // namespace extension
} // namespace field
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
hryky::http::header::field::extension::Entity::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(name);
	hryky_write_member(contents);

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
namespace field
{
namespace extension
{
} // namespace extension
} // namespace field
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_FIELD_EXTENSION_ENTITY_H_20130114162809352
// end of file
