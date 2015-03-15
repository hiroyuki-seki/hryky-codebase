/**
  @file     ostream_iterator.h
  @brief    adapts an iterator for output stream.
  @author   HRYKY
  @version  $Id: ostream_iterator.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef OSTREAM_ITERATOR_H_20140328221330592
#define OSTREAM_ITERATOR_H_20140328221330592
#include "hryky/retention/retention_value.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename IteratorT
#define hryky_template_arg \
	IteratorT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace ostream
{
	/// adapts an iterator for output stream.
	template <typename IteratorT>
	class Iterator;

} // namespace ostream
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief adapts an iterator for output stream.
 */
template <hryky_template_param>
class hryky::ostream::Iterator :
	public retention::Value<IteratorT>,
	public WithStreamOut<Iterator<hryky_template_arg> >,
	public WithSwap<Iterator<hryky_template_arg> >
{
public :

	typedef Iterator<hryky_template_arg>                this_type;
	typedef retention::Value<IteratorT>                 retention_type;
	typedef typename retention_type::initializer_type   initializer_type;

	/// default constructor.
	Iterator();

	/// copy constructor.
	Iterator(this_type const &);

	/// move constructor.
	Iterator(this_type &&);

	/// instantiates with an iterator.
	explicit Iterator(initializer_type itr);

	/// destructor.
	~Iterator();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// inputs a value of arbitrary type.
	template <typename RhsT>
	this_type & operator<<(RhsT rhs);

protected :

private :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace ostream
{
} // namespace ostream
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::ostream::Iterator<hryky_template_arg>::Iterator()
	: retention_type()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::ostream::Iterator<hryky_template_arg>::Iterator(
	this_type const & rhs)
	: retention_type(rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::ostream::Iterator<hryky_template_arg>::Iterator(
	this_type && rhs)
	: retention_type(::std::move(rhs))
{
}
/**
  @brief instantiates with an iterator.
 */
template <hryky_template_param>
hryky::ostream::Iterator<hryky_template_arg>::Iterator(
	initializer_type itr)
	: retention_type(itr)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::ostream::Iterator<hryky_template_arg>::~Iterator()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::ostream::Iterator<hryky_template_arg>::clear()
{
	this->retention_type::clear()
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::ostream::Iterator<hryky_template_arg>::swap(
	this_type & src)
{
	this->retention_type::swap(src);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::ostream::Iterator<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return this->retention_type::write_to(out);
}
/**
  @brief inputs a value of arbitrary type.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::ostream::Iterator<hryky_template_arg> & 
hryky::ostream::Iterator<hryky_template_arg>::operator<<(
	RhsT rhs)
{
	*((*this->get())++) = rhs;
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
namespace ostream
{
	/// creates an ostream::Iterator.
	template <hryky_template_param>
	Iterator<hryky_template_arg> iterator(IteratorT const & itr);

	/// creates an output stream which appends value at the end of the container.
	template <typename ContainerT>
	Iterator< ::std::back_insert_iterator<ContainerT> >
		back_inserter(ContainerT & container);

} // namespace ostream
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates an ostream::Iterator.
 */
template <hryky_template_param>
hryky::ostream::Iterator<hryky_template_arg>
hryky::ostream::iterator(IteratorT const & itr)
{
	return Iterator<IteratorT>(itr);
}
/**
  @brief creates an output stream which appends value at the end of the container.
 */
template <typename ContainerT>
hryky::ostream::Iterator< ::std::back_insert_iterator<ContainerT> > 
hryky::ostream::back_inserter(ContainerT & container)
{
	return iterator(::std::back_inserter(container));
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // OSTREAM_ITERATOR_H_20140328221330592
// end of file
