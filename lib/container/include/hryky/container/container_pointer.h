/**
  @file     container_pointer.h
  @brief    retains the container and the position as a pointer.
  @author   HRYKY
  @version  $Id: container_pointer.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef CONTAINER_POINTER_H_20130504210220543
#define CONTAINER_POINTER_H_20130504210220543
#include "hryky/definition.h"
#include "hryky/type_traits/add_pointer.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
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
	/// retains the container and the position as a pointer.
	template <hryky_template_param>
	class ContainerPointer;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the container and the position as a pointer.
 */
template <
	typename ContainerT,
	typename ValueT,
	typename ReferenceT = typename AddReference<ValueT>::type,
	typename SizeT = ::std::size_t
>
class hryky::ContainerPointer :
	public WithStreamOut<ContainerPointer<hryky_template_arg> >,
	public WithSwap<ContainerPointer<hryky_template_arg> >
{
public :
	typedef ContainerPointer<hryky_template_arg> this_type;
	typedef ContainerT cotnainer_type;
	typedef SizeT size_type;
	typedef typename AddPointer<cotnainer_type>::type container_pointer;

	/// default constructor.
	ContainerPointer();

	/// constructor with parameters.
	ContainerPointer(
		container_pointer const container, size_type const pos);

	/// copy constructor.
	ContainerPointer(this_type const &);

	/// move constructor.
	ContainerPointer(this_type &&);

	/// destructor.
	~ContainerPointer();

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

	/// dereferences the pointer.
	ReferenceT operator*() const;

	/// retrieves the pointer of the container.
	container_pointer container() const;

	/// retrieves the position in the container.
	size_type pos() const;

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
hryky::ContainerPointer<hryky_template_arg>::ContainerPointer()
	: container_()
	  , pos_()
{
}
/**
  @brief constructor with parameters.
 */
template <hryky_template_param>
hryky::ContainerPointer<hryky_template_arg>::ContainerPointer(
	container_pointer const container, size_type const pos)
	: container_(container)
	  , pos_(pos)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::ContainerPointer<hryky_template_arg>::ContainerPointer(
	this_type const & rhs)
	: hryky_copy_member(container)
	  , hryky_copy_member(pos)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::ContainerPointer<hryky_template_arg>::ContainerPointer(
	this_type && rhs)
	: hryky_move_member(container)
	  , hryky_move_member(pos)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::ContainerPointer<hryky_template_arg>::~ContainerPointer()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::ContainerPointer<hryky_template_arg>::clear()
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
hryky::ContainerPointer<hryky_template_arg>::write_to(
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
void hryky::ContainerPointer<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(container);
	hryky_swap_member(pos);
}
/**
  @brief retrieves the pointer of the container.
 */
template <hryky_template_param>
typename hryky::ContainerPointer<hryky_template_arg>::container_pointer 
hryky::ContainerPointer<hryky_template_arg>::container() const
{
	return this->container_;
}
/**
  @brief retrieves the position in the container.
 */
template <hryky_template_param>
typename hryky::ContainerPointer<hryky_template_arg>::size_type 
hryky::ContainerPointer<hryky_template_arg>::pos() const
{
	return this->pos_;
}
/**
  @brief dereferences the pointer.
 */
template <hryky_template_param>
ReferenceT
hryky::ContainerPointer<hryky_template_arg>::operator*() const
{
	return ReferneceT(this->container_, this->pos_);
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
#endif // CONTAINER_POINTER_H_20130504210220543
// end of file
