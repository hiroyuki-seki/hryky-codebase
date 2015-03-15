/**
  @file         date_entity.h
  @brief        retains a month and a day.
  @author       HRYKY
  @version      $Id: date_entity.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef DATE_ENTITY_H_20121230142904270
#define DATE_ENTITY_H_20121230142904270
#include "hryky/date/date_common.h"
#include "hryky/date/date_month_common.h"
#include "hryky/date/date_week_common.h"
#include "hryky/pragma.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_padded
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace date
{
	/// retains a month and a day.
	class Entity;

} // namespace date

typedef date::Entity date_type;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains a month and a day.
 */
class hryky::date::Entity :
	public WithStreamOut<Entity>,
	public WithSwap<Entity>
{
public :

	typedef Entity this_type;

	/// default constructor.
	Entity();

	/// copy constructor.
	Entity(this_type const &);

	/// move constructor.
	Entity(this_type && rhs);

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

	/// retrieves the year of this date.
	year_type const & year() const;

	/// retrieves the month of this date.
	month_type const & month() const;

	/// retrieves the day of this date.
	day_type const & day() const;

	/// retrieves the weekday of this date.
	week_type const & week() const;

	/// retrieves the hour of this date.
	hour_type const & hour() const;

	/// retrieves the minute of this date.
	minute_type const & minute() const;

	/// retrieves the second of this date.
	second_type const & second() const;

	/// assigns a new year to this date.
	void year(year_type const src);

	/// assign a new month to this date.
	void month(month_type::raw_type const src);

	/// assign a new day to this date.
	void day(day_type const src);

	/// assigns a new weekday to this date.
	void week(week_type::raw_type const src);

	/// assigns a new hour to this date.
	void hour(hour_type const src);

	/// assigns a new minute to this date.
	void minute(minute_type const src);

	/// assigns a new second to this date.
	void second(second_type const src);

	/// assigns a new time from an arbitrary type.
	template <typename ValueT>
	void time(ValueT const & value);

protected :

private :

	year_type   year_;
	month_type  month_;
	day_type    day_;
	week_type   week_;
	hour_type   hour_;
	minute_type minute_;
	second_type second_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace date
{
} // namespace date
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief assigns a new time from an arbitrary type.
 */
template <typename ValueT>
void hryky::date::Entity::time(ValueT const & value)
{
	this->hour(value.hour());
	this->minute(value.minute());
	this->second(value.second());
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::date::Entity::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(year);
	hryky_write_member(month);
	hryky_write_member(day);
	hryky_write_member(week);
	hryky_write_member(hour);
	hryky_write_member(minute);
	hryky_write_member(second);
	
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
namespace date
{
} // namespace date
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // DATE_ENTITY_H_20121230142904270
// end of file
