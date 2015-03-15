/**
  @file         http_header_accept_charset_content_entity.h
  @brief        retains the information for 'Accept-Charset' field-content of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_accept_charset_content_entity.h 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_ACCEPT_CHARSET_CONTENT_ENTITY_H_20130113091902054
#define HTTP_HEADER_ACCEPT_CHARSET_CONTENT_ENTITY_H_20130113091902054
#include "hryky/http/http_header_common.h"
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
namespace charset
{
namespace content
{
	/// retains the information for 'Accept-Charset' field-content of HTTP Header.
	class Entity;

} // namespace content

typedef content::Entity content_type;

} // namespace charset
} // namespace accept
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information for 'Accept-Charset' field-content of HTTP Header.
 */
class hryky::http::header::accept::charset::content::Entity :
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

	/// assigns a new 'charset'.
	void charset(header::charset_type const & src);

	/// assigns a new 'qvalue'.
	void qvalue(header::qvalue_type const src);

protected :

private :

	header::charset_type charset_;
	header::qvalue_type qvalue_;

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
namespace charset
{
namespace content
{
} // namespace content
} // namespace charset
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
hryky::http::header::accept::charset::content::Entity::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(charset);
	hryky_write_member(qvalue);
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
namespace charset
{
namespace content
{
} // namespace content
} // namespace charset
} // namespace accept
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_ACCEPT_CHARSET_CONTENT_ENTITY_H_20130113091902054
// end of file
