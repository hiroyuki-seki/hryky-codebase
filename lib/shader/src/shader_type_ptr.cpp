/**
  @file     shader_type_ptr.cpp
  @brief    retains a pointer to type::Base.
  @author   HRYKY
  @version  $Id: shader_type_ptr.cpp 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/shader/shader_type_ptr.h"
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
namespace
{
	/// creates a type with the name.
	template <size_t Size>
	TypePtr base_type(char const (&name)[Size]);

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
hryky::shader::TypePtr::TypePtr()
	: base_type(void_type())
{
}
/**
  @brief creates an instance with a pointer.
 */
hryky::shader::TypePtr::TypePtr(
	pointer const ptr, bool const add_ref)
	: base_type(ptr, add_ref)
{
}
/**
  @brief copy constructor.
 */
hryky::shader::TypePtr::TypePtr(this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief move constructor.
 */
hryky::shader::TypePtr::TypePtr(this_type && rhs)
	: base_type(std::move(rhs))
{
}
/**
  @brief destructor.
 */
hryky::shader::TypePtr::~TypePtr()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::shader::TypePtr::clear()
{
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::shader::TypePtr::swap(this_type & src)
{
	this->base_type::swap(src);
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
/**
  @brief creates a type for void.
 */
hryky::shader::TypePtr hryky::shader::void_type()
{
	return base_type("void");
}
/**
  @brief creates a type for bool.
 */
hryky::shader::TypePtr hryky::shader::bool_type()
{
	return base_type("bool");
}
/**
  @brief creates a type for int.
 */
hryky::shader::TypePtr hryky::shader::int_type()
{
	return base_type("int");
}
/**
  @brief creates a type for uint.
 */
hryky::shader::TypePtr hryky::shader::uint_type()
{
	return base_type("uint");
}
/**
  @brief creates a type for float.
 */
hryky::shader::TypePtr hryky::shader::float_type()
{
	return base_type("float");
}
//------------------------------------------------------------------------------
// defines functions used in this file
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
namespace
{
/**
  @brief creates a type with the name.
 */
template <size_t Size>
TypePtr base_type(char const (&name)[Size])
{
	allocator::Mempool<type::Base> allocator;
	return TypePtr(allocator::instantiate_by(allocator, name));
}
} // namespace "anonymous"
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
