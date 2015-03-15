/**
  @file     shader_function_ptr.cpp
  @brief    retains a pointer to Function.
  @author   HRYKY
  @version  $Id: shader_function_ptr.cpp 380 2014-08-24 07:41:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/shader/shader_function_ptr.h"
#include "hryky/shader/shader_function.h"
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
hryky::shader::FunctionPtr::FunctionPtr()
	: base_type()
{
}
/**
  @brief creates an intance from pointer.
 */
hryky::shader::FunctionPtr::FunctionPtr(
	pointer const ptr, bool const add_ref)
	: base_type(ptr, add_ref)
{
}
/**
  @brief copy constructor.
 */
hryky::shader::FunctionPtr::FunctionPtr(this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief move constructor.
 */
hryky::shader::FunctionPtr::FunctionPtr(this_type && rhs)
	: base_type(std::move(rhs))
{
}
/**
  @brief destructor.
 */
hryky::shader::FunctionPtr::~FunctionPtr()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::shader::FunctionPtr::clear()
{
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::shader::FunctionPtr::swap(this_type & src)
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
