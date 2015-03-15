/**
  @file         exclusion_boolean.h
  @brief        synchronizes the change of a boolean value.
  @author       HRYKY
  @version      $Id: exclusion_boolean.h 370 2014-07-21 16:00:02Z hryky.private@gmail.com $
  @addtogroup   exclusion_control
  @{
 */
#ifndef EXCLUSION_BOOLEAN_H_20111129173852401
#define EXCLUSION_BOOLEAN_H_20111129173852401
#include "hryky/exclusion/exclusion_cond.h"
#include "hryky/exclusion/exclusion_variable.h"
#include "hryky/without_copy.h"
#include "hryky/with_stream_out.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename LockableT
#define hryky_template_arg \
	LockableT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace exclusion
{
	/// synchronizes the change of a boolean value
	template <hryky_template_param>
	class Boolean;
}
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief synchronizes the change of a boolean value.
 */
template <typename LockableT = hryky::exclusion::Mutex>
class hryky::exclusion::Boolean :
	public WithStreamOut<Boolean<hryky_template_arg> >,
	private WithoutCopy
{
public :

	typedef Boolean<hryky_template_arg> this_type;
	typedef bool                        value_type;

	/// default constructor
	Boolean();

	/// constructor with a boolean value
	explicit Boolean(value_type const value);

	/// destructor
	~Boolean();

	/// assigns a new boolean value.
	this_type & operator=(value_type const rhs);

	/// releases the internal resources.
	void clear();

	/**
	  @brief    changes the boolean value to true.
	  @return   The previous value before this operation.

	  The all units waiting that this value becomes false are notified.
	 */
	value_type enable();

	/**
	  @brief    changes the boolean value to false.
	  @return   The previous value before this operation.

	  The all units waiting that this value becomes true are notified.
	 */
	value_type disable();

	/**
	  @brief    suspends for an indefinite period until the boolean value
	            comes to true.
	  @attention
	  - This function might suspend the caller context for long periods.
	 */
	void wait_true();

	/**
	  @brief    suspends until the boolean value comes to true or the
	            duration elapses.
	  @param    duration is a period of time which the suspension will
	            expire.
	  @retval   true if the wait completed successfully.
	  @retval   false if the @a duration elapsed.
	  @attention
	  - This function might suspend the caller context for long periods.
	 */
	template <typename DurationT>
	bool wait_true(DurationT const & duration);

	/**
	  @brief    suspends for an indefinite period until the boolean value
	            comes to false.
	  @attention
	  - This function might suspend the caller context for long periods.
	 */
	void wait_false();

	/**
	  @brief    suspends until the boolean value comes to false or the
	            duration elapses.
	  @param    duration is a period of time which the suspension
	            will expire.
	  @retval   true if the wait completed successfully.
	  @retval   false if the @a duration elapsed.
	  @attention
	  - This function might suspend the caller context for long periods.
	 */
	template <typename DurationT>
	bool wait_false(DurationT const & duration);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

private :
	typedef Cond                                cond_type;
	typedef Variable<value_type, LockableT>     variable_type;
	typedef typename variable_type::lock_type   lock_type;

	hryky_delete_this_copy_constructor(Boolean);
	hryky_delete_this_copy_assign_op(Boolean);

	cond_type       cond_;
	variable_type   value_;
};
//------------------------------------------------------------------------------
// inline functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief constructor.
 */
template <hryky_template_param>
hryky::exclusion::Boolean<hryky_template_arg>::Boolean()
	: cond_()
	  , value_()
{
}
/**
  @brief initializes with a boolean value.
 */
template <hryky_template_param>
hryky::exclusion::Boolean<hryky_template_arg>::Boolean(
	value_type const value)
	: cond_()
	  , value_(value)
{
}
/**
  @brief destrunctor.
 */
template <hryky_template_param>
hryky::exclusion::Boolean<hryky_template_arg>::~Boolean()
{
}
/**
  @brief assigns a new boolean value.
 */
template <hryky_template_param>
hryky::exclusion::Boolean<hryky_template_arg> & 
hryky::exclusion::Boolean<hryky_template_arg>::operator=(
	value_type const rhs)
{
	if (rhs) {
		this->enable();
	}
	else {
		this->disable();
	}
	
	return *this;
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::exclusion::Boolean<hryky_template_arg>::clear()
{
	hryky::clear(this->value_);
	hryky::clear(this->cond_);
}
/**
  @brief changes the boolean value to true.
 */
template <hryky_template_param>
bool hryky::exclusion::Boolean<hryky_template_arg>::enable()
{
	if (this->value_) {
		return true;
	}

	value_type const prev = this->value_.exchange(true);

	if (!prev) {
		this->cond_.notify();
	}

	return prev;
}
/**
  @brief changes the boolean value to false.
 */
template <hryky_template_param>
bool hryky::exclusion::Boolean<hryky_template_arg>::disable()
{
	if (!this->value_) {
		return false;
	}

	value_type const prev = this->value_.exchange(false);

	if (prev) {
		this->cond_.notify();
	}

	return prev;
}
/**
  @brief suspends until for an indefinite period the boolean
    value comes to true.
 */
template <hryky_template_param>
void hryky::exclusion::Boolean<hryky_template_arg>::wait_true()
{
	if (this->value_) {
		return;
	}

	this->value_.waitable_exclude([this](
		value_type const value, lock_type & lock) {
		if (!value) {
			this->cond_.join(lock);
		}
	});
}
/**
  @brief suspends until the boolean value comes to true
    or the duration elapses.
 */
template <hryky_template_param>
template <typename DurationT>
bool hryky::exclusion::Boolean<hryky_template_arg>::wait_true(
	DurationT const & duration)
{
	if (this->value_) {
		return true;
	}

	return true == this->value_.waitable_exclude([this, &duration](
		value_type const value, lock_type & lock) {
		if (!value) {
			this->cond_.join(lock, duration);
		}
	});
}
/**
  @brief suspends for an indefinite period until the boolean
    value comes to false.
 */
template <hryky_template_param>
void hryky::exclusion::Boolean<hryky_template_arg>::wait_false()
{
	if (!this->value_) {
		return;
	}

	this->value_.waitable_exclude([this](
		value_type const value, lock_type & lock) {
		if (value) {
			this->cond_.join(lock);
		}
	});
}
/**
  @brief suspends until the boolean value comes to false
    or the duration elapses.
 */
template <hryky_template_param>
template <typename DurationT>
bool hryky::exclusion::Boolean<hryky_template_arg>::wait_false(
	DurationT const & duration)
{
	if (!this->value_) {
		return true;
	}
	
	return false == this->value_.waitable_exclude([this, &duration](
		value_type const value, lock_type & lock) {
		if (value) {
			this->cond_.join(lock, duration);
		}
	});
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::exclusion::Boolean<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(value);
	return out;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // EXCLUSION_BOOLEAN_H_20111129173852401
/// @}
// end of file
