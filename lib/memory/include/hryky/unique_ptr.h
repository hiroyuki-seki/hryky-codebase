/**
  @file     unique_ptr.h
  @brief    deletes the instance at the end of the scope.
  @author   HRYKY
  @version  $Id: unique_ptr.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef UNIQUE_PTR_H_20140121164720366
#define UNIQUE_PTR_H_20140121164720366
#include "hryky/without_copy.h"
#include "hryky/clear.h"
#include "hryky/type_traits/add_pointer.h"
#include "hryky/type_traits/as_parameter.h"
#include "hryky/with_is_null.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/is_null.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ElementT, typename DeleterT
#define hryky_template_arg \
	ElementT, DeleterT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// deletes the instance at the end of the scope.
	template <hryky_template_param>
	class UniquePtr;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief deletes the instance at the end of the scope.
 */
template <hryky_template_param>
class hryky::UniquePtr :
	private WithoutCopy,
	public WithStreamOut<UniquePtr<hryky_template_arg> >,
	public WithSwap<UniquePtr<hryky_template_arg> >,
	public WithIsNull<UniquePtr<hryky_template_arg> >
{
public :
	typedef UniquePtr<hryky_template_arg>           this_type;
	typedef ElementT                                element_type;
	typedef typename AddPointer<ElementT>::type     pointer;
	typedef DeleterT                                deleter_type;
	typedef typename AsParameter<DeleterT>::type    deleter_param_type;

	/// default constructor.
	UniquePtr();

	/// constructs with the released instance and the deleter.
	UniquePtr(pointer const ptr, deleter_param_type deleter);

	/// constructs with the released instance.
	UniquePtr(pointer const ptr);

	/// move constructor.
	UniquePtr(this_type &&);

	/// destructor.
	~UniquePtr();

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// brings out the internal pointer.
	pointer release();

	/// retrieves the raw pointer.
	pointer get() const;

	/// deletes the current instance and assigns a new instance.
	void reset(pointer const ptr = pointer());

	/// confirms whether the internal pointer is null.
	bool is_null() const;

protected :

private :
	hryky_delete_this_copy_constructor(UniquePtr);
	hryky_delete_this_copy_assign_op(UniquePtr);

	DeleterT deleter_;
	pointer ptr_;

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
hryky::UniquePtr<hryky_template_arg>::UniquePtr()
	: deleter_()
	  , ptr_()
{
}
/**
  @brief constructs with the released instance and the deleter.
 */
template <hryky_template_param>
hryky::UniquePtr<hryky_template_arg>::UniquePtr(
	pointer const ptr, deleter_param_type deleter)
	: deleter_(deleter)
	  , ptr_(ptr)
{
}
/**
  @brief constructs with the released instance.
 */
template <hryky_template_param>
hryky::UniquePtr<hryky_template_arg>::UniquePtr(pointer const ptr)
	: deleter_()
	  , ptr_(ptr)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::UniquePtr<hryky_template_arg>::UniquePtr(
	this_type && rhs)
	: hryky_move_member(deleter)
	  , hryky_move_member(ptr)
{
	hryky::clear(rhs.ptr_);
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::UniquePtr<hryky_template_arg>::~UniquePtr()
{
	this->reset();
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::UniquePtr<hryky_template_arg>::clear()
{
	if (!hryky_is_null(this->ptr_)) {
		this->deleter_(this->ptr_);
		hryky::clear(this->ptr_);
	}
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::UniquePtr<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(deleter);
	hryky_write_member(ptr);

	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::UniquePtr<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(deleter);
	hryky_swap_member(ptr);
}
/**
  @brief brings out the internal pointer.
 */
template <hryky_template_param>
typename hryky::AddPointer<ElementT>::type
hryky::UniquePtr<hryky_template_arg>::release()
{
	pointer const ptr = this->ptr_;
	hryky::clear(this->ptr_);
	return ptr;
}
/**
  @brief retrieves the raw pointer.
 */
template <hryky_template_param>
typename hryky::AddPointer<ElementT>::type
hryky::UniquePtr<hryky_template_arg>::get() const
{
	return this->ptr_;
}
/**
  @brief deletes the current instance and assigns a new instance.
 */
template <hryky_template_param>
void hryky::UniquePtr<hryky_template_arg>::reset(pointer const ptr)
{
	if (!hryky_is_null(this->ptr_)) {
		this->deleter_(this->ptr_);
	}

	this->ptr_ = ptr;
}
/**
  @brief confirms whether the internal pointer is null.
 */
template <hryky_template_param>
bool hryky::UniquePtr<hryky_template_arg>::is_null() const
{
	return hryky_is_null(this->get());
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
	/// instantiates UniquePtr.
	template <hryky_template_param>
	UniquePtr<hryky_template_arg> unique_ptr(
		ElementT * const ptr,
		DeleterT const & deleter);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief instantiates UniquePtr.
 */
template <hryky_template_param>
hryky::UniquePtr<hryky_template_arg>
hryky::unique_ptr(
	ElementT * const ptr,
	DeleterT const & deleter)
{
	return UniquePtr<hryky_template_arg>(ptr, deleter);
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // UNIQUE_PTR_H_20140121164720366
// end of file
