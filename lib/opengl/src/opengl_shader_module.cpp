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
	  , glIsShader_()
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
	  , hryky_copy_member(glIsShader)
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
	  , hryky_move_member(glIsShader)
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
	hryky_swap_member(glIsShader);
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
/**
  @brief compiles a shader.
 */
bool hryky::opengl::shader::Module::compile(
	raw::shader_type const shader) const
{
	if (hryky_is_null(this->glIsShader_)) {
		hryky_log_err("glIsShader_ is not loaded.");
		return false;
	}

	if (hryky_is_null(this->glCompileShader_)) {
		hryky_log_err("glCompileShader is not loaded.");
		return false;
	}
	
	if (hryky_is_null(this->glGetShaderiv_)) {
		hryky_log_err("glGetShaderiv_ is not loaded.");
		return false;
	}
	
	if (hryky_is_null(this->glGetShaderInfoLog_)) {
		hryky_log_err("glGetShaderInfoLog_ is not loaded.");
		return false;
	}
	
	if (!hryky_call_gl1(this->glIsShader_, shader)) {
		hryky_log_err("The argument 'shader' is not a shader object");
		return false;
	}

	hryky_call_gl1(this->glCompileShader_, shader);

	GLint status = 0;
	hryky_call_gl3(
		this->glGetShaderiv_, shader, GL_COMPILE_STATUS, &status);

	if (GL_TRUE == status) {
		return true;
	}

	GLint info_log_length = 0;
	hryky_call_gl3(
		this->glGetShaderiv_, shader, GL_INFO_LOG_LENGTH, &info_log_length);

	typedef Vector<char> info_log_type;
	info_log_type info_log;
	info_log.resize(
		static_cast<info_log_type::size_type>(info_log_length));

	hryky_call_gl4(
		this->glGetShaderInfoLog_,
		shader,
		info_log_length,
		hryky_nullptr,
		&info_log[0]);

	String<> const info_log_str(info_log.begin(), info_log.end());

	hryky_log_err(
		"failed to compile a shader "
		<< (json::writer()
			<< hryky_stream_denote(info_log_str)));

	return false;
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
	hryky_get_gl_proc(glIsShader);

	return true;
}
/**
  @brief assigns characters as a source to be compiled.
 */
bool hryky::opengl::shader::Module::source(
	raw::shader_type const shader,
	char const * const str,
	size_t const str_size) const
{
	if (hryky_is_null(this->glIsShader_)) {
		hryky_log_err("glIsShader_ is not loaded.");
		return false;
	}

	if (hryky_is_null(this->glShaderSource_)) {
		hryky_log_err("glShaderSource_ is not loaded.");
		return false;
	}

	if (!hryky_call_gl1(this->glIsShader_, shader)) {
		hryky_log_err("The argument 'shader' is not a shader object");
		return false;
	}

	GLsizei const count = 1u;
	GLint const length = static_cast<GLint>(str_size);
	GLchar const * string = str;

	return hryky_call_gl4(
		this->glShaderSource_, shader, count, &string, &length);
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
