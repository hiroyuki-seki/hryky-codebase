/**
  @file         display_environment.cpp
  @brief        collects the available display environments.
  @author       HRYKY
  @version      $Id: display_environment.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include <precompiled.h>
#include "hryky/clear.h"
#include "hryky/display/display_environment.h"
#include "hryky/repeat.h"
#include "hryky/log/log_definition.h"
#include "hryky/nullptr.h"
#include "hryky/sdl/sdl_common.h"
#include "hryky/sdl/sdl_module.h"
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
	Driver const g_dummy_driver;
}
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
  @brief constructor.
 */
hryky::display::Environment::Environment()
	: drivers_()
	  , initial_driver_id_()
{
}
/**
  @brief constructor with mempool.
 */
hryky::display::Environment::Environment(mempool_type mempool)
	: drivers_(mempool)
	  , initial_driver_id_()
{
	return;
}
/**
  @brief copy constructor.
 */
hryky::display::Environment::Environment(this_type const & rhs)
	: hryky_copy_member(drivers)
	  , hryky_copy_member(initial_driver_id)
{
}
/**
  @brief move constructor.
 */
hryky::display::Environment::Environment(this_type && rhs)
	: hryky_move_member(drivers)
	  , hryky_move_member(initial_driver_id)
{
}
/**
  @brief destructor.
 */
hryky::display::Environment::~Environment()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::display::Environment::clear()
{
	hryky::clear(this->initial_driver_id_);
	hryky::clear(this->drivers_);
}
/**
  @brief recreates new resources with the default parameters.
 */
bool hryky::display::Environment::reset()
{
	return this->reset(ResetParameter());
}
/**
  @brief clears the existing resources and creates new resources.
 */
bool hryky::display::Environment::reset(ResetParameter const &)
{
	this->clear();

	drivers_type::allocator_type allocator = this->drivers_.get_allocator();

	sdl::Module sdl_module;
	if (!sdl_module.reset()) {
		hryky_log_err(
			"failed to reset the SDL system in preparation for "
			"enumerating the information about display environment.");
		return false;
	}

	// retrieves the number of the video drivers
	int const drivers_size = ::SDL_GetNumVideoDrivers();

	if (1 > drivers_size) {
		hryky_log_alert(
			"failed to get the number of video driver."
			<< (json::writer()
				<< stream::denote("SDL_error") << ::SDL_GetError()));
		return false;
	}

	hryky_log_debug(
		"The number of video drivers is " << drivers_size);

	drivers_type drivers(allocator);
	if (!drivers.reserve(static_cast<size_t>(drivers_size))) {
		hryky_log_alert(
			"failed to allocate the buffer for display drivers"
			<< (json::writer()
				<< stream::denote("drivers_size") << drivers_size));
		return false;
	}

	sdl::Video const sdl_video;
	if (hryky_is_null(sdl_video)) {
		hryky_log_err(
			"failed to reset the SDL Video System in preparation for "
			"enumerating the information about display environment.");
		return false;
	}
	
	char const * const initial_driver_name = ::SDL_GetCurrentVideoDriver();

	if (hryky_is_null(initial_driver_name)) {
		hryky_log_alert(
			"failed to get the name of current video driver."
			<< (json::writer()
				<< stream::denote("SDL_error") << ::SDL_GetError()));
		return false;
	}
	hryky_log_debug(
		"The initial Video driver is " << initial_driver_name);

	driver_id_type initial_driver_id = driver_id_type();

	if (!hryky::repeat(static_cast<size_t>(drivers_size)).every_at(
		[&allocator, &drivers, &initial_driver_name, &initial_driver_id](
			size_t const driver_id) {
			driver_type driver(allocator.mempool());
			if (!driver.reset(Driver::ResetParameter(driver_id))) {
				hryky_log_err(
					"failed to reset video driver."
					<< (json::writer()
						<< stream::denote("driver") << driver_id));
				return false;
			}
			drivers.push_back(driver);

			if (initial_driver_name == driver.name()) {
				initial_driver_id = driver_id;
			}
			return true;
		})) {
		return false;
	}

	this->drivers_.swap(drivers);
	this->initial_driver_id_ = initial_driver_id;

	return true;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::display::Environment::swap(this_type & src)
{
	hryky_swap_member(drivers);
	hryky_swap_member(initial_driver_id);
}
/**
  @brief retrieves the number of video drivers.
 */
hryky::size_t hryky::display::Environment::drivers_size() const
{
	return this->drivers_.size();
}
/**
  @brief retrieves the initial driver.
 */
hryky::display::Driver const & 
hryky::display::Environment::initial_driver() const
{
	if (this->drivers_size() <= this->initial_driver_id_) {
		hryky_log_warning("No valid video driver is found.");
		return g_dummy_driver;
	}
	
	return this->drivers_[this->initial_driver_id_];
}
/**
  @brief retrieves the size of the current display.
 */
hryky::display::size_type const &
hryky::display::Environment::initial_size() const
{
	driver_type const & driver = this->initial_driver();
	screen_type const & screen = driver.screen();
	mode_type const & mode = screen.current_mode();

	return mode.size();
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
#endif // HRYKY_USE_SDL
