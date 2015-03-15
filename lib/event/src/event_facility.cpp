/**
  @file     event_facility.cpp
  @brief    facilicates handling events from the system.
  @author   HRYKY
  @version  $Id: event_facility.cpp 377 2014-08-15 02:49:04Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/event/event_facility.h"
#include "hryky/chrono.h"
#include "hryky/sdl.h"
#include "hryky/clock.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace event
{
namespace
{
} // namespace "anonymous"
} // namespace event
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
hryky::event::Facility::Facility()
	: mempool_()
	  , on_quit_()
	  , on_draw_()
{
}
/**
  @brief creates an instance with mempool.
 */
hryky::event::Facility::Facility(mempool::Ptr const & mempool)
	: mempool_(mempool)
	  , on_quit_()
	  , on_draw_()
{
}
/**
  @brief destructor.
 */
hryky::event::Facility::~Facility()
{
}
/**
  @brief assigns the callback invoked when system quits.
 */
hryky::event::Facility &
hryky::event::Facility::on_quit(on_quit_type const & src)
{
	this->on_quit_ = src;
	
	return *this;
}
/**
  @brief assigns the callback for rendering.
 */
hryky::event::Facility &
hryky::event::Facility::on_draw(on_draw_type const & src)
{
	this->on_draw_ = src;
	
	return *this;
}
/**
  @brief starts the loop to handle events.
 */
bool hryky::event::Facility::run()
{
	bool quit = false;
	clock::Elapse draw_after;
	while (!quit) {
		if (!this->step(quit, draw_after)) {
			return false;
		}
	}
	return true;
}
/**
  @brief starts the loop to handle events for the specified duration.
 */
bool hryky::event::Facility::run(
	chrono::milliseconds const & duration)
{
	bool quit = false;
	clock::Elapse expire;
	clock::Elapse draw_after;
	while (!quit) {
		if (duration < expire()) {
			return true;
		}
		if (!this->step(quit, draw_after)) {
			return false;
		}
	}
	return true;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief handles an event.
 */
void hryky::event::Facility::poll(bool & quit)
{
#if HRYKY_USE_SDL
	::SDL_Event event;
	if (0 == ::SDL_PollEvent(&event)) {
		return;
	}
	
	switch (event.type) {
	case ::SDL_QUIT:
		this->on_quit();
		quit = true;
		break;
	case ::SDL_WINDOWEVENT:
		switch (event.window.event) {
		case ::SDL_WINDOWEVENT_SHOWN:
			hryky_log_info("system shows window.");
			break;
		case ::SDL_WINDOWEVENT_HIDDEN:
			hryky_log_info("system hides window.");
			break;
		case ::SDL_WINDOWEVENT_EXPOSED:
			hryky_log_info("system requires to draw window.");
			break;
		case ::SDL_WINDOWEVENT_MOVED:
			hryky_log_info("system moves window.");
			break;
		case ::SDL_WINDOWEVENT_RESIZED:
			hryky_log_info("system changes the size of window.");
			break;
		case ::SDL_WINDOWEVENT_SIZE_CHANGED:
			hryky_log_info("the size of window has been changed.");
			break;
		case ::SDL_WINDOWEVENT_MINIMIZED:
			hryky_log_info("the window has been nimimized.");
			break;
		case ::SDL_WINDOWEVENT_MAXIMIZED:
			hryky_log_info("the window has been maximized.");
			break;
		case ::SDL_WINDOWEVENT_RESTORED:
			hryky_log_info("the size of window is back to normal.");
			break;
		case ::SDL_WINDOWEVENT_ENTER:
			hryky_log_info("the window gained the mouse-focus.");
			break;
		case ::SDL_WINDOWEVENT_LEAVE:
			hryky_log_info("the window lost the mouse-focus.");
			break;
		case ::SDL_WINDOWEVENT_FOCUS_GAINED:
			hryky_log_info("the window gained the keyboard-focus.");
			break;
		case ::SDL_WINDOWEVENT_FOCUS_LOST:
			hryky_log_info("the window lost the keyboard-focus.");
			break;
		case ::SDL_WINDOWEVENT_CLOSE:
			hryky_log_info("system closes window.");
			break;
		default:
			hryky_log_info(
				"unhandled SDL window event"
				<< (json::writer()
					<< "type" << event.window.event
					<< "id" << event.window.windowID));
			break;
		}
		break;
	default:
		hryky_log_info(
			"unhandled SDL event"
			<< (json::writer()
				<< "type" << event.type));
		break;
	}
#endif
}
/**
  @brief arises when system is about to quit.
 */
void hryky::event::Facility::on_quit()
{
	if (hryky_is_null(this->on_quit_)) {
		return;
	}
	this->on_quit_->run(Tuple<>());
}
/**
  @brief arises for rendering.
 */
bool hryky::event::Facility::on_draw()
{
	if (hryky_is_null(this->on_draw_)) {
		return true;
	}
	return this->on_draw_->run(Tuple<>());
}
/**
  @brief handles events in one loop.
 */
bool hryky::event::Facility::step(
	bool & quit, clock::Elapse & draw_after)
{
	if (1u * clock::duration_type::period::den
		< (60u
		   * clock::duration_type::period::num
		   * draw_after().count())) {
		draw_after.clear();
		if (!this->on_draw()) {
			return false;
		}
	}
	this->poll(quit);
	return true;
}
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines functions used in this file
//------------------------------------------------------------------------------
namespace hryky
{
namespace event
{
namespace
{
} // namespace "anonymous"
} // namespace event
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
