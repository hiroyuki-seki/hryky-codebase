/**
  @file         ip_v6_entity.cpp
  @brief        retains the information of IPv6 Address.
  @author       HRYKY
  @version      $Id: ip_v6_entity.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/ip/ip_v6_entity.h"
#include "hryky/log/log_definition.h"
#include "hryky/clear.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace
{
} // namespace "anonymous"
//------------------------------------------------------------------------------
// static variable
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// function prototype
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief constructor.
 */
hryky::ip::v6::Entity::Entity()
	: segments_()
{
}
/**
  @brief copy constructor.
 */
hryky::ip::v6::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(segments)
{
}
/**
  @brief move constructor.
 */
hryky::ip::v6::Entity::Entity(this_type && rhs)
	: hryky_move_member(segments)
{
}
/**
  @brief constructor with all segments.
 */
hryky::ip::v6::Entity::Entity(
	segment_type const s0,
	segment_type const s1,
	segment_type const s2,
	segment_type const s3,
	segment_type const s4,
	segment_type const s5,
	segment_type const s6,
	segment_type const s7)
	: segments_()
{
	segments_[0] = s0;
	segments_[1] = s1;
	segments_[2] = s2;
	segments_[3] = s3;
	segments_[4] = s4;
	segments_[5] = s5;
	segments_[6] = s6;
	segments_[7] = s7;
}
/**
  @brief destructor.
 */
hryky::ip::v6::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::ip::v6::Entity::clear()
{
	hryky::clear(this->segments_);
}
/**
  @brief assigns a segment specified by the index.
 */
bool hryky::ip::v6::Entity::segment(uint8_t const index, segment_type const src)
{
	if (g_segments_size <= index) {
		hryky_log_err("the index of segments must be less than 8");
		return false;
	}

	this->segments_[index] = src;
	
	return true;
}
/**
  @brief retrieves the array of segments of IPv6.
 */
hryky::ip::v6::Entity::segments_type const & 
hryky::ip::v6::Entity::segments() const
{
	return this->segments_;
}
/**
  @brief retrieves one of the segments of IPv6.
 */
hryky::ip::v6::segment_type hryky::ip::v6::Entity::segment(
	uint8_t const index) const
{
	if (g_segments_size <= index) {
		hryky_log_err(
			"invalid index for IPv6 segment " << index);
		return 0;
	}
	return this->segments_[index];
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::ip::v6::Entity::swap(this_type & src)
{
	hryky_swap_member(segments);
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace
{
} // namespace "anonymous"
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file

