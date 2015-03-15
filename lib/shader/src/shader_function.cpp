/**
  @file     shader_function.cpp
  @brief    retains a definition of function.
  @author   HRYKY
  @version  $Id: shader_function.cpp 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/shader/shader_function.h"
#include "hryky/shader/shader_type_base.h"
#include "hryky/shader/shader_declaration_of.h"
#include "hryky/stream/stream_indent_scope.h"
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
	char const g_default_name[] = "main";
	
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
hryky::shader::Function::Function()
	: base_type()
	  , name_(g_default_name)
	  , rettype_(void_type())
	  , arguments_()
{
}
/**
  @brief creates a function without a returned value.
 */
hryky::shader::Function::Function(
	name_type const & name)
	: base_type()
	  , name_(name)
	  , rettype_(void_type())
	  , arguments_()
{
}
/**
  @brief copy constructor.
 */
hryky::shader::Function::Function(
	this_type const & rhs)
	: base_type(rhs)
	  , hryky_copy_member(name)
	  , hryky_copy_member(rettype)
	  , hryky_copy_member(arguments)
{
}
/**
  @brief move constructor.
 */
hryky::shader::Function::Function(
	this_type && rhs)
	: base_type(std::move(rhs))
	  , hryky_move_member(name)
	  , hryky_move_member(rettype)
	  , hryky_move_member(arguments)
{
}
/**
  @brief destructor.
 */
hryky::shader::Function::~Function()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::shader::Function::clear()
{
	hryky::clear(this->arguments_);
	hryky::clear(this->rettype_);
	hryky::clear(this->name_);
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::shader::Function::swap(
	this_type & src)
{
	this->base_type::swap(src);
	hryky_swap_member(name);
	hryky_swap_member(rettype);
	hryky_swap_member(arguments);
}
/**
  @brief retrieves the container of arguments.
 */
hryky::shader::Function::arguments_type &
hryky::shader::Function::arguments()
{
	return this->arguments_;
}
/**
  @brief writes out the code of node.
 */
hryky::shader::Coder &
hryky::shader::Function::code_impl(Coder & coder) const
{
	(coder
	 << declaration_of(*this->rettype_) << ' '
	 << this->name_
	 << '('
	 << declaration_of(this->arguments_)
	 << ')' << hryky::endl
	 << '{' << hryky::endl);

	{
		stream::indent::Scope<Coder> const indent(coder);
		this->base_type::code_impl(coder);
	}
	
	coder << '}' << hryky::endl;

	return coder;
}
/**
  @brief writes out the prototype of function.
 */
hryky::shader::Coder &
hryky::shader::Function::declare_impl(
	Coder & coder) const
{
	return (
		coder
		<< declaration_of(*this->rettype_)
		<< ' ' << this->name_ << '('
		<< declaration_of(this->arguments_)
		<< ");" << hryky::endl);
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
