/**
  @file     sdl_subsystem_module.cpp
  @brief    facilitates to manage sub-systems of SDL.
  @author   HRYKY
  @version  $Id: sdl_subsystem_module.cpp 350 2014-04-24 10:10:31Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/clear.h"
#include "hryky/sdl/sdl_common.h"
#include "hryky/sdl/sdl_subsystem_module.h"
#include "hryky/json/json_writer.h"
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
namespace subsystem
{
namespace
{
} // namespace "anonymous"
} // namespace subsystem
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
hryky::sdl::subsystem::Module::Module()
	: flag_()
{
}
/**
  @brief destructor.
 */
hryky::sdl::subsystem::Module::~Module()
{
	this->clear();
}
/**
  @brief releases the internal resources.
 */
void hryky::sdl::subsystem::Module::clear()
{
	if (this->valid()) {
		uint32_t const sdl_flag = raw_flag_of(this->flag_);
		::SDL_QuitSubSystem(sdl_flag);
		hryky::clear(this->flag_);
	}
}
/**
  @brief releases the exising resources and initializes the sub-systems.
 */
bool hryky::sdl::subsystem::Module::reset(flag_type const flag)
{
	this->clear();

	uint32_t const sdl_flag = raw_flag_of(flag);

	if (0 == sdl_flag) {
		return true;
	}
	
	// initializes SDL
	if (-1 == ::SDL_InitSubSystem(sdl_flag)) {
		hryky_log_alert(
			"failed to initialize the subsystems of SDL"
			<< (json::writer()
			<< stream::denote("SDL_error") << ::SDL_GetError()
			<< stream::denote("flag") << flag));
		return false;
	}

	this->flag_ = flag;
	
	return true;
}
/**
  @brief confirms whether the SDL subsystem is initialized.
 */
bool hryky::sdl::subsystem::Module::valid() const
{
	return this->flag_.any();
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
