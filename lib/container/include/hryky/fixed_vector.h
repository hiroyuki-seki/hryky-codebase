/**
  @file         fixed_vector.h
  @brief        vector of fixed size on compile time.
  @author       HRYKY
  @version      $Id: fixed_vector.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef FIXED_VECTOR_H_20120805214745574
#define FIXED_VECTOR_H_20120805214745574
#include "hryky/allocator/allocator_base.h"
#include "hryky/array.h"
#include "hryky/capacity_of.h"
#include "hryky/container/container_constructor_assign.h"
#include "hryky/foreach.h"
#include "hryky/with_at.h"
#include "hryky/with_iteration.h"
#include "hryky/with_iterator.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT, size_t Capacity, typename ConstructorT
#define hryky_template_arg \
	ValueT, Capacity, ConstructorT
#define hryky_iterator \
	hryky::iterator::random::Mutable< \
		FixedVector<hryky_template_arg>, \
		ValueT, \
		hryky_pointer, \
		hryky_reference, \
		hryky_size_type, \
		hryky_difference_type >
#define hryky_const_iterator \
	hryky::iterator::random::Immutable< \
		FixedVector<hryky_template_arg>, \
		ValueT, \
		hryky_pointer, \
		hryky_reference, \
		hryky_const_pointer, \
		hryky_const_reference, \
		hryky_size_type, \
		hryky_difference_type >
#define hryky_pointer \
	typename AddPointer<ValueT>::type
#define hryky_reference \
	typename AddReference<ValueT>::type
#define hryky_const_pointer \
	typename AddConstPointer<ValueT>::type
#define hryky_const_reference \
	typename AddConstReference<ValueT>::type
#define hryky_size_type \
	typename UnsignedEnoughUint<Capacity>::type
#define hryky_difference_type \
	typename SignedEnoughInt<Capacity>::type
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// vector of fixed size on compile time.
	template <
		typename ValueT,
		size_t Capacity,
		typename ConstructorT = container::constructor::Assign
	>
	class FixedVector;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief vector of fixed size on compile time.
 */
template <hryky_template_param>
class hryky::FixedVector :
	public WithIterator<
		FixedVector<hryky_template_arg>,
		hryky_iterator,
		hryky_const_iterator >,
	public WithIteration<
		FixedVector<hryky_template_arg>,
		hryky_iterator,
		hryky_const_iterator >,
	public WithAt<
		FixedVector<hryky_template_arg>,
		ValueT,
		hryky_reference,
		hryky_const_reference,
		hryky_size_type >,
	public WithStreamOut<FixedVector<hryky_template_arg> >,
	public WithSwap<FixedVector<hryky_template_arg> >
{
public :
	typedef FixedVector<hryky_template_arg> this_type;
	typedef ValueT                          value_type;
	typedef hryky_pointer                   pointer;
	typedef hryky_reference                 reference;
	typedef hryky_const_pointer             const_pointer;
	typedef hryky_const_reference           const_reference;
	typedef hryky_size_type                 size_type;
	typedef hryky_difference_type           difference_type;

	/// default constructor.
	FixedVector();

	/// copy constructor.
	FixedVector(this_type const & rhs);

	/// move constructor.
	FixedVector(this_type && rhs);

	/// constructs with the range between two iterators.
	template <typename InputIteratorT>
	FixedVector(InputIteratorT begin, InputIteratorT end);

	/// destructor.
	~FixedVector();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// retrieves the number of elements.
	size_type size() const;

	/**
	  retrieves the number of elements that is able to be held without
	  additional memory allocation
	 */
	size_type capacity() const;

	/// confirms whether container has no element.
	bool empty() const;

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

	/// makes the container empty.
	bool clear();

	/// interchanges all internal values.
	void swap(this_type & src);

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

private :

	typedef WithIteration<
		FixedVector<hryky_template_arg>,
		hryky_iterator,
		hryky_const_iterator
	> with_iteration;

	Array<ValueT,Capacity>  buffer_;
	size_type               size_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief retrieves the capacity of FixedVector.
 */
template <hryky_template_param, typename RetT>
class CapacityOf<FixedVector<hryky_template_arg>, RetT>
{
public :

	static RetT const value = Capacity;

};
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::FixedVector<hryky_template_arg>::FixedVector()
	: buffer_()
	  , size_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::FixedVector<hryky_template_arg>::FixedVector(this_type const & rhs)
	: buffer_()
	  , size_(rhs.size())
{
	rhs.foreach_at([this](const_reference rhs_value, size_type const index) {
		this->buffer_[index] = rhs_value;
	});
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::FixedVector<hryky_template_arg>::FixedVector(this_type && rhs)
	: hryky_move_member(buffer)
	  , hryky_move_member(size)
{
}
/**
  @brief constructs with the range between two iterators.
 */
template <hryky_template_param>
template <typename InputIteratorT>
hryky::FixedVector<hryky_template_arg>::FixedVector(
	InputIteratorT begin, InputIteratorT end)
	: buffer_()
	  , size_()
{
	this->assign(begin, end);
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::FixedVector<hryky_template_arg>::~FixedVector()
{
}
/**
  @brief retrieves the number of elements.
 */
template <hryky_template_param>
typename hryky::FixedVector<hryky_template_arg>::size_type
hryky::FixedVector<hryky_template_arg>::size() const
{
	return this->size_;
}
/**
  retrieves the number of elements that is able to be held without
  additional memory allocation
 */
template <hryky_template_param>
typename hryky::FixedVector<hryky_template_arg>::size_type
hryky::FixedVector<hryky_template_arg>::capacity() const
{
	return Capacity;
}
/**
  @brief confirms whether container has no element.
 */
template <hryky_template_param>
bool hryky::FixedVector<hryky_template_arg>::empty() const
{
	return 0 == this->size_;
}
/**
  @brief retrieves the mutable element with offset.
 */
template <hryky_template_param>
typename hryky::FixedVector<hryky_template_arg>::reference
hryky::FixedVector<hryky_template_arg>::operator[](
	size_type const index)
{
	return this->buffer_[index];
}
/**
  @brief retrieves the immutable element with offset.
 */
template <hryky_template_param>
typename hryky::FixedVector<hryky_template_arg>::const_reference
hryky::FixedVector<hryky_template_arg>::operator[](
	size_type const index) const
{
	return this->buffer_[index];
}
/**
  @brief assigns the multiple elements between [begin,end).
 */
template <hryky_template_param>
template < typename InputIteratorT >
bool hryky::FixedVector<hryky_template_arg>::assign(
	InputIteratorT begin, InputIteratorT end)
{
	typedef ::std::iterator_traits<InputIteratorT> iterator_traits;
	
	iterator_traits::difference_type const size = ::std::distance(begin, end);

	if (0 > size) {
		hryky_throw(
			::std::invalid_argument,
			"The range of sources is invalid."
			<< " : source_size " << size,
			return false);
	}

	if (Capacity < size) {
		hryky_throw(
			::std::invalid_argument,
			"The range of sources is too large."
			<< " : source_size " << size
			<< " : capacity " << this->capacity(),
			return false);
	}

	this->resize(0);

	hryky::range(begin, end).foreach_at([this](
		iterator_traits::reference rhs, size_t const index) {
		this->buffer_[static_cast<size_type>(index)] = rhs;
	});
	this->size_ = static_cast<size_type>(size);

	return true;
}
/**
  @brief assigns the copies of an element.
 */
template <hryky_template_param>
bool hryky::FixedVector<hryky_template_arg>::assign(
	size_type size, const_reference value)
{
	if (Capacity < size) {
		return false;
	}

	this->resize(0);

	hryky::repeat(size).foreach_at([this, &value](size_type const index) {
		this->buffer_[index] = value;
	});
	this->size_ = size;

	return true;
}
/**
  @brief adds the element into the end of container.
 */
template <hryky_template_param>
bool hryky::FixedVector<hryky_template_arg>::push_back(const_reference src)
{
	if (this->size_ == Capacity) {
		return false;
	}

	this->buffer_[this->size_] = src;
	++this->size_;

	return true;
}
/**
  @brief removes the last element.
 */
template <hryky_template_param>
bool hryky::FixedVector<hryky_template_arg>::pop_back()
{
	if (this->empty()) {
		return false;
	}

	this->buffer_[this->size_ - 1] = ValueT();
	--this->size_;

	return true;
}
/**
  @brief inserts an element before the element at the indicated iterator.
 */
template <hryky_template_param>
typename hryky::FixedVector<hryky_template_arg>::iterator
hryky::FixedVector<hryky_template_arg>::insert(iterator position, const_reference value)
{
	if (this->begin() > position || this->end() < position) {
		return this->end();
	}

	/// @attention reserve() can invalidate @a position.
	size_type const inserted_index = position - this->begin();
	
	if (Capacity == this->size_) {
		return this->end();
	}

	size_type const moved_size      = this->size_ - inserted_index;

	if (0 < moved_size) {
		hryky::memmove(
			&this->buffer_[inserted_index + 1],
			&this->buffer_[inserted_index],
			sizeof(value_type) * moved_size);
	}
	this->buffer_[inserted_index] = value;
	++this->size_;

	return this->begin() + inserted_index;
}
/**
  @brief inserts the elements between two input iterator.
 */
template <hryky_template_param>
template < typename InputIteratorT >
bool hryky::FixedVector<hryky_template_arg>::insert(
	iterator position, InputIteratorT first, InputIteratorT last)
{
	if (this->begin() > position || this->end() < position) {
		return false;
	}

	typedef ::std::iterator_traits<InputIteratorT> iterator_traits;

	iterator_traits::difference_type const inserted_size =
		::std::distance(first, last);

	if (0 > inserted_size) {
		hryky_throw(
			::std::invalid_argument,
			"The range of sources is invalid."
			<< " : source_size " << inserted_size,
			return false);
	}

	if (0 == inserted_size) {
		return true;
	}

	/// @attention reserve() can invalidate @a position.
	size_type const inserted_index = ::std::distance(this->begin(), position);
	
	if (Capacity < this->size_ + inserted_size) {
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
		iterator_traits::reference ref, size_t const index) {
		this->buffer_[inserted_index + index] = ref;
	});
	this->size_ += inserted_size;

	return true;
}
/**
  @brief removes some elements between two iterators.
 */
template <hryky_template_param>
typename hryky::FixedVector<hryky_template_arg>::iterator
hryky::FixedVector<hryky_template_arg>::erase(iterator first, iterator last)
{
	if (this->begin() > first
		 || this->end() < last
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

	return this->buffer_ + pos;
}
/**
  @brief expands or shrinks the length of the container.
 */
template <hryky_template_param>
bool hryky::FixedVector<hryky_template_arg>::resize(
	size_type const size)
{
	size_type const pre_size = this->size();
	
	if (pre_size == size) {
		return true;
	}

	if (pre_size < size) {
		if (Capacity < size) {
			return false;
		}

		allocator::Base<value_type> allocator;

		ConstructorT::construct(
			allocator,
			&this->buffer_[pre_size],
			&this->buffer_[size]);
	}
	else {
		allocator::Base<value_type> allocator;

		ConstructorT::destroy(
			allocator,
			&this->buffer_[size],
			&this->buffer_[pre_size]);
	}
	this->size_ = size;

	return true;
}
/**
  @brief makes the container empty.
 */
template <hryky_template_param>
bool hryky::FixedVector<hryky_template_arg>::clear()
{
	return this->resize(0);
}
/**
  @brief interchanges all internal values.
 */
template <hryky_template_param>
void hryky::FixedVector<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(buffer);
	hryky_swap_member(size);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::FixedVector<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(size);
	out << hryky_stream_denote(Capacity);

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
#undef hryky_iterator
#undef hryky_const_iterator
#undef hryky_pointer
#undef hryky_reference
#undef hryky_const_pointer
#undef hryky_const_reference
#undef hryky_size_type
#undef hryky_difference_type
#endif // FIXED_VECTOR_H_20120805214745574
// end of file
