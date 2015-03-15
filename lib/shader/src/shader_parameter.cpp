/**
  @file     shader_parameter.cpp
  @brief    qualifies a variable in regard to parameter of function.
  @author   HRYKY
  @version  $Id: shader_parameter.cpp 380 2014-08-24 07:41:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/shader/shader_parameter.h"
#include "hryky/shader/shader_coder.h"
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
hryky::LiteralString<> const
hryky::shader::Parameter::Kind::tokens[
	hryky::shader::Parameter::Kind::num] =
{
	LiteralString<>("none"),
	LiteralString<>("in"),
	LiteralString<>("out"),
	LiteralString<>("inout"),
};
//------------------------------------------------------------------------------
// function prototype
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
hryky::shader::Parameter::Parameter()
	: kind_()
{
}
/**
  @brief copy constructor.
 */
hryky::shader::Parameter::Parameter(this_type const & rhs)
	: hryky_copy_member(kind)
{
}
/**
  @brief move constructor.
 */
hryky::shader::Parameter::Parameter(this_type && rhs)
	: hryky_move_member(kind)
{
}
/**
  @brief destructor.
 */
hryky::shader::Parameter::~Parameter()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::shader::Parameter::clear()
{
	hryky::clear(this->kind_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::shader::Parameter::swap(this_type & src)
{
	hryky_swap_member(kind);
}
/**
  @brief writes out the Parameter Qualifier.
 */
hryky::shader::Coder &
hryky::shader::Parameter::code(Coder & coder) const
{
	if (Kind::none != this->kind_) {
		return this->kind_.write_to(coder);
	}
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
