/**
  @file     http_header_field_entity.h
  @brief    retains the kind and the name of HTTP Header field.
  @author   HRYKY
  @version  $Id: http_header_field_entity.h 328 2014-02-24 02:40:42Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_FIELD_ENTITY_H_20130813154020319
#define HTTP_HEADER_FIELD_ENTITY_H_20130813154020319
#include "hryky/http/http_header_common.h"
#include "hryky/http/http_header_field_common.h"
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
	/// retains the kind and the name of HTTP Header field.
	class Entity;

	typedef Entity entity_type;

} // namespace field
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the kind and the name of HTTP Header field.
 */
class hryky::http::header::field::Entity :
	public WithStreamOut<Entity>,
	public WithSwap<Entity>
{
public :

	typedef Entity this_type;
	typedef Vector<octet_type> name_type;
	typedef Vector<octet_type> content_type;

	/// default constructor.
	Entity();

	/// constructor.
	Entity(Kind::Raw const kind, name_type const & name);

	/// copy constructor.
	Entity(this_type const &);

	/// move constructor.
	Entity(this_type &&);

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

	/// retrieves the kind of HTTP Header field.
	kind_type const & kind() const;

	/// assigns a new name of this field.
	void name(name_type const & src);

	/// appends a new content of this field.
	bool append(content_type const & src);

protected :

private :

	typedef Vector<content_type> contents_type;
	
	kind_type kind_;
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
hryky::http::header::field::Entity::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(kind);
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
} // namespace field
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_FIELD_ENTITY_H_20130813154020319
// end of file
