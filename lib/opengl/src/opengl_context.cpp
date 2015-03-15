/**
  @file     opengl_context.cpp
  @brief    retains a context of OpenGL.
  @author   HRYKY
  @version  $Id: opengl_context.cpp 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/opengl/opengl_context.h"
#include "hryky/window/window_context.h"
#include "hryky/clear.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace opengl
{
namespace
{
} // namespace "anonymous"
} // namespace opengl
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
  @brief creates an instance associating with the window.
 */
hryky::opengl::Context::Context(
	window::Context const & window)
	: raw_(window.raw())
{
}
/**
  @brief move constructor.
 */
hryky::opengl::Context::Context(this_type && rhs)
	: hryky_move_member(raw)
{
}
/**
  @brief destructor.
 */
hryky::opengl::Context::~Context()
{
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::opengl::Context::swap(this_type & src)
{
	hryky_swap_member(raw);
}
/**
  @brief retrieves the implementation of OpenGL context.
 */
hryky::opengl::Context::raw_type &
hryky::opengl::Context::raw()
{
	return this->raw_;
}
/**
  @brief retrieves the implementation of OpenGL context as immutable.
 */
hryky::opengl::Context::raw_type const &
hryky::opengl::Context::raw() const
{
	return this->raw_;
}
/**
  @brief confirms whether this instance is invalid.
 */
bool hryky::opengl::Context::is_null() const
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
namespace opengl
{
namespace
{
} // namespace "anonymous"
} // namespace opengl
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
