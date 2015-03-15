/**
  @file     retain_value.h
  @brief    retains a value.
  @author   HRYKY
  @version  $Id: retention_value.h 377 2014-08-15 02:49:04Z hryky.private@gmail.com $
 */
#ifndef RETENTION_VALUE_H_20130503123928194
#define RETENTION_VALUE_H_20130503123928194
#include "hryky/definition.h"
#include "hryky/swap.h"
#include "hryky/type_traits/add_const_pointer.h"
#include "hryky/type_traits/add_const_reference.h"
#include "hryky/type_traits/add_pointer.h"
#include "hryky/type_traits/add_reference.h"
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
	/// retains a value.
	template <hryky_template_param>
	class Value;

} // namespace retention
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains a value.
 */
template <hryky_template_param>
class hryky::retention::Value
{
public :

	typedef Value<hryky_template_arg>                       this_type;
	typedef ValueT                                          value_type;
	typedef typename AddPointer<value_type>::type           pointer;
	typedef typename AddConstPointer<value_type>::type      const_pointer;
	typedef typename AddReference<value_type>::type         reference;
	typedef typename AddConstReference<value_type>::type    const_reference;
	typedef const_reference                                 initializer_type;

	/// default constructor.
	Value();

	/// constructor with a value.
	Value(initializer_type value);

	/// constructor with a rvalue.
	Value(ValueT && value);

	/// copy constructor.
	Value(this_type const &);

	/// move constructor.
	Value(this_type &&);

	/// destructor.
	~Value();

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

	/// retrieves the pointer to the immutable value.
	const_pointer get() const;

	/// retrieves the pointer to the mutable value.
	pointer get();

protected :

private :

	ValueT value_;

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
hryky::retention::Value<hryky_template_arg>::Value()
	: value_()
{
}
/**
  @brief constructor with a value.
 */
template <hryky_template_param>
hryky::retention::Value<hryky_template_arg>::Value(initializer_type value)
	: value_(value)
{
}
/**
  @brief constructor with a rvalue.
 */
template <hryky_template_param>
hryky::retention::Value<hryky_template_arg>::Value(ValueT && value)
	: value_(::std::move(value))
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::retention::Value<hryky_template_arg>::Value(this_type const & rhs)
	: hryky_copy_member(value)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::retention::Value<hryky_template_arg>::Value(this_type && rhs)
	: hryky_move_member(value)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::retention::Value<hryky_template_arg>::~Value()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::retention::Value<hryky_template_arg>::clear()
{
	hryky::clear(this->value_);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::retention::Value<hryky_template_arg>::write_to(
	StreamT & out) const
{
	out << this->value_;
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::retention::Value<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(value);
}
/**
  @brief retrieves the value as immutable reference.
 */
template <hryky_template_param>
typename hryky::retention::Value<hryky_template_arg>::const_pointer
hryky::retention::Value<hryky_template_arg>::get() const
{
	return &this->value_;
}
/**
  @brief retrieves the value as mutable reference.
 */
template <hryky_template_param>
typename hryky::retention::Value<hryky_template_arg>::pointer
hryky::retention::Value<hryky_template_arg>::get()
{
	return &this->value_;
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
// revokes macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // RETENTION_VALUE_H_20130503123928194
// end of file
