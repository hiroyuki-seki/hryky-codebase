/**
  @file         http_request_entity.h
  @brief        retains the information of HTTP Request.
  @author       HRYKY
  @version      $Id: http_request_entity.h 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#ifndef HTTP_REQUEST_H_20120602152652310
#define HTTP_REQUEST_H_20120602152652310
#include "hryky/http/http_header_common.h"
#include "hryky/http/http_header_entity.h"
#include "hryky/http/http_method_common.h"
#include "hryky/http/http_version_entity.h"
#include "hryky/http/http_body_entity.h"
#include "hryky/mempool/mempool_base.h"
#include "hryky/substring.h"
#include "hryky/uri.h"
#include "hryky/vector.h"
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
namespace request
{
	/// retains the information of HTTP Request.
	class Entity;

} // namespace request

typedef request::Entity request_type;

} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information of HTTP Request.
 */
class hryky::http::request::Entity :
	public WithStreamOut<Entity>,
	public WithSwap<Entity>
{
public :

	typedef Entity                          this_type;
	typedef method::kind_type               method_type;

	/// default constructor.
	Entity();

	/// constructor with the specified mempool.
	Entity(mempool_type const mempool);

	/// copy constructor.
	Entity(this_type const & rhs);

	/// move constructor.
	Entity(this_type && rhs);

	/// destructor.
	~Entity();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// retrieves the mutable entity of URI.
	uri_type & uri();

	/// retrieves the immutable entity of URI.
	uri_type const & uri() const;

	/// assigns a new URI.
	void uri(uri_type const & src);

	/// assigns a HTTP Method.
	void method(method_type const & src);

	/// retrieves the HTTP Method.
	method_type method() const {
		return this->method_;
	}

	/// assigns a HTTP-Version.
	void version(version_type const & src);

	/// formats the information of http::request::Entity as string.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// retrieves the mutable message-header.
	header_type & header();

	/// retrieves the immutable message-header.
	header_type const & header() const;

	/// assigns a new list of headers.
	void header(header_type const & src);

	/// retrieves the immutable message-body of HTTP Message.
	body_type const & body() const;

	/// retrieves the mutable message-body of HTTP Message.
	body_type & body();

	/// assigns a new block for body of HTTP Message.
	void body(body_type const & src);

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

protected :

private :

	method_type     method_;
	uri_type        uri_;
	version_type    version_;
	header_type     header_;
	body_type       body_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace http
{
namespace request
{
} // namespace request
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief formats the information of http::request::Entity as string.
 */
template <typename StreamT>
StreamT &
hryky::http::request::Entity::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(method);
	hryky_write_member(uri);
	hryky_write_member(version);
	hryky_write_member(header);
	hryky_write_member(body);

	
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
namespace request
{
} // namespace request
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_REQUEST_H_20120602152652310
// end of file
