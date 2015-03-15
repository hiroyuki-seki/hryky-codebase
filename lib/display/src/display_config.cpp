/**
  @file     display_config.cpp
  @brief    retains the configuration of display.
  @author   HRYKY
  @version  $Id: display_config.cpp 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/display/display_config.h"
#include "hryky/clear.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace display
{
namespace
{
} // namespace "anonymous"
} // namespace display
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
hryky::display::Config::Config()
{
}
/**
  @brief constructor with parameters
 */
hryky::display::Config::Config(
	driver_name_type const & driver_name,
	format_type const & format,
	size_type const & size,
	refresh_rate_type refresh_rate)
	: driver_name_(driver_name)
	  , format_(format)
	  , size_(size)
	  , refresh_rate_(refresh_rate)
{
}
/**
  @brief copy constructor.
 */
hryky::display::Config::Config(this_type const & rhs)
	: hryky_copy_member(driver_name)
	  , hryky_copy_member(format)
	  , hryky_copy_member(size)
	  , hryky_copy_member(refresh_rate)
{
}
/**
  @brief move constructor.
 */
hryky::display::Config::Config(this_type && rhs)
	: hryky_move_member(driver_name)
	  , hryky_move_member(format)
	  , hryky_move_member(size)
	  , hryky_move_member(refresh_rate)
{
}
/**
  @brief destructor.
 */
hryky::display::Config::~Config()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::display::Config::clear()
{
	hryky::clear(this->refresh_rate_);
	hryky::clear(this->size_);
	hryky::clear(this->format_);
	hryky::clear(this->driver_name_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::display::Config::swap(this_type & src)
{
	hryky_swap_member(driver_name);
	hryky_swap_member(format);
	hryky_swap_member(size);
	hryky_swap_member(refresh_rate);
}
/**
  @brief retrieves the name of the driver.
 */
hryky::display::driver_name_type const &
hryky::display::Config::driver_name() const
{
	return this->driver_name_;
}
/**
  @brief retrieves the format of this display mode.
 */
hryky::display::format_type const &
hryky::display::Config::format() const
{
	return this->format_;
}
/**
  @brief retrieves the size of this display mode.
 */
hryky::display::size_type const & hryky::display::Config::size() const
{
	return this->size_;
}
/**
  @brief retrieves the refresh-rate of this display mode.
 */
hryky::display::refresh_rate_type
hryky::display::Config::refresh_rate() const
{
	return this->refresh_rate_;
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
namespace display
{
namespace
{
} // namespace "anonymous"
} // namespace display
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
