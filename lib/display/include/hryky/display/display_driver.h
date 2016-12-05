/**
  @file         display_driver.h
  @brief        retains the information of each display driver.
  @author       HRYKY
  @version      $Id: display_driver.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef DISPLAY_DRIVER_H_20120916182903436
#define DISPLAY_DRIVER_H_20120916182903436
#include "hryky/mempool/mempool_base.h"
#include "hryky/display/display_screen.h"
#include "hryky/display/display_common.h"
#include "hryky/vector.h"
#include "hryky/string.h"
#include "hryky/foreach.h"
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
	/// retains the information of each display driver.
	class Driver;

} // namespace display
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information of each display driver.
 */
class hryky::display::Driver :
	public WithStreamOut<Driver>,
	public WithSwap<Driver>
{
public :

	typedef Driver              this_type;
	typedef Screen              screen_type;
	typedef mempool_type   mempool_type;

	struct ResetParameter
	{
		ResetParameter()
			: name_cstr_()
		{}

		ResetParameter & driver_id(driver_id_type const driver_id)
		{
			this->name_cstr_ = ::SDL_GetVideoDriver(
				static_cast<int>(driver_id));
			return *this;
		}

		ResetParameter & name_cstr(char const * const src)
		{
			this->name_cstr_ = src;
			return *this;
		}
		
	private:
		friend class Driver;
		
		char const * name_cstr_;
	};

	/// default constructor.
	Driver();

	/// constructor.
	Driver(mempool_type mempool);

	/// copy constructor.
	Driver(this_type const &);

	/// move constructor.
	Driver(this_type && rhs);

	/// destructor.
	~Driver();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// resets the internal resources.
	void clear();

	/// assigns the information of display driver.
	bool reset(ResetParameter const & param);

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// retrieves the name of this display driver.
	driver_name_type const & name() const;

	/**
	  @brief traverses the all display configurations of this driver.
	  @param functor is called for each display mode.
	  @retval true when the operation is not canceled by user.
	  @retval false when the operation is canceled by user.

	   The function 'bool functor(display::Config &)' is called during the
	  iteration of display modes.
	 */
	template < typename FunctorT >
	bool traverse(FunctorT const & functor) const;

	/// retrieves the number of screens which this video driver has.
	size_t screens_size() const;

	/// retrieves the screen at the specified index.
	screen_type const & screen_at(size_t const index) const;

	/// retrieves the default screen.
	screen_type const & screen() const;

protected :

private :

	typedef Vector<screen_type>     screens_type;

	driver_name_type    name_;
	screens_type        screens_;
	driver_id_type      id_;

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
  @brief traverses the all display configurations of this driver.
 */
template < typename FunctorT >
bool hryky::display::Driver::traverse(FunctorT const & functor) const
{
	return this->screens_.every([this, &functor](
		screens_type::const_reference screen) {
		return screen.traverse(this->name_, functor);
	});
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::display::Driver::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(name);
	hryky_write_member(id);
	hryky_write_member(screens);
	
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
#endif // DISPLAY_DRIVER_H_20120916182903436
// end of file
