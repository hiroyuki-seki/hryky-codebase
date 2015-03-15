/**
  @file     shader_precision.cpp
  @brief    qualifies a variable in regard to its precision.
  @author   HRYKY
  @version  $Id: shader_precision.cpp 380 2014-08-24 07:41:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/shader/shader_precision.h"
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
hryky::shader::Precision::Kind::tokens[
	hryky::shader::Precision::Kind::num] =
{
	LiteralString<>("highp"),
	LiteralString<>("mediump"),
	LiteralString<>("lowp"),
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
hryky::shader::Precision::Precision()
	: kind_()
{
}
/**
  @brief copy constructor.
 */
hryky::shader::Precision::Precision(this_type const & rhs)
	: hryky_copy_member(kind)
{
}
/**
  @brief move constructor.
 */
hryky::shader::Precision::Precision(this_type && rhs)
	: hryky_move_member(kind)
{
}
/**
  @brief destructor.
 */
hryky::shader::Precision::~Precision()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::shader::Precision::clear()
{
	hryky::clear(this->kind_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::shader::Precision::swap(this_type & src)
{
	hryky_swap_member(kind);
}
/**
  @brief writes out the Precision Qualifier.
 */
hryky::shader::Coder &
hryky::shader::Precision::code(Coder & coder) const
{
	return this->kind_.write_to(coder);
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
