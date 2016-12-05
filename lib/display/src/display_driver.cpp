/**
  @file         display_driver.cpp
  @brief        retains the information of each display driver.
  @author       HRYKY
  @version      $Id: display_driver.cpp 360 2014-07-05 06:59:57Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/clear.h"
#include "hryky/display/display_driver.h"
#include "hryky/repeat.h"
#include "hryky/log.h"
#include "hryky/nullptr.h"
#include "hryky/raii.h"
#include "hryky/sdl/sdl_video.h"
#include "hryky/json/json_writer.h"
#include "hryky/is_null.h"
#if HRYKY_USE_SDL
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
	Screen const g_dummy_screen;
	
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
hryky::display::Driver::Driver()
	: name_()
	  , screens_()
{
	return;
}
/**
  @brief constructor.
 */
hryky::display::Driver::Driver(mempool_type mempool)
	: name_(mempool)
	  , screens_(mempool)
{
}
/**
  @brief copy constructor.
 */
hryky::display::Driver::Driver(this_type const & rhs)
	: hryky_copy_member(name)
	  , hryky_copy_member(screens)
{
}
/**
  @brief move constructor.
 */
hryky::display::Driver::Driver(this_type && rhs)
	: hryky_move_member(name)
	  , hryky_move_member(screens)
{
}
/**
  @brief destructor.
 */
hryky::display::Driver::~Driver()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::display::Driver::clear()
{
	hryky::clear(this->screens_);
	hryky::clear(this->name_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::display::Driver::swap(this_type & src)
{
	hryky_swap_member(name);
	hryky_swap_member(screens);
}
/**
  @brief assigns the information of display driver.
 */
bool hryky::display::Driver::reset(ResetParameter const & param)
{
	auto const name_cstr = param.name_cstr_;

	screens_type::allocator_type allocator =
		this->screens_.get_allocator();

	// initializes the video module of SDL
	sdl::Video const sdl_video(
		allocator.mempool(), name_cstr);
	if (hryky_is_null(sdl_video)) {
		hryky_log_err(
			"failed to init a video driver."
			<< (json::writer()
				<< "driver_name"
				<< (hryky_is_null(name_cstr)
					? "<default>"
					: name_cstr)));
		return false;
	}

	// retrieves the number of screens of the display.
	int const screens_size = ::SDL_GetNumVideoDisplays();
	if (1 > screens_size) {
		hryky_log_err(
			"failed to get the number of displays"
			<< (json::writer()
				<< stream::denote("SDL_error") << ::SDL_GetError()));
		return false;
	}

	screens_type screens(allocator);
	if (!screens.reserve(static_cast<size_t>(screens_size))) {
		hryky_log_alert(
			"failed to allocate memory."
			<< (json::writer()
				<< stream::denote("screens_size") << screens_size));
		return false;
	}

	if (!hryky::repeat(static_cast<size_t>(screens_size)).every_at(
		[&allocator, &name_cstr, &screens](size_t const screen_id) {
			Screen screen(allocator.mempool());
			if (!screen.reset(Screen::ResetParameter(screen_id))) {
				hryky_log_err(
					"Initialize screen failed. "
					<< (json::writer()
						<< stream::denote("name") << name_cstr
						<< stream::denote("screen") << screen_id));
				return false;
			}
			screens.push_back(screen);
			return true;
		})) {
		return false;
	}

	hryky::swap(this->screens_, screens);
	this->name_ = name_cstr;

	return true;
}
/**
  @brief retrieves the name of this display driver.
 */
hryky::display::driver_name_type const & hryky::display::Driver::name() const
{
	return this->name_;
}
/**
  @brief retrieves the number of screens which this video driver has.
 */
hryky::size_t hryky::display::Driver::screens_size() const
{
	return this->screens_.size();
}
/**
  @brief retrieves the screen at the specified index.
 */
hryky::display::Screen const & hryky::display::Driver::screen_at(
	size_t const index) const
{
	return this->screens_[index];
}
/**
  @brief retrieves the default screen.
 */
hryky::display::Screen const & hryky::display::Driver::screen() const
{
	if (0 >= this->screens_size()) {
		hryky_log_warning("This driver has no screen.");
		return g_dummy_screen;
	}
	
	return this->screen_at(0);
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
#endif // HRYKY_USE_SDL
