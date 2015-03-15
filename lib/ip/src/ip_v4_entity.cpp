/**
  @file         ip_v4_entity.cpp
  @brief        retains the information of IPv4 Address.
  @author       HRYKY
  @version      $Id: ip_v4_entity.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/clear.h"
#include "hryky/ip/ip_v4_entity.h"
#include "hryky/log.h"
#include "hryky/stream.h"
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
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
/**
  @brief constructor.
 */
hryky::ip::v4::Entity::Entity()
	: segments_()
{
}
/**
  @brief constructor with all segments of IPv4 Address.
 */
hryky::ip::v4::Entity::Entity(
	segment_type const src0,
	segment_type const src1,
	segment_type const src2,
	segment_type const src3)
	: segments_()
{
	this->assign(src0, src1, src2, src3);
}
/**
  @brief destructor.
 */
hryky::ip::v4::Entity::~Entity()
{
}
/**
  @brief copy constructor.
 */
hryky::ip::v4::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(segments)
{
}
/**
  @brief move constructor.
 */
hryky::ip::v4::Entity::Entity(this_type && rhs)
	: hryky_move_member(segments)
{
}
/**
  @brief releases the internal resources.
 */
void hryky::ip::v4::Entity::clear()
{
	hryky::clear(this->segments_);
}
/**
  @brief assigns the all segments of IPv4 Address.
 */
void hryky::ip::v4::Entity::assign(
	segment_type const src0,
	segment_type const src1,
	segment_type const src2,
	segment_type const src3)
{
	this->segments_[0] = src0;
	this->segments_[1] = src1;
	this->segments_[2] = src2;
	this->segments_[3] = src3;
}
/**
  @brief retrieves the segments.
 */
hryky::ip::v4::Entity::segments_type const & 
hryky::ip::v4::Entity::segments() const
{
	return this->segments_;
}
/**
  @brief retrieves one of the segments of IPv4.
 */
hryky::ip::v4::segment_type hryky::ip::v4::Entity::segment(
	uint8_t const index) const
{
	if (g_segments_size <= index) {
		hryky_log_err(
			"invalid index for the segments of IPv4 " << index);
		return 0;
	}
	return this->segments_[index];
}
/**
  @brief interchanges the internal resources.
 */
void hryky::ip::v4::Entity::swap(this_type & src)
{
	hryky_swap_member(segments);
}
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
