/**
  @file     retain_reference.h
  @brief    retains a reference.
  @author   HRYKY
  @version  $Id: retention_reference.h 364 2014-07-12 01:03:03Z hryky.private@gmail.com $
 */
#ifndef RETENTION_REFERENCE_H_20130503134604240
#define RETENTION_REFERENCE_H_20130503134604240
#include "hryky/type_traits/remove_reference.h"
#include "hryky/type_traits/add_reference.h"
#include "hryky/type_traits/add_const_reference.h"
#include "hryky/type_traits/add_pointer.h"
#include "hryky/type_traits/add_const_pointer.h"
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
	/// retains a reference.
	template <hryky_template_param>
	class Reference;
	
} // namespace retention
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains a reference.
 */
template <hryky_template_param>
class hryky::retention::Reference
{
public :

	typedef Reference<hryky_template_arg>                   this_type;
	typedef ValueT                                          value_type;
	typedef typename AddPointer<value_type>::type           pointer;
	typedef typename AddConstPointer<value_type>::type      const_pointer;
	typedef typename AddReference<value_type>::type         reference;
	typedef typename AddConstReference<value_type>::type    const_reference;
	typedef reference                                       initializer_type;

	/// constructor with a reference.
	Reference(initializer_type reference);

	/// copy constructor.
	Reference(this_type const &);

	/// destructor.
	~Reference();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// retrieves the pointer to immutable reference.
	const_pointer get() const;

	/// retrieves the pointer to mutable reference.
	pointer get();

protected :

private :

	hryky_delete_default_constructor(Reference);

	reference reference_;

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
  @brief constructor with a reference.
 */
template <hryky_template_param>
hryky::retention::Reference<hryky_template_arg>::Reference(
	initializer_type reference)
	: reference_(reference)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::retention::Reference<hryky_template_arg>::Reference(
	this_type const & rhs)
	: hryky_copy_member(reference)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::retention::Reference<hryky_template_arg>::~Reference()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::retention::Reference<hryky_template_arg>::clear()
{
	// The value to which this instance refers is not clearred.
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::retention::Reference<hryky_template_arg>::write_to(
	StreamT & out) const
{
	out << this->reference_;
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::retention::Reference<hryky_template_arg>::swap(this_type & src)
{
	// The value to which this instance refers is not interchanged.
}
/**
  @brief retrieves the pointer to immutable reference.
 */
template <hryky_template_param>
typename hryky::retention::Reference<hryky_template_arg>::const_pointer 
hryky::retention::Reference<hryky_template_arg>::get() const
{
	return &this->reference_;
}
/**
  @brief retrieves the pointer to mutable reference.
 */
template <hryky_template_param>
typename hryky::retention::Reference<hryky_template_arg>::pointer 
hryky::retention::Reference<hryky_template_arg>::get()
{
	return &this->reference_;
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
#endif // RETENTION_REFERENCE_H_20130503134604240
// end of file
