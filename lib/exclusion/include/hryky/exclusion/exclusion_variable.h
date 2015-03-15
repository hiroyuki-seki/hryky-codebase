/**
  @file         exclusion_variable.h
  @brief        synchronizes a writing access to an object.
  @author       HRYKY
  @version      $Id: exclusion_variable.h 374 2014-07-27 11:54:24Z hryky.private@gmail.com $
  @addtogroup   concurrent_programming
  @{
 */
#ifndef EXCLUSION_VARIABLE_H_20120917104035111
#define EXCLUSION_VARIABLE_H_20120917104035111
#include "hryky/common.h"
#include "hryky/definition.h"
#include "hryky/exclusion/exclusion_lock.h"
#include "hryky/exclusion/exclusion_mutex.h"
#include "hryky/type_traits/as_parameter.h"
#include "hryky/with_stream_out.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT, typename LockableT
#define hryky_template_arg \
	ValueT, LockableT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace exclusion
{
	/// synchronizes a writing access to an object
	template <
		typename ValueT,
		typename LockableT = exclusion::Mutex
	>
	class Variable;
	
} // namespace exclusion
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
template <hryky_template_param>
class hryky::exclusion::Variable :
	public WithStreamOut<Variable<hryky_template_arg> >
{
public :

	typedef ValueT              value_type;
	typedef LockableT           lockable_type;
	typedef Lock<lockable_type> lock_type;
	
	typedef typename AsParameter<value_type>::type parameter_type;

	/// self
	typedef Variable<hryky_template_arg> this_type;

	/// default constructor.
	Variable();

	/**
	  @brief    constructor with the initial value.
	  @param    value is the left-hand side of the assignment.
	 */
	Variable(parameter_type value);

	/// destructor
	~Variable();

	/**
	  @brief    copy constructor.
	  @param    rhs is the left-hand side of the assignment.
	 */
	explicit Variable(this_type const & rhs);

	/// move constructor.
	Variable(this_type && rhs);

	/**
	  @brief    assignment operator.
	  @param    rhs is the left-hand side of the assignment.
	  @return   the reference of this instance.
	 */
	this_type & operator=(this_type const &rhs);

	/**
	  @brief    assigns a new value.
	  @param    rhs is the left-hand side of the assignment.
	  @return   the value of this instance.
	 */
	value_type operator=(parameter_type rhs);

	/**
	  @brief casts to the type of the value.
	 */
	operator value_type() const;

	/**
	  appends the value to the this instance.
	  @return A new value after this operation is applied.
	 */
	value_type operator+=(parameter_type rhs);

	/**
	  pre-increments the value.
	  @return A new value after this operation is applied.
	 */
	value_type operator++();

	/**
	  post-increments the value.
	  @return The previous value before thie operation is applied.
	 */
	value_type operator++(int);

	/**
	  subtracts the value from the this instance.
	  @return A new value after this operation is applied.
	 */
	value_type operator-=(parameter_type rhs);

	/**
	  pre-decrements the value.
	  @return A new value after this operation is applied.
	 */
	value_type operator--();

	/**
	  post-decrements the value.
	  @return The previous value before thie operation is applied.
	 */
	value_type operator--(int);

	/**
	  multiplies the value to the this instance.
	  @return A new value after this operation is applied.
	 */
	value_type operator*=(parameter_type rhs);

	/**
	  divides the this instance by the value.
	  @return A new value after this operation is applied.
	 */
	value_type operator/=(parameter_type rhs);

	/**
	  assigns the remainder divided by the value to this instance.
	  @return A new value after this operation is applied.
	 */
	value_type operator%=(parameter_type rhs);

	/**
	  operates logical AND with the parameter.
	  @return A new value after this operation is applied.
	 */
	value_type operator&=(parameter_type rhs);

	/**
	  operates logical OR with the parameter.
	  @return A new value after this operation is applied.
	 */
	value_type operator|=(parameter_type rhs);

	/**
	  operates logical XOR with the parameter.
	  @return A new value after this operation is applied.
	 */
	value_type operator^=(parameter_type rhs);

	/// releases the internal resources.
	void clear();

	/**
	  @brief    assigns a new value if the internal value is same
	            with a given value.
	  @param    old_value is compared whether the internal value is same with.
	  @param    new_value is assigned if the internal value is same
	            with @a old_value.
	  @return   the value before assgined.
	 */
	value_type compare_and_swap(
		parameter_type old_value,
		parameter_type new_value);

	/**
	  @brief    updates the value and retrieves the next value.
	  @param    functor is called with the current value.
	  @return   the value after the functor was called.

	  @a functor must have a function typed as the following signature.
	  
	    value_type operator()(parameter_type);
	  
	   The return value of the functor is assigned to the value of this
	  instance.
	 */
	template < typename FunctorT >
	value_type update(FunctorT const & functor);

	/**
	  @brief    updates the value and retrieves the previous value.
	  @param    functor is called with the current value.
	  @return   the previous value before the functor is called.

	  @a functor must have a function typed as the following signature.
	  
	    value_type operator()(parameter_type);
	  
	   The return value of the functor is assigned to the value of this
	  instance.
	 */
	template < typename FunctorT >
	value_type fetch(FunctorT const & functor);

	/**
	  @brief    executes an arbitrary functor under the exclusion control.
	  @param    functor is called with the current value.
	  @return   the value after the functor was called.

	  @a functor must have a function typed as the following signature.
	  
	    void operator()(parameter_type);
	 */
	template <typename FunctorT>
	value_type exclude(FunctorT const & functor);

	/**
	  @brief    executes an arbitrary functor under the waitable
                exclusion control.
	  @param    functor is called with the current value.
	  @return   the value after the functor was called.

	  @a functor must have a function typed as the following signature.
	  
	    void operator()(value_type const, lock_type &);
	 */
	template < typename FunctorT >
	value_type waitable_exclude(FunctorT const & functor);

	/**
	  adds the argument to the value of this instance.
	  @return The previous value before this operation is applied.
	 */
	value_type fetch_add(parameter_type rhs);

	/**
	  subtracts the argument from the value of this instance.
	  @return The previous value before this operation is applied.
	 */
	value_type fetch_sub(parameter_type src);

	/**
	  multiplies the argument to the value of this instance.
	  @return The previous value before this operation is applied.
	 */
	value_type fetch_mul(parameter_type rhs);

	/**
	  divides the value of this instance with the argument .
	  @return The previous value before this operation is applied.
	 */
	value_type fetch_div(parameter_type src);

	/**
	  assigns the residue of this instance with the argument.
	  @return The previous value before this operation is applied.
	 */
	value_type fetch_mod(parameter_type src);

	/**
	  operates logical and between the argument and the value of
	  this instance.
	  @return The previous value before this operation is applied.
	 */
	value_type fetch_and(parameter_type src);

	/**
	  operates logical OR between the argument and the value of
	  this instance.
	  @return The previous value before this operation is applied.
	 */
	value_type fetch_or(parameter_type src);

	/**
	  operates logical XOR between the argument and the value of
	  this instance.
	  @return The previous value before this operation is applied.
	 */
	value_type fetch_xor(parameter_type src);

	/// retrieves the current internal value.
	value_type load() const;

	/**
	  replaces the current value with the argument.
	  @return The previous value before this operation is applied.
	 */
	value_type exchange(parameter_type src);

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

	mutable lockable_type   lockable_;
	value_type              value_;

private :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace exclusion
{
} // namespace exclusion
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::exclusion::Variable<hryky_template_arg>::Variable()
	: lockable_()
	  , value_()
{
}
/**
  @brief constructor with the initial value.
 */
template <hryky_template_param>
hryky::exclusion::Variable<hryky_template_arg>::Variable(
	parameter_type value)
	: lockable_()
	  , value_(value)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::exclusion::Variable<hryky_template_arg>::Variable(
	this_type const & rhs)
	: lockable_()
	  , hryky_copy_member(value)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::exclusion::Variable<hryky_template_arg>::Variable(
	this_type && rhs)
	: lockable_()
	  , hryky_move_member(value)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::exclusion::Variable<hryky_template_arg>::~Variable()
{
	return;
}
/**
  @brief assignment operator.
 */
template <hryky_template_param>
hryky::exclusion::Variable<hryky_template_arg> & 
hryky::exclusion::Variable<hryky_template_arg>::operator=(
	this_type const & rhs)
{
	if (this == &rhs) {
		return *this;
	}
	
	lock_type const lock(this->lockable_);

	this->value_ = rhs.value_;

	return *this;
}
/**
  @brief assigns a new value.
 */
template <hryky_template_param>
ValueT
hryky::exclusion::Variable<hryky_template_arg>::operator=(
	parameter_type rhs)
{
	lock_type const lock(this->lockable_);

	this->value_ = rhs;

	return this->value_;
}
/**
  @brief casts to the type of the value.
 */
template <hryky_template_param>
hryky::exclusion::Variable<hryky_template_arg>::operator ValueT() const
{
	return this->value_;
}
/**
  @brief appends the value to the this instance.
 */
template <hryky_template_param>
ValueT
hryky::exclusion::Variable<hryky_template_arg>::operator+=(
	parameter_type rhs)
{
	lock_type const lock(this->lockable_);

	this->value_ += rhs;
	
	return this->value_;
}
/**
  @brief pre-increments the value.
 */
template <hryky_template_param>
ValueT
hryky::exclusion::Variable<hryky_template_arg>::operator++()
{
	lock_type const lock(this->lockable_);

	++this->value_;

	return this->value_;
}
/**
  @brief post-increments the value.
 */
template <hryky_template_param>
ValueT
hryky::exclusion::Variable<hryky_template_arg>::operator++(int)
{
	lock_type const lock(this->lockable_);
	
	value_type const value = this->value_;
	++this->value_;
	
	return value;
}
/**
  @brief subtracts the value from the this instance.
 */
template <hryky_template_param>
ValueT
hryky::exclusion::Variable<hryky_template_arg>::operator-=(
	parameter_type rhs)
{
	lock_type const lock(this->lockable_);

	this->value_ -= rhs;
	
	return this->value_;
}
/**
  @brief pre-decrements the value.
 */
template <hryky_template_param>
ValueT
hryky::exclusion::Variable<hryky_template_arg>::operator--()
{
	lock_type const lock(this->lockable_);

	--this->value_;

	return this->value_;
}
/**
  @brief post-decrements the value.
 */
template <hryky_template_param>
ValueT
hryky::exclusion::Variable<hryky_template_arg>::operator--(int)
{
	lock_type const lock(this->lockable_);
	
	value_type const value = this->value_;
	--this->value_;
	
	return value;
}
/**
  @brief multiplies the value to the this instance.
 */
template <hryky_template_param>
ValueT
hryky::exclusion::Variable<hryky_template_arg>::operator*=(
	parameter_type rhs)
{
	lock_type const lock(this->lockable_);

	this->value_ *= rhs;
	
	return this->value_;
}
/**
  @brief divides the this instance by the value.
 */
template <hryky_template_param>
ValueT
hryky::exclusion::Variable<hryky_template_arg>::operator/=(
	parameter_type rhs)
{
	lock_type const lock(this->lockable_);

	this->value_ /= rhs;
	
	return this->value_;
}
/**
  @brief assigns the remainder divided by the value to this instance.
 */
template <hryky_template_param>
ValueT
hryky::exclusion::Variable<hryky_template_arg>::operator%=(
	parameter_type rhs)
{
	lock_type const lock(this->lockable_);

	this->value_ %= rhs;
	
	return this->value_;
}
/**
  @brief operates logical AND with the argument.
 */
template <hryky_template_param>
ValueT
hryky::exclusion::Variable<hryky_template_arg>::operator&=(
	parameter_type rhs)
{
	lock_type const lock(this->lockable_);

	this->value_ &= rhs;
	
	return this->value_;
}
/**
  @brief operates logical OR with the argument.
 */
template <hryky_template_param>
ValueT
hryky::exclusion::Variable<hryky_template_arg>::operator|=(
	parameter_type rhs)
{
	lock_type const lock(this->lockable_);

	this->value_ |= rhs;
	
	return this->value_;
}
/**
  @brief operates logical XOR with the argument.
 */
template <hryky_template_param>
ValueT
hryky::exclusion::Variable<hryky_template_arg>::operator^=(
	parameter_type rhs)
{
	lock_type const lock(this->lockable_);

	this->value_ ^= rhs;
	
	return this->value_;
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void
hryky::exclusion::Variable<hryky_template_arg>::clear()
{
	lock_type const lock(this->lockable_);
	
	hryky::clear(this->value_);
}
/**
  @brief assigns a new value if the internal value is same with
    a given value.
 */
template <hryky_template_param>
ValueT
hryky::exclusion::Variable<hryky_template_arg>::compare_and_swap(
	parameter_type old_value,
	parameter_type new_value)
{
	if (this->value_ != old_value) {
		return this->value_;
	}
	
	lock_type const lock(this->lockable_);

	if (this->value_ != old_value) {
		return this->value_;
	}

	this->value_ = new_value;

	return old_value;
}
/**
  @brief updates the value by an arbitrary functor under the
    exclusion control.
 */
template <hryky_template_param>
template < typename FunctorT >
ValueT
hryky::exclusion::Variable<hryky_template_arg>::update(
	FunctorT const & functor)
{
	lock_type const lock(this->lockable_);

	this->value_ = functor(this->value_);
	
	return this->value_;
}
/**
  @brief updates the value and retrieves the previous value.
 */
template <hryky_template_param>
template <typename FunctorT>
ValueT
hryky::exclusion::Variable<hryky_template_arg>::fetch(
	FunctorT const & functor)
{
	lock_type const lock(this->lockable_);

	value_type const value = this->value_;
	this->value_ = functor(this->value_);
	
	return value;
}
/**
  @brief executes an arbitrary functor under the exclusion control.
 */
template <hryky_template_param>
template <typename FunctorT>
ValueT
hryky::exclusion::Variable<hryky_template_arg>::exclude(
	FunctorT const & functor)
{
	lock_type const lock(this->lockable_);

	functor(this->value_);
	
	return this->value_;
}
/**
  @brief executes an arbitrary functor under the waitable exclusion
    control.
 */
template <hryky_template_param>
template < typename FunctorT >
ValueT
hryky::exclusion::Variable<hryky_template_arg>::waitable_exclude(
	FunctorT const & functor)
{
	lock_type lock(this->lockable_);

	functor(this->value_, lock);
	
	return this->value_;
}
/**
  @brief adds the argument to the value of this instance.
 */
template <hryky_template_param>
ValueT
hryky::exclusion::Variable<hryky_template_arg>::fetch_add(
	parameter_type src)
{
	lock_type const lock(this->lockable_);
	
	value_type const value = this->value_;
	this->value_ += src;
	
	return value;
}
/**
  @brief subtracts the argument from the value of this instance.
 */
template <hryky_template_param>
ValueT
hryky::exclusion::Variable<hryky_template_arg>::fetch_sub(
	parameter_type src)
{
	lock_type const lock(this->lockable_);
	
	value_type const value = this->value_;
	this->value_ -= src;
	
	return value;
}
/**
  @brief multiplies the argument to the value of this instance.
 */
template <hryky_template_param>
ValueT
hryky::exclusion::Variable<hryky_template_arg>::fetch_mul(
	parameter_type src)
{
	lock_type const lock(this->lockable_);
	
	value_type const value = this->value_;
	this->value_ *= src;
	
	return value;
}
/**
  @brief divides the value of this instance with the argument.
 */
template <hryky_template_param>
ValueT
hryky::exclusion::Variable<hryky_template_arg>::fetch_div(
	parameter_type src)
{
	lock_type const lock(this->lockable_);
	
	value_type const value = this->value_;
	this->value_ /= src;
	
	return value;
}
/**
  @brief assigns the residue of the value of this instance with
                the argument.
 */
template <hryky_template_param>
ValueT
hryky::exclusion::Variable<hryky_template_arg>::fetch_mod(
	parameter_type src)
{
	lock_type const lock(this->lockable_);
	
	value_type const value = this->value_;
	this->value_ %= src;
	
	return value;
}
/**
  @brief operates logical OR between the argument and the value of this instance.
 */
template <hryky_template_param>
ValueT
hryky::exclusion::Variable<hryky_template_arg>::fetch_or(
	parameter_type src)
{
	lock_type const lock(this->lockable_);
	
	value_type const value = this->value_;
	this->value_ |= src;
	
	return value;
}
/**
  @brief operates logical XOR between the argument and the value of this instance.
 */
template <hryky_template_param>
ValueT
hryky::exclusion::Variable<hryky_template_arg>::fetch_xor(
	parameter_type src)
{
	lock_type const lock(this->lockable_);
	
	value_type const value = this->value_;
	this->value_ ^= src;
	
	return value;
}
/**
  @brief retrieves the current internal value.
 */
template <hryky_template_param>
ValueT
hryky::exclusion::Variable<hryky_template_arg>::load() const
{
	lock_type const lock(this->lockable_);

	value_type const value = this->value_;
	
	return value;
}
/**
  @brief replaces the current value with the argument.
 */
template <hryky_template_param>
ValueT
hryky::exclusion::Variable<hryky_template_arg>::exchange(
	parameter_type src)
{
	lock_type const lock(this->lockable_);

	value_type const value = this->value_;
	this->value_ = src;
	
	return value;
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::exclusion::Variable<hryky_template_arg>::write_to(
	StreamT & out) const
{
	out << this->value_;
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
namespace exclusion
{

} // namespace exclusion
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // EXCLUSION_VARIABLE_H_20120917104035111
/// @}
// end of file
