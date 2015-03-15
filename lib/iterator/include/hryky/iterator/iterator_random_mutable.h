/**
  @file     iterator_random_mutable.h
  @brief    A random access iterator whose value is mutable.
  @author   HRYKY
  @version  $Id: iterator_random_mutable.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef ITERATOR_RANDOM_MUTABLE_H_20130331092342058
#define ITERATOR_RANDOM_MUTABLE_H_20130331092342058
#include "hryky/iterator/iterator_random_base.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ContainerT, \
	typename ValueT, \
	typename PointerT, \
	typename ReferenceT, \
	typename SizeT, \
	typename DifferenceT
#define hryky_template_arg \
	ContainerT, ValueT, PointerT, ReferenceT, SizeT, DifferenceT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace iterator
{
namespace random
{
	/// mutable random access iterator.
	template <hryky_template_param>
	class Mutable;
	
} // namespace random
} // namespace iterator
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief mutable random access iterator.
 */
template <
	typename ContainerT,
	typename ValueT = typename ContainerT::value_type,
	typename PointerT = typename AddPointer<ValueT>::type,
	typename ReferenceT = typename AddReference<ValueT>::type,
	typename SizeT = ::std::size_t,
	typename DifferenceT = ::std::ptrdiff_t
	>
class hryky::iterator::random::Mutable
	: public Base<hryky_template_arg>
{
public :
	typedef Mutable<hryky_template_arg>   this_type;
	typedef Base<hryky_template_arg>      base_type;

	/// default constructor
	Mutable();

	/// constructor with container and position.
	Mutable(container_pointer const container, size_type const pos);

	/// copy constructor
	Mutable(this_type const & rhs);

	/// move constructor.
	Mutable(this_type && rhs);

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// pre-increment operator
	this_type & operator++();

	/// post-increment operator
	this_type operator++(int);

	/// pre-decrement operator
	this_type & operator--();

	/// post-decrement operator
	this_type operator--(int);

	/// retrieves a forward iterator
	this_type operator+(difference_type rhs) const;

	/// retrieves a backward iterator
	this_type operator-(difference_type rhs) const;

	/// measures the distance between two iterators
	difference_type operator-(this_type const & rhs) const;

	/// advances iterator
	this_type & operator+=(difference_type rhs);

	/// backs iterator
	this_type & operator-=(difference_type rhs);

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
hryky::iterator::random::Mutable<hryky_template_arg>::Mutable()
	: base_type()
{
}
/**
  @brief constructor with container and position..
 */
template <hryky_template_param>
hryky::iterator::random::Mutable<hryky_template_arg>::Mutable(
	container_pointer const container, size_type const pos)
	: base_type(container, pos)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::iterator::random::Mutable<hryky_template_arg>::Mutable(
	this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::iterator::random::Mutable<hryky_template_arg>::Mutable(
	this_type && rhs)
	: base_type(::std::move(rhs))
{
}
/**
  @brief pre-increment operator.
 */
template <hryky_template_param>
hryky::iterator::random::Mutable<hryky_template_arg> &
hryky::iterator::random::Mutable<hryky_template_arg>::operator++()
{
	++this->pos_;
	return *this;
}
/**
  @brief post-increment operator.
 */
template <hryky_template_param>
hryky::iterator::random::Mutable<hryky_template_arg>
hryky::iterator::random::Mutable<hryky_template_arg>::operator++(int)
{
	this_type tmp(*this);
	++this->pos_;
	return tmp;
}
/**
  @brief pre-decrement operator.
 */
template <hryky_template_param>
hryky::iterator::random::Mutable<hryky_template_arg> &
hryky::iterator::random::Mutable<hryky_template_arg>::operator--()
{
	--this->pos_;
	return *this;
}
/**
  @brief post-decrement operator.
 */
template <hryky_template_param>
hryky::iterator::random::Mutable<hryky_template_arg>
hryky::iterator::random::Mutable<hryky_template_arg>::operator--(int)
{
	this_type tmp(*this);
	--this->pos_;
	return tmp;
}
/**
  @brief retrieves a forward iterator.
 */
template <hryky_template_param>
hryky::iterator::random::Mutable<hryky_template_arg>
hryky::iterator::random::Mutable<hryky_template_arg>::operator+(
	difference_type rhs) const
{
	return this_type(this->container_, this->pos_ + rhs);
}
/**
  @brief retrieves a backward iterator.
 */
template <hryky_template_param>
hryky::iterator::random::Mutable<hryky_template_arg>
hryky::iterator::random::Mutable<hryky_template_arg>::operator-(
	difference_type rhs) const
{
	return this_type(this->container_, this->pos_ - rhs);
}
/**
  @brief measures the distance between two iterators.
 */
template <hryky_template_param>
typename hryky::iterator::random::Mutable<hryky_template_arg>::difference_type
hryky::iterator::random::Mutable<hryky_template_arg>::operator-(
	this_type const & rhs) const
{
	return this->base_type::operator-(rhs);
}
/**
  @brief advances iterator.
 */
template <hryky_template_param>
hryky::iterator::random::Mutable<hryky_template_arg> &
hryky::iterator::random::Mutable<hryky_template_arg>::operator+=(
	difference_type rhs)
{
	this->pos_ += rhs;
	return *this;
}
/**
  @brief backs iterator.
 */
template <hryky_template_param>
hryky::iterator::random::Mutable<hryky_template_arg> &
hryky::iterator::random::Mutable<hryky_template_arg>::operator-=(
	difference_type rhs)
{
	this->pos_ -= rhs;
	return *this;
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
	/// retrieves a forwarded iterator.
	template <hryky_template_param>
	Mutable<hryky_template_arg> operator+(
		typename Mutable<hryky_template_arg>::difference_type lhs,
		Mutable<hryky_template_arg> const & rhs);
	
} // namespace random
} // namespace iterator
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief retrieves a forwarded iterator.
 */
template <hryky_template_param>
hryky::iterator::random::Mutable<hryky_template_arg>
hryky::iterator::random::operator+(
	typename Mutable<hryky_template_arg>::difference_type lhs,
	Mutable<hryky_template_arg> const & rhs)
{
	return rhs + lhs;
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // ITERATOR_RANDOM_MUTABLE_H_20130331092342058
// end of file
