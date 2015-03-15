/**
  @file     shader_arguments.cpp
  @brief    bundles arguments.
  @author   HRYKY
  @version  $Id: shader_arguments.cpp 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/range.h"
#include "hryky/shader/shader_arguments.h"
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
hryky::shader::Arguments::Arguments()
	: base_type()
{
}
/**
  @brief copy constructor.
 */
hryky::shader::Arguments::Arguments(this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief move constructor.
 */
hryky::shader::Arguments::Arguments(this_type && rhs)
	: base_type(std::move(rhs))
{
}
/**
  @brief destructor.
 */
hryky::shader::Arguments::~Arguments()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::shader::Arguments::clear()
{
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::shader::Arguments::swap(this_type & src)
{
	this->base_type::swap(src);
}
/**
  @brief writes the declaration of each argument.
 */
hryky::shader::Coder &
hryky::shader::Arguments::declare_impl(
	Coder & coder) const
{
	auto itr = this->nodes().begin();
	auto const end = this->nodes().end();
	if (end == itr) {
		return coder;
	}
	coder << declaration_of(**itr);
	++itr;

	hryky::range(itr, end).foreach([&coder](node_type const & node) {
		coder << ", " << declaration_of(*node);
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
