/**
  @file         window_context.cpp
  @brief        creates GUI window.
  @author       HRYKY
  @version      $Id: window_context.cpp 375 2014-07-29 04:27:53Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/window/window_context.h"
#include "hryky/window/window_context_reset.h"
#include "hryky/window/window_context_fullscreen.h"
#include "hryky/log/log_definition.h"
#include "hryky/log/log_writer_base.h"
#include "hryky/raii.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace window
{
namespace
{
	/// creates a raw parameter for resetting.
	Context::raw_type::Reset raw_reset(context::Reset const & param);

} // namespace
} // namespace window
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
hryky::window::Context::Context()
	: module_()
	  , raw_()
{
}
/**
  @brief creates an instance with the specified parameters.
 */
hryky::window::Context::Context(context::Reset const & param)
	: module_()
	  , raw_(raw_reset(param))
{
}
/**
  @brief move constructor.
 */
hryky::window::Context::Context(this_type && rhs)
	: module_()
	  , hryky_move_member(raw)
{
}
/**
  @brief destructor.
 */
hryky::window::Context::~Context()
{
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::window::Context::swap(this_type & src)
{
	hryky_swap_member(raw);
}
/**
  @brief updates the result of rendering.
 */
void hryky::window::Context::update() const
{
	this->raw_.update();
}
/**
  @brief sets the window to fullscreen-mode.
 */
bool hryky::window::Context::fullscreen(
	context::Fullscreen const & param)
{
	raw_type::Fullscreen const raw_param = {
		param.format().sdl_format(),
		static_cast<int>(param.width()),
		static_cast<int>(param.height()),
		static_cast<int>(param.refresh_rate()),
	};
	
	if (!this->raw_.fullscreen(raw_param)) {
		hryky_log_err("failed to apply fullscreen-mode to SDL.");
		return false;
	}

	return true;
}
/**
  @brief retrieves the implementation of Window.
 */
hryky::window::Context::raw_type &
hryky::window::Context::raw()
{
	return this->raw_;
}
/**
  @brief retrieves the implementation of Window as immutable.
 */
hryky::window::Context::raw_type const &
hryky::window::Context::raw() const
{
	return this->raw_;
}
/**
  @brief confirms whether this instance is invalid.
 */
bool hryky::window::Context::is_null() const
{
	return hryky_is_null(this->raw_);
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
namespace window
{
namespace
{
/**
  @brief creates a raw parameter for resetting.
 */
Context::raw_type::Reset raw_reset(context::Reset const & param)
{
	region_type const & region = param.region();
	region_type::value_type const & left_top = region.left_top();
	region_type::value_type const size = region.size();

	Context::raw_type::Reset const raw_param = {
		param.caption().c_str(),
		static_cast<int>(left_top.x()),
		static_cast<int>(left_top.y()),
		static_cast<int>(size.x()),
		static_cast<int>(size.y()),
		true, // use_opengl
		param.hidden(),
	};

	return raw_param;
}
} // namespace
} // namespace window
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
