/**
  @file         uri_authority_entity.h
  @brief        retains the information of an authority of URI.
  @author       HRYKY
  @version      $Id: uri_authority_entity.h 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#ifndef URI_AUTHORITY_ENTITY_H_20120820221848596
#define URI_AUTHORITY_ENTITY_H_20120820221848596
#include "hryky/mempool/mempool_base.h"
#include "hryky/uri/uri_userinfo_entity.h"
#include "hryky/uri/uri_host_entity.h"
#include "hryky/uri/uri_port_entity.h"
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
namespace authority
{
	/// retains the information of an authority of URI.
	class Entity;

} // namespace authority

typedef authority::Entity authority_type;

} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information of an authority of URI.
 */
class hryky::uri::authority::Entity :
	public WithStreamOut<Entity>,
	public WithSwap<Entity>
{
public :

	typedef Entity              this_type;
	typedef mempool_type   mempool_type;

	/// default constructor.
	Entity();

	/// constructor with mempool.
	Entity(mempool_type mempool);

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

	/// assigns a userinfo of URI.
	void userinfo(userinfo_type const & src);

	/// assigns a new host of URI.
	void host(host_type const & src);

	/// assigns a port number of URI.
	void port(port_type const & src);

	/// outputs the information formatted as string.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

protected :

private :

	userinfo_type   userinfo_;
	host_type       host_;
	port_type       port_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace uri
{
namespace authority
{
} // namespace authority
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information formatted as string.
 */
template <typename StreamT>
StreamT &
hryky::uri::authority::Entity::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(userinfo);
	hryky_write_member(host);
	hryky_write_member(port);

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
namespace authority
{
} // namespace authority
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // URI_AUTHORITY_ENTITY_H_20120820221848596
// end of file
