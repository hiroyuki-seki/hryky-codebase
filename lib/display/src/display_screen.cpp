/**
  @file         display_screen.cpp
  @brief        retains the information of each display screen.
  @author       HRYKY
  @version      $Id: display_screen.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/clear.h"
#include "hryky/display/display_screen.h"
#include "hryky/repeat.h"
#include "hryky/log.h"
#include "hryky/sdl/sdl_common.h"
#include "hryky/json/json_writer.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace
{
} // namespace "anonymous"
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
hryky::display::Screen::Screen()
	: modes_()
	  , current_mode_()
	  , desktop_mode_()
	  , region_()
	  , id_()
{
	return;
}
/**
  @brief constructor.
 */
hryky::display::Screen::Screen(mempool_type mempool)
	: modes_(mempool)
	  , current_mode_()
	  , desktop_mode_()
	  , region_()
	  , id_()
{
}
/**
  @brief copy constructor.
 */
hryky::display::Screen::Screen(this_type const & rhs)
	: hryky_copy_member(modes)
	  , hryky_copy_member(current_mode)
	  , hryky_copy_member(desktop_mode)
	  , hryky_copy_member(region)
	  , hryky_copy_member(id)
{
}
/**
  @brief move constructor.
 */
hryky::display::Screen::Screen(this_type && rhs)
	: hryky_move_member(modes)
	  , hryky_move_member(current_mode)
	  , hryky_move_member(desktop_mode)
	  , hryky_move_member(region)
	  , hryky_move_member(id)
{
}
/**
  @brief destructor.
 */
hryky::display::Screen::~Screen()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::display::Screen::clear()
{
	hryky::clear(this->id_);
	hryky::clear(this->region_);
	hryky::clear(this->desktop_mode_);
	hryky::clear(this->current_mode_);
	hryky::clear(this->modes_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::display::Screen::swap(this_type & src)
{
	hryky_swap_member(modes);
	hryky_swap_member(current_mode);
	hryky_swap_member(desktop_mode);
	hryky_swap_member(region);
	hryky_swap_member(id);
}
/**
  @brief assigns the information of display screen of driver.
 */
bool hryky::display::Screen::reset(ResetParameter const & param)
{
	screen_id_type const screen_id = param.screen_id();

	// retrieves current display mode
	mode_type current_mode;
	{
		::SDL_DisplayMode raw_mode;

		if (0 != ::SDL_GetCurrentDisplayMode(
			static_cast<int>(screen_id), &raw_mode)) {
			hryky_log_alert(
				"failed to get the current display-mode."
				<< (json::writer()
					<< stream::denote("SDL_error") << ::SDL_GetError()
					<< hryky_stream_denote(screen_id)));
			return false;
		}

		current_mode.reset(mode_type::ResetParameter(raw_mode));
	}

	// retrieves desktop display mode
	mode_type desktop_mode;
	{
		::SDL_DisplayMode raw_mode;

		if (0 != ::SDL_GetDesktopDisplayMode(
			static_cast<int>(screen_id), &raw_mode)) {
			hryky_log_alert(
				"failed to get the desktop display-mode."
				<< (json::writer()
					<< stream::denote("SDL_error") << ::SDL_GetError()
					<< hryky_stream_denote(screen_id)));
			return false;
		}

		desktop_mode.reset(mode_type::ResetParameter(raw_mode));
	}

	SDL_Rect boundary;
	if (0 != ::SDL_GetDisplayBounds(
		static_cast<int>(screen_id), &boundary)) {
		hryky_log_alert(
			"failed to get the boundary of the display."
			<< (json::writer()
				<< stream::denote("SDL_error") << ::SDL_GetError()
				<< hryky_stream_denote(screen_id)));
		return false;
	}

	region_type const region(
		coord_type(
			static_cast<size_t>(boundary.x),
			static_cast<size_t>(boundary.y)),
		coord_type(
			static_cast<size_t>(boundary.x + boundary.w),
			static_cast<size_t>(boundary.y + boundary.h)));

	int const modes_size = ::SDL_GetNumDisplayModes(static_cast<int>(screen_id));
	if (1 > modes_size) {
		hryky_log_alert(
			"failed to get the number of modes of the display."
			<< (json::writer()
				<< stream::denote("SDL_error") << ::SDL_GetError()
				<< hryky_stream_denote(screen_id)));
		return false;
	}

	modes_type::allocator_type allocator = this->modes_.get_allocator();

	modes_type modes(allocator);
	if (!modes.reserve(static_cast<size_t>(modes_size))) {
		hryky_log_alert(
			"failed to allocate memory."
			<< (json::writer()
				<< stream::denote("modes_size") << modes_size));
		return false;
	}

	// gathers the information of all modes of the display.
	if (!hryky::repeat(static_cast<size_t>(modes_size)).every_at(
		[screen_id, &modes](size_t const mode_id) {
			::SDL_DisplayMode raw_mode;

			if (0 != ::SDL_GetDisplayMode(
				static_cast<int>(screen_id),
				static_cast<int>(mode_id),
				&raw_mode)) {
				hryky_log_alert(
					"failed to get the display-mode."
					<< (json::writer()
						<< stream::denote("SDL_error") << ::SDL_GetError()
						<< hryky_stream_denote(screen_id)
						<< hryky_stream_denote(mode_id)));
				return false;
			}

			mode_type mode;
			mode.reset(mode_type::ResetParameter(raw_mode));

			modes.push_back(mode);
			return true;
		})) {
		return false;
	}

	hryky::swap(this->modes_, modes);
	hryky::swap(this->current_mode_, current_mode);
	hryky::swap(this->desktop_mode_, desktop_mode);
	this->region_ = region;
	this->id_ = screen_id;

	return true;
}
/**
  @brief retrieves the current display mode.
 */
hryky::display::Mode const & hryky::display::Screen::current_mode() const
{
	return this->current_mode_;
}
/**
  @brief retrieves the desktop display mode.
 */
hryky::display::Mode const & hryky::display::Screen::desktop_mode() const
{
	return this->desktop_mode_;
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
