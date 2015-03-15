/**
  @file         display_screen.h
  @brief        retains the information of each display screen.
  @author       HRYKY
  @version      $Id: display_screen.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef DISPLAY_SCREEN_H_20120916211556552
#define DISPLAY_SCREEN_H_20120916211556552
#include "hryky/coord/coord_cartesian2.h"
#include "hryky/display/display_common.h"
#include "hryky/display/display_mode.h"
#include "hryky/geometry/geometry_rect.h"
#include "hryky/mempool/mempool_base.h"
#include "hryky/vector.h"
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
namespace display
{
	/// retains the information of each display screen.
	class Screen;

	typedef Screen screen_type;

} // namespace display
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information of each display screen.
 */
class hryky::display::Screen :
	public WithStreamOut<Screen>,
	public WithSwap<Screen>
{
public :

	typedef Screen                      this_type;
	typedef coord::Cartesian2<size_t>  coord_type;
	typedef geometry::Rect<coord_type>  region_type;
	typedef mempool_type           mempool_type;
	typedef Mode                        mode_type;

	struct ResetParameter
	{
		ResetParameter(screen_id_type const screen_id)
			: screen_id_(screen_id)
		{}

	private :
		hryky_accessor_read(screen_id_type, screen_id);
	};

	/// default constructor.
	Screen();

	/// constructor.
	Screen(mempool_type mempool);

	/// copy constructor.
	Screen(this_type const &);

	/// move constructor.
	Screen(this_type && rhs);

	/// destructor.
	~Screen();

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

	/// assigns the information of display screen of driver.
	bool reset(ResetParameter const & param);

	/**
	  traverses the all display configurations of this screen.
	  @param functor is called for each display mode.
	  @param driver_name is the name of the driver which retains this mode.
	  @retval true when the operation is not canceled by user.
	  @retval false when the operation is canceled by user.

	   The function 'bool functor(display::Config &)' is called during the
	  iteration of display modes.
	 */
	template < typename FunctorT >
	bool traverse(
		driver_name_type const & driver_name,
		FunctorT const & functor) const;

	/// retrieves the current display mode.
	Mode const & current_mode() const;

	/// retrieves the desktop display mode.
	Mode const & desktop_mode() const;

protected :

private :

	typedef Vector<mode_type> modes_type;

	modes_type          modes_;
	mode_type           current_mode_;
	mode_type           desktop_mode_;
	region_type         region_;
	screen_id_type      id_;

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
  @brief traverses the all display configurations of this screen.
 */
template < typename FunctorT >
bool hryky::display::Screen::traverse(
	driver_name_type const & driver_name,
	FunctorT const & functor) const
{
	return this->modes_.every([&driver_name, &functor](
		modes_type::const_reference mode) {
		return mode.traverse(driver_name, functor);
	});
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::display::Screen::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(id);
	hryky_write_member(modes);
	hryky_write_member(current_mode);
	hryky_write_member(desktop_mode);
	hryky_write_member(region);
	
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
#endif // DISPLAY_SCREEN_H_20120916211556552
// end of file
