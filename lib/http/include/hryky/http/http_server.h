/**
  @file     http_server.h
  @brief    starts HTTP Server.
  @author   HRYKY
  @version  $Id: http_server.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef HTTP_SERVER_H_20130814160842339
#define HTTP_SERVER_H_20130814160842339
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
	/// starts HTTP Server.
	class Server;

} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief starts HTTP Server.
 */
class hryky::http::Server :
	public WithStreamOut<Server>,
	public WithSwap<Server>
{
public :

	typedef Server this_type;

	/// default constructor.
	Server();

	/// destructor.
	~Server();

	/// move constructor.
	Server(this_type &&);

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// confirms whether the HTTP Server is down.
	bool terminal() const;

	/// starts HTTP server with the default parameters.
	bool open(char const * const document_root);

protected :

private :

	hryky_delete_this_copy_constructor(Server);
	hryky_delete_this_copy_assign_op(Server);

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace http
{
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
hryky::http::Server::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
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
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_SERVER_H_20130814160842339
// end of file
