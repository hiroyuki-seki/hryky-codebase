/**
  @file         scoped_array.h
  @brief        allocates a container used as an array whose size is determined dynamically.
  @author       HRYKY
  @version      $Id: scoped_array.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef SCOPED_ARRAY_H_20120204020838755
#define SCOPED_ARRAY_H_20120204020838755
#include "hryky/clear.h"
#include "hryky/definition.h"
#include "hryky/iterator/iterator_random.h"
#include "hryky/log/log_definition.h"
#include "hryky/without_copy.h"
#include "hryky/nullptr.h"
#include "hryky/with_at.h"
#include "hryky/with_is_null.h"
#include "hryky/with_iteration.h"
#include "hryky/with_iterator.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/is_null.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT, typename DeleterT
#define hryky_template_arg \
	ValueT, DeleterT
#define hryky_iterator \
	hryky::iterator::random::Mutable<ScopedArray<hryky_template_arg>, ValueT>
#define hryky_const_iterator \
	hryky::iterator::random::Immutable<ScopedArray<hryky_template_arg>, ValueT>
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/**
	  allocates a container used as an array whose size is determined
	  dynamically.
	 */
	template <hryky_template_param>
	class ScopedArray;
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief allocates a container used as an array whose size is determined
    dynamically.

  The differences with hryky::Vector are
  - A user is responsible for allocation of an array of instances.
  - The size of array is retained during the lifetime of this instance.
    The size of array is neither extended nor shrinked.

   If the size of array can be determined on compile time, hryky::FixedVector
  is preferable.
 */
template <hryky_template_param>
class hryky::ScopedArray :
	private WithoutCopy,
	public WithIterator<
		ScopedArray<hryky_template_arg>,
		hryky_iterator,
		hryky_const_iterator
	>,
	public WithIteration<
		ScopedArray<hryky_template_arg>,
		hryky_iterator,
		hryky_const_iterator
	>,
	public WithAt<
		ScopedArray<hryky_template_arg>,
		ValueT
	>,
	public WithStreamOut<ScopedArray<hryky_template_arg> >,
	public WithSwap<ScopedArray<hryky_template_arg> >,
	public WithIsNull<ScopedArray<hryky_template_arg> >
{
public :

	typedef ScopedArray<hryky_template_arg>             this_type;
	typedef ValueT                                      value_type;
	typedef ::std::size_t                                 size_type;
	typedef ::std::ptrdiff_t                              difference_type;
	typedef typename AddPointer<ValueT>::type           pointer;
	typedef typename AddReference<ValueT>::type         reference;
	typedef typename AddConstPointer<ValueT>::type      const_pointer;
	typedef typename AddConstReference<ValueT>::type    const_reference;
	typedef DeleterT                                    deleter_type;

	/// default constructor.
	ScopedArray();

	/// constructs with a pointer to the existing array and the size.
	ScopedArray(pointer const ptr, size_type const size);

	/// move constructor.
	ScopedArray(this_type && rhs);

	/// destructor.
	~ScopedArray();

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// assigns a new pointer.
	void reset(pointer const ptr, size_type const size);

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// retrieves the range of data.
	size_type size() const;

	/// retrieves the immutable element of array.
	const_reference operator[](size_type const index) const;

	/// retrieves the mutable element of array.
	reference operator[](size_type const index);

	/// confirms to have an invalid pointer.
	bool is_null() const;

protected :

private :

	typedef WithIteration<
		ScopedArray<hryky_template_arg>,
		hryky_iterator,
		hryky_const_iterator
	> with_iteration;

	hryky_delete_this_copy_constructor(ScopedArray);
	hryky_delete_this_copy_assign_op(ScopedArray);

	DeleterT    deleter_;
	pointer     ptr_;
	size_type   size_;

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::ScopedArray<hryky_template_arg>::ScopedArray()
	: deleter_()
	  , ptr_()
	  , size_()
{
}
/**
  @brief constructs with a pointer to the existing array and the size.
 */
template <hryky_template_param>
hryky::ScopedArray<hryky_template_arg>::ScopedArray(
	pointer const ptr, size_type const size)
	: deleter_()
	  , ptr_(ptr)
	  , size_(size)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::ScopedArray<hryky_template_arg>::ScopedArray(this_type && rhs)
	: hryky_move_member(deleter)
	  , hryky_move_member(ptr)
	  , hryky_move_member(size)
{
	hryky::clear(rhs.ptr_);
	hryky::clear(rhs.size_);
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::ScopedArray<hryky_template_arg>::~ScopedArray()
{
	this->clear();
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::ScopedArray<hryky_template_arg>::clear()
{
	if (!hryky_is_null(this->ptr_)) {
		this->deleter_(this->ptr_, this->size_);
		hryky::clear(this->ptr_);
	}
	hryky::clear(this->size_);
}
/**
  @brief assigns a new pointer.
 */
template <hryky_template_param>
void hryky::ScopedArray<hryky_template_arg>::reset(
	pointer const ptr, size_type const size)
{
	this->clear();
	
	this->ptr_ = ptr;
	this->size_ = size;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::ScopedArray<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(deleter);
	hryky_swap_member(ptr);
	hryky_swap_member(size);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::ScopedArray<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(deleter);
	hryky_write_member(size);

	return this->with_iteration::write_to(out);
}
/**
  @brief retrieves the range of data.
 */
template <hryky_template_param>
typename hryky::ScopedArray<hryky_template_arg>::size_type 
hryky::ScopedArray<hryky_template_arg>::size() const
{
	return this->size_;
}
/**
  @brief retrieves the immutable element of array.
 */
template <hryky_template_param>
typename hryky::ScopedArray<hryky_template_arg>::const_reference 
hryky::ScopedArray<hryky_template_arg>::operator[](
	size_type const index) const
{
	return this->ptr_[index];
}
/**
  @brief retrieves the mutable element of array.
 */
template <hryky_template_param>
typename hryky::ScopedArray<hryky_template_arg>::reference 
hryky::ScopedArray<hryky_template_arg>::operator[](
	size_type const index)
{
	return this->ptr_[index];
}
/**
  @brief confirms to have an invalid pointer.
 */
template <hryky_template_param>
bool hryky::ScopedArray<hryky_template_arg>::is_null() const
{
	return hryky::is_null(this->ptr_);
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// global functions prototype
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
#undef hryky_iterator
#undef hryky_const_iterator
#endif // SCOPED_ARRAY_H_20120204020838755
// end of file
