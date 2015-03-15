/**
  @file     iterator_random_base.h
  @brief    The base class for random access iterator.
  @author   HRYKY
  @version  $Id: iterator_random_base.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef ITERATOR_RANDOM_BASE_H_20130331090221043
#define ITERATOR_RANDOM_BASE_H_20130331090221043
#include "hryky/definition.h"
#include "hryky/std/std_iterator.h"
#include "hryky/stream/stream_definition.h"
#include "hryky/swap.h"
#include "hryky/type_traits/add_const_pointer.h"
#include "hryky/type_traits/add_const_reference.h"
#include "hryky/type_traits/add_pointer.h"
#include "hryky/type_traits/add_reference.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_padded
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
	/// The base class for random access iterator.
	template <hryky_template_param>
	class Base;

} // namespace random
} // namespace iterator
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief base class for random access iterator.
 */
template <
	typename ContainerT, 
	typename ValueT = typename ContainerT::value_type,
	typename PointerT = typename AddPointer<ValueT>::type,
	typename ReferenceT = typename AddReference<ValueT>::type,
	typename SizeT = ::std::size_t,
	typename DifferenceT = ::std::ptrdiff_t
	>
class hryky::iterator::random::Base :
	public ::std::iterator<
		::std::random_access_iterator_tag,
		ValueT,
		DifferenceT,
		PointerT,
		ReferenceT>,
	public WithStreamOut<Base<hryky_template_arg> >,
	public WithSwap<Base<hryky_template_arg> >
{
public :
	typedef Base<hryky_template_arg> this_type;
	typedef typename SizeT size_type;
	typedef typename AddPointer<ContainerT>::type container_pointer;

	/// default constructor.
	Base();

	/// constructor with the container and position.
	Base(container_pointer const container, size_type const pos);

	/// copy constructor.
	Base(this_type const & rhs);

	/// move constructor.
	Base(this_type && rhs);

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// compares for equality.
	bool operator==(this_type const & rhs) const;

	/// compares for inequality.
	bool operator!=(this_type const & rhs) const;

	/// dereferences.
	reference operator*() const;

	/// dereferences by "->" operator.
	pointer operator->() const;

	/// measures the distance between two iterators.
	difference_type operator-(this_type const & rhs) const;

	/// compares for inequality "<".
	bool operator<(this_type const & rhs) const;

	/// compares for inequality ">".
	bool operator>(this_type const & rhs) const;

	/// compares for inequality "<=".
	bool operator<=(this_type const & rhs) const;

	/// compares for inequality ">=".
	bool operator>=(this_type const & rhs) const;

	/// dereferences with offset.
	reference operator[](difference_type index) const;

	/// interchanges internal values.
	void swap(this_type & src);

	/// retrieves the internal container.
	container_pointer container() const;

	/// retrieves the internal position in the container.
	size_type pos() const;

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

	container_pointer container_;
	size_type pos_;

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
hryky::iterator::random::Base<hryky_template_arg>::Base()
	: container_()
{
}
/**
  @brief constructor with the container and position.
 */
template <hryky_template_param>
hryky::iterator::random::Base<hryky_template_arg>::Base(
	container_pointer const container, size_type const pos)
	: container_(container)
	  , pos_(pos)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::iterator::random::Base<hryky_template_arg>::Base(
	this_type const & rhs)
	: hryky_copy_member(container)
	  , hryky_copy_member(pos)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::iterator::random::Base<hryky_template_arg>::Base(
	this_type && rhs)
	: hryky_move_member(container)
	  , hryky_move_member(pos)
{
}
/**
  @brief compares for equality.
 */
template <hryky_template_param>
bool
hryky::iterator::random::Base<hryky_template_arg>::operator==(
	this_type const & rhs) const
{
	return this->container_ == rhs.container_
		&& this->pos_ == rhs.pos_;
}
/**
  @brief compares for inequality.
 */
template <hryky_template_param>
bool
hryky::iterator::random::Base<hryky_template_arg>::operator!=(
	this_type const & rhs) const
{
	return !this->operator==(rhs);
}
/**
  @brief dereferences.
 */
template <hryky_template_param>
typename hryky::iterator::random::Base<hryky_template_arg>::reference
hryky::iterator::random::Base<hryky_template_arg>::operator*(
	) const
{
	return (*this->container_)[
		static_cast<ContainerT::size_type>(this->pos_)];
}
/**
  dereferences by "->" operator
 */
template <hryky_template_param>
typename hryky::iterator::random::Base<hryky_template_arg>::pointer
hryky::iterator::random::Base<hryky_template_arg>::operator->(
	) const
{
	return &this->operator*();
}
/**
  @brief measures the distance between two iterators.
 */
template <hryky_template_param>
typename hryky::iterator::random::Base<hryky_template_arg>::difference_type
hryky::iterator::random::Base<hryky_template_arg>::operator-(
	this_type const & rhs) const
{
	return static_cast<difference_type>(this->pos_ - rhs.pos_);
}
/**
  @brief compares for inequality "<".
 */
template <hryky_template_param>
bool
hryky::iterator::random::Base<hryky_template_arg>::operator<(
	this_type const & rhs) const
{
	return this->pos_ < rhs.pos_;
}
/**
  @brief compares for inequality ">".
 */
template <hryky_template_param>
bool
hryky::iterator::random::Base<hryky_template_arg>::operator>(
	this_type const & rhs) const
{
	return this->pos_ > rhs.pos_;
}
/**
  @brief compares for inequality "<=".
 */
template <hryky_template_param>
bool
hryky::iterator::random::Base<hryky_template_arg>::operator<=(
	this_type const & rhs) const
{
	return this->pos_ <= rhs.pos_;
}
/**
  @brief compares for inequality ">=".
 */
template <hryky_template_param>
bool
hryky::iterator::random::Base<hryky_template_arg>::operator>=(
	this_type const & rhs) const
{
	return this->pos_ >= rhs.pos_;
}
/**
  @brief dereferences with offset.
 */
template <hryky_template_param>
typename hryky::iterator::random::Base<hryky_template_arg>::reference
hryky::iterator::random::Base<hryky_template_arg>::operator[](
	difference_type index) const
{
	return (*this->container_)[this->pos_ + index];
}
/**
  @brief interchanges internal values.
 */
template <hryky_template_param>
void
hryky::iterator::random::Base<hryky_template_arg>::swap(
	this_type & src)
{
	hryky_swap_member(container);
	hryky_swap_member(pos);
}
/**
  @brief retrieves the internal container.
 */
template <hryky_template_param>
typename hryky::iterator::random::Base<hryky_template_arg>::container_pointer
hryky::iterator::random::Base<hryky_template_arg>::container(
	) const
{
	return this->container_;
}
/**
  @brief retrieves the internal position in the container.
 */
template <hryky_template_param>
typename hryky::iterator::random::Base<hryky_template_arg>::size_type
hryky::iterator::random::Base<hryky_template_arg>::pos(
	) const
{
	return this->pos_;
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & 
hryky::iterator::random::Base<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(pos);
	hryky_write_member(container);

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
namespace iterator
{
namespace random
{

} // namespace random
} // namespace iterator
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // ITERATOR_RANDOM_BASE_H_20130331090221043
// end of file
