/**
  @file         opengl_module.cpp
  @brief        manages OpenGL module.
  @author       HRYKY
  @version      $Id: opengl_module.cpp 377 2014-08-15 02:49:04Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "./opengl_common_internal.h"
#include "hryky/log.h"
#include "hryky/opengl/opengl_module.h"
#include "hryky/opengl/opengl_version.h"
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
}
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
hryky::opengl::Module::Module(window_type const & window)
	: context_(window)
	  , cleaner_()
	  , shader_()
	  , glBindFragDataLocation_()
	  , initialized_()
{
	if (!this->reset()) {
		hryky_log_err(
			"failed to initialize the module for OpenGL.");
		return;
	}
	this->initialized_ = true;
}
/**
  @brief move constructor.
 */
hryky::opengl::Module::Module(this_type && rhs)
	: hryky_move_member(context)
	  , hryky_move_member(cleaner)
	  , hryky_move_member(shader)
	  , hryky_move_member(glBindFragDataLocation)
	  , hryky_move_member(initialized)
{
}
/**
  @brief destructor.
 */
hryky::opengl::Module::~Module()
{
}
/**
  @brief retrieves the cleaner.
 */
hryky::opengl::Cleaner const &
hryky::opengl::Module::cleaner() const
{
	return this->cleaner_;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::opengl::Module::swap(this_type & src)
{
	hryky_swap_member(context);
	hryky_swap_member(cleaner);
	hryky_swap_member(shader);
	hryky_swap_member(glBindFragDataLocation);
	hryky_swap_member(initialized);
}
/**
  @brief creates a shader object for Vertex Shader.
 */
hryky::opengl::vshader_type
hryky::opengl::Module::vshader() const
{
	return this->shader_.vshader();
}
/**
  @brief creates a shader object for Fragment Shader.
 */
hryky::opengl::fshader_type
hryky::opengl::Module::fshader() const
{
	return this->shader_.fshader();
}
/**
  @brief confirms whether this instance is invalid.
 */
bool hryky::opengl::Module::is_null() const
{
	return !this->initialized_;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief clears the existing resources and creates new resources.
 */
bool hryky::opengl::Module::reset()
{
	version_type const version = Version().load();
	hryky_log_info(
		"The version of OpenGL is " << version);
	if (Version(3, 0) <= version) {
		hryky_get_gl_proc(glBindFragDataLocation);
	}
	
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
namespace opengl
{
namespace
{
}
} // namepsace opengl
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
