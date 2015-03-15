/**
  @file     shader_node_ptr.cpp
  @brief    retains a pointer to Node.
  @author   HRYKY
  @version  $Id: shader_node_ptr.cpp 380 2014-08-24 07:41:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/shader/shader_node_ptr.h"
#include "hryky/shader/shader_node.h"
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
hryky::shader::NodePtr::NodePtr()
	: base_type()
{
}
/**
  @brief creates an instance with the pointer.
 */
hryky::shader::NodePtr::NodePtr(
	pointer const ptr, bool const add_ref)
	: base_type(ptr, add_ref)
{
}
/**
  @brief copy constructor.
 */
hryky::shader::NodePtr::NodePtr(this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief move constructor.
 */
hryky::shader::NodePtr::NodePtr(this_type && rhs)
	: base_type(std::move(rhs))
{
}
/**
  @brief destructor.
 */
hryky::shader::NodePtr::~NodePtr()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::shader::NodePtr::clear()
{
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::shader::NodePtr::swap(this_type & src)
{
	this->base_type::swap(src);
}
/**
  @brief writes out the code of node.
 */
hryky::shader::Coder &
hryky::shader::NodePtr::code(Coder & coder) const
{
	if (!hryky_is_null(*this)) {
		(*this)->code(coder);
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
