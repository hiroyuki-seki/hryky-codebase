/**
  @file     container_const_reference.h
  @brief    retains the container and the position as a immutable reference.
  @author   HRYKY
  @version  $Id: container_const_reference.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef CONTAINER_CONST_REFERENCE_H_20130504210906547
#define CONTAINER_CONST_REFERENCE_H_20130504210906547
#include "hryky/type_traits/add_const.h"
#include "hryky/type_traits/add_pointer.h"
#include "hryky/container/container_reference.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ContainerT, \
	typename ValueT, \
	typename SizeT
#define hryky_template_arg \
	ContainerT, ValueT, SizeT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retains the container and the position as a immutable reference.
	template <hryky_template_param>
	class ContainerConstReference;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the container and the position as a immutable reference.
 */
template <
	typename ContainerT,
	typename ValueT,
	typename SizeT = typename ::std::size_t
>
class hryky::ContainerConstReference :
	public WithStreamOut<ContainerConstReference<hryky_template_arg> >,
	public WithSwap<ContainerConstReference<hryky_template_arg> >
{
public :
	typedef ContainerConstReference<hryky_template_arg> this_type;
	typedef typename AddConst<ContainerT>::type container_type;
	typedef SizeT size_type;
	typedef ValueT value_type;
	typedef typename AddPointer<container_type>::type container_pointer;

	typedef ContainerReference<ContainerT, ValueT, SizeT> mutable_type;

	/// default constructor.
	ContainerConstReference();

	/// constructor with parameters.
	ContainerConstReference(
		container_pointer const container, size_type const pos);

	/// constructor with a mutable type.
	ContainerConstReference(mutable_type const & rhs);

	/// copy constructor.
	ContainerConstReference(this_type const &);

	/// move constructor.
	ContainerConstReference(this_type &&);

	/// destructor.
	~ContainerConstReference();

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// retrieves the value at the specified position in this container.
	operator value_type() const;

private :

	hryky_delete_this_copy_assign_op(ContainerConstReference);
	
	container_pointer container_;
	size_type pos_;

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
hryky::ContainerConstReference<hryky_template_arg>::ContainerConstReference()
	: container_()
	  , pos_()
{
}
/**
  @brief constructor with parameters.
 */
template <hryky_template_param>
hryky::ContainerConstReference<hryky_template_arg>::ContainerConstReference(
	container_pointer const container, size_type const pos)
	: container_(container), pos_(pos)
{
}
/**
  @brief constructor with a mutable type.
 */
template <hryky_template_param>
hryky::ContainerConstReference<hryky_template_arg>::ContainerConstReference(
	mutable_type const & rhs)
	: container_(rhs.container())
	  , pos_(rhs.pos())
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::ContainerConstReference<hryky_template_arg>::ContainerConstReference(
	this_type const & rhs)
	: hryky_copy_member(container)
	  , hryky_copy_member(pos)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::ContainerConstReference<hryky_template_arg>::ContainerConstReference(
	this_type && rhs)
	: hryky_move_member(container)
	  , hryky_move_member(pos)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>

hryky::ContainerConstReference<hryky_template_arg>::~ContainerConstReference()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::ContainerConstReference<hryky_template_arg>::clear()
{
	hryky::clear(this->container_);
	hryky::clear(this->pos_);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & 
hryky::ContainerConstReference<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(container);
	hryky_write_member(pos);
	
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::ContainerConstReference<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(container);
	hryky_swap_member(pos);
}
/**
  @brief retrieves the value at the specified position in this container.
 */
template <hryky_template_param>
hryky::ContainerConstReference<hryky_template_arg>::operator value_type() const
{
	return this->container_->get(this->pos_);
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
#endif // CONTAINER_CONST_REFERENCE_H_20130504210906547
// end of file
