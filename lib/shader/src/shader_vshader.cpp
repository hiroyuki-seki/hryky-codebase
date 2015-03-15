/**
  @file     shader_vshader.cpp
  @brief    creates a source for vertex shader.
  @author   HRYKY
  @version  $Id: shader_vshader.cpp 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/shader/shader_vshader.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
namespace
{
} // namespace "anonymous"
} // namespace shader
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
hryky::shader::Vshader::Vshader()
	: base_type()
{
}
/**
  @brief copy constructor.
 */
hryky::shader::Vshader::Vshader(this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief move constructor.
 */
hryky::shader::Vshader::Vshader(this_type && rhs)
	: base_type(std::move(rhs))
{
}
/**
  @brief destructor.
 */
hryky::shader::Vshader::~Vshader()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::shader::Vshader::clear()
{
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::shader::Vshader::swap(this_type & src)
{
	this->base_type::swap(src);
}
/**
  @brief creates the built-in variable gl_Position.
 */
hryky::shader::VariablePtr<hryky::shader::Vector<float, 4> >
hryky::shader::Vshader::position() const
{
	return vec4("gl_Position");
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
// defines functions used in this file
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
namespace
{
} // namespace "anonymous"
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
