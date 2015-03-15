/**
  @file         random_uniform.h
  @brief        creates a pseudo-random number according to the uniform distribution.
  @author       HRYKY
  @version      $Id: random_uniform.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef RANDOM_UNIFORM_H_20120308224739616
#define RANDOM_UNIFORM_H_20120308224739616
#include "hryky/random/random_common.h"
#include "hryky/integer/max_of.h"
#include "hryky/integer/min_of.h"
#include "hryky/with_stream_out.h"
#include "hryky/std/std_random.h"
#include "hryky/type_traits/conditional.h"
#include "hryky/type_traits/is_unsigned.h"
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
	/// creates a pseudo-random number according to the uniform distribution.
	template <hryky_template_param>
	class Uniform;
} // namespace random
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief creates a pseudo-random number according to the uniform distribution.
 */
template <hryky_template_param>
class hryky::random::Uniform :
	public WithStreamOut<Uniform<hryky_template_arg> >
{
public :

	/// self.
	typedef Uniform<hryky_template_arg> this_type;

	/// constructor with the default range.
	Uniform(generator_type & generator);

	/// constructor with the range of random numbers.
	Uniform(generator_type & generator, ValueT min, ValueT max);

	/// generates a pseudo-random number.
	ValueT operator()();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

private :
	
	/// represents implementation
	typedef ::std::uniform_int_distribution<
		typename ConditionalC<
			(sizeof(uint16_t) > sizeof(ValueT)),
			typename Conditional<
				IsUnsigned<ValueT>, uint16_t, int16_t
			>::type,
			ValueT
		>::type
	> distribution_type;

	hryky_delete_default_constructor(Uniform);
	hryky_delete_this_copy_constructor(Uniform);
	hryky_delete_this_copy_assign_op(Uniform);

	generator_type &    generator_;
	distribution_type   distribution_;

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
  @brief constructor with the default range.
 */
template <typename ValueT>
hryky::random::Uniform<hryky_template_arg>::Uniform(
	generator_type & generator)
	: generator_(generator)
	  , distribution_(
		  MinOf<hryky_template_arg>::value,
		  MaxOf<hryky_template_arg>::value)
{
}
/**
  @brief constructor with the range of random numbers.
 */
template <hryky_template_param>
hryky::random::Uniform<hryky_template_arg>::Uniform(
	generator_type & generator, ValueT min, ValueT max)
	: generator_(generator)
	  , distribution_(min, max)
{
	return;
}
/**
  @brief generates a pseudo-random number.
 */
template <hryky_template_param>
ValueT
hryky::random::Uniform<hryky_template_arg>::operator()()
{
	return static_cast<ValueT>(
		this->distribution_(this->generator_));
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename ValueT>
template <typename StreamT>
StreamT &
hryky::random::Uniform<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << stream::denote("min")
		<< this->distribution_.min();
	out << stream::denote("max")
		<< this->distribution_.max();
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
#endif // RANDOM_UNIFORM_H_20120308224739616
// end of file
