/**
  @file     shader_interpolation.cpp
  @brief    qualifies a variable with the type of interpolation.
  @author   HRYKY
  @version  $Id: shader_interpolation.cpp 380 2014-08-24 07:41:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/shader/shader_interpolation.h"
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
hryky::shader::Interpolation::Kind::tokens[
	hryky::shader::Interpolation::Kind::num] = {
	LiteralString<>("none"),
	LiteralString<>("smooth"),
	LiteralString<>("flat"),
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
hryky::shader::Interpolation::Interpolation()
	: kind_()
{
}
/**
  @brief creates an instance with the kind.
 */
hryky::shader::Interpolation::Interpolation(kind_type const & kind)
	: kind_(kind)
{
}
/**
  @brief copy constructor.
 */
hryky::shader::Interpolation::Interpolation(this_type const & rhs)
	: hryky_copy_member(kind)
{
}
/**
  @brief move constructor.
 */
hryky::shader::Interpolation::Interpolation(this_type && rhs)
	: hryky_move_member(kind)
{
}
/**
  @brief destructor.
 */
hryky::shader::Interpolation::~Interpolation()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::shader::Interpolation::clear()
{
	hryky::clear(this->kind_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::shader::Interpolation::swap(this_type & src)
{
	hryky_swap_member(kind);
}
/**
  @brief writes out the Interpolation Qualifier.
 */
hryky::shader::Coder &
hryky::shader::Interpolation::code(Coder & coder) const
{
	if (Kind::none != this->kind_.raw()) {
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
