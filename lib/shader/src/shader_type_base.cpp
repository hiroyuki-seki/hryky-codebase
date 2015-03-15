/**
  @file     shader_type_base.cpp
  @brief    The base class for type of variable.
  @author   HRYKY
  @version  $Id: shader_type_base.cpp 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/shader/shader_type_base.h"
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
namespace type
{
namespace
{
} // namespace "anonymous"
} // namespace type
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
hryky::shader::type::Base::Base()
	: base_type()
	  , retain_type()
{
}
/**
  @brief creates an instance with a name of this type.
 */
hryky::shader::type::Base::Base(name_type const & name)
	: base_type()
	  , retain_type(name)
{
}
/**
  @brief copy constructor.
 */
hryky::shader::type::Base::Base(this_type const & rhs)
	: base_type(rhs)
	  , retain_type(rhs)
{
}
/**
  @brief move constructor.
 */
hryky::shader::type::Base::Base(this_type && rhs)
	: base_type(std::move(rhs))
	  , retain_type(std::move(rhs))
{
}
/**
  @brief destructor.
 */
hryky::shader::type::Base::~Base()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::shader::type::Base::clear()
{
	this->retain_type::clear();
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::shader::type::Base::swap(this_type & src)
{
	this->base_type::swap(src);
	this->retain_type::swap(src);
}
/**
  @brief retrieves the name of type.
 */
hryky::shader::type::Base::name_type const & 
hryky::shader::type::Base::name() const
{
	return *this->get();
}
/**
  @brief writes the declaration of type.
 */
hryky::shader::Coder &
hryky::shader::type::Base::declare_impl(
	Coder & coder) const
{
	return coder << this->name();
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
namespace type
{
namespace
{
} // namespace "anonymous"
} // namespace type
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
