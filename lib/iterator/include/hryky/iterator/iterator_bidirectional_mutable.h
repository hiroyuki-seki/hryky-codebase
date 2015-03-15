/**
  @file     iterator_bidirectional_mutable.h
  @brief    A mutable bidirectional iterator.
  @author   HRYKY
  @version  $Id: iterator_bidirectional_mutable.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef ITERATOR_BIDIRECTIONAL_MUTABLE_H_20130413185042451
#define ITERATOR_BIDIRECTIONAL_MUTABLE_H_20130413185042451
#include "hryky/iterator/iterator_bidirectional_base.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ContainerT, \
	typename IndexT
#define hryky_template_arg \
	ContainerT, IndexT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace iterator
{
namespace bidirectional
{
	/// A mutable bidirectional iterator.
	template <hryky_template_param>
	class Mutable;

} // namespace bidirectional
} // namespace iterator
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief A mutable bidirectional iterator.
 */
template <hryky_template_param>
class hryky::iterator::bidirectional::Mutable
	: public Base<hryky_template_arg>
{
public :

	typedef Base<hryky_template_arg>
		base_type;

	typedef Mutable<hryky_template_arg>
		this_type;

	/// default constructor.
	Mutable();

	/// copy constructor.
	Mutable(this_type const &);

	/// move constructor.
	Mutable(this_type &&);

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// constructor with resources.
	Mutable(container_pointer const container, index_param_type index);

	/// pre-increment this iterator.
	this_type & operator++();

	/// post-increment this iterator.
	this_type operator++(int);

	/// pre-decrement this iterator.
	this_type & operator--();

	/// post-decrement this iterator.
	this_type operator--(int);

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
hryky::iterator::bidirectional::Mutable<
	hryky_template_arg>::Mutable()
	: base_type()
{
}
/**
  @brief constructor with a resource.
 */
template <hryky_template_param>
hryky::iterator::bidirectional::Mutable<
	hryky_template_arg>::Mutable(
	container_pointer const container, index_param_type index)
	: base_type(container, index)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::iterator::bidirectional::Mutable<
	hryky_template_arg>::Mutable(
	this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::iterator::bidirectional::Mutable<
	hryky_template_arg>::Mutable(
	this_type && rhs)
	: base_type(::std::move(rhs))
{
}
/**
  @brief pre-increment this iterator.
 */
template <hryky_template_param>
hryky::iterator::bidirectional::Mutable<
	hryky_template_arg> & 
hryky::iterator::bidirectional::Mutable<
	hryky_template_arg>::operator++()
{
	this->index_ = this->container_->next(this->index_);
	return *this;
}
/**
  @brief post-increment this iterator.
 */
template <hryky_template_param>
hryky::iterator::bidirectional::Mutable<
	hryky_template_arg>
hryky::iterator::bidirectional::Mutable<
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
hryky::iterator::bidirectional::Mutable<
	hryky_template_arg> & 
hryky::iterator::bidirectional::Mutable<
	hryky_template_arg>::operator--()
{
	this->index_ = this->container_->prev(this->index_);
	return *this;
}
/**
  @brief post-decrement this iterator.
 */
template <hryky_template_param>
hryky::iterator::bidirectional::Mutable<
	hryky_template_arg>
hryky::iterator::bidirectional::Mutable<
	hryky_template_arg>::operator--(int)
{
	index_type const index = this->index_;
	this->index_ = this->container_->prev(this->index_);
	return this_type(container, index);
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
} // namespace bidirectional
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
#endif // ITERATOR_BIDIRECTIONAL_MUTABLE_H_20130413185042451
// end of file
