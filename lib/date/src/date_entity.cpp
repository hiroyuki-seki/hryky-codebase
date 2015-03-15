/**
  @file         date_entity.cpp
  @brief        retains a month and a day.
  @author       HRYKY
  @version      $Id: date_entity.cpp 328 2014-02-24 02:40:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/clear.h"
#include "hryky/intrusive_ptr.h"
#include "hryky/date/date_entity.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace date
{
namespace
{
} // namespace "anonymous"
} // namespace date
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
hryky::date::Entity::Entity()
	: year_()
	  , month_()
	  , day_()
	  , week_()
	  , hour_()
	  , minute_()
	  , second_()
{
}
/**
  @brief copy constructor.
 */
hryky::date::Entity::Entity(this_type const & rhs)
	: hryky_copy_member(year)
	  , hryky_copy_member(month)
	  , hryky_copy_member(day)
	  , hryky_copy_member(week)
	  , hryky_copy_member(hour)
	  , hryky_copy_member(minute)
	  , hryky_copy_member(second)
{
}
/**
  @brief move constructor.
 */
hryky::date::Entity::Entity(this_type && rhs)
	: hryky_move_member(year)
	  , hryky_move_member(month)
	  , hryky_move_member(day)
	  , hryky_move_member(week)
	  , hryky_move_member(hour)
	  , hryky_move_member(minute)
	  , hryky_move_member(second)
{
}
/**
  @brief destructor.
 */
hryky::date::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::date::Entity::clear()
{
	hryky::clear(this->second_);
	hryky::clear(this->minute_);
	hryky::clear(this->hour_);
	hryky::clear(this->week_);
	hryky::clear(this->day_);
	hryky::clear(this->month_);
	hryky::clear(this->year_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::date::Entity::swap(this_type & src)
{
	hryky_swap_member(year);
	hryky_swap_member(month);
	hryky_swap_member(day);
	hryky_swap_member(week);
	hryky_swap_member(hour);
	hryky_swap_member(minute);
	hryky_swap_member(second);
}
/**
  @brief retrieves the year of this date.
 */
hryky::date::year_type const & hryky::date::Entity::year() const
{
	return this->year_;
}
/**
  @brief retrieves the month of this date.
 */
hryky::date::month_type const & hryky::date::Entity::month() const
{
	return this->month_;
}
/**
  @brief retrieves the day of this date.
 */
hryky::date::day_type const & hryky::date::Entity::day() const
{
	return this->day_;
}
/**
  @brief retrieves the weekday of this date.
 */
hryky::date::week_type const & hryky::date::Entity::week() const
{
	return this->week_;
}
/**
  @brief retrieves the hour of this date.
 */
hryky::date::hour_type const & hryky::date::Entity::hour() const
{
	return this->hour_;
}
/**
  @brief retrieves the minute of this date.
 */
hryky::date::minute_type const & hryky::date::Entity::minute() const
{
	return this->minute_;
}
/**
  @brief retrieves the second of this date.
 */
hryky::date::second_type const & hryky::date::Entity::second() const
{
	return this->second_;
}
/**
  @brief assigns a new year to this date.
 */
void hryky::date::Entity::year(year_type const src)
{
	this->year_ = src;
}
/**
  @brief assign a new month to this date.
 */
void hryky::date::Entity::month(month_type::raw_type const src)
{
	this->month_ = src;
}
/**
  @brief assign a new day to this date.
 */
void hryky::date::Entity::day(day_type const src)
{
	this->day_ = src;
}
/**
  @brief assigns a new weekday to this date.
 */
void hryky::date::Entity::week(week_type::raw_type const src)
{
	this->week_ = src;
}
/**
  @brief assigns a new hour to this date.
 */
void hryky::date::Entity::hour(hour_type const src)
{
	this->hour_ = src;
}
/**
  @brief assigns a new minute to this date.
 */
void hryky::date::Entity::minute(minute_type const src)
{
	this->minute_ = src;
}
/**
  @brief assigns a new second to this date.
 */
void hryky::date::Entity::second(second_type const src)
{
	this->second_ = src;
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
namespace date
{
namespace
{
} // namespace "anonymous"
} // namespace date
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
