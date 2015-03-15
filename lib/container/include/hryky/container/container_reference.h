/**
  @file     container_reference.h
  @brief    retains the container and the position as a reference.
  @author   HRYKY
  @version  $Id: container_reference.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef CONTAINER_REFERENCE_H_20130504210512545
#define CONTAINER_REFERENCE_H_20130504210512545
#include "hryky/clear.h"
#include "hryky/definition.h"
#include "hryky/type_traits/add_pointer.h"
#include "hryky/type_traits/as_parameter.h"
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
	/// retains the container and the position as a reference.
	template <hryky_template_param>
	class ContainerReference;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the container and the position as a reference.
 */
template <
	typename ContainerT,
	typename ValueT,
	typename SizeT = ::std::size_t
>
class hryky::ContainerReference :
	public WithStreamOut<ContainerReference<hryky_template_arg> >,
	public WithSwap<ContainerReference<hryky_template_arg> >
{
public :
	typedef ContainerReference<hryky_template_param> this_type;
	typedef ContainerT container_type;
	typedef ValueT value_type;
	typedef SizeT size_type;
	typedef typename AddPointer<container_type>::type container_pointer;
	typedef typename AsParameter<value_type>::type value_param_type;

	/// default constructor.
	ContainerReference();

	/// constructor with parameters.
	ContainerReference(container_pointer const container, size_type const pos);

	/// copy constructor.
	ContainerReference(this_type const &);

	/// move constructor.
	ContainerReference(this_type &&);

	/// destructor.
	~ContainerReference();

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// casts as a value.
	operator value_type() const;

	/// assign other reference as value value.
	this_type & operator=(this_type const & rhs);
	
	/// assigns a new value.
	this_type & operator=(value_param_type value);

	/// retrieves the raw pointer of container.
	container_pointer container() const;

	/// retrieves the position in container.
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
hryky::ContainerReference<hryky_template_arg>::ContainerReference()
	: container_()
	  , pos_()
{
}
/**
  @brief constructor with parameters.
 */
template <hryky_template_param>
hryky::ContainerReference<hryky_template_arg>::ContainerReference(
	container_pointer const container, size_type const pos)
	: container_(container)
	  , pos_(pos)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::ContainerReference<hryky_template_arg>::ContainerReference(
	this_type const & rhs)
	: hryky_copy_member(container)
	  , hryky_copy_member(pos)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::ContainerReference<hryky_template_arg>::ContainerReference(
	this_type && rhs)
	: hryky_move_member(container)
	  , hryky_move_member(pos)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::ContainerReference<hryky_template_arg>::~ContainerReference()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::ContainerReference<hryky_template_arg>::clear()
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
hryky::ContainerReference<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(cotnainer);
	hryky_write_member(pos);

	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::ContainerReference<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(container);
	hryky_swap_member(pos);
}
/**
  @brief casts as a value.
 */
template <hryky_template_param>
hryky::ContainerReference<hryky_template_arg>::operator value_type() const
{
	return this->container_->get(this->pos_);
}
/**
  @brief assigns other instance as value.
 */
template <hryky_template_param>
hryky::ContainerReference<hryky_template_arg> & 
hryky::ContainerReference<hryky_template_arg>::operator=(
	this_type const & rhs)
{
	return this->operator=(static_cast<value_type>(rhs));
}
/**
  @brief assigns a new value.
 */
template <hryky_template_param>
hryky::ContainerReference<hryky_template_arg> & 
hryky::ContainerReference<hryky_template_arg>::operator=(
	value_param_type value)
{
	this->container_->set(this->pos_, value);
	return *this;
}
/**
  @brief retrieves the raw pointer of container.
 */
template <hryky_template_param>
typename hryky::ContainerReference<hryky_template_arg>::container_pointer 
hryky::ContainerReference<hryky_template_arg>::container() const
{
	return this->container_;
}
/**
  @brief retrieves the position in container.
 */
template <hryky_template_param>
typename hryky::ContainerReference<hryky_template_arg>::size_type 
hryky::ContainerReference<hryky_template_arg>::pos() const
{
	return this->pos_;
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
// revokes the temporary macro.
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // CONTAINER_REFERENCE_H_20130504210512545
// end of file
