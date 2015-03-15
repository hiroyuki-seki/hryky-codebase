/**
  @file         display_config.h
  @brief        retains the configuration of display.
  @author       HRYKY
  @version      $Id: display_config.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef DISPLAY_CONFIG_H_20120917090904047
#define DISPLAY_CONFIG_H_20120917090904047
#include "hryky/display/display_common.h"
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
namespace display
{
	/// retains the configuration of display.
	class Config;

	typedef Config config_type;

} // namespace display
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the configuration of display.
 */
class hryky::display::Config :
	private WithoutCopy,
	public WithStreamOut<Config>,
	public WithSwap<Config>
{
public :

	typedef Config this_type;

	/// default constructor.
	Config();

	/// constructor with parameters.
	Config(
		driver_name_type const & driver_name,
		format_type const & format,
		size_type const & size,
		refresh_rate_type refresh_rate);

	/// copy constructor.
	Config(this_type const &);

	/// move constructor.
	Config(this_type &&);

	/// destructor.
	~Config();

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

	/// retrieves the name of the driver.
	driver_name_type const & driver_name() const;
	
	/// retrieves the format of this display mode.
	format_type const & format() const;

	/// retrieves the size of this display mode.
	size_type const & size() const;

	/// retrieves the refresh-rate of this display mode.
	refresh_rate_type refresh_rate() const;

protected :

private :

	driver_name_type    driver_name_;
	format_type         format_;
	size_type           size_;
	refresh_rate_type   refresh_rate_;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace display
{
} // namespace display
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::display::Config::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	
	hryky_write_member(driver_name);
	hryky_write_member(format);
	hryky_write_member(size);
	hryky_write_member(refresh_rate);

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
namespace display
{
} // namespace display
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // DISPLAY_CONFIG_H_20120917090904047
// end of file
