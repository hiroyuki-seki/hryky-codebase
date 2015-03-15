/**
  @file     opengl_shader_entity_fshader.cpp
  @brief    retains a fragment shader.
  @author   HRYKY
  @version  $Id: opengl_shader_entity_fshader.cpp 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/opengl/opengl_shader_entity_fshader.h"
#include "hryky/opengl/opengl_shader_module.h"
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
namespace entity
{
namespace
{
} // namespace "anonymous"
} // namespace entity
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
  @brief constructs with the shader module.
 */
hryky::opengl::shader::entity::Fshader::Fshader(
	module_type const module)
	: base_type(module)
{
}
/**
  @brief move constructor.
 */
hryky::opengl::shader::entity::Fshader::Fshader(this_type && rhs)
	: base_type(::std::move(rhs))
{
}
/**
  @brief destructor.
 */
hryky::opengl::shader::entity::Fshader::~Fshader()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::opengl::shader::entity::Fshader::clear()
{
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::opengl::shader::entity::Fshader::swap(this_type & src)
{
	this->base_type::swap(src);
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
namespace shader
{
namespace entity
{
namespace
{
} // namespace "anonymous"
} // namespace entity
} // namespace shader
} // namespace opengl
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
