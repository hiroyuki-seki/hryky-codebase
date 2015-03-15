/**
  @file     shader_outputs.cpp
  @brief    collects output variables.
  @author   HRYKY
  @version  $Id: shader_outputs.cpp 380 2014-08-24 07:41:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/shader/shader_outputs.h"
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
hryky::shader::Outputs::Outputs()
	: base_type()
{
}
/**
  @brief copy constructor.
 */
hryky::shader::Outputs::Outputs(this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief move constructor.
 */
hryky::shader::Outputs::Outputs(this_type && rhs)
	: base_type(std::move(rhs))
{
}
/**
  @brief destructor.
 */
hryky::shader::Outputs::~Outputs()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::shader::Outputs::clear()
{
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::shader::Outputs::swap(this_type & src)
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
