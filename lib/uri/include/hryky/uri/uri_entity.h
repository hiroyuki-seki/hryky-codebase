/**
  @file         uri_entity.h
  @brief        retains the information of URI.
  @author       HRYKY
  @version      $Id: uri_entity.h 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#ifndef URI_ENTITY_H_20120807232259640
#define URI_ENTITY_H_20120807232259640
#include "hryky/mempool/mempool_base.h"
#include "hryky/string.h"
#include "hryky/uri/uri_common.h"
#include "hryky/uri/uri_fragment_entity.h"
#include "hryky/uri/uri_hierarchy_entity.h"
#include "hryky/uri/uri_query_entity.h"
#include "hryky/uri/uri_scheme_entity.h"
#include "hryky/vector.h"
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
	/// retains the information of URI.
	class Entity;

} // namespace uri

typedef uri::Entity uri_type;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information of URI.
 */
class hryky::uri::Entity :
	public WithStreamOut<Entity>,
	public WithSwap<Entity>
{
public :

	typedef Entity              this_type;
	typedef mempool_type   mempool_type;

	/// default constructor.
	Entity();

	/// copy constructor.
	Entity(this_type const & rhs);

	/// move constructor.
	Entity(this_type && rhs);

	/// constructor with the memory pool.
	Entity(mempool_type mempool);

	/// destructor.
	~Entity();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// formats the information of uri::Entity as string.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// assigns a URI Scheme.
	void scheme(scheme_type const & src);

	/// assigns a new hierarchy part of URI.
	void hierarchy(hierarchy_type const & src);

	/// assigns a query of URI.
	void query(query_type const & src);

	/// assigns a fragment of URI.
	void fragment(fragment_type const & src);

protected :

private :

	scheme_type         scheme_;
	hierarchy_type      hierarchy_;
	query_type          query_;
	fragment_type       fragment_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace uri
{
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief formats the information of uri::Entity as string.
 */
template <typename StreamT>
StreamT &
hryky::uri::Entity::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(scheme);
	hryky_write_member(hierarchy);
	hryky_write_member(query);
	hryky_write_member(fragment);

	
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
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // URI_ENTITY_H_20120807232259640
// end of file
