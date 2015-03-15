/**
  @file     retain_pointer.h
  @brief    retains a pointer.
  @author   HRYKY
  @version  $Id: retention_pointer.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef RETENTION_POINTER_H_20130503125843207
#define RETENTION_POINTER_H_20130503125843207
#include "hryky/definition.h"
#include "hryky/type_traits/remove_pointer.h"
#include "hryky/type_traits/add_reference.h"
#include "hryky/type_traits/add_pointer.h"
#include "hryky/type_traits/add_const_reference.h"
#include "hryky/type_traits/add_const_pointer.h"
#include "hryky/swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT
#define hryky_template_arg \
	ValueT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace retention
{
	/// retains a pointer.
	template <hryky_template_param>
	class Pointer;
} // namespace retention
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains a pointer.
 */
template <hryky_template_param>
class hryky::retention::Pointer
{
public :

	typedef Pointer<hryky_template_arg>                     this_type;
	typedef ValueT                                          value_type;
	typedef typename AddPointer<value_type>::type           pointer;
	typedef typename AddConstPointer<value_type>::type      const_pointer;
	typedef typename AddReference<value_type>::type         reference;
	typedef typename AddConstReference<value_type>::type    const_reference;

	/// default constructor.
	Pointer();

	/// copy constructor.
	Pointer(this_type const &);

	/// move constructor.
	Pointer(this_type &&);

	/// constructor with a pointer.
	Pointer(pointer const pointer);

	/// constructor with a reference.
	Pointer(reference ref);

	/// destructor.
	~Pointer();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// dereferences the internal pointer as mutable.
	reference operator*() const;

	/// retrieves the internal pointer.
	pointer operator->() const;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// retrieves the immutable reference.
	pointer get() const;

protected :

	/// assigns a new pointer.
	void assign(pointer const ptr);

private :

	pointer pointer_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::retention::Pointer<hryky_template_arg>::Pointer()
	: pointer_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::retention::Pointer<hryky_template_arg>::Pointer(
	this_type const & rhs)
	: hryky_copy_member(pointer)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::retention::Pointer<hryky_template_arg>::Pointer(
	this_type && rhs)
	: hryky_move_member(pointer)
{
}
/**
  @brief constructor with a pointer.
 */
template <hryky_template_param>
hryky::retention::Pointer<hryky_template_arg>::Pointer(
	pointer const src)
	: pointer_(src)
{
}
/**
  @brief constructor with a reference.
 */
template <hryky_template_param>
hryky::retention::Pointer<hryky_template_arg>::Pointer(
	reference ref)
	: pointer_(&ref)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::retention::Pointer<hryky_template_arg>::~Pointer()
{
}
/**
  @brief dereferences the internal pointer as mutable.
 */
template <hryky_template_param>
typename hryky::retention::Pointer<hryky_template_arg>::reference 
hryky::retention::Pointer<hryky_template_arg>::operator*() const
{
	return hryky::dereference(this->get());
}
/**
  @brief retrieves the internal pointer.
 */
template <hryky_template_param>
typename hryky::retention::Pointer<hryky_template_arg>::pointer 
hryky::retention::Pointer<hryky_template_arg>::operator->() const
{
	return this->pointer_;
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::retention::Pointer<hryky_template_arg>::clear()
{
	hryky::clear(this->pointer_);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::retention::Pointer<hryky_template_arg>::write_to(
	StreamT & out) const
{
	out << this->pointer_;
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::retention::Pointer<hryky_template_arg>::swap(
	this_type & src)
{
	hryky_swap_member(pointer);
}
/**
  @brief retrieves the reference.
 */
template <hryky_template_param>
typename hryky::retention::Pointer<hryky_template_arg>::pointer 
hryky::retention::Pointer<hryky_template_arg>::get() const
{
	return this->pointer_;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
/**
  @brief assigns a new pointer.
 */
template <hryky_template_param>
void hryky::retention::Pointer<hryky_template_arg>::assign(
	pointer const src)
{
	this->pointer_ = src;
}
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace retention
{

} // namespace retention
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the macro definition
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // RETENTION_POINTER_H_20130503125843207
// end of file
