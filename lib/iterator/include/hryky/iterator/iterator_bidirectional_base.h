/**
  @file     iterator_bidirectional_base.h
  @brief    The base class for bidirectional iterator.
  @author   HRYKY
  @version  $Id: iterator_bidirectional_base.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef ITERATOR_BIDIRECTIONAL_BASE_H_20130413182356433
#define ITERATOR_BIDIRECTIONAL_BASE_H_20130413182356433
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/type_traits/as_parameter.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ContainerT, \
	typename IndexT, \
	typename PointerT, \
	typename ReferenceT
#define hryky_template_arg \
	ContainerT, IndexT, PointerT, ReferenceT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace iterator
{
namespace bidirectional
{
	/// The base class for bidirectional iterator.
	template <hryky_template_param>
	class Base;

} // namespace bidirectional
} // namespace iterator
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief The base class for bidirectional iterator.
 */
template <
	typename ContainerT,
	typename IndexT = typename ContainerT::size_type,
	typename PointerT = typename ContainerT::pointer,
	typename ReferenceT = typename ContainerT::reference
>
class hryky::iterator::bidirectional::Base :
	public ::std::iterator<
		::std::bidirectional_iterator_tag,
		typename ContainerT::value_type,
		typename ContainerT::difference_type,
		PointerT,
		ReferenceT
	>,
	public WithStreamOut<Base<hryky_template_arg> >,
	public WithSwap<Base<hryky_template_arg> >
{
public :

	typedef Base<hryky_template_arg> this_type;
	typedef typename AddPointer<ContainerT>::type container_pointer;
	typedef IndexT index_type;
	typedef typename AsParameter<IndexT>::type index_param_type;

	/// default constructor.
	Base();

	/// constructor with resources.
	Base(container_pointer const container, index_param_type index);

	/// copy constructor.
	Base(this_type const &);

	/// move constructor.
	Base(this_type &&);

	/// destructor.
	~Base();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// confirms the equality between two iterators.
	bool operator==(this_type const & rhs) const;

	/// confirms the inequality between two iterators.
	bool operator!=(this_type const & rhs) const;

	/// retrieves the pointer to the value.
	pointer operator->() const;

	/// retrieves the reference to the value.
	reference operator*() const;

	/// retrieves the internal pointer to the container.
	container_pointer container() const;

	/// retrieves the internal index of the container.
	index_param_type index() const;

protected :

	container_pointer container_;
	index_type index_;

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
hryky::iterator::bidirectional::Base<
	hryky_template_arg>::Base()
	: container_()
	  , index_()
{
}
/**
  @brief constructor with a resource.
 */
template <hryky_template_param>
hryky::iterator::bidirectional::Base<
	hryky_template_arg>::Base(
		container_pointer const container, index_param_type index)
	: container_(container)
	  , index_(index)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::iterator::bidirectional::Base<
	hryky_template_arg>::Base(
		this_type const & rhs)
	: hryky_copy_member(container)
	  , hryky_copy_member(index)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::iterator::bidirectional::Base<
	hryky_template_arg>::Base(
		this_type && rhs)
	: hryky_move_member(container)
	  , hryky_move_member(index)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::iterator::bidirectional::Base<
	hryky_template_arg>::~Base()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::iterator::bidirectional::Base<
	hryky_template_arg>::clear()
{
	hryky::clear(this->index_);
	hryky::clear(this->container_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::iterator::bidirectional::Base<
	hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(container);
	hryky_swap_member(index);
}
/**
  @brief confirms the equality between two iterators.
 */
template <hryky_template_param>
bool
hryky::iterator::bidirectional::Base<
	hryky_template_arg>::operator==(
		this_type const & rhs) const
{
	return this->container_ == rhs.container_
		&& this->index_ == rhs.index_;
}
/**
  @brief confirms the inequality between two iterators.
 */
template <hryky_template_param>
bool
hryky::iterator::bidirectional::Base<
	hryky_template_arg>::operator!=(
		this_type const & rhs) const
{
	return !this->operator==(rhs);
}
/**
  @brief retrieves the pointer to the value.
 */
template <hryky_template_param>
typename hryky::iterator::bidirectional::Base<
	hryky_template_arg>::pointer
hryky::iterator::bidirectional::Base<
	hryky_template_arg>::operator->() const
{
	return this->container_->inquire(this->index_);
}
/**
  @brief retrieves the reference to the value.
 */
template <hryky_template_param>
typename hryky::iterator::bidirectional::Base<
	hryky_template_arg>::reference
hryky::iterator::bidirectional::Base<
	hryky_template_arg>::operator*() const
{
	return *this->operator->();
}
/**
  @brief retrieves the internal pointer to the container.
 */
template <hryky_template_param>
typename hryky::iterator::bidirectional::Base<
	hryky_template_arg>::container_pointer 
hryky::iterator::bidirectional::Base<
	hryky_template_arg>::container() const
{
	return this->container_;
}
/**
  @brief retrieves the internal index of the container.
 */
template <hryky_template_param>
typename hryky::iterator::bidirectional::Base<
	hryky_template_arg>::index_param_type 
hryky::iterator::bidirectional::Base<
	hryky_template_arg>::index() const
{
	return this->index_;
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::iterator::bidirectional::Base<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_pointer_member(container);
	hryky_write_member(index);
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
#endif // ITERATOR_BIDIRECTIONAL_BASE_H_20130413182356433
// end of file
