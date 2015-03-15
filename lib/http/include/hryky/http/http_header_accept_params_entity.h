/**
  @file         http_header_accept_params_entity.h
  @brief        retains the information for 'accept-params' of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_accept_params_entity.h 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_ACCEPT_PARAMS_ENTITY_H_20130112125100202
#define HTTP_HEADER_ACCEPT_PARAMS_ENTITY_H_20130112125100202
#include "hryky/http/http_header_common.h"
#include "hryky/http/http_header_accept_extension_entity.h"
#include "hryky/mempool/mempool_base.h"
#include "hryky/vector.h"
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
namespace params
{
	/// retains the information for 'accept-params' of HTTP Header.
	class Entity;

} // namespace params

typedef params::Entity params_type;

} // namespace accept
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information for 'accept-params' of HTTP Header.
 */
class hryky::http::header::accept::params::Entity :
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

	/// appends an 'accept-extension'.
	bool append(extension_type const & extension);

	/// assigns a new 'qvalue'.
	void qvalue(qvalue_type const src);

protected :

private :

	typedef Vector<extension_type> extensions_type;

	qvalue_type qvalue_;
	extensions_type extensions_;

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
namespace params
{
} // namespace params
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
hryky::http::header::accept::params::Entity::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(qvalue);
	hryky_write_member(extensions);
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
namespace params
{
} // namespace params
} // namespace accept
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_ACCEPT_PARAMS_ENTITY_H_20130112125100202
// end of file
