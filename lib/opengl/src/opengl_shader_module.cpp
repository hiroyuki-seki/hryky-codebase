/**
  @file     opengl_shader_module.cpp
  @brief    retains the interfaces for the operation of OpenGL shader.
  @author   HRYKY
  @version  $Id: opengl_shader_module.cpp 377 2014-08-15 02:49:04Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "./opengl_common_internal.h"
#include "hryky/is_null.h"
#include "hryky/json/json_writer.h"
#include "hryky/opengl/opengl_shader_module.h"
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
namespace shader
{
namespace
{
} // namespace "anonymous"
} // namespace shader
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
  @brief default constructor.
 */
hryky::opengl::shader::Module::Module()
	: issuer_()
	  , glGetShaderiv_()
	  , glCompileShader_()
	  , glGetShaderInfoLog_()
	  , glGetShaderSource_()
	  , glShaderSource_()
	  , initialized_()
{
	if (!this->reset(Version().load())) {
		hryky_log_err(
			"failed to initialize the module handling shader.");
		return;
	}
	this->initialized_ = true;
}
/**
  @brief copy constructor.
 */
hryky::opengl::shader::Module::Module(this_type const & rhs)
	: hryky_copy_member(issuer)
	  , hryky_copy_member(glGetShaderiv)
	  , hryky_copy_member(glCompileShader)
	  , hryky_copy_member(glGetShaderInfoLog)
	  , hryky_copy_member(glGetShaderSource)
	  , hryky_copy_member(glShaderSource)
	  , hryky_copy_member(initialized)
{
}
/**
  @brief move constructor.
 */
hryky::opengl::shader::Module::Module(this_type && rhs)
	: hryky_move_member(issuer)
	  , hryky_move_member(glGetShaderiv)
	  , hryky_move_member(glCompileShader)
	  , hryky_move_member(glGetShaderInfoLog)
	  , hryky_move_member(glGetShaderSource)
	  , hryky_move_member(glShaderSource)
	  , hryky_move_member(initialized)
{
	hryky::clear(rhs.initialized_);
}
/**
  @brief destructor.
 */
hryky::opengl::shader::Module::~Module()
{
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::opengl::shader::Module::swap(this_type & src)
{
	hryky_swap_member(issuer);
	hryky_swap_member(glGetShaderiv);
	hryky_swap_member(glCompileShader);
	hryky_swap_member(glGetShaderInfoLog);
	hryky_swap_member(glGetShaderSource);
	hryky_swap_member(glShaderSource);
	hryky_swap_member(initialized);
}
/**
  @brief creates a raw object of OpenGL Shader.
 */
hryky::opengl::raw::shader_type
hryky::opengl::shader::Module::new_raw_shader(
	raw::shader_kind_type const kind) const
{
	return this->issuer_.new_raw(kind);
}
/**
  @brief renounces the shader with the confirmation
  whether the object is already deleted.
 */
void hryky::opengl::shader::Module::delete_raw_shader(
	raw::shader_type const shader) const
{
	if (raw::g_invalid_shader == shader) {
		return;
	}
	
	if (!hryky_is_null(this->glGetShaderiv_)) {
		raw::shader_property_type deleted;
		hryky_call_gl3(
			this->glGetShaderiv_, shader, GL_DELETE_STATUS, &deleted);
		if (raw::g_true == deleted) {
			return;
		}
	}
	
	this->issuer_.delete_raw(shader);
}
/**
  @brief creates a new object to retain Vertex Shader.
 */
hryky::opengl::shader::entity::Vshader
hryky::opengl::shader::Module::vshader() const
{
	return entity::Vshader(this);
}
/**
  @brief creates a new object to retain Fragment Shader.
 */
hryky::opengl::fshader_type
hryky::opengl::shader::Module::fshader() const
{
	return entity::Fshader(this);
}
/**
  @brief confirms whether this instance is invalid.
 */
bool hryky::opengl::shader::Module::is_null() const
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
  @brief recreates the internal resources.
 */
bool hryky::opengl::shader::Module::reset(Version const &)
{
	if (hryky_is_null(this->issuer_)) {
		hryky_log_warning("failed to reset the issuer of shader object.");
		return false;
	}
	
	hryky_get_gl_proc(glGetShaderiv);
	hryky_get_gl_proc(glCompileShader);
	hryky_get_gl_proc(glGetShaderInfoLog);
	hryky_get_gl_proc(glGetShaderSource);
	hryky_get_gl_proc(glShaderSource);

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
namespace shader
{
namespace
{
} // namespace "anonymous"
} // namespace shader
} // namespace opengl
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
