/**
  @file     shader_layout.cpp
  @brief    specifies the layout of a variable.
  @author   HRYKY
  @version  $Id: shader_layout.cpp 380 2014-08-24 07:41:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/shader/shader_layout.h"
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
//------------------------------------------------------------------------------
// function prototype
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
hryky::shader::Layout::Layout()
	: value_()
{
}
/**
  @brief copy constructor.
 */
hryky::shader::Layout::Layout(this_type const & rhs)
	: hryky_copy_member(value)
{
}
/**
  @brief move constructor.
 */
hryky::shader::Layout::Layout(this_type && rhs)
	: hryky_move_member(value)
{
}
/**
  @brief destructor.
 */
hryky::shader::Layout::~Layout()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::shader::Layout::clear()
{
	hryky::clear(this->value_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::shader::Layout::swap(this_type & src)
{
	hryky_swap_member(value);
}
/**
  @brief writes out the Layout Qualifier.
 */
hryky::shader::Coder &
hryky::shader::Layout::code(Coder & coder) const
{
	bool start = false;
	
	if (this->value_.location_.available_) {
		if (start) {
			coder << ",";
		}
		else {
			coder << "layout(";
		}
		coder << "location=" << this->value_.location_.index_;
	}

	if (start) {
		coder << ")";
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
