/**
  @file         ip_v4_entity.h
  @brief        retains the information of IPv4 Address.
  @author       HRYKY
  @version      $Id: ip_v4_entity.h 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#ifndef IP_V4_ENTITY_H_20120818184602448
#define IP_V4_ENTITY_H_20120818184602448
#include "hryky/array.h"
#include "hryky/ip/ip_v4_common.h"
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
namespace v4
{
	/// retains the information of IPv4 Address.
	class Entity;

} // namespace v4

typedef v4::Entity v4_type;

} // namespace ip
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information of IPv4 Address.
 */
class hryky::ip::v4::Entity :
	public WithStreamOut<Entity>,
	public WithSwap<Entity>
{
public :

	typedef Entity                                  this_type;
	typedef Array<segment_type, g_segments_size>    segments_type;

	/// default constructor.
	Entity();

	/// copy constructor.
	Entity(this_type const & rhs);

	/// move constructor.
	Entity(this_type && rhs);

	/// constructor with all segments of IPv4 Address.
	Entity(
		segment_type const src0,
		segment_type const src1,
		segment_type const src2,
		segment_type const src3);

	/// destructor.
	~Entity();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// assigns the all segments of IPv4 Address.
	void assign(
		segment_type const src0,
		segment_type const src1,
		segment_type const src2,
		segment_type const src3);

	/// retrieves the segments.
	segments_type const & segments() const;

	/// outputs the information formatted as string.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;
	
	/// retrieves one of the segments of IPv4.
	segment_type segment(uint8_t const index) const;

	/// interchanges the internal resources.
	void swap(this_type & src);

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
namespace v4
{
} // namespace v4
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
hryky::ip::v4::Entity::write_to(
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
namespace v4
{
} // namespace v4
} // namespace ip
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // IP_V4_ENTITY_H_20120818184602448
// end of file
