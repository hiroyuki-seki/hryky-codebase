/**
  @file     tuple_array.h
  @brief    wraps a built-in array as tuple.
  @author   HRYKY
  @version  $Id: tuple_array.h 350 2014-04-24 10:10:31Z hryky.private@gmail.com $
 */
#ifndef TUPLE_ARRAY_H_20131015232756644
#define TUPLE_ARRAY_H_20131015232756644
#include "hryky/tuple/tuple_adapter.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT, size_t Size
#define hryky_template_arg \
	ValueT[Size]
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief wraps a built-in array as tuple.
 */
template <hryky_template_param>
class TupleAdapter<hryky_template_arg> :
	public WithStreamOut<TupleAdapter<hryky_template_arg> >,
	public WithSwap<TupleAdapter<hryky_template_arg> >
{
private :
	typedef ValueT container_type[Size];
public :

	typedef TupleAdapter<hryky_template_arg> this_type;

	typedef typename AddConstReference<ValueT>::type    const_reference;
	typedef typename AddReference<ValueT>::type         reference;
	typedef size_t                                      size_type;

	/// constructs with the internal container.
	TupleAdapter(container_type & container);

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

	container_type & container_;

};
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief constructs with the internal container.
 */
template <hryky_template_param>
hryky::TupleAdapter<hryky_template_arg>::TupleAdapter(container_type & container)
	: container_(container)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::TupleAdapter<hryky_template_arg>::TupleAdapter(this_type const & rhs)
	: hryky_copy_member(container)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::TupleAdapter<hryky_template_arg>::TupleAdapter(this_type && rhs)
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
  @todo optimizes the repeat for constant times.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::TupleAdapter<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::array::Scope<StreamT> const array(out);
	
	size_t index = 0u;
	for (; Size != index; ++index) {
		out << this->container_[index];
	}
	
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
	return Size;
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
#endif // TUPLE_ARRAY_H_20131015232756644
// end of file
