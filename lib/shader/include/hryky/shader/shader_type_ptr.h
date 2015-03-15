/**
  @file     shader_type_ptr.h
  @brief    retains a pointer to type::Base.
  @author   HRYKY
  @version  $Id: shader_type_ptr.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_TYPE_PTR_H_20140830170540378
#define SHADER_TYPE_PTR_H_20140830170540378
#include "hryky/intrusive_ptr.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
	/// retains a pointer to type::Base.
	class TypePtr;

namespace type
{
	class Base;
} // namespace type
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains a pointer to type::Base.
 */
class hryky::shader::TypePtr :
	public IntrusivePtr<type::Base>
{
public :

	typedef IntrusivePtr<type::Base> base_type;

	typedef TypePtr this_type;

	/// default constructor.
	TypePtr();

	/// creates an instance with a pointer.
	TypePtr(pointer const ptr, bool const add_ref = true);

	/// copy constructor.
	TypePtr(this_type const &);

	/// move constructor.
	TypePtr(this_type &&);

	/// destructor.
	~TypePtr();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

private :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT &
hryky::shader::TypePtr::write_to(StreamT & out) const
{
	if (hryky_is_null(*this)) {
		return this->base_type::write_to(out);
	}
	else {
		return (*this)->write_to(out);
	}
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
	/// creates a type for void.
	TypePtr void_type();

	/// creates a type for bool.
	TypePtr bool_type();

	/// creates a type for int.
	TypePtr int_type();

	/// creates a type for uint.
	TypePtr uint_type();

	/// creates a type for float.
	TypePtr float_type();

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // SHADER_TYPE_PTR_H_20140830170540378
// end of file
