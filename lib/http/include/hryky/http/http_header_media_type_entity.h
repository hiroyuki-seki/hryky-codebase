/**
  @file         http_header_media_type_entity.h
  @brief        retains the information for 'media-range' of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_media_type_entity.h 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_MEDIA_TYPE_ENTITY_H_20130112150338294
#define HTTP_HEADER_MEDIA_TYPE_ENTITY_H_20130112150338294
#include "hryky/vector.h"
#include "hryky/http/http_header_parameter_entity.h"
#include "hryky/http/http_header_media_type_common.h"
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
namespace media_type
{
	/// retains the information for 'media-range' of HTTP Header.
	class Entity;

} // namespace media_type

typedef media_type::Entity media_type_type;

} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information for 'media-range' of HTTP Header.
 */
class hryky::http::header::media_type::Entity :
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

	/// constructor with mempool.
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

	/// assigns a new 'type-name'.
	void type_name(type_name_type const & src);

	/// assigns a new 'subtype-name'.
	void subtype_name(subtype_name_type const & src);

	/// appends a new 'parameter'.
	bool append(parameter_type const & src);

protected :

private :

	typedef Vector<parameter_type> parameters_type;

	type_name_type type_name_;
	subtype_name_type subtype_name_;
	parameters_type parameters_;

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
namespace media_type
{
} // namespace media_type
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
hryky::http::header::media_type::Entity::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(type_name);
	hryky_write_member(subtype_name);
	hryky_write_member(parameters);

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
namespace media_type
{
} // namespace media_type
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_MEDIA_TYPE_ENTITY_H_20130112150338294
// end of file
