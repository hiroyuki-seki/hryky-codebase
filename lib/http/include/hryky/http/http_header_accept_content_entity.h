/**
  @file         http_header_accept_content_entity.h
  @brief        retains the information for 'Accept' field-content of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_accept_content_entity.h 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_ACCEPT_CONTENT_ENTITY_H_20130112171712386
#define HTTP_HEADER_ACCEPT_CONTENT_ENTITY_H_20130112171712386
#include "hryky/http/http_header_accept_params_entity.h"
#include "hryky/http/http_header_media_type_entity.h"
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
namespace content
{
	/// retains the information for 'Accept' field-content of HTTP Header.
	class Entity;

} // namespace content

typedef content::Entity content_type;

} // namespace accept
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information for 'Accept' field-content of HTTP Header.
 */
class hryky::http::header::accept::content::Entity :
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

	/// assigns a new 'media-range'.
	void media_range(media_type_type const & src);

	/// assigns a new 'accept-params'.
	void params(params_type const & src);

protected :

private :

	media_type_type media_range_;
	params_type params_;

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
namespace content
{
} // namespace content
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
hryky::http::header::accept::content::Entity::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(media_range);
	hryky_write_member(params);
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
namespace content
{
} // namespace content
} // namespace accept
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_ACCEPT_CONTENT_ENTITY_H_20130112171712386
// end of file
