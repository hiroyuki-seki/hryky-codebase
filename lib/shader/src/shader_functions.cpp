/**
  @file     shader_functions.cpp
  @brief    composes functions in the global scope.
  @author   HRYKY
  @version  $Id: shader_functions.cpp 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/shader/shader_functions.h"
#include "hryky/shader/shader_function.h"
#include "hryky/shader/shader_coder.h"
#include "hryky/shader/shader_declaration_of.h"
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
hryky::shader::Functions::Functions()
	: base_type()
{
}
/**
  @brief copy constructor.
 */
hryky::shader::Functions::Functions(this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief move constructor.
 */
hryky::shader::Functions::Functions(this_type && rhs)
	: base_type(std::move(rhs))
{
}
/**
  @brief destructor.
 */
hryky::shader::Functions::~Functions()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::shader::Functions::clear()
{
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::shader::Functions::swap(this_type & src)
{
	this->base_type::swap(src);
}
/**
  @brief writes out the code of this node.
 */
hryky::shader::Coder &
hryky::shader::Functions::code_impl(Coder & coder) const
{
	this->nodes().foreach([&coder](function_type const & function) {
		coder << declaration_of(*function);
	});
	this->nodes().foreach([&coder](function_type const & function) {
		coder << function;
	});
	return coder;
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
