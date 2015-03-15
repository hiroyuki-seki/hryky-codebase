/**
  @file         uri_path_entity.h
  @brief        retains the information of the 'Path' part of URI.
  @author       HRYKY
  @version      $Id: uri_path_entity.h 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#ifndef URI_PATH_ENTITY_H_20130103161617344
#define URI_PATH_ENTITY_H_20130103161617344
#include "hryky/uri/uri_common.h"
#include "hryky/vector.h"
#include "hryky/mempool/mempool_base.h"
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
namespace path
{
	/// retains the information of the 'Path' part of URI.
	class Entity;

} // namespace path

typedef path::Entity path_type;

} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information of the 'Path' part of URI.
 */
class hryky::uri::path::Entity :
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

	/// appends a segment to this instance.
	bool append(segment_type const & src);

	/// appends an other entity.
	bool append(this_type const & src);

protected :

private :

	typedef Vector<segment_type> segments_type;
	
	segments_type segments_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace uri
{
namespace path
{
} // namespace path
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
hryky::uri::path::Entity::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(segments);
	
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
namespace path
{
} // namespace path
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // URI_PATH_ENTITY_H_20130103161617344
// end of file
