/**
  @file         exclusion_counter.h
  @brief        joinable counter.
  @author       HRYKY
  @version      $Id: exclusion_counter.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
  @addtogroup   concurrent_programming
  @{
 */
#ifndef EXCLUSION_COUNTER_H_20120109144007277
#define EXCLUSION_COUNTER_H_20120109144007277
#include "hryky/exclusion/exclusion_common.h"
#include "hryky/exclusion/exclusion_cond.h"
#include "hryky/exclusion/exclusion_mutex.h"
#include "hryky/exclusion/exclusion_variable.h"
#include "hryky/json/json_writer.h"
#include "hryky/log/log_definition.h"
#include "hryky/without_copy.h"
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
	/// joinable counter
	template <
		typename ValueT = size_t,
		typename LockableT = hryky::exclusion::Mutex
	>
	class Counter;

}
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief joinable counter.

   When the internal value gets to zero by restore(), the waiting threads are
  awoken.
 */
template <hryky_template_param>
class hryky::exclusion::Counter :
	public WithStreamOut<Counter<hryky_template_arg> >,
	private WithoutCopy
{
public :

	struct AutoRestore :
		private WithoutCopy
	{
		typedef AutoRestore this_type;
		typedef Counter<hryky_template_arg> counter_type;
		
		AutoRestore(
			counter_type & counter, ValueT const size = 1u)
			: counter_(counter)
			  , size_(size)
			  , disable_()
		{
		}

		~AutoRestore()
		{
			if (!this->disable_) {
				this->counter_.restore(this->size_);
			}
		}

		void disable()
		{
			this->disable_ = true;
		}

	private :
		hryky_delete_this_copy_constructor(AutoRestore);
		hryky_delete_this_copy_assign_op(AutoRestore);
		
		counter_type &  counter_;
		ValueT          size_;
		bool            disable_;
	};

	struct ScopedAcquire :
		private WithoutCopy
	{
		typedef Counter<hryky_template_arg> counter_type;
		
		ScopedAcquire(
			counter_type & counter,
			ValueT const size = 1u)
			: restore_(counter, size)
		{
			counter.acquire(size);
		}

		~ScopedAcquire()
		{
		}

		void disable()
		{
			this->restore_.disable();
		}

	private :
		AutoRestore     restore_;
	};

	
	typedef Counter<hryky_template_arg>             this_type;
	typedef LockableT                               lockable_type;
	typedef ValueT                                  value_type;
	typedef typename AsParameter<value_type>::type  parameter_type;

	/// default constructor.
	Counter();

	/// instantiates with an initial value.
	explicit Counter(parameter_type value);

	/// destructor.
	~Counter();

	/// acquires one resource.
	typename value_type operator++();

	/// restores one resource.
	typename value_type operator--();

	/**
	  @brief requires multiple resources.
	  @return The incremented value after this operation.
	 */
	value_type acquire(parameter_type size);

	/**
	  @brief restores multiple resources.
	  @return The decremented value after this operation.
	 */
	value_type restore(parameter_type size);

	/**
	  @brief requires a resource.
	  @return The incremented value after this operation.
	 */
	value_type acquire();

	/**
	  @brief restores a resource.
	  @return The decremented value after this operation.
	 */
	value_type restore();

	/**
	  @brief    waits until the counter reach zero.
	  @retval   true if this counter reached zero in the specified duration.
	  @retval   false if this counter didn't reach zero in the specified
	            duration.
	 */
	template <typename DurationT>
	bool join(DurationT const & duration);

	/**
	  @brief    waits untile the counter reach zero.

	  This function may block the current context forever.
	 */
	void join();

	/// outputs the information formatted as string.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// retrieves the raw value of this counter.
	value_type value() const;

protected :

private :

	typedef Variable<value_type, lockable_type> variable_type;
	typedef typename variable_type::lock_type   lock_type;

	hryky_delete_this_copy_constructor(Counter);
	hryky_delete_this_copy_assign_op(Counter);

	cond_type       cond_;
	variable_type   value_;

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::exclusion::Counter<hryky_template_arg>::Counter()
	: cond_()
	  , value_()
{
}
/**
  @brief instantiates with an initial value.
 */
template <hryky_template_param>
hryky::exclusion::Counter<hryky_template_arg>::Counter(parameter_type value)
	: cond_()
	  , value_(value)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::exclusion::Counter<hryky_template_arg>::~Counter()
{
}
/**
  @brief acquires one resource.
 */
template <hryky_template_param>
typename hryky::exclusion::Counter<hryky_template_arg>::value_type 
hryky::exclusion::Counter<hryky_template_arg>::operator++()
{
	return this->acquire(1u);
}
/**
  @brief restores one resource.
 */
template <hryky_template_param>
typename hryky::exclusion::Counter<hryky_template_arg>::value_type 
hryky::exclusion::Counter<hryky_template_arg>::operator--()
{
	return this->restore(1u);
}
/**
  @brief requires multiple resources.
 */
template <hryky_template_param>
typename hryky::exclusion::Counter<hryky_template_arg>::value_type
hryky::exclusion::Counter<hryky_template_arg>::acquire(
	parameter_type size)
{
	return this->value_ += size;
}
/**
  @brief restores multiple resources.
 */
template <hryky_template_param>
typename hryky::exclusion::Counter<hryky_template_arg>::value_type
hryky::exclusion::Counter<hryky_template_arg>::restore(
	parameter_type size)
{
	value_type result;
	
	if (this->value_ < size) {
		hryky_log_warning(
			"Too many restorations are required."
			<< (json::writer()
				<< *this
				<< stream::denote("restoration") << size));
		result = (this->value_ = value_type());
	}
	else {
		result = (this->value_ -= size);
	}

	if (value_type() == result) {
		this->cond_.notify();
	}

	return result;
}
/**
  @brief restores a resource.
 */
template <hryky_template_param>
typename hryky::exclusion::Counter<hryky_template_arg>::value_type
hryky::exclusion::Counter<hryky_template_arg>::restore()
{
	return this->restore(value_type(1));
}
/**
  @brief requires a resource.
 */
template <hryky_template_param>
typename hryky::exclusion::Counter<hryky_template_arg>::value_type
hryky::exclusion::Counter<hryky_template_arg>::acquire()
{
	return this->acquire(value_type(1));
}
/**
  @brief waits while the counter is positive.
 */
template <hryky_template_param>
template <typename DurationT>
bool hryky::exclusion::Counter<hryky_template_arg>::join(
	DurationT const & duration)
{
	this_type & self = *this;
	return value_type() == this->value_.waitable_exclude([&self, &duration](
		value_type const value, lock_type & lock) {
		if (value_type() < value) {
			self.cond_.join(lock, duration);
		}
	});
}
/**
  @brief waits while the counter is positive.
 */
template <hryky_template_param>
void hryky::exclusion::Counter<hryky_template_arg>::join()
{
	this_type & self = *this;
	this->value_.waitable_exclude([&self](
		value_type const value, lock_type & lock) {
		if (value_type() < value) {
			self.cond_.join(lock);
		}
	});
}
/**
  @brief outputs the information formatted as string.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::exclusion::Counter<hryky_template_arg>::write_to(
	StreamT & out) const
{
	out << this->value_;
	return out;
}
/**
  @brief retrieves the raw value of this counter.
 */
template <hryky_template_param>
typename hryky::exclusion::Counter<hryky_template_arg>::value_type
hryky::exclusion::Counter<hryky_template_arg>::value() const
{
	return this->value_;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// global function prototype
//------------------------------------------------------------------------------
namespace hryky
{
namespace exclusion
{

}
}
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // EXCLUSION_COUNTER_H_20120109144007277
/// @}
// end of file
