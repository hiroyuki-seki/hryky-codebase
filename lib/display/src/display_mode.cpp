/**
  @file         display_mode.cpp
  @brief        retains the information of the resolution and color format of a display.
  @author       HRYKY
  @version      $Id: display_mode.cpp 360 2014-07-05 06:59:57Z hryky.private@gmail.com $
 */
#include <precompiled.h>
#include "hryky/clear.h"
#include "hryky/display/display_mode.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace
{
}
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
hryky::display::Mode::Mode()
	: format_()
	  , size_()
	  , refresh_rate_()
{
}
/**
  @brief destructor.
 */
hryky::display::Mode::~Mode()
{
}
/**
  @brief copy constructor.
 */
hryky::display::Mode::Mode(Mode const & rhs)
	: hryky_copy_member(format)
	  , hryky_copy_member(size)
	  , hryky_copy_member(refresh_rate)
{
	return;
}
/**
  @brief move constructor.
 */
hryky::display::Mode::Mode(this_type && rhs)
	: hryky_move_member(format)
	  , hryky_move_member(size)
	  , hryky_move_member(refresh_rate)
{
}
/**
  @brief releases the internal resources.
 */
void hryky::display::Mode::clear()
{
	hryky::clear(this->refresh_rate_);
	hryky::clear(this->size_);
	hryky::clear(this->format_);
}
/**
  @brief clears the existing resources and creates new resources.
 */
bool hryky::display::Mode::reset(ResetParameter const & param)
{
	this->format_       = param.format();
	this->size_         = param.size();
	this->refresh_rate_ = param.refresh_rate();
	
	return true;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::display::Mode::swap(this_type & src)
{
	hryky_swap_member(format);
	hryky_swap_member(size);
	hryky_swap_member(refresh_rate);
}
/**
  @brief retrieves the size of display of the current mode.
 */
hryky::display::size_type const & hryky::display::Mode::size() const
{
	return this->size_;
}
/**
  @brief retrieves the width of the display.
 */
hryky::size_t hryky::display::Mode::width() const
{
	return this->size_.x();
}
/**
  @brief retrieves the height of the display.
 */
hryky::size_t hryky::display::Mode::height() const
{
	return this->size_.y();
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
}
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
