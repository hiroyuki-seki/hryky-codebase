/**
  @file     tuple_adapter.h
  @brief    lets an existing container have the interfaces of Tuple.
  @author   HRYKY
  @version  $Id: tuple_adapter.h 353 2014-06-17 04:55:19Z hryky.private@gmail.com $
 */
#ifndef TUPLE_ADAPTER_H_20131015231057632
#define TUPLE_ADAPTER_H_20131015231057632
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
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
	/// wraps a container as tuple.
	template <hryky_template_param>
	class TupleAdapter;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief wraps a container as tuple.
 */
template <hryky_template_param>
class hryky::TupleAdapter :
	public WithStreamOut<TupleAdapter<hryky_template_arg> >,
	public WithSwap<TupleAdapter<hryky_template_arg> >
{
public :

	typedef TupleAdapter<hryky_template_arg> this_type;

	typedef typename ContainerT::const_reference    const_reference;
	typedef typename ContainerT::reference          reference;
	typedef typename ContainerT::size_type          size_type;

	/// constructs with the internal container.
	TupleAdapter(ContainerT & container);

	/// copy constructor.
	TupleAdapter(this_type const &);

	/// move constructor.
	TupleAdapter(this_type &&);

	/// destructor.
	~TupleAdapter();

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

	/// retrieves the size of the container.
	size_type size() const;

	/// retrieves an element in the container.
	template <size_t Index>
	const_reference at() const;

	/// retrieves a mutable element in the container.
	template <size_t Index>
	reference at();

protected :

private :

	hryky_delete_default_constructor(TupleAdapter);

	ContainerT & container_;

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
  @brief constructs with the internal container.
 */
template <hryky_template_param>
hryky::TupleAdapter<hryky_template_arg>::TupleAdapter(
	ContainerT & container)
	: container_(container)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::TupleAdapter<hryky_template_arg>::TupleAdapter(
	this_type const & rhs)
	: hryky_copy_member(container)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::TupleAdapter<hryky_template_arg>::TupleAdapter(
	this_type && rhs)
	: hryky_move_member(container)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::TupleAdapter<hryky_template_arg>::~TupleAdapter()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::TupleAdapter<hryky_template_arg>::clear()
{
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::TupleAdapter<hryky_template_arg>::write_to(
	StreamT & out) const
{
	out << this->container_;
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::TupleAdapter<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(container);
}
/**
  @brief retrieves the size of the container.
 */
template <hryky_template_param>
typename hryky::TupleAdapter<hryky_template_arg>::size_type
hryky::TupleAdapter<hryky_template_arg>::size() const
{
	return this->container_.size();
}
/**
  @brief retrieves an element in the container.
 */
template <hryky_template_param>
template <size_t Index>
typename hryky::TupleAdapter<hryky_template_arg>::const_reference
hryky::TupleAdapter<hryky_template_arg>::at() const
{
	return this->container_[Index];
}
/**
  @brief retrieves a mutable element in the container.
 */
template <hryky_template_param>
template <size_t Index>
typename hryky::TupleAdapter<hryky_template_arg>::reference 
hryky::TupleAdapter<hryky_template_arg>::at()
{
	return this->container_[Index];
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
	
	
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // TUPLE_ADAPTER_H_20131015231057632
// end of file
