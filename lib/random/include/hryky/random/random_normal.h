/**
  @file         random_normal.h
  @brief        creates a pseudo-random number according to the normal distribution.
  @author       HRYKY
  @version      $Id: random_normal.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef RANDOM_NORMAL_H_20120308224056611
#define RANDOM_NORMAL_H_20120308224056611
#include "hryky/integer/max_of.h"
#include "hryky/integer/min_of.h"
#include "hryky/random/random_common.h"
#include "hryky/type_traits/as_parameter.h"
#include "hryky/with_stream_out.h"
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
namespace random
{
	/// creates a pseudo-random number according to the normal distribution.
	template <hryky_template_param>
	class Normal;

} // namespace random
} // namespace hryky

//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief creates a pseudo-random number according to the normal distribution.
 */
template <hryky_template_param>
class hryky::random::Normal :
	public WithStreamOut<Normal<hryky_template_arg> >,
	private WithoutCopy
{
public :
	typedef Normal<hryky_template_arg>          this_type;
	typedef ValueT                              value_type;
	typedef typename AsParameter<ValueT>::type  value_param_type;

	/// constructor.
	Normal(
		generator_type & generator,
		value_type const mean,
		value_type const deviation,
		value_type const min,
		value_type const max);

	/// constructor with the minimum settings.
	Normal(
		generator_type & generator, value_type deviation);

	/// retrieves a random number based on the normal distribution.
	value_type operator()();

	/**
	  @brief outputs the information.
	 */
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;
	
	/// assigns a new mean value.
	this_type & mean(value_param_type src);

	/// assigns a new maximum value.
	this_type & max(value_param_type src);

	/// assigns a new minimum value.
	this_type & min(value_param_type src);

	/// retrieves the deviation.
	value_param_type deviation() const;

	/// retrieves the mean value.
	value_param_type mean() const;

	/// retrieves the maximum value.
	value_param_type max() const;

	/// retrieves the minimum value.
	value_param_type min() const;

protected :

private :

	/// type of distribution
	typedef ::std::normal_distribution<> distribution_type;

	hryky_delete_default_constructor(Normal);
	hryky_delete_this_copy_constructor(Normal);
	hryky_delete_this_copy_assign_op(Normal);

	generator_type &        generator_;
	distribution_type       distribution_;
	value_type              deviation_;
	value_type              mean_;
	value_type              min_;
	value_type              max_;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace random
{
} // namespace random
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief constructor.
 */
template <hryky_template_param>
hryky::random::Normal<hryky_template_arg>::Normal(
	generator_type & generator,
	value_type const deviation,
	value_type const mean,
	value_type const min,
	value_type const max)
	: generator_(generator)
	  , distribution_()
	  , deviation_(deviation)
	  , mean_(mean)
	  , min_(min)
	  , max_(max)
{
}
/**
  @brief constructor with the minimum settings.
 */
template <hryky_template_param>
hryky::random::Normal<hryky_template_arg>::Normal(
	generator_type & generator, value_type deviation)
	: generator_(generator)
	  , distribution_()
	  , deviation_(deviation)
	  , mean_(
		  (MaxOf<hryky_template_arg>::value -
		   MinOf<hryky_template_arg>::value) >> 1)
	  , min_(MinOf<hryky_template_arg>::value)
	  , max_(MaxOf<hryky_template_arg>::value)
{
	return;
}
/**
  @brief retrieves a random number based on the normal distribution.
 */
template <hryky_template_param>
ValueT
hryky::random::Normal<hryky_template_arg>::operator()()
{
	return static_cast<hryky_template_arg>(
		::std::min<int64_t>(
			static_cast<int64_t>(this->max_),
			::std::max<int64_t>(
				static_cast<int64_t>(this->min_),
				static_cast<int64_t>(
					this->mean_
					+ (this->distribution_(this->generator_)
					   * this->deviation_)))));
}
/**
  @brief outputs the information.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::random::Normal<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(deviation);
	hryky_write_member(mean);
	hryky_write_member(min);
	hryky_write_member(max);

	return out;
}
/**
  @brief assigns a new mean value.
 */
template <hryky_template_param>
hryky::random::Normal<hryky_template_arg> & 
hryky::random::Normal<hryky_template_arg>::mean(
	value_param_type src)
{
	this->mean_ = src;
	return *this;
}
/**
  @brief assigns a maximum value.
 */
template <hryky_template_param>
hryky::random::Normal<hryky_template_arg> & 
hryky::random::Normal<hryky_template_arg>::max(
	value_param_type src)
{
	this->max_ = src;
	return *this;
}
/**
  @brief assigns a minimum value.
 */
template <hryky_template_param>
hryky::random::Normal<hryky_template_arg> & 
hryky::random::Normal<hryky_template_arg>::min(
	value_param_type src)
{
	this->min_ = src;
	return *this;
}
/**
  @brief retrieves the deviation.
 */
template <hryky_template_param>
typename hryky::random::Normal<
	hryky_template_arg>::value_param_type 
hryky::random::Normal<hryky_template_arg>::deviation() const
{
	return this->deviation_;
}
/**
  @brief retrieves the mean value.
 */
template <hryky_template_param>
typename hryky::random::Normal<
	hryky_template_arg>::value_param_type 
hryky::random::Normal<hryky_template_arg>::mean() const
{
	return this->mean_;
}
/**
  @brief retrieves the maximum value.
 */
template <hryky_template_param>
typename hryky::random::Normal<
	hryky_template_arg>::value_param_type 
hryky::random::Normal<hryky_template_arg>::max() const
{
	return this->max_;
}
/**
  @brief retrieves the minimum value.
 */
template <hryky_template_param>
typename hryky::random::Normal<
	hryky_template_arg>::value_param_type 
hryky::random::Normal<hryky_template_arg>::min() const
{
	return this->min_;
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
namespace random
{
} // namespace random
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // RANDOM_NORMAL_H_20120308224056611
// end of file
