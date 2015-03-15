/**
  @file         uri_host_entity.h
  @brief        retains the information about the 'host' of URI.
  @author       HRYKY
  @version      $Id: uri_host_entity.h 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#ifndef URI_HOST_ENTITY_H_20130104081755012
#define URI_HOST_ENTITY_H_20130104081755012
#include "hryky/ip.h"
#include "hryky/vector.h"
#include "hryky/uri/uri_regname_entity.h"
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
namespace uri
{
namespace host
{
	/// retains the information about the 'host' of URI.
	class Entity;

} // namespace host

typedef host::Entity host_type;

} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information about the 'host' of URI.
 */
class hryky::uri::host::Entity :
	public WithStreamOut<Entity>,
	public WithSwap<Entity>
{
public :

	typedef Entity this_type;
	typedef mempool_type mempool_type;

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

	/// assigns a new IPv4 address.
	void ipv4(ip::v4_type const & src);

	/// assigns a new IPv6 address.
	void ipv6(ip::v6_type const & src);

	/// assigns a new IP address of future version.
	void ipvf(ip::vf_type const & src);

	/// assigns a new registerred name.
	void regname(regname_type const & src);

protected :

private :

	ip::v4_type ipv4_;
	ip::v6_type ipv6_;
	ip::vf_type ipvf_;
	regname_type regname_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace uri
{
namespace host
{
} // namespace host
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::uri::host::Entity::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(ipv4);
	hryky_write_member(ipv6);
	hryky_write_member(ipvf);
	hryky_write_member(regname);
	
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
namespace uri
{
namespace host
{
} // namespace host
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // URI_HOST_ENTITY_H_20130104081755012
// end of file
