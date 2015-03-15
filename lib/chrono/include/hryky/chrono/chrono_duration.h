/**
  @file     chrono_duration.h
  @brief    substitutes for ::std::chrono::duration.
  @author   HRYKY
  @version  $Id: chrono_duration.h 374 2014-07-27 11:54:24Z hryky.private@gmail.com $
 */
#ifndef CHRONO_DURATION_H_20140713171816387
#define CHRONO_DURATION_H_20140713171816387
#include "hryky/definition.h"
#include "hryky/ratio.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename RepT, typename RatioT
#define hryky_template_arg \
	RepT, RatioT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace chrono
{
	/// substitutes for ::std::chrono::duration.
	template <
		typename RepT,
		typename RatioT = Ratio<1>
	>
	class Duration;

	typedef Duration<intmax_t, nano>             nanoseconds;
	typedef Duration<intmax_t, micro>            microseconds;
	typedef Duration<intmax_t, milli>            milliseconds;
	typedef Duration<intmax_t>                   seconds;
	typedef Duration<intmax_t, Ratio<60> >       minutes;
	typedef Duration<intmax_t, Ratio<3600> >     hours;
	typedef Duration<intmax_t, Ratio<86400> >    days;
	typedef Duration<intmax_t, Ratio<604800> >   weeks;

	typedef Duration<float, nano>           fnanoseconds;
	typedef Duration<float, micro>          fmicroseconds;
	typedef Duration<float, milli>          fmilliseconds;
	typedef Duration<float>                 fseconds;
	typedef Duration<float, Ratio<60> >     fminutes;
	typedef Duration<float, Ratio<3600> >   fhours;
	typedef Duration<float, Ratio<86400> >  fdays;
	typedef Duration<float, Ratio<604800> > fweeks;

namespace std
{
	typedef ::std::chrono::nanoseconds    nanoseconds;
	typedef ::std::chrono::microseconds   microseconds;
	typedef ::std::chrono::milliseconds   milliseconds;
	typedef ::std::chrono::seconds        seconds;
	typedef ::std::chrono::minutes        minutes;
	typedef ::std::chrono::hours          hours;
	
	typedef ::std::chrono::duration<int32_t, ::std::ratio<86400> > days;
	typedef ::std::chrono::duration<int32_t, ::std::ratio<604800> > weeks;

	typedef ::std::chrono::duration<float, ::std::nano >        fnanoseconds;
	typedef ::std::chrono::duration<float, ::std::micro >       fmicroseconds;
	typedef ::std::chrono::duration<float, ::std::milli >       fmilliseconds;
	typedef ::std::chrono::duration<float>                      fseconds;
	typedef ::std::chrono::duration<float, ::std::ratio<60> >   fminutes;
	typedef ::std::chrono::duration<float, ::std::ratio<3600> > fhours;
} // namespace std

} // namespace chrono
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief substitutes for ::std::chrono::duration.
 */
template <hryky_template_param>
class hryky::chrono::Duration :
	public WithSwap<Duration<hryky_template_arg> >,
	public WithStreamOut<Duration<hryky_template_arg> >
{
public :

	typedef Duration<hryky_template_arg> this_type;

	typedef RepT rep;
	typedef RatioT period;

	/// default constructor.
	Duration();

	/// creates an instance from the initial count.
	template <typename RhsRepT>
	Duration(RhsRepT const & count);

	/// creates an instance from other duration.
	template <typename RhsRepT, typename RhsRatioT>
	Duration(Duration<RhsRepT, RhsRatioT> const & rhs);

	/// creates an instance from ::std::chrono::duration.
	template <typename RhsRepT, typename RhsRatioT>
	Duration(::std::chrono::duration<RhsRepT, RhsRatioT> const & rhs);

	/// copy constructor.
	Duration(this_type const &);

	/// move constructor.
	Duration(this_type &&);

	/// destructor.
	~Duration();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// adds the other duration.
	template <typename RhsRepT, typename RhsRatioT>
	this_type & operator+=(
		Duration<RhsRepT, RhsRatioT> const & rhs);

	/// compares whether LHS < RHS.
	bool operator<(this_type const & rhs) const;

	/// compares whether LHS < RHS.
	template <typename RhsRepT, typename RhsRatioT>
	bool operator<(
		Duration<RhsRepT, RhsRatioT> const & rhs) const;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// retrieves the count of duration.
	rep count() const;

protected :

private :

	template <typename RhsRatioT>
	struct RelativeRatio
	{
		typedef Ratio<
			RhsRatioT::num * RatioT::den,
			RhsRatioT::den * RatioT::num> type;
	};

	rep count_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace chrono
{
} // namespace chrono
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::chrono::Duration<hryky_template_arg>::Duration()
	: count_()
{
}
/**
  @brief creates an instance from the initial count.
 */
template <hryky_template_param>
template <typename RhsRepT>
hryky::chrono::Duration<hryky_template_arg>::Duration(
	RhsRepT const & count)
	: count_(static_cast<RepT>(count))
{
}
/**
  @brief creates an instance from other duration.
 */
template <hryky_template_param>
template <typename RhsRepT, typename RhsRatioT>
hryky::chrono::Duration<hryky_template_arg>::Duration(
	Duration<RhsRepT, RhsRatioT> const & rhs)
	: count_(
		static_cast<RepT>(
			rhs.count() * RelativeRatio<RhsRatioT>::type::num)
		/ RelativeRatio<RhsRatioT>::type::den)
{
}
/**
  @brief creates an instance from ::std::chrono::duration.
 */
template <hryky_template_param>
template <typename RhsRepT, typename RhsRatioT>
hryky::chrono::Duration<hryky_template_arg>::Duration(
	::std::chrono::duration<RhsRepT, RhsRatioT> const & rhs)
	: count_(
		static_cast<RepT>(
			rhs.count() * RelativeRatio<RhsRatioT>::type::num)
		/ RelativeRatio<RhsRatioT>::type::den)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::chrono::Duration<hryky_template_arg>::Duration(
	this_type const & rhs)
	: hryky_copy_member(count)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::chrono::Duration<hryky_template_arg>::Duration(
	this_type && rhs)
	: hryky_move_member(count)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::chrono::Duration<hryky_template_arg>::~Duration()
{
}
/**
  @brief adds the other duration.
 */
template <hryky_template_param>
template <typename RhsRepT, typename RhsRatioT>
hryky::chrono::Duration<hryky_template_arg> & 
hryky::chrono::Duration<hryky_template_arg>::operator+=(
	Duration<RhsRepT, RhsRatioT> const & rhs)
{
	this->count_ += (
		static_cast<RepT>(
			rhs.count() * RelativeRatio<RhsRatioT>::type::num)
		/ RelativeRatio<RhsRatioT>::type::den);
	
	return *this;
}
/**
  @brief compares whether LHS < RHS.
 */
template <hryky_template_param>
bool hryky::chrono::Duration<hryky_template_arg>::operator<(
	this_type const & rhs) const
{
	return this->count_ < rhs.count();
}
/**
  @brief compares whether LHS < RHS.
 */
template <hryky_template_param>
template <typename RhsRepT, typename RhsRatioT>
bool hryky::chrono::Duration<hryky_template_arg>::operator<(
	Duration<RhsRepT, RhsRatioT> const & rhs) const
{
	return (
		this->count_ * RelativeRatio<RhsRatioT>::type::den
		< static_cast<RepT>(
			rhs.count() * RelativeRatio<RhsRatioT>::type::num));
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::chrono::Duration<hryky_template_arg>::clear()
{
	hryky::clear(this->count_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::chrono::Duration<hryky_template_arg>::swap(
	this_type & src)
{
	hryky_swap_member(count);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::chrono::Duration<hryky_template_arg>::write_to(
	StreamT & out) const
{
	out << this->count();
	return out;
}
/**
  @brief retrieves the count of duration.
 */
template <hryky_template_param>
RepT hryky::chrono::Duration<hryky_template_arg>::count() const
{
	return this->count_;
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
namespace chrono
{
} // namespace chrono
} // namespace hryky
namespace std
{
namespace chrono
{
	/// outputs a duration.
	template <typename LhsT, typename RepT, typename RatioT>
	LhsT & operator<<(
		LhsT & lhs,
		::std::chrono::duration<RepT, RatioT> const & rhs);
} // namespace chrono
} // namespace std
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief outputs a duration.
 */
template <typename LhsT, typename RepT, typename RatioT>
LhsT & ::std::chrono::operator<<(
	LhsT & lhs,
	::std::chrono::duration<RepT, RatioT> const & rhs)
{
	return lhs << rhs.count();
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // CHRONO_DURATION_H_20140713171816387
// end of file
