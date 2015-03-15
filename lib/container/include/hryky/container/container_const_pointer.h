/**
  @file     container_const_pointer.h
  @brief    retains the container and the position as an immutable pointer.
  @author   HRYKY
  @version  $Id: container_const_pointer.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef CONTAINER_CONST_POINTER_H_20130505182349433
#define CONTAINER_CONST_POINTER_H_20130505182349433
#include "hryky/container/container_pointer.h"
#include "hryky/definition.h"
#include "hryky/type_traits/add_const.h"
#include "hryky/type_traits/add_pointer.h"
#include "hryky/with_swap.h"
#include "hryky/with_stream_out.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ContainerT, \
	typename ValueT, \
	typename ReferenceT, \
	typename SizeT
#define hryky_template_arg \
	ContainerT, ValueT, ReferenceT, SizeT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retains the container and the position as an immutable pointer.
	template <hryky_template_param>
	class ContainerConstPointer;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the container and the position as an immutable pointer.
 */
template <
	typename ContainerT,
	typename ValueT,
	typename ReferenceT = typename AddReference<ValueT>::type,
	typename SizeT = ::std::size_t
>
class hryky::ContainerConstPointer :
	public WithStreamOut<ContainerConstPointer<hryky_template_arg> >,
	public WithSwap<ContainerConstPointer<hryky_template_arg> >
{
public :

	typedef ContainerConstPointer<hryky_template_arg> this_type;
	typedef SizeT size_type;
	typedef typename AddConst<ContainerT>::type container_type;
	typedef typename AddPointer<container_type>::type container_pointer;

	typedef ContainerPointer<ContainerT, ReferenceT, SizeT> mutable_type;

	/// default constructor.
	ContainerConstPointer();

	/// constructor with parameters.
	ContainerConstPointer(
		container_pointer const container, size_type const pos);

	/// constructor with a mutable pointer.
	ContainerConstPointer(mutable_type const & src);

	/// copy constructor.
	ContainerConstPointer(this_type const &);

	/// move constructor.
	ContainerConstPointer(this_type &&);

	/// destructor.
	~ContainerConstPointer();

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

protected :

private :
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
hryky::ContainerConstPointer<hryky_template_arg>::ContainerConstPointer()
	: container_()
	  , pos_()
{
}
/**
  @brief constructor with parameters.
 */
template <hryky_template_param>
hryky::ContainerConstPointer<hryky_template_arg>::ContainerConstPointer(
	container_pointer const container, size_type const pos)
	: container_(container)
	  , pos_(pos)
{
}
/**
  @brief constructor with a mutable pointer.
 */
template <hryky_template_param>
hryky::ContainerConstPointer<hryky_template_arg>::ContainerConstPointer(
	mutable_type const & src)
	: container_(src.container())
	  , pos_(src.pos())
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::ContainerConstPointer<hryky_template_arg>::ContainerConstPointer(
	this_type const & rhs)
	: hryky_copy_member(container)
	  , hryky_copy_member(pos)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::ContainerConstPointer<hryky_template_arg>::ContainerConstPointer(
	this_type && rhs)
	: hryky_move_member(container)
	  , hryky_move_member(pos)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::ContainerConstPointer<hryky_template_arg>::~ContainerConstPointer()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::ContainerConstPointer<hryky_template_arg>::clear()
{
	hryky::clear(this->pos_);
	hryky::clear(this->container_);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & 
hryky::ContainerConstPointer<hryky_template_arg>::write_to(
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
void hryky::ContainerConstPointer<hryky_template_arg>::swap(
	this_type & src)
{
	hryky_swap_member(container);
	hryky_swap_member(pos);
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
#endif // CONTAINER_CONST_POINTER_H_20130505182349433
// end of file
