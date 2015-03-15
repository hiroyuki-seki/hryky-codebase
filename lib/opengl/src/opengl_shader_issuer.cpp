/**
  @file     opengl_shader_issuer.cpp
  @brief    accrues and renounces an object of OpenGL Shader.
  @author   HRYKY
  @version  $Id: opengl_shader_issuer.cpp 377 2014-08-15 02:49:04Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "./opengl_common_internal.h"
#include "hryky/clear.h"
#include "hryky/is_null.h"
#include "hryky/json/json_writer.h"
#include "hryky/log.h"
#include "hryky/opengl/opengl_common.h"
#include "hryky/opengl/opengl_shader_issuer.h"
#include "hryky/opengl/opengl_version.h"
#include "hryky/stream/stream_endl.h"
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
hryky::opengl::shader::Issuer::Issuer()
	: glCreateShader_()
	  , glDeleteShader_()
	  , initialized_()
{
	if (!this->reset(Version().load())) {
		hryky_log_err(
			"failed to initialize the issuer for Shader Object.");
		return;
	}
	this->initialized_ = true;
}
/**
  @brief copy constructor.
 */
hryky::opengl::shader::Issuer::Issuer(this_type const & rhs)
	: hryky_copy_member(glCreateShader)
	  , hryky_copy_member(glDeleteShader)
	  , hryky_copy_member(initialized)
{
}
/**
  @brief move constructor.
 */
hryky::opengl::shader::Issuer::Issuer(this_type && rhs)
	: hryky_move_member(glCreateShader)
	  , hryky_move_member(glDeleteShader)
	  , hryky_move_member(initialized)
{
	hryky::clear(rhs.initialized_);
}
/**
  @brief destructor.
 */
hryky::opengl::shader::Issuer::~Issuer()
{
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::opengl::shader::Issuer::swap(this_type & src)
{
	hryky_swap_member(initialized);
	hryky_swap_member(glCreateShader);
	hryky_swap_member(glDeleteShader);
}
/**
  @brief accrues the name of OpenGL Shader Object.
 */
hryky::opengl::raw::shader_type
hryky::opengl::shader::Issuer::new_raw(
	raw::shader_kind_type const shader_kind) const
{
	if (hryky_is_null(this->glCreateShader_)) {
		hryky_log_err("glCreateShader is not loaded.");
		return raw::g_invalid_shader;
	}

	raw::shader_type const raw_shader = this->glCreateShader_(shader_kind);

	while (GL_NO_ERROR != glGetError()) {
		hryky_log_warning("OpenGL Error occurred");
	}

	hryky_log_debug(
		"An OpenGL Shader Object is accrued "
		<< (json::writer()
			<< hryky_stream_denote(raw_shader)
			<< hryky_stream_denote(shader_kind)));
	
	return raw_shader;
}
/**
  @brief renounces the shader object without checking the deletion.
 */
void hryky::opengl::shader::Issuer::delete_raw(
	raw::shader_type const raw_shader) const
{
	if (hryky_is_null(this->glDeleteShader_)) {
		hryky_log_err("glDeleteShader is not loaded.");
		return;
	}

	if (raw::g_invalid_shader == raw_shader) {
		return;
	}

	hryky_log_debug(
		"The OpenGL Shader Object is renounced "
		<< (json::writer()
			<< hryky_stream_denote(raw_shader)));

	hryky_call_gl1(this->glDeleteShader_, raw_shader);
}
/**
  @brief confirms whether this instance is invalid.
 */
bool hryky::opengl::shader::Issuer::is_null() const
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
  @brief reassembles the internal resources.
 */
bool hryky::opengl::shader::Issuer::reset(Version const &)
{
	hryky_get_gl_proc(glCreateShader);
	hryky_get_gl_proc(glDeleteShader);
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
