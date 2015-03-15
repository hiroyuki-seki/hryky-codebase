/**
  @file     window_context_reset.cpp
  @brief    A parameter for window::context_type::reset().
  @author   HRYKY
  @version  $Id: window_context_reset.cpp 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/window/window_context_reset.h"
#include "hryky/window/window_module.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace window
{
namespace context
{
namespace
{
} // namespace "anonymous"
} // namespace context
} // namespace window
} // namespace hryky
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
  @brief default constructor.
 */
hryky::window::context::Reset::Reset()
	: region_()
	  , caption_()
	  , flags_()
{
}
/**
  @brief copy constructor.
 */
hryky::window::context::Reset::Reset(this_type const & rhs)
	: hryky_copy_member(region)
	  , hryky_copy_member(caption)
	  , hryky_copy_member(flags)
{
}
/**
  @brief move constructor.
 */
hryky::window::context::Reset::Reset(this_type && rhs)
	: hryky_move_member(region)
	  , hryky_move_member(caption)
	  , hryky_move_member(flags)
{
}
/**
  @brief destructor.
 */
hryky::window::context::Reset::~Reset()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::window::context::Reset::clear()
{
	hryky::clear(this->flags_);
	hryky::clear(this->caption_);
	hryky::clear(this->region_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::window::context::Reset::swap(this_type & src)
{
	hryky_swap_member(region);
	hryky_swap_member(caption);
	hryky_swap_member(flags);
}
/**
  @brief assigns a new region for this window.
 */
hryky::window::context::Reset &
hryky::window::context::Reset::region(
	int32_t const left,
	int32_t const top,
	int32_t const right,
	int32_t const bottom)
{
	this->region_ = region_type(
		region_type::value_type(left, top),
		region_type::value_type(right, bottom));
	return *this;
}
/**
  @brief retrives the caption of window.
 */
hryky::window::caption_type const & 
hryky::window::context::Reset::caption() const
{
	return this->caption_;
}
/**
  @brief confirms whether a window is hidden initially.
 */
bool hryky::window::context::Reset::hidden() const
{
	return this->flag_.hidden_;
}
/**
  @brief confirms whether a window use OpenGL.
 */
bool hryky::window::context::Reset::use_opengl() const
{
	return this->flag_.use_opengl_;
}
/**
  @brief hides a window initially.
 */
void hryky::window::context::Reset::hidden(bool const src)
{
	this->flag_.hidden_ = src;
}
/**
  @brief indicates to use OpenGL.
 */
void hryky::window::context::Reset::use_opengl(bool const src)
{
	this->flag_.use_opengl_ = src;
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
namespace hryky
{
namespace window
{
namespace context
{
namespace
{
} // namespace "anonymous"
} // namespace context
} // namespace window
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
