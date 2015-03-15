/**
  @file     iterator_random_immutable.h
  @brief    A random access iterator whose value is immutable.
  @author   HRYKY
  @version  $Id: iterator_random_immutable.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef ITERATOR_RANDOM_IMMUTABLE_H_20130331094431072
#define ITERATOR_RANDOM_IMMUTABLE_H_20130331094431072
#include "hryky/type_traits/add_const.h"
#include "hryky/iterator/iterator_random_mutable.h"

#include "hryky/integer/bits_enough_signed.h"
#include "hryky/integer/signed_enough.h"

//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ContainerT, \
	typename ValueT, \
	typename PointerT, \
	typename ReferenceT, \
	typename ConstPointerT, \
	typename ConstReferenceT, \
	typename SizeT, \
	typename DifferenceT
#define hryky_template_arg \
	ContainerT, \
	ValueT, \
	PointerT, \
	ReferenceT, \
	ConstPointerT, \
	ConstReferenceT, \
	SizeT, \
	DifferenceT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace iterator
{
namespace random
{
	/// immutable random access iterator.
	template <hryky_template_param>
	class Immutable;
	

} // namespace random
} // namespace iterator
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief immutable random access iterator.
 */
template <
	typename ContainerT,
	typename ValueT = typename ContainerT::value_type,
	typename PointerT = typename AddPointer<ValueT>::type,
	typename ReferenceT = typename AddReference<ValueT>::type,
	typename ConstPointerT = typename AddConstPointer<ValueT>::type,
	typename ConstReferenceT = typename AddConstReference<ValueT>::type,
	typename SizeT = ::std::size_t,
	typename DifferenceT = ::std::ptrdiff_t
	>
class hryky::iterator::random::Immutable
	: public hryky::iterator::random::Base<
		typename hryky::AddConst<ContainerT>::type,
		typename hryky::AddConst<ValueT>::type,
		ConstPointerT,
		ConstReferenceT,
		SizeT,
		DifferenceT>
{
public :

	typedef Immutable<hryky_template_arg> this_type;
	
	typedef Base<
		typename AddConst<ContainerT>::type,
		typename AddConst<ValueT>::type,
		ConstPointerT,
		ConstReferenceT,
		SizeT,
		DifferenceT> base_type;

	/// The mutable type which can be converted to the immutable type.
	typedef Mutable<
		ContainerT, ValueT, PointerT, ReferenceT, SizeT, DifferenceT>
			mutable_type;
	
	/// default constructor.
	Immutable();

	/// copy constructor.
	Immutable(this_type const & rhs);

	/// move constructor.
	Immutable(this_type && rhs);

	/// constructor with container and position.
	Immutable(
		container_pointer container,
		size_type const pos);

	/// constructor with mutable type.
	Immutable(mutable_type const & rhs);

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// assignment operator with mutable type.
	this_type & operator=(mutable_type const & rhs);

	/// pre-increment operator.
	this_type & operator++();

	/// post-increment operator.
	this_type operator++(int);

	/// pre-decrement operator.
	this_type & operator--();

	/// post-decrement operator.
	this_type operator--(int);

	/// retrieves a forward iterator.
	this_type operator+(difference_type rhs) const;

	/// retrieves a backward iterator.
	this_type operator-(difference_type rhs) const;

	/// measures the distance between two iterators.
	difference_type operator-(this_type const & rhs) const;

	/// advances this iterator.
	this_type & operator+=(difference_type rhs);

	/// rewinds this interator.
	this_type & operator-=(difference_type rhs);

	/// confirms whether this itearator is less than the other.
	bool operator<(this_type const & rhs) const;

	/// confirms whether this itearator is greater than the other.
	bool operator>(this_type const & rhs) const;

	/// confirms whether this itearator is less than or equal to the other.
	bool operator<=(this_type const & rhs) const;

	/// confirms whether this itearator is greater than or equal to the other.
	bool operator>=(this_type const & rhs) const;

	/// confirms whether this itearator is equal to the other.
	bool operator==(this_type const & rhs) const;

	/// confirms whether this itearator is not equal to the other.
	bool operator!=(this_type const & rhs) const;

	/// confirms whether this itearator is less than the mutable other.
	bool operator<(mutable_type const & rhs) const;

	/// confirms whether this itearator is greater than the mutable other.
	bool operator>(mutable_type const & rhs) const;

	/// confirms whether this itearator is less than or equal to the mutable other.
	bool operator<=(mutable_type const & rhs) const;

	/// confirms whether this itearator is greater than or equal to the mutable other.
	bool operator>=(mutable_type const & rhs) const;

	/// confirms whether this itearator is equal to the mutable other.
	bool operator==(mutable_type const & rhs) const;

	/// confirms whether this itearator is not equal to the mutable other.
	bool operator!=(mutable_type const & rhs) const;


};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace iterator
{
namespace random
{
} // namespace random
} // namespace iterator
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::iterator::random::Immutable<
	hryky_template_arg>::Immutable()
	: base_type()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::iterator::random::Immutable<
	hryky_template_arg>::Immutable(this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::iterator::random::Immutable<
	hryky_template_arg>::Immutable(
	this_type && rhs)
	: base_type(::std::move(rhs))
{
}
/**
  @brief constructor with container and position..
 */
template <hryky_template_param>
hryky::iterator::random::Immutable<
	hryky_template_arg>::Immutable(
	container_pointer container,
	size_type const pos)
	: base_type(container, pos)
{
}
/**
  @brief constructor with mutable type.
 */
template <hryky_template_param>
hryky::iterator::random::Immutable<
	hryky_template_arg>::Immutable(mutable_type const & rhs)
	: base_type(rhs.container(), rhs.pos())
{
}
/**
  @brief assignment operator with mutable type.
 */
template <hryky_template_param>
hryky::iterator::random::Immutable<
	hryky_template_arg> &
hryky::iterator::random::Immutable<
	hryky_template_arg>::operator=(mutable_type const & rhs)
{
	this->base_type::operator=(base_type(rhs.container(), rhs.pos()));
	return *this;
}
/**
  @brief pre-increment operator.
 */
template <hryky_template_param>
hryky::iterator::random::Immutable<
	hryky_template_arg> &
hryky::iterator::random::Immutable<
	hryky_template_arg>::operator++()
{
	++this->pos_;
	return *this;
}
/**
  @brief post-increment operator.
 */
template <hryky_template_param>
hryky::iterator::random::Immutable<
	hryky_template_arg>
hryky::iterator::random::Immutable<
	hryky_template_arg>::operator++(int)
{
	this_type tmp(*this);
	++this->pos_;
	return tmp;
}
/**
  @brief pre-decrement operator.
 */
template <hryky_template_param>
hryky::iterator::random::Immutable<
	hryky_template_arg> &
hryky::iterator::random::Immutable<
	hryky_template_arg>::operator--()
{
	--this->pos_;
	return *this;
}
/**
  @brief post-decrement operator.
 */
template <hryky_template_param>
hryky::iterator::random::Immutable<
	hryky_template_arg>
hryky::iterator::random::Immutable<
	hryky_template_arg>::operator--(int)
{
	this_type tmp(*this);
	--this->pos_;
	return tmp;
}
/**
  @brief retrieves a forward iterator.
 */
template <hryky_template_param>
hryky::iterator::random::Immutable<
	hryky_template_arg>
hryky::iterator::random::Immutable<
	hryky_template_arg>::operator+(difference_type rhs) const
{
	return this_type(this->container_, this->pos_ + rhs);
}
/**
  @brief retrieves a backward iterator.
 */
template <hryky_template_param>
hryky::iterator::random::Immutable<
	hryky_template_arg>
hryky::iterator::random::Immutable<
	hryky_template_arg>::operator-(difference_type rhs) const
{
	return this_type(this->container_, this->pos_ - rhs);
}
/**
  @brief measures the distance between two iterators.
 */
template <hryky_template_param>
typename hryky::iterator::random::Immutable<
	hryky_template_arg>::difference_type
hryky::iterator::random::Immutable<
	hryky_template_arg>::operator-(this_type const & rhs) const
{
	return this->base_type::operator-(rhs);
}
/**
  @brief advances this iterator.
 */
template <hryky_template_param>
hryky::iterator::random::Immutable<
	hryky_template_arg> &
hryky::iterator::random::Immutable<
	hryky_template_arg>::operator+=(difference_type rhs)
{
	this->pos_ += rhs;
	return *this;
}
/**
  @brief rewinds this interator.
 */
template <hryky_template_param>
hryky::iterator::random::Immutable<
	hryky_template_arg> &
hryky::iterator::random::Immutable<
	hryky_template_arg>::operator-=(difference_type rhs)
{
	this->pos_ -= rhs;
	return *this;
}
/**
  @brief confirms whether this iterator is less than the other iterator.
 */
template <hryky_template_param>
bool
hryky::iterator::random::Immutable<
	hryky_template_arg>::operator<(
		this_type const & rhs) const
{
	return this->base_type::operator<(rhs);
}
/**
  @brief confirms whether this iterator is greater than the other iterator.
 */
template <hryky_template_param>
bool
hryky::iterator::random::Immutable<
	hryky_template_arg>::operator>(
		this_type const & rhs) const
{
	return this->base_type::operator>(rhs);
}
/**
  @brief confirms whether this iterator is less than or equal to the other iterator.
 */
template <hryky_template_param>
bool
hryky::iterator::random::Immutable<
	hryky_template_arg>::operator<=(
		this_type const & rhs) const
{
	return this->base_type::operator<=(rhs);
}
/**
  @brief confirms whether this iterator is greater than or equal to the other iterator.
 */
template <hryky_template_param>
bool
hryky::iterator::random::Immutable<
	hryky_template_arg>::operator>=(
		this_type const & rhs) const
{
	return this->base_type::operator>=(rhs);
}
/**
  @brief confirms whether this iterator is equal to the other iterator.
 */
template <hryky_template_param>
bool
hryky::iterator::random::Immutable<
	hryky_template_arg>::operator==(
		this_type const & rhs) const
{
	return this->base_type::operator==(rhs);
}
/**
  @brief confirms whether this iterator is not equal to the other iterator.
 */
template <hryky_template_param>
bool
hryky::iterator::random::Immutable<
	hryky_template_arg>::operator!=(
		this_type const & rhs) const
{
	return this->base_type::operator!=(rhs);
}
/**
  @brief confirms whether this iterator is less than the other mutable iterator.
 */
template <hryky_template_param>
bool
hryky::iterator::random::Immutable<
	hryky_template_arg>::operator<(
		mutable_type const & rhs) const
{
	return this->base_type::operator<(this_type(rhs));
}
/**
  @brief confirms whether this iterator is greater than the other mutable iterator.
 */
template <hryky_template_param>
bool
hryky::iterator::random::Immutable<
	hryky_template_arg>::operator>(
		mutable_type const & rhs) const
{
	return this->base_type::operator>(this_type(rhs));
}
/**
  @brief confirms whether this iterator is less than or equal to the other mutable iterator.
 */
template <hryky_template_param>
bool
hryky::iterator::random::Immutable<
	hryky_template_arg>::operator<=(
		mutable_type const & rhs) const
{
	return this->base_type::operator<=(this_type(rhs));
}
/**
  @brief confirms whether this iterator is greater than or equal to the other mutable iterator.
 */
template <hryky_template_param>
bool
hryky::iterator::random::Immutable<
	hryky_template_arg>::operator>=(
		mutable_type const & rhs) const
{
	return this->base_type::operator>=(this_type(rhs));
}
/**
  @brief confirms whether this iterator is equal to the other mutable iterator.
 */
template <hryky_template_param>
bool
hryky::iterator::random::Immutable<
	hryky_template_arg>::operator==(
		mutable_type const & rhs) const
{
	return this->base_type::operator==(this_type(rhs));
}
/**
  @brief confirms whether this iterator is not equal to the other mutable iterator.
 */
template <hryky_template_param>
bool
hryky::iterator::random::Immutable<
	hryky_template_arg>::operator!=(
		mutable_type const & rhs) const
{
	return this->base_type::operator!=(this_type(rhs));
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
namespace iterator
{
namespace random
{
	/// confirms a mutable iterator is less than a immutable iterator.
	template <hryky_template_param>
	bool operator<(
		typename Immutable<hryky_template_arg>::mutable_type const & lhs,
		Immutable<hryky_template_arg> const & rhs);

	/// confirms a mutable iterator is graeter than a immutable iterator.
	template <hryky_template_param>
	bool operator>(
		typename Immutable<hryky_template_arg>::mutable_type const & lhs,
		Immutable<hryky_template_arg> const & rhs);

	/// confirms a mutable iterator is less than or equal to a immutable iterator.
	template <hryky_template_param>
	bool operator<=(
		typename Immutable<hryky_template_arg>::mutable_type const & lhs,
		Immutable<hryky_template_arg> const & rhs);

	/// confirms a mutable iterator is graeter than or equal to a immutable iterator.
	template <hryky_template_param>
	bool operator>=(
		typename Immutable<hryky_template_arg>::mutable_type const & lhs,
		Immutable<hryky_template_arg> const & rhs);

	/// confirms a mutable iterator is equal to a immutable iterator.
	template <hryky_template_param>
	bool operator==(
		typename Immutable<hryky_template_arg>::mutable_type const & lhs,
		Immutable<hryky_template_arg> const & rhs);

	/// confirms a mutable iterator is not equal to a immutable iterator.
	template <hryky_template_param>
	bool operator!=(
		typename Immutable<hryky_template_arg>::mutable_type const & lhs,
		Immutable<hryky_template_arg> const & rhs);

} // namespace random
} // namespace iterator
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief confirms a mutable iterator is less than a immutable iterator.
 */
template <hryky_template_param>
bool hryky::iterator::random::operator<(
	typename Immutable<hryky_template_arg>::mutable_type const & lhs,
	Immutable<hryky_template_arg> const & rhs)
{
	return Immutable<hryky_template_arg>(lhs) < rhs;
}
/**
  @brief confirms a mutable iterator is graeter than a immutable iterator.
 */
template <hryky_template_param>
bool hryky::iterator::random::operator>(
	typename Immutable<hryky_template_arg>::mutable_type const & lhs,
	Immutable<hryky_template_arg> const & rhs)
{
	return Immutable<hryky_template_arg>(lhs) > rhs;
}
/**
  @brief confirms a mutable iterator is less than or equal to a immutable iterator.
 */
template <hryky_template_param>
bool hryky::iterator::random::operator<=(
	typename Immutable<hryky_template_arg>::mutable_type const & lhs,
	Immutable<hryky_template_arg> const & rhs)
{
	return Immutable<hryky_template_arg>(lhs) <= rhs;
}
/**
  @brief confirms a mutable iterator is graeter than or equal to a immutable iterator.
 */
template <hryky_template_param>
bool hryky::iterator::random::operator>=(
	typename Immutable<hryky_template_arg>::mutable_type const & lhs,
	Immutable<hryky_template_arg> const & rhs)
{
	return Immutable<hryky_template_arg>(lhs) >= rhs;
}
/**
  @brief confirms a mutable iterator is equal to a immutable iterator.
 */
template <hryky_template_param>
bool hryky::iterator::random::operator==(
	typename Immutable<hryky_template_arg>::mutable_type const & lhs,
	Immutable<hryky_template_arg> const & rhs)
{
	return Immutable<hryky_template_arg>(lhs) == rhs;
}
/**
  @brief confirms a mutable iterator is not equal to a immutable iterator.
 */
template <hryky_template_param>
bool hryky::iterator::random::operator!=(
	typename Immutable<hryky_template_arg>::mutable_type const & lhs,
	Immutable<hryky_template_arg> const & rhs)
{
	return Immutable<hryky_template_arg>(lhs) != rhs;
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // ITERATOR_RANDOM_IMMUTABLE_H_20130331094431072
// end of file
