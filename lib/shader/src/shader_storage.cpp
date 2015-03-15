/**
  @file     shader_storage.cpp
  @brief    qualifies a variable as interface between GPU and CPU.
  @author   HRYKY
  @version  $Id: shader_storage.cpp 380 2014-08-24 07:41:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/shader/shader_storage.h"
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
hryky::shader::Storage::Kind::tokens[
	hryky::shader::Storage::Kind::num] = {
	LiteralString<>("none"),
	LiteralString<>("in"),
	LiteralString<>("out"),
	LiteralString<>("uniform"),
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
hryky::shader::Storage::Storage()
	: kind_()
{
}
/**
  @brief creates an instance with the kind.
 */
hryky::shader::Storage::Storage(Kind::Raw const & kind)
	: kind_(kind)
{
}
/**
  @brief copy constructor.
 */
hryky::shader::Storage::Storage(this_type const & rhs)
	: hryky_copy_member(kind)
{
}
/**
  @brief move constructor.
 */
hryky::shader::Storage::Storage(this_type && rhs)
	: hryky_move_member(kind)
{
}
/**
  @brief destructor.
 */
hryky::shader::Storage::~Storage()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::shader::Storage::clear()
{
	hryky::clear(this->kind_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::shader::Storage::swap(this_type & src)
{
	hryky_swap_member(kind);
}
/**
  @brief writes out the Storage Qualifier.
 */
hryky::shader::Coder &
hryky::shader::Storage::code(Coder & coder) const
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
