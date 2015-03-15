/**
  @file         ip_v6_entity.h
  @brief        retains the information of IPv6 Address.
  @author       HRYKY
  @version      $Id: ip_v6_entity.h 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#ifndef IP_V6_ENTITY_H_20120818170953381
#define IP_V6_ENTITY_H_20120818170953381
#include "hryky/array.h"
#include "hryky/ip/ip_v6_common.h"
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
namespace ip
{
namespace v6
{
	/// retains the information of IPv6 Address.
	class Entity;

} // namespace v6

typedef v6::Entity v6_type;

} // namespace ip
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information of IPv6 Address.
 */
class hryky::ip::v6::Entity :
	public WithStreamOut<Entity>,
	public WithSwap<Entity>
{
public :
	typedef Entity this_type;
	typedef Array<segment_type, g_segments_size> segments_type;

	/// default constructor.
	Entity();

	/// copy constructor.
	Entity(this_type const & rhs);

	/// move constructor.
	Entity(this_type && rhs);

	/// constructor with all segments.
	Entity(
		segment_type const s0,
		segment_type const s1,
		segment_type const s2,
		segment_type const s3,
		segment_type const s4,
		segment_type const s5,
		segment_type const s6,
		segment_type const s7);

	/// destructor.
	~Entity();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// assigns a segment specified by the index.
	bool segment(uint8_t const index, segment_type const src);

	/// outputs the information formatted as string.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// retrieves the array of segments of IPv6.
	segments_type const & segments() const;

	/// retrieves one of the segments of IPv6.
	segment_type segment(uint8_t const index) const;

protected :

private :

	segments_type   segments_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace ip
{
namespace v6
{
} // namespace v6
} // namespace ip
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information formatted as string.
 */
template <typename StreamT>
StreamT &
hryky::ip::v6::Entity::write_to(
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
namespace ip
{
namespace v6
{
} // namespace v6
} // namespace ip
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // IP_V6_ENTITY_H_20120818170953381
// end of file

