/**
  @file         window_module.cpp
  @brief        manages window module.
  @author       HRYKY
  @version      $Id: window_module.cpp 375 2014-07-29 04:27:53Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/sdl/sdl_video.h"
#include "hryky/window/window_module.h"
#include "hryky/log/log_definition.h"
#include "hryky/clear.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace
{
}
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
  @brief destructor.
 */
hryky::window::Module::~Module()
{
}
/**
  @brief confirms whether the instance is invalid.
 */
bool hryky::window::Module::is_null() const
{
	return hryky_is_null(this->impl_);
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief constructor.
 */
hryky::window::Module::Module()
	: impl_()
{
	if (this->is_null()) {
		hryky_log_alert(
			"failed to initialize implementation of Window System");
	}
}
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
