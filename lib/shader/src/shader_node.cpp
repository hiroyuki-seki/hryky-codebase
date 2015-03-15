/**
  @file     shader_node.cpp
  @brief    The base class of expression.
  @author   HRYKY
  @version  $Id: shader_node.cpp 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "./shader_code.h"
#include "./shader_declare.h"
#include "hryky/shader/shader_node.h"
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
  @brief destructor.
 */
hryky::shader::Node::~Node()
{
}
/**
  @brief passes this concrete class to a dispatcher.
 */
void hryky::shader::Node::dispatch(
	dispatcher_type & dispatcher)
{
	this->dispatch_impl(dispatcher);
}
/**
  @brief passes this immutable concrete class to a dispatcher.
 */
void hryky::shader::Node::dispatch(
	const_dispatcher_type & dispatcher) const
{
	this->dispatch_impl(dispatcher);
}
/**
  @brief writes the information as the code of shader.
 */
hryky::shader::Coder &
hryky::shader::Node::code(Coder & coder) const
{
	Code code(coder);
	this->dispatch(code);
	return coder;
}
/**
  @brief wirtes the code as declaration.
 */
hryky::shader::Coder &
hryky::shader::Node::declare(Coder & coder) const
{
	Declare declare(coder);
	this->dispatch(declare);
	return coder;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
hryky::shader::Node::Node()
	: intrusive_ptr_trait()
{
}
/**
  @brief copy constructor.
 */
hryky::shader::Node::Node(this_type const & rhs)
	: intrusive_ptr_trait(rhs)
{
}
/**
  @brief move constructor.
 */
hryky::shader::Node::Node(this_type && rhs)
	: intrusive_ptr_trait(std::move(rhs))
{
}
/**
  @brief releases the internal resources.
 */
void hryky::shader::Node::clear()
{
	this->intrusive_ptr_trait::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::shader::Node::swap(this_type &)
{
}
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief writes the information as the code of shader.
 */
hryky::shader::Coder &
hryky::shader::Node::code_impl(Coder & coder) const
{
	return coder;
}
/**
  @brief writes out the declaration of node.
 */
hryky::shader::Coder &
hryky::shader::Node::declare_impl(Coder & coder) const
{
	return coder;
}
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
