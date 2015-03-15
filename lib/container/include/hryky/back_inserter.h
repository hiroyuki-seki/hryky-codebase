/**
  @file     back_inserter.h
  @brief    substitutes for ::std::back_insert_iterator for the use with ::std::iterator_traits.
  @author   HRYKY
  @version  $Id: back_inserter.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef BACK_INSERTER_H_20140419194734491
#define BACK_INSERTER_H_20140419194734491
#include "hryky/std/std_iterator.h"
#include "hryky/is_null.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ContainerT
#define hryky_template_arg \
	ContainerT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/**
	  substitutes for ::std::back_insert_iterator
	  for the use with ::std::iterator_traits.
	 */
	template <typename ContainerT>
	class BackInserter;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief substitutes for ::std::back_insert_iterator
    for the use with ::std::iterator_traits.
 */
template <hryky_template_param>
class hryky::BackInserter :
	public ::std::iterator<
		::std::output_iterator_tag,
		typename ContainerT::value_type,
		typename ContainerT::difference_type,
		typename ContainerT::pointer,
		typename ContainerT::reference
	>
{
public :

	typedef ::std::iterator<
		::std::output_iterator_tag,
		typename ContainerT::value_type,
		typename ContainerT::difference_type,
		typename ContainerT::pointer,
		typename ContainerT::reference
	> base_type;

	typedef BackInserter<hryky_template_arg> this_type;

	/// default constructor.
	BackInserter();

	/// instantiates with a container.
	explicit BackInserter(ContainerT & container);

	/// copy constructor.
	BackInserter(this_type const &);

	/// move constructor.
	BackInserter(this_type &&);

	/// destructor.
	~BackInserter();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// appends a value at the end of container.
	this_type & operator=(
		typename ContainerT::const_reference rhs);

	/// The pre-increment is not effective.
	this_type & operator++();

	/// The post-increment is not effective.
	this_type operator++(int);

	/// The dereferencing is not effective.
	this_type & operator*();

	/// The immutable dereferencing is not effective.
	this_type const & operator*() const;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

private :

	ContainerT * container_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::BackInserter<hryky_template_arg>::BackInserter()
	: base_type()
	  , container_()
{
}
/**
  @brief instantiates with a container.
 */
template <hryky_template_param>
hryky::BackInserter<hryky_template_arg>::BackInserter(
	ContainerT & container)
	: base_type()
	  , container_(&container)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::BackInserter<hryky_template_arg>::BackInserter(
	this_type const & rhs)
	: base_type(rhs)
	  , hryky_copy_member(container)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::BackInserter<hryky_template_arg>::BackInserter(
	this_type && rhs)
	: base_type(::std::move(rhs))
	  , hryky_move_member(container)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::BackInserter<hryky_template_arg>::~BackInserter()
{
}
/**
  @brief appends a value at the end of container.
 */
template <hryky_template_param>
hryky::BackInserter<hryky_template_arg> & 
hryky::BackInserter<hryky_template_arg>::operator=(
	typename ContainerT::const_reference rhs)
{
	if (!hryky_is_null(this->container_)) {
		this->container_->push_back(rhs);
	}
	return *this;
}
/**
  @brief The pre-increment is not effective.
 */
template <hryky_template_param>
hryky::BackInserter<hryky_template_arg> & 
hryky::BackInserter<hryky_template_arg>::operator++()
{
	return *this;
}
/**
  @brief The post-increment is not effective.
 */
template <hryky_template_param>
hryky::BackInserter<hryky_template_arg>
hryky::BackInserter<hryky_template_arg>::operator++(int)
{
	return *this;
}
/**
  @brief The dereferencing is not effective.
 */
template <hryky_template_param>
hryky::BackInserter<hryky_template_arg> & 
hryky::BackInserter<hryky_template_arg>::operator*()
{
	return *this;
}
/**
  @brief The immutable dereferencing is not effective.
 */
template <hryky_template_param>
hryky::BackInserter<hryky_template_arg> const & 
hryky::BackInserter<hryky_template_arg>::operator*() const
{
	return *this;
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::BackInserter<hryky_template_arg>::clear()
{
	hryky::clear(this->container_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::BackInserter<hryky_template_arg>::swap(
	this_type & src)
{
	hryky_swap_member(container);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::BackInserter<hryky_template_arg>::write_to(
	StreamT & out) const
{
	if (hryky_is_null(this->container_)) {
		return out;
	}
	else {
		return this->container_->write_to(out);
	}
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
	/// creates an instance of BackInserter<>.
	template <hryky_template_param>
	BackInserter<hryky_template_arg>
		back_inserter(ContainerT & container);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates an instance of BackInserter<>.
 */
template <hryky_template_param>
hryky::BackInserter<hryky_template_arg> hryky::back_inserter(
	ContainerT & container)
{
	return BackInserter<hryky_template_arg>(container);
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // BACK_INSERTER_H_20140419194734491
// end of file
