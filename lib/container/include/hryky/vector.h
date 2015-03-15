/**
  @file         vector.h
  @brief        substitutes for ::std::vector container.
  @author       HRYKY
  @version      $Id: vector.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef VECTOR_H_20120225233011645
#define VECTOR_H_20120225233011645
#include "hryky/allocator/allocator_mempool.h"
#include "hryky/debug/debug_common.h"
#include "hryky/foreach.h"
#include "hryky/iterator/iterator_random.h"
#include "hryky/memory/memory_common.h"
#include "hryky/nullptr.h"
#include "hryky/mempool/mempool_global_registry.h"
#include "hryky/pragma.h"
#include "hryky/range.h"
#include "hryky/repeat.h"
#include "hryky/stream/stream_definition.h"
#include "hryky/swap.h"
#include "hryky/type_traits/add_const_pointer.h"
#include "hryky/type_traits/add_const_reference.h"
#include "hryky/type_traits/add_pointer.h"
#include "hryky/type_traits/add_reference.h"
#include "hryky/with_at.h"
#include "hryky/with_iteration.h"
#include "hryky/with_iterator.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/container/container_constructor_normal.h"
#include "hryky/is_null.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_padded
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT, typename AllocatorT, typename ConstructorT
#define hryky_template_arg \
	ValueT, AllocatorT, ConstructorT
/**
  The definition of vector::resize() with variadic parameters.
 */
#define hryky_vector_resize(...) {\
	size_type const pre_size = this->size();\
	\
	if (pre_size == size) {\
		return true;\
	}\
\
	if (pre_size < size) {\
		if (!this->reserve(size)) {\
			return false;\
		}\
\
		ConstructorT::construct(\
			this->allocator_,\
			&this->buffer_[pre_size],\
			&this->buffer_[size],\
			__VA_ARGS__);\
	}\
	else {\
		ConstructorT::destroy(\
			this->allocator_,\
			&this->buffer_[size],\
			&this->buffer_[pre_size]);\
	}\
	this->size_ = size;\
}
#define hryky_iterator \
	hryky::iterator::random::Mutable<Vector<ValueT, AllocatorT>, ValueT>
#define hryky_const_iterator \
	hryky::iterator::random::Immutable<Vector<ValueT, AllocatorT>, ValueT >
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// substitutes for ::std::vector container.
	template <
		typename ValueT,
		typename AllocatorT = allocator::Mempool<ValueT>,
		typename ConstructorT = container::constructor::Normal
	>
	class Vector;

}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief substitutes for ::std::vector container.
 */
template <hryky_template_param>
class hryky::Vector :
	public WithIterator<
		Vector<hryky_template_arg>,
		hryky_iterator,
		hryky_const_iterator >,
	public WithIteration<
		Vector<hryky_template_arg>,
		hryky_iterator,
		hryky_const_iterator >,
	public WithAt<
		Vector<hryky_template_arg>,
		ValueT>,
	public WithStreamOut<Vector<hryky_template_arg> >,
	public WithSwap<Vector<hryky_template_arg> >
{
public :

	typedef hryky::Vector<hryky_template_arg>           this_type;
	typedef ValueT                                      value_type;
	typedef typename AddPointer<ValueT>::type           pointer;
	typedef typename AddReference<ValueT>::type         reference;
	typedef typename AddConstPointer<ValueT>::type      const_pointer;
	typedef typename AddConstReference<ValueT>::type    const_reference;
	typedef ::std::size_t                               size_type;
	typedef ::std::ptrdiff_t                            difference_type;
	typedef AllocatorT                                  allocator_type;

	/// default constructor.
	Vector();

	/// copy constructor.
	Vector(this_type const & rhs);

	/// move constructor.
	Vector(this_type && rhs);

	/// constructor with allocator.
	Vector(allocator_type const & allocator);

	/// constructs with the range between two iterators.
	template <typename InputIteratorT>
	Vector(
		InputIteratorT begin, InputIteratorT end);

	/// constructs with the range between two iterators and allocator.
	template <typename InputIteratorT>
	Vector(
		InputIteratorT begin,
		InputIteratorT end,
		allocator_type const & allocator);

	/// destructor.
	~Vector();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// retrieves the number of elements.
	size_type size() const;

	/// retrieves the maximum number of allocatable elements.
	size_type max_size() const;

	/**
	  retrieves the number of elements that is able to be held without
	  additional memory allocation
	 */
	size_type capacity() const;

	/// confirms whether container has no element.
	bool empty() const;

	/**
	  @brief    allocates memory
	  @return   success and failure
	 */
	bool reserve(size_type const capacity);

	/// retrieves the mutable element with offset.
	reference operator[](size_type const index);

	/// retrieves the immutable element with offset.
	const_reference operator[](size_type const index) const;

	/// assigns the multiple elements between [begin,end).
	template < typename InputIteratorT >
	bool assign(InputIteratorT begin, InputIteratorT end);
	
	/// assigns the copies of an element.
	bool assign(size_type size, const_reference value);

	/// adds the element into the end of container.
	bool push_back(const_reference src);

	/// appends an element at the end of the container by rvalue reference.
	bool push_back(value_type && src);

	/// removes the last element.
	bool pop_back();

	/// inserts an element before the element at the indicated iterator.
	iterator insert(iterator position, const_reference value);

	/// inserts the elements between two input iterator.
	template < typename InputIteratorT >
	bool insert(iterator position, InputIteratorT first, InputIteratorT last);

	/// removes some elements between two iterators.
	iterator erase(iterator first, iterator last);

	/// expands or shrinks the length of the container.
	bool resize(size_type const size);

	/**
	  @brief expands or shrinks the length of the container with an argument.
	  This interface doesn't conform the ::std::vector.
	 */
	template <typename Arg1T>
	bool resize(size_type const size, Arg1T && arg1);
	
	/**
	  @brief expands or shrinks the length of the container with two arguments.
	  This interface doesn't conform the ::std::vector.
	 */
	template <typename Arg1T, typename Arg2T>
	bool resize(size_type const size, Arg1T && arg1, Arg2T && arg2);
	
	/// makes the container empty.
	bool clear();

	/// interchanges all internal values.
	void swap(this_type & src);

	/// retrieves the allocator of this instance.
	allocator_type get_allocator() const;

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

private :

	typedef WithIteration<
		Vector<hryky_template_arg>,
		hryky_iterator,
		hryky_const_iterator > with_iteration;

	allocator_type      allocator_;
	pointer             buffer_;
	size_type           capacity_;
	size_type           size_;

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::Vector<hryky_template_arg>::Vector()
	: allocator_()
	  , buffer_()
	  , capacity_()
	  , size_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::Vector<hryky_template_arg>::Vector(this_type const & rhs)
	: hryky_copy_member(allocator)
	  , buffer_()
	  , capacity_()
	  , size_()
{
	if (!this->reserve(rhs.size())) {
		return;
	}

	rhs.foreach_at([this](const_reference rhs_value, size_type const index) {
		this->allocator_.construct(&this->buffer_[index], rhs_value);
	});

	this->size_ = rhs.size();
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::Vector<hryky_template_arg>::Vector(this_type && rhs)
	: allocator_()
	  , buffer_()
	  , capacity_()
	  , size_()
{
	this->swap(rhs);
}
/**
  @brief constructor with allocator.
 */
template <hryky_template_param>
hryky::Vector<hryky_template_arg>::Vector(allocator_type const & allocator)
	: allocator_(allocator)
	  , buffer_()
	  , capacity_()
	  , size_()
{
}
/**
  @brief constructs with the range between two iterators.
 */
template <hryky_template_param>
template <typename InputIteratorT>
hryky::Vector<hryky_template_arg>::Vector(
	InputIteratorT begin, InputIteratorT end)
	: allocator_()
	  , buffer_()
	  , capacity_()
	  , size_()
{
	this->assign(begin, end);
}
/**
  @brief constructs with the range between two iterators and allocator.
 */
template <hryky_template_param>
template <typename InputIteratorT>
hryky::Vector<hryky_template_arg>::Vector(
	InputIteratorT begin,
	InputIteratorT end,
	allocator_type const & allocator)
	: allocator_(allocator)
	  , buffer_()
	  , capacity_()
	  , size_()
{
	this->assign(begin, end);
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::Vector<hryky_template_arg>::~Vector()
{
	if (hryky_is_null(this->buffer_)) {
		return;
	}

	ConstructorT::destroy(this->allocator_, this->begin(), this->end());
	
	this->allocator_.deallocate(this->buffer_, this->capacity_);
	this->buffer_ = hryky_nullptr;
	this->size_ = 0;
	this->capacity_ = 0;
}
/**
  @brief retrieves the number of elements.
 */
template <hryky_template_param>
typename hryky::Vector<hryky_template_arg>::size_type
hryky::Vector<hryky_template_arg>::size() const
{
	return this->size_;
}
/**
  @brief retrieves the maximum number of allocatable elements.
 */
template <hryky_template_param>
typename hryky::Vector<hryky_template_arg>::size_type
hryky::Vector<hryky_template_arg>::max_size() const
{
	return this->allocator_.max_size();
}
/**
  retrieves the number of elements that is able to be held without
  additional memory allocation
 */
template <hryky_template_param>
typename hryky::Vector<hryky_template_arg>::size_type
hryky::Vector<hryky_template_arg>::capacity() const
{
	return this->capacity_;
}
/**
  @brief confirms whether container has no element.
 */
template <hryky_template_param>
bool hryky::Vector<hryky_template_arg>::empty() const
{
	return 0 == this->size_;
}
/**
  @brief    allocates memory
  @return   success and failure
 */
template <hryky_template_param>
bool hryky::Vector<hryky_template_arg>::reserve(
	size_type const capacity)
{
	if (this->capacity_ >= capacity) {
		return true;
	}

	pointer const buffer
		= this->allocator_.allocate(capacity);

	if (hryky_is_null(buffer)) {
		return false;
	}

	if (0 != this->size_) {
		hryky::memcpy(
			buffer,
			this->buffer_,
			sizeof(value_type) * this->size_);
	}

	if (!hryky_is_null(this->buffer_)) {
		this->allocator_.deallocate(
			this->buffer_, this->capacity_);
	}

	this->buffer_ = buffer;
	this->capacity_ = capacity;

	return true;
}
/**
  @brief retrieves the mutable element with offset.
 */
template <hryky_template_param>
typename hryky::Vector<hryky_template_arg>::reference
hryky::Vector<hryky_template_arg>::operator[](
	size_type const index)
{
	return this->buffer_[index];
}
/**
  @brief retrieves the immutable element with offset.
 */
template <hryky_template_param>
typename hryky::Vector<hryky_template_arg>::const_reference
hryky::Vector<hryky_template_arg>::operator[](
	size_type const index) const
{
	return this->buffer_[index];
}
/**
  @brief assigns the multiple elements between [begin,end).
 */
template <hryky_template_param>
template < typename InputIteratorT >
bool hryky::Vector<hryky_template_arg>::assign(
	InputIteratorT begin, InputIteratorT end)
{
	typedef ::std::iterator_traits<InputIteratorT> iterator_traits;
	
	iterator_traits::difference_type const size = 
		::std::distance(begin, end);

	if (0 > size) {
		hryky_throw(
			::std::invalid_argument,
			"The range of sources is invalid."
			<< " : difference " << size,
			return false);
	}

	if (!this->reserve(static_cast<size_type>(size))) {
		return false;
	}

	this->resize(0);

	hryky::range(begin, end).foreach_at([this](
		iterator_traits::reference ref, size_type const index) {
		this->allocator_.construct(&this->buffer_[index], ref);
	});
	this->size_ = static_cast<size_type>(size);

	return true;
}
/**
  @brief assigns the copies of an element.
 */
template <hryky_template_param>
bool hryky::Vector<hryky_template_arg>::assign(
	size_type size, const_reference value)
{
	if (!this->reserve(size)) {
		return false;
	}

	this->resize(0);

	hryky::repeat(size).foreach_at([this, &value](size_type const index) {
		this->allocator_.construct(&this->buffer_[index], value);
	});
	this->size_ = size;

	return true;
}
/**
  @brief adds the element into the end of container.
 */
template <hryky_template_param>
bool hryky::Vector<hryky_template_arg>::push_back(const_reference src)
{
	if (this->size_ == this->capacity_) {
		if (!this->reserve((this->capacity_ + 1) << 1)) {
			return false;
		}
	}

	this->allocator_.construct(&this->buffer_[this->size_], src);
	++this->size_;

	return true;
}
/**
  @brief appends an element at the end of the container by rvalue reference.
 */
template <hryky_template_param>
bool hryky::Vector<hryky_template_arg>::push_back(value_type && src)
{
	if (this->size_ == this->capacity_) {
		if (!this->reserve((this->capacity_ + 1) << 1)) {
			return false;
		}
	}

	this->allocator_.construct(
		&this->buffer_[this->size_], ::std::forward<value_type>(src));
	++this->size_;

	return true;
}
/**
  @brief removes the last element.
 */
template <hryky_template_param>
bool hryky::Vector<hryky_template_arg>::pop_back()
{
	if (this->empty()) {
		return false;
	}

	ConstructorT::destroy(
		this->allocator_, &this->buffer_[this->size_ - 1]);
	--this->size_;

	return true;
}
/**
  @brief inserts an element before the element at the indicated iterator.
 */
template <hryky_template_param>
typename hryky::Vector<hryky_template_arg>::iterator
hryky::Vector<hryky_template_arg>::insert(
	iterator position, const_reference value)
{
	if (this->begin() > position || this->end() < position) {
		hryky_throw(
			::std::out_of_range,
			"The position to which sources are inserted is invalid."
			<< " : position " << ::std::distance(this->begin(), position)
			<< " : size " << this->size(),
			return this->end());
	}

	/// @attention reserve() can invalidate @a position.
	size_type const inserted_index = static_cast<size_type>(
		position - this->begin());
	
	if (!this->reserve(this->size_ + 1)) {
		return this->end();
	}

	size_type const moved_size = this->size_ - inserted_index;

	if (0 < moved_size) {
		hryky::memmove(
			&this->buffer_[inserted_index + 1],
			&this->buffer_[inserted_index],
			sizeof(value_type) * moved_size);
	}
	this->allocator_.construct(&this->buffer_[inserted_index], value);
	++this->size_;

	return this->begin() + static_cast<difference_type>(inserted_index);
}
/**
  @brief inserts the elements between two input iterator.
 */
template <hryky_template_param>
template < typename InputIteratorT >
bool hryky::Vector<hryky_template_arg>::insert(
	iterator position, InputIteratorT first, InputIteratorT last)
{
	if (this->begin() > position || this->end() < position) {
		hryky_throw(
			::std::out_of_range,
			"The position to which sources are inserted is invalid."
			<< " : position " << ::std::distance(this->begin(), position)
			<< " : size " << this->size(),
			return false);
	}

	typedef ::std::iterator_traits<InputIteratorT> iterator_traits;

	iterator_traits::difference_type const inserted_size = 
		::std::distance(first, last);

	if (0 > inserted_size) {
		hryky_throw(
			::std::invalid_argument,
			"The range of sources is invalid."
			<< " : difference " << inserted_size,
			return false);
	}

	if (0 == inserted_size) {
		return true;
	}

	/// @attention reserve() can invalidate @a position.
	size_type const inserted_index = static_cast<size_type>(
		::std::distance(this->begin(), position));
	
	if (!this->reserve(this->size_ + inserted_size)) {
		return false;
	}

	size_type const moved_size = this->size_ - inserted_index;

	if (0 < moved_size) {
		hryky::memmove(
			&this->buffer_[inserted_index + inserted_size],
			&this->buffer_[inserted_index],
			sizeof(value_type) * moved_size);
	}

	hryky::range(first, last).foreach_at([this, inserted_index](
		iterator_traits::reference ref, size_type const index) {
		this->allocator_.construct(
			&this->buffer_[inserted_index + index], ref);
	});
	this->size_ += inserted_size;

	return true;
}
/**
  @brief removes some elements between two iterators.
 */
template <hryky_template_param>
typename hryky::Vector<hryky_template_arg>::iterator
hryky::Vector<hryky_template_arg>::erase(iterator first, iterator last)
{
	if (this->begin() > first
		 || this->end() < first
		 || this->begin() > last
		 || this->end() < last) {
		hryky_throw(
			::std::out_of_range,
			"argument 'first' or 'last' exceeds the range of this instance"
			<< " : first " << (first - this->begin())
			<< " : last " << (last - this->begin())
			<< " : size " << this->size(),
			return this->end());
	}

	difference_type const size = last - first;
	if (0 >= size) {
		hryky_throw(
			::std::invalid_argument,
			"the first iterator exceeds the last iterator"
			<< " : difference " << size,
			return this->end());
	}

	size_type const pos         = first - this->begin();
	size_type const moved_size  = this->size() - (pos + size);

	if (0 != moved_size) {
		hryky::memmove(
			this->buffer_ + pos,
			this->buffer_ + pos + size,
			moved_size * sizeof(value_type));
	}

	this->size_ -= size;

	return iterator(this, pos);
}
/**
  @brief expands or shrinks the length of the container.
 */
template <hryky_template_param>
bool hryky::Vector<hryky_template_arg>::resize(size_type const size)
{
	size_type const pre_size = this->size();
	
	if (pre_size == size) {
		return true;
	}

	if (pre_size < size) {
		if (!this->reserve(size)) {
			return false;
		}

		ConstructorT::construct(
			this->allocator_,
			&this->buffer_[pre_size],
			&this->buffer_[size]);
	}
	else {
		ConstructorT::destroy(
			this->allocator_,
			&this->buffer_[size],
			&this->buffer_[pre_size]);
	}
	this->size_ = size;

	return true;
}
/**
  @brief expands or shrinks the length of the container with an argument.
  This interface doesn't conform the ::std::vector.
 */
template <hryky_template_param>
template <typename Arg1T>
bool hryky::Vector<hryky_template_arg>::resize(
	size_type const size, Arg1T && arg1)
{
	hryky_vector_resize(::std::forward<Arg1T>(arg1));

	return true;
}
/**
  @brief expands or shrinks the length of the container with two arguments.
  This interface doesn't conform the ::std::vector.
 */
template <hryky_template_param>
template <typename Arg1T, typename Arg2T>
bool hryky::Vector<hryky_template_arg>::resize(
	size_type const size, Arg1T && arg1, Arg2T && arg2)
{
	hryky_vector_resize(
		::std::forward<Arg1T>(arg1),
		::std::forward<ARg2T>(arg2));

	return true;
}
/**
  @brief makes the container empty.
 */
template <hryky_template_param>
bool hryky::Vector<hryky_template_arg>::clear()
{
	return this->resize(0);
}
/**
  @brief interchanges all internal values.
 */
template <hryky_template_param>
void hryky::Vector<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(allocator);
	hryky_swap_member(buffer);
	hryky_swap_member(capacity);
	hryky_swap_member(size);
}
/**
  @brief retrieves the allocator of this instance.
 */
template <hryky_template_param>
typename hryky::Vector<hryky_template_arg>::allocator_type 
hryky::Vector<hryky_template_arg>::get_allocator() const
{
	return this->allocator_;
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::Vector<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(size);
	hryky_write_member(capacity);

	return this->with_iteration::write_to(out);
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
#undef hryky_vector_resize
#undef hryky_iterator
#undef hryky_const_iterator
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // VECTOR_H_20120225233011645
// end of file
