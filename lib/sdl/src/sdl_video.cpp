/**
  @file     sdl_video.cpp
  @brief    facilitates the operation to SDL_Video.
  @author   HRYKY
  @version  $Id: sdl_video.cpp 375 2014-07-29 04:27:53Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/sdl/sdl_video.h"
#include "hryky/sdl/sdl_common.h"
#include "hryky/clear.h"
#include "hryky/json/json_writer.h"
#include "hryky/is_null.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace sdl
{
namespace
{
} // namespace "anonymous"
} // namespace sdl
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
hryky::sdl::Video::Video()
	: module_()
	  , prev_driver_name_()
	  , flags_()
{
	if (!this->reset(hryky_nullptr)) {
		hryky_log_err(
			"failed to reset SDL by the default driver.");
		return;
	}
}
/**
  @brief constructs with the memory pool.
 */
hryky::sdl::Video::Video(mempool_type const mempool)
	: module_()
	  , prev_driver_name_(mempool)
	  , flags_()
{
	if (!this->reset(hryky_nullptr)) {
		hryky_log_err(
			"failed to reset SDL by the default driver.");
		return;
	}
}
/**
  @brief creates an instance with the mempool and the name of driver.
 */
hryky::sdl::Video::Video(
	mempool_type const mempool,
	driver_name_type const driver_name)
	: module_()
	  , prev_driver_name_(mempool)
	  , flags_()
{
	if (!this->reset(driver_name)) {
		hryky_log_err(
			"failed to initialize SDL by the name of driver "
			<< driver_name);
		return;
	}
}
/**
  @brief destructor.
 */
hryky::sdl::Video::~Video()
{
	this->clear();
}
/**
  @brief confirms whether resources are not initialized.
 */
bool hryky::sdl::Video::is_null() const
{
	return !this->flag_.initialized_;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief releases the internal resources.
 */
void hryky::sdl::Video::clear()
{
	if (this->flag_.initialized_) {
		this->flag_.initialized_ = false;
		::SDL_VideoQuit();
		if (this->flag_.restore_driver_) {
			::SDL_VideoInit(this->prev_driver_name_.c_str());
			hryky_log_info(
				"SDL Video is restored for "
				<< this->prev_driver_name_.c_str());
		}
	}
	hryky::clear(this->flags_);
	hryky::clear(this->module_);
}
/**
  @brief rebuilds the SDL Video system with the particular driver.
 */
bool hryky::sdl::Video::reset(driver_name_type const driver_name)
{
	this->clear();

	if (!this->module_.reset()) {
		hryky_log_alert(
			"failed to reset the SDL system before the SDL Video system.");
		return false;
	}

	driver_name_type const prev_driver_name
		= ::SDL_GetCurrentVideoDriver();
	
	// initializes the default video module of SDL
	if (-1 == ::SDL_VideoInit(driver_name)) {
		hryky_log_alert(
			"failed to initialize the SDL video system"
			<< (json::writer()
				<< "driver_name"
				<< (hryky_is_null(driver_name) ? "<default>" : driver_name)
				<< "SDL_error" << ::SDL_GetError()));
		return false;
	}

	hryky_log_info(
		"SDL Video is initialized for "
		<< (hryky_is_null(driver_name) ?
			"the default driver" : driver_name));

	if (!hryky_is_null(prev_driver_name)) {
		this->prev_driver_name_ = prev_driver_name;
		this->flag_.restore_driver_ = true;
	}

	this->flag_.initialized_ = true;

	return true;
}
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace sdl
{
namespace
{
} // namespace "anonymous"
} // namespace sdl
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
