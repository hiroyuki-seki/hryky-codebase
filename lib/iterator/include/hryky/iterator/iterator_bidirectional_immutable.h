/**
  @file     iterator_bidirectional_immutable.h
  @brief    A immutable bidirectional iterator.
  @author   HRYKY
  @version  $Id: iterator_bidirectional_immutable.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef ITERATOR_BIDIRECTIONAL_IMMUTABLE_H_20130413190036458
#define ITERATOR_BIDIRECTIONAL_IMMUTABLE_H_20130413190036458
#include "hryky/iterator/iterator_bidirectional_mutable.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ContainerT, typename IndexT, typename MutableT
#define hryky_template_arg \
	ContainerT, IndexT, MutableT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace iterator
{
namespace bidirectional
{
	/// A immutable bidirectional iterator.
	template <hryky_template_param>
	class Immutable;

} // namespace bidirectional
} // namespace iterator
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief A immutable bidirectional iterator.
 */
template <
	typename ContainerT,
	typename IndexT = typename ContainerT::size_type,
	typename MutableT = Mutable<ContainerT, IndexT> >
class hryky::iterator::bidirectional::Immutable
	: public Base<
		typename AddConst<ContainerT>::type,
		IndexT,
		typename ContainerT::const_pointer,
		typename ContainerT::const_reference>
{
public :

	typedef Base<
		typename AddConst<ContainerT>::type,
		IndexT,
		typename ContainerT::const_pointer,
		typename ContainerT::const_reference> base_type;
	typedef Immutable<hryky_template_arg>
		this_type;
	typedef MutableT mutable_type;

	/// default constructor.
	Immutable();

	/// constructor with resources.
	Immutable(container_pointer const container, index_param_type index);

	/// constructor with a mutable iterator.
	Immutable(mutable_type const & rhs);

	/// copy constructor.
	Immutable(this_type const &);

	/// move constructor.
	Immutable(this_type &&);

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// assigns a new container from a mutable iterator.
	this_type & operator=(mutable_type const & rhs);

	/// pre-increment this iterator.
	this_type & operator++();

	/// post-increment this iterator.
	this_type operator++(int);

	/// pre-decrement this iterator.
	this_type & operator--();

	/// post-decrement this iterator.
	this_type operator--(int);

	/// confirms the equality between two instances.
	bool operator==(this_type const & rhs) const;

	/// confirms the inequality between two instances.
	bool operator!=(this_type const & rhs) const;

	/// confirms the equality with a mutable iterator.
	bool operator==(mutable_type const & rhs) const;

	/// confirms the inequality with a mutable iterator.
	bool operator!=(mutable_type const & rhs) const;

protected :

private :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace iterator
{
namespace bidirectional
{
} // namespace bidirectional
} // namespace iterator
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::iterator::bidirectional::Immutable<
	hryky_template_arg>::Immutable()
	: base_type()
{
}
/**
  @brief constructor with a resource.
 */
template <hryky_template_param>
hryky::iterator::bidirectional::Immutable<
	hryky_template_arg>::Immutable(
		container_pointer const container, index_param_type index)
	: base_type(container, index)
{
}
/**
  @brief constructor with a mutable iterator.
 */
template <hryky_template_param>
hryky::iterator::bidirectional::Immutable<
	hryky_template_arg>::Immutable(
		mutable_type const & rhs)
	: base_type(rhs.container(), rhs.index())
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::iterator::bidirectional::Immutable<
	hryky_template_arg>::Immutable(
		this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::iterator::bidirectional::Immutable<
	hryky_template_arg>::Immutable(
		this_type && rhs)
	: base_type(::std::move(rhs))
{
}
/**
  @brief assigns a new container from a mutable iterator.
 */
template <hryky_template_param>
hryky::iterator::bidirectional::Immutable<
	hryky_template_arg> & 
hryky::iterator::bidirectional::Immutable<
	hryky_template_arg>::operator=(
		mutable_type const & rhs)
{
	this->container_ = rhs.container();
	this->index_ = rhs.index();
	return *this;
}
/**
  @brief pre-increment this iterator.
 */
template <hryky_template_param>
hryky::iterator::bidirectional::Immutable<
	hryky_template_arg> & 
hryky::iterator::bidirectional::Immutable<
	hryky_template_arg>::operator++()
{
	this->index_ = this->container_->next(this->index_);
	return *this;
}
/**
  @brief post-increment this iterator.
 */
template <hryky_template_param>
hryky::iterator::bidirectional::Immutable<
	hryky_template_arg>
hryky::iterator::bidirectional::Immutable<
	hryky_template_arg>::operator++(int)
{
	index_type const index = this->index_;
	this->index_ = this->container_->next(this->index_);
	return this_type(container, index);
}
/**
  @brief pre-decrement this iterator.
 */
template <hryky_template_param>
hryky::iterator::bidirectional::Immutable<
	hryky_template_arg> & 
hryky::iterator::bidirectional::Immutable<
	hryky_template_arg>::operator--()
{
	this->index_ = this->container_->prev(this->index_);
	return *this;
}
/**
  @brief post-decrement this iterator.
 */
template <hryky_template_param>
hryky::iterator::bidirectional::Immutable<
	hryky_template_arg>
hryky::iterator::bidirectional::Immutable<
	hryky_template_arg>::operator--(int)
{
	index_type const index = this->index_;
	this->index_ = this->index_->prev(this->index_);
	return this_type(container, index);
}
/**
  @brief confirms the equality between two instances.
 */
template <hryky_template_param>
bool hryky::iterator::bidirectional::Immutable<hryky_template_arg>::operator==(
	this_type const & rhs) const
{
	return this->base_type::operator==(rhs);
}
/**
  @brief confirms the inequality between two instances.
 */
template <hryky_template_param>
bool hryky::iterator::bidirectional::Immutable<hryky_template_arg>::operator!=(
	this_type const & rhs) const
{
	return this->base_type::operator!=(rhs);
}
/**
  @brief confirms the equality with a mutable iterator.
 */
template <hryky_template_param>
bool hryky::iterator::bidirectional::Immutable<hryky_template_arg>::operator==(
	mutable_type const & rhs) const
{
	return this->base_type::operator==(this_type(rhs));
}
/**
  @brief confirms the inequality with a mutable iterator.
 */
template <hryky_template_param>
bool hryky::iterator::bidirectional::Immutable<hryky_template_arg>::operator!=(
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
namespace bidirectional
{
	/// confirms the equality between a mutable iterator and an immutable iterator.
	template <hryky_template_param>
	bool operator==(
		typename Immutable<hryky_template_arg>::mutable_type const & lhs,
		Immutable<hryky_template_arg> const & rhs);

	/// confirms the inequality between a mutable iterator and an immutable iterator.
	template <hryky_template_param>
	bool operator!=(
		typename Immutable<hryky_template_arg>::mutable_type const & lhs,
		Immutable<hryky_template_arg> const & rhs);

} // namespace bidirectional
} // namespace iterator
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief confirms the equality between a mutable iterator and an immutable iterator.
 */
template <hryky_template_param>
bool hryky::iterator::bidirectional::operator==(
	typename Immutable<hryky_template_arg>::mutable_type const & lhs,
	Immutable<hryky_template_arg> const & rhs)
{
	return Immutable<hryky_template_arg>(lhs) == rhs;
}
/**
  @brief confirms the inequality between a mutable iterator and an immutable iterator.
 */
template <hryky_template_param>
bool hryky::iterator::bidirectional::operator!=(
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
#endif // ITERATOR_BIDIRECTIONAL_IMMUTABLE_H_20130413190036458
// end of file
