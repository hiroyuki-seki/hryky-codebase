/**
  @file         atomic_entity.h
  @brief        synchronizes a writing access to an object.
  @author       HRYKY
  @version      $Id: atomic_entity.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
  @addtogroup   concurrent_programming
  @{
 */
#ifndef ATOMIC_ENTITY_H_20130320162746352
#define ATOMIC_ENTITY_H_20130320162746352
#include "hryky/std/std_atomic.h"
#include "hryky/type_traits/as_parameter.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace atomic
{
	/// synchronizes a writing access to an object
	template < typename ValueT >
	class Entity;
	
} // namespace atomic
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief    synchronize a writing access to an object.
  @param    ValueT is the type of the object accessed through this class.

   On the contrast to the conventional behavior of some operators,
  this function returns the value itself, instead for the reference to the
  instance.
 */
template < typename ValueT >
class hryky::atomic::Entity
{
public :

	typedef ValueT value_type;
	typedef typename AsParameter<value_type>::type parameter_type;

	/// self
	typedef Entity<ValueT> this_type;

	/// default constructor.
	Entity();

	/**
	  @brief    constructor with the initial value.
	  @param    value is the left-hand side of the assignment.
	 */
	Entity(parameter_type value);

	/// copy constructor.
	explicit Entity(this_type const & rhs);

	/// destructor
	~Entity();

	/// move constructor.
	Entity(this_type && rhs);

	/**
	  @brief    assigns a new value.
	  @param    rhs is the left-hand side of the assignment.
	  @return   the value of this instance.
	 */
	value_type operator=(parameter_type rhs);

	/**
	  @brief casts to the type of the value.
	 */
	operator ValueT() const;

	/**
	  appends the value to the this instance.
	  @return The value appended the parameter.
	 */
	value_type operator+=(parameter_type rhs);

	/**
	  pre-increments the value.
	  @return The incremented VALUE. NOT the reference to the instance.
	 */
	value_type operator++();

	/**
	  post-increments the value.
	 */
	value_type operator++(int);

	/**
	   subtracts the value from the this instance.
	 */
	value_type operator-=(parameter_type rhs);

	/**
	  pre-decrements the value.
	 */
	value_type operator--();

	/// post-decrements the value.
	value_type operator--(int);

	/**
	  operates logical AND with the argument.
	  @return the value after the operation is applied.
	 */
	value_type operator&=(parameter_type rhs);

	/**
	  operates logical OR with the argument.
	  @return the value after the operation is applied.
	 */
	value_type operator|=(parameter_type rhs);

	/**
	  operates logical XOR with the argument.
	  @return the value after the operation is applied.
	 */
	value_type operator^=(parameter_type rhs);

	/**
	  adds the argument to the value of this instance.
	  @return The previous value before this operation.
	 */
	ValueT fetch_add(parameter_type rhs);

	/**
	  subtracts the argument from the value of this instance.
	  @return The previous value before this operation.
	 */
	ValueT fetch_sub(parameter_type src);

	/**
	  operates logical and between the argument and the value of this instance.
	  @return The previous value before this operation.
	 */
	ValueT fetch_and(parameter_type src);

	/**
	  operates logical OR between the argument and the value of
	  this instance.
	  @return The previous value before this operation.
	 */
	ValueT fetch_or(parameter_type src);

	/**
	  operates logical XOR between the argument and the value of
	  this instance.
	  @return The previous value before this operation.
	 */
	ValueT fetch_xor(parameter_type src);

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

private :

	typedef ::std::atomic<value_type> raw_type;

	/// assignment operator.
	this_type & operator=(this_type const &rhs);

	raw_type raw_;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace atomic
{
} // namespace atomic
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <typename ValueT>
hryky::atomic::Entity<ValueT>::Entity()
	: raw_()
{
}
/**
  @brief constructor with the initial value.
 */
template < typename ValueT >
hryky::atomic::Entity<ValueT>::Entity(
	parameter_type value)
	: raw_(value)
{
}
/**
  @brief destructor.
 */
template < typename ValueT >
hryky::atomic::Entity<ValueT>::~Entity()
{
	return;
}
/**
  @brief copy constructor.
 */
template < typename ValueT >
hryky::atomic::Entity<ValueT>::Entity(
	this_type const & rhs)
	: hryky_copy_member(raw)
{
}
/**
  @brief move constructor.
 */
template <typename ValueT>
hryky::atomic::Entity<ValueT>::Entity(this_type && rhs)
	: hryky_move_member(raw)
{
}
/**
  @brief assigns a new value.
 */
template < typename ValueT >
ValueT hryky::atomic::Entity<ValueT>::operator=(
	parameter_type rhs)
{
	return (this->raw_ = rhs);
}
/**
  @brief casts to the type of the value.
 */
template < typename ValueT >
hryky::atomic::Entity<ValueT>::operator ValueT() const
{
	return this->raw_;
}
/**
  @brief appends the value to the this instance.
 */
template < typename ValueT >
ValueT hryky::atomic::Entity<ValueT>::operator+=(
	parameter_type rhs)
{
	return this->raw_ += rhs;
}
/**
  @brief pre-increments the value.
 */
template < typename ValueT >
ValueT hryky::atomic::Entity<ValueT>::operator++()
{
	return ++this->raw_;
}
/**
  @brief post-increments the value.
 */
template < typename ValueT >
ValueT hryky::atomic::Entity<ValueT>::operator++(int)
{
	return this->raw_++;
}
/**
  @brief subtracts the value from the this instance.
 */
template < typename ValueT >
ValueT hryky::atomic::Entity<ValueT>::operator-=(
	parameter_type rhs)
{
	return this->raw_ -= rhs;
}
/**
  @brief pre-decrements the value.
 */
template < typename ValueT >
ValueT hryky::atomic::Entity<ValueT>::operator--()
{
	return --this->raw_;
}
/**
  @brief post-decrements the value.
 */
template < typename ValueT >
ValueT hryky::atomic::Entity<ValueT>::operator--(int)
{
	return this->raw_--;
}
/**
  @brief operates logical AND with the argument.
 */
template < typename ValueT >
ValueT hryky::atomic::Entity<ValueT>::operator&=(
	parameter_type rhs)
{
	return this->raw_ &= rhs;
}
/**
  @brief operates logical OR with the argument.
 */
template < typename ValueT >
ValueT hryky::atomic::Entity<ValueT>::operator|=(
	parameter_type rhs)
{
	return this->raw_ |= rhs;
}
/**
  @brief operates logical XOR with the argument.
 */
template < typename ValueT >
ValueT hryky::atomic::Entity<ValueT>::operator^=(
	parameter_type rhs)
{
	return this->raw_ ^= rhs;
}
/**
  @brief adds the argument to the value of this instance.
 */
template <typename ValueT>
ValueT hryky::atomic::Entity<ValueT>::fetch_add(
	parameter_type src)
{
	return this->raw_.fetch_add(src);
}
/**
  @brief subtracts the argument from the value of this instance.
 */
template <typename ValueT>
ValueT hryky::atomic::Entity<ValueT>::fetch_sub(
	parameter_type src)
{
	return this->raw_.fetch_sub(src);
}
/**
  @brief operates logical and between the argument and the value of this instance.
 */
template <typename ValueT>
ValueT hryky::atomic::Entity<ValueT>::fetch_and(
	parameter_type src)
{
	return this->raw_.fetch_and(src);
}
/**
  @brief operates logical OR between the argument and the value of this instance.
 */
template <typename ValueT>
ValueT hryky::atomic::Entity<ValueT>::fetch_or(
	parameter_type src)
{
	return this->raw_.fetch_or(src);
}
/**
  @brief operates logical XOR between the argument and the value of this instance.
 */
template <typename ValueT>
ValueT hryky::atomic::Entity<ValueT>::fetch_xor(
	parameter_type src)
{
	return this->raw_.fetch_xor(src);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename ValueT>
template <typename StreamT>
StreamT &
hryky::atomic::Entity<ValueT>::write_to(
	StreamT & out) const
{
	out << this->raw_.load();
	return out;
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
namespace atomic
{

} // namespace atomic
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // ATOMIC_ENTITY_H_20130320162746352
/// @}
// end of file
