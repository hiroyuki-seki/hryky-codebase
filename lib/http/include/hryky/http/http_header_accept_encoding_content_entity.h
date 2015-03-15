/**
  @file         http_header_accept_encoding_content_entity.h
  @brief        retains the information for 'Accept-Encoding' field-content of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_accept_encoding_content_entity.h 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_ACCEPT_ENCODING_CONTENT_ENTITY_H_20130112174517406
#define HTTP_HEADER_ACCEPT_ENCODING_CONTENT_ENTITY_H_20130112174517406
#include "hryky/http/http_header_common.h"
#include "hryky/http/http_header_content_common.h"
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
namespace encoding
{
namespace content
{
	/// retains the information for 'Accept-Encoding' field-content of HTTP Header.
	class Entity;

} // namespace content

typedef content::Entity content_type;

} // namespace encoding
} // namespace accept
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information for 'Accept-Encoding' field-content of HTTP Header.
 */
class hryky::http::header::accept::encoding::content::Entity :
	public WithStreamOut<Entity>,
	public WithSwap<Entity>
{
public :

	typedef Entity this_type;
	typedef header::content::coding_type coding_type;

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

	/// assigns a new 'content-coding'.
	void coding(coding_type const & src);

	/// assigns a new 'qvalue'.
	void qvalue(qvalue_type const src);

protected :

private :

	coding_type coding_;
	qvalue_type qvalue_;

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
namespace encoding
{
namespace content
{
} // namespace content
} // namespace encoding
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
hryky::http::header::accept::encoding::content::Entity::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(coding);
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
namespace encoding
{
namespace content
{
} // namespace content
} // namespace encoding
} // namespace accept
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_ACCEPT_ENCODING_CONTENT_ENTITY_H_20130112174517406
// end of file
