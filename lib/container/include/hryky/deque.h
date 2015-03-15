/**
  @file     deque.h
  @brief    substitutes ::std::deque.
  @author   HRYKY
  @version  $Id: deque.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef DEQUE_H_20130402193845485
#define DEQUE_H_20130402193845485
#include "hryky/allocator/allocator_mempool.h"
#include "hryky/clear.h"
#include "hryky/foreach.h"
#include "hryky/type_traits/as_parameter.h"
#include "hryky/range.h"
#include "hryky/repeat.h"
#include "hryky/with_at.h"
#include "hryky/with_iteration.h"
#include "hryky/with_iterator.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/is_null.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT, typename AllocatorT
#define hryky_template_arg \
	ValueT, AllocatorT
/**
  The definition of Deque::resize() with variadic parameters.
 */
#define hryky_deque_resize(...) {\
	size_type const pre_size = this->size();\
	if (pre_size == size) {\
		return true;\
	}\
	if (pre_size < size) {\
		if (!this->reserve(size)) {\
			return false;\
		}\
		size_type index = pre_size;\
		for (; size != index; ++index) {\
			this->allocator_.\
				construct(&this->buffer_[this->after_begin(index)],\
						  __VA_ARGS__);\
		}\
	}\
	else {\
		hryky::repeat(size, pre_size).\
			foreach_at([this](size_type const index) {\
				this->allocator_.\
					destroy(&this->buffer_[this->after_begin(index)]);\
			});\
	}\
	this->size_ = size;\
}
#define hryky_iterator \
	hryky::iterator::random::Mutable<Deque<hryky_template_arg>, ValueT>
#define hryky_const_iterator \
	hryky::iterator::random::Immutable<Deque<hryky_template_arg>, ValueT>
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// substitutes ::std::deque.
	template <
		typename ValueT,
		typename AllocatorT = allocator::Mempool<ValueT>
	>
	class Deque;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief substitutes ::std::deque.
 */
template <hryky_template_param>
class hryky::Deque :
	public WithIterator<
		Deque<hryky_template_arg>,
		hryky_iterator,
		hryky_const_iterator >,
	public WithIteration<
		Deque<hryky_template_arg>,
		hryky_iterator,
		hryky_const_iterator >,
	public WithAt<
		Deque<hryky_template_arg>,
		ValueT>,
	public WithStreamOut<Deque<hryky_template_arg> >,
	public WithSwap<Deque<hryky_template_arg> >
{
public :

	typedef Deque<hryky_template_arg>                   this_type;
	typedef ValueT                                      value_type;
	typedef typename AddPointer<ValueT>::type           pointer;
	typedef typename AddConstPointer<ValueT>::type      const_pointer;
	typedef typename AddReference<ValueT>::type         reference;
	typedef typename AddConstReference<ValueT>::type    const_reference;
	typedef ::std::size_t                                 size_type;
	typedef ::std::ptrdiff_t                              difference_type;
	typedef AllocatorT                                  allocator_type;

	/// default constructor.
	Deque();

	/// constructor with an allocator.
	explicit Deque(allocator_type const & allocator);

	/// constructor with size.
	Deque(size_type const size, allocator_type const & allocator);

	/// constructor with a value.
	Deque(size_type const size, const_reference value, allocator_type const & allocator);

	/// constructor with the range of values.
	template <typename InputIteratorT>
	Deque(InputIteratorT first, InputIteratorT last, allocator_type const & allocator);

	/// constructor with the range of values.
	template <typename InputIteratorT>
	Deque(InputIteratorT first, InputIteratorT last);

	/// copy constructor.
	Deque(this_type const &);

	/// move constructor.
	Deque(this_type &&);

	/// destructor.
	~Deque();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// retrieves the mutable reference by a distance from the beginning.
	reference operator[](size_type const index);

	/// retrieves the immutable reference by a distance from the beginning.
	const_reference operator[](size_type const index) const;

	/// confirms the equality between two deques.
	bool operator==(this_type const & rhs) const;

	/// confirms the inequality between two deques.
	bool operator!=(this_type const & rhs) const;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// retrieves the capacity of the container.
	size_type size() const;

	/// changes the size of the container.
	bool resize(size_type const size);

	/// changes the size of the container.
	template <typename Arg1T>
	bool resize(size_type const size, Arg1T && arg1);

	/// allocates the memory in advance.
	bool reserve(size_type const capacity);
	
	/// confirms whether There is no instantiated value in this container.
	bool empty() const;

	/// assigns new elements between a range.
	template <typename InputIteratorT>
	bool assign(InputIteratorT first, InputIteratorT last);

	/// assigns new elements having the same value.
	bool assign(size_type const size, const_reference value);

	/// assigns new elements having the same value by rvalue reference.
	bool assign(size_type const size, value_type && value);

	/// appends a new value at the end of the container.
	bool push_back(const_reference value);

	/// appends a new value at the end of the container as rvalue reference.
	bool push_back(value_type && value);

	/// appends a new value at the beginning of the container.
	bool push_front(const_reference value);

	/// appends a new value at the beginning of the container as rvalue reference.
	bool push_front(value_type && value);

	/// removes the last element from the end of the container.
	bool pop_back();

	/// removes the first element from the beginning of the container.
	bool pop_front();

	/// inserts a new value just before the specified position.
	iterator insert(const_iterator position, const_reference value);

	/// inserts new same values just before the specified position.
	iterator insert(const_iterator position, size_type const size, const_reference value);

	/// inserts new values just before the specified position.
	template <typename InputIteratorT>
	iterator insert(const_iterator position, InputIteratorT first, InputIteratorT last);

	/// inserts a new value just before the specified position by rvalue reference.
	iterator insert(const_iterator position, value_type && value);

	/// removes an element.
	iterator erase(const_iterator position);

	/// removes elements.
	template <typename InputIteratorT>
	iterator erase(InputIteratorT first, InputIteratorT last);

	/// retrieves the allocator used in this instance.
	allocator_type get_allocator() const;

protected :

private :

	typedef WithIteration<
		Deque<hryky_template_arg>,
		hryky_iterator,
		hryky_const_iterator>
			with_iteration;
	
	/// retrieves an index of the internal buffer by distance from the beginning.
	size_type after_begin(size_type const index) const;

	/// retrieves an internal index prededing the beginning.
	size_type before_begin(size_type const index) const;

	/// replaces a range of the buffer.
	void memmove(size_type const dest, size_type const src, size_type const size);

	/// copies a range of the buffer.
	void memcpy(size_type const dest, size_type const src, size_type const size);

	/// makes a space for an insertion of a signle value.
	size_type expand(size_type const insertion_distance);

	/// makes a space for an insertion.
	size_type expand(size_type const insertion_begin, size_type const size);

	/// instantiates new values at a range of the container.
	template <typename InputIteratorT>
	void construct(
		size_type const insertion_begin,
		size_type const size,
		InputIteratorT itr);

	/// instantiates new same values at a range of the container.
	void construct(
		size_type const insertion_begin,
		size_type const size,
		const_reference value);

	/// closes up the space from which the element is erased.
	void shorten(size_type const erase_distance);

	/// applies destructors to the range of the container.
	void destroy(size_type const erase_begin, size_type const size);

	/// closes up the space from which the elements are erased.
	void shorten(size_type const erase_distance, size_type const size);

	allocator_type allocator_;
	pointer buffer_;
	size_type begin_;
	size_type size_;
	size_type capacity_;

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
hryky::Deque<hryky_template_arg>::Deque()
	: allocator_()
	  , buffer_()
	  , begin_()
	  , size_()
	  , capacity_()
{
}
/**
  @brief constructor with an allocator.
 */
template <hryky_template_param>
hryky::Deque<hryky_template_arg>::Deque(allocator_type const & allocator)
	: allocator_(allocator)
	  , buffer_()
	  , begin_()
	  , size_()
	  , capacity_()
{
}
/**
  @brief constructor with size.
 */
template <hryky_template_param>
hryky::Deque<hryky_template_arg>::Deque(
	size_type const size, allocator_type const & allocator)
	: allocator_(allocator)
	  , buffer_()
	  , begin_()
	  , size_()
	  , capacity_()
{
	this->resize(size);
}
/**
  @brief constructor with a value.
 */
template <hryky_template_param>
hryky::Deque<hryky_template_arg>::Deque(
	size_type const size,
	const_reference value,
	allocator_type const & allocator)
	: allocator_(allocator)
	  , buffer_()
	  , begin_()
	  , size_()
	  , capacity_()
{
	this->assign(size, value);
}
/**
  @brief constructor with the range of values.
 */
template <hryky_template_param>
template <typename InputIteratorT>
hryky::Deque<hryky_template_arg>::Deque(
	InputIteratorT first, InputIteratorT last, allocator_type const & allocator)
	: allocator_(allocator)
	  , buffer_()
	  , begin_()
	  , size_()
	  , capacity_()
{
	this->assign(first, last);
}
/**
  @brief constructor with the range of values.
 */
template <hryky_template_param>
template <typename InputIteratorT>
hryky::Deque<hryky_template_arg>::Deque(
	InputIteratorT first, InputIteratorT last)
	: allocator_()
	  , buffer_()
	  , begin_()
	  , size_()
	  , capacity_()
{
	this->assign(first, last);
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::Deque<hryky_template_arg>::Deque(this_type const & rhs)
	: hryky_copy_member(allocator)
	  , buffer_()
	  , begin_()
	  , size_()
	  , capacity_()
{
	if (rhs.empty()) {
		return;
	}

	size_type const size = rhs.size();

	if (hryky_is_null(this->buffer_ = this->allocator_.allocate(size))) {
		return;
	}

	rhs.foreach_at([this](const_reference rhs_value, size_type const index) {
		this->allocator_.construct(&this->buffer_[index], rhs_value);
	});

	this->size_ = size;
	this->capacity_ = size;
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::Deque<hryky_template_arg>::Deque(this_type && rhs)
	: allocator_()
	  , buffer_()
	  , begin_()
	  , size_()
	  , capacity_()
{
	this->swap(rhs);
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::Deque<hryky_template_arg>::~Deque()
{
	if (hryky_is_null(this->buffer_)) {
		return;
	}

	this->foreach([this](reference value) {
		this->allocator_.destroy(&value);
	});
	this->allocator_.deallocate(this->buffer_, this->capacity_);
	hryky::clear(this->buffer_);
	hryky::clear(this->capacity_);
}
/**
  @brief retrieves the mutable reference by a distance from the beginning.
 */
template <hryky_template_param>
typename hryky::Deque<hryky_template_arg>::reference 
hryky::Deque<hryky_template_arg>::operator[](size_type const index)
{
	return this->buffer_[this->after_begin(index)];
}
/**
  @brief retrieves the immutable reference by a distance from the beginning.
 */
template <hryky_template_param>
typename hryky::Deque<hryky_template_arg>::const_reference 
hryky::Deque<hryky_template_arg>::operator[](size_type const index) const
{
	return this->buffer_[this->after_begin(index)];
}
/**
  @brief confirms the equality between two deques.
 */
template <hryky_template_param>
bool hryky::Deque<hryky_template_arg>::operator==(this_type const & rhs) const
{
	if (this->size_ != rhs.size_) {
		return false;
	}
	return this->every_at([&rhs](const_reference lhs, size_type const index) {
		return lhs == rhs[index];
	});
}
/**
  @brief confirms the inequality between two deques.
 */
template <hryky_template_param>
bool hryky::Deque<hryky_template_arg>::operator!=(this_type const & rhs) const
{
	if (this->size_ != rhs.size_) {
		return true;
	}
	return this->some_at([&rhs](const_reference lhs, size_type const index) {
		return lhs != rhs[index];
	});
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::Deque<hryky_template_arg>::clear()
{
	this->resize(0);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::Deque<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(allocator);
	hryky_write_member(begin);
	hryky_write_member(size);
	hryky_write_member(capacity);

	return this->with_iteration::write_to(out);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::Deque<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(allocator);
	hryky_swap_member(buffer);
	hryky_swap_member(begin);
	hryky_swap_member(size);
	hryky_swap_member(capacity);
}
/**
  @brief retrieves the capacity of the container.
 */
template <hryky_template_param>
typename hryky::Deque<hryky_template_arg>::size_type 
hryky::Deque<hryky_template_arg>::size() const
{
	return this->size_;
}
/**
  @brief changes the size of the container.
 */
template <hryky_template_param>
bool hryky::Deque<hryky_template_arg>::resize(size_type const size)
{
	size_type const pre_size = this->size();
	if (pre_size == size) {
		return true;
	}
	if (pre_size < size) {
		if (!this->reserve(size)) {
			return false;
		}
		size_type index = pre_size;
		for (; size != index; ++index) {
			this->allocator_.construct(
				&this->buffer_[this->after_begin(index)]);
		}
	}
	else {
		hryky::repeat(size, pre_size).
			foreach_at([this](size_type const index) {
				this->allocator_.
					destroy(&this->buffer_[this->after_begin(index)]);
			});
	}
	this->size_ = size;
	return true;
}
/**
  @brief changes the size of the container with an argument.
 */
template <hryky_template_param>
template <typename Arg1T>
bool hryky::Deque<hryky_template_arg>::resize(
	size_type const size, Arg1T && arg1)
{
	hryky_deque_resize(::std::forward<Arg1T>(arg1));
	return true;
}
/**
  @brief allocates the memory in advance.
 */
template <hryky_template_param>
bool hryky::Deque<hryky_template_arg>::reserve(size_type const capacity)
{
	if (this->capacity_ >= capacity) {
		return true;
	}

	pointer const buffer = this->allocator_.allocate(capacity);
	if (hryky_is_null(buffer)) {
		return false;
	}
	
	if (!this->empty()) {
		if (this->begin_ + this->size_ > this->capacity_) {
			size_type const first_size = this->capacity_ - this->begin_;
			hryky::memcpy(
				&buffer[0],
				&this->buffer_[this->begin_],
				sizeof(value_type) * first_size);
			hryky::memcpy(
				&buffer[first_size],
				&this->buffer_[0],
				sizeof(value_type) * (this->size_ - first_size));
		}
		else {
			hryky::memcpy(
				&buffer[0],
				&this->buffer_[this->begin_],
				sizeof(value_type) * this->size_);
		}
		this->begin_ = 0;
	}

	if (!hryky_is_null(this->buffer_)) {
		this->allocator_.deallocate(this->buffer_, this->capacity_);
	}

	this->buffer_ = buffer;
	this->capacity_ = capacity;
	
	return true;
}
/**
  @brief confirms whether There is no instantiated value in this container.
 */
template <hryky_template_param>
bool hryky::Deque<hryky_template_arg>::empty() const
{
	return 0 == this->size_;
}
/**
  @brief assigns new elements between a range.
 */
template <hryky_template_param>
template <typename InputIteratorT>
bool hryky::Deque<hryky_template_arg>::assign(
	InputIteratorT first, InputIteratorT last)
{
	typedef ::std::iterator_traits<InputIteratorT> iterator_traits;

	iterator_traits::difference_type const size = ::std::distance(first, last);

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

	hryky::range(first, last).foreach_at([this](
		iterator_traits::reference rhs_value, size_t const index) {
		this->allocator_.construct(&this->operator[](index), rhs_value);
	});
	this->size_ = static_cast<size_type>(size);
	
	return true;
}
/**
  @brief assigns new elements having the same value.
 */
template <hryky_template_param>
bool hryky::Deque<hryky_template_arg>::assign(
	size_type const size, const_reference value)
{
	if (!this->reserve(size)) {
		return false;
	}

	this->resize(0);

	hryky::repeat(size).foreach_at([this, &value](size_type const index) {
		this->allocator_.construct(&this->operator[](index), value);
	});
	this->size_ = size;
	
	return true;
}
/**
  @brief assigns new elements having the same value by rvalue reference.
 */
template <hryky_template_param>
bool hryky::Deque<hryky_template_arg>::assign(
	size_type const size, value_type && value)
{
	if (!this->reserve(size)) {
		return false;
	}

	this->resize(0);

	hryky::repeat(size).foreach_at([this, &value](size_type const index) {
		this->allocator_.construct(&this->operator[](index), value);
	});
	this->size_ = size;
	
	return true;
}
/**
  @brief appends a new value at the end of the container.
 */
template <hryky_template_param>
bool hryky::Deque<hryky_template_arg>::push_back(const_reference value)
{
	if (!this->reserve((this->size_ + 1) << 1)) {
		return false;
	}

	this->allocator_.construct(
		&this->operator[](this->size_), value);

	++this->size_;
	
	return true;
}
/**
  @brief appends a new value at the end of the container as rvalue reference.
 */
template <hryky_template_param>
bool hryky::Deque<hryky_template_arg>::push_back(value_type && value)
{
	if (!this->reserve((this->size_ + 1) << 1)) {
		return false;
	}

	this->allocator_.construct(
		&this->operator[](this->size_), ::std::move(value));

	++this->size_;
	
	return true;
}
/**
  @brief appends a new value at the beginning of the container.
 */
template <hryky_template_param>
bool hryky::Deque<hryky_template_arg>::push_front(const_reference value)
{
	if (!this->reserve((this->size_ + 1) << 1)) {
		return false;
	}

	size_type const next_begin =
		0 < this->begin_ ? (this->begin_ - 1) : (this->capacity_ - 1);

	this->allocator_.construct(
		&this->buffer_[next_begin], value);

	++this->size_;
	this->begin_ = next_begin;
	
	return true;
}
/**
  @brief appends a new value at the beginning of the container
  as rvalue reference.
 */
template <hryky_template_param>
bool hryky::Deque<hryky_template_arg>::push_front(value_type && value)
{
	if (!this->reserve((this->size_ + 1)) << 1) {
		return false;
	}

	size_type const next_begin = this->before_begin(1);

	this->allocator_.construct(
		&this->buffer_[next_begin], ::std::move(value));

	++this->size_;
	this->begin_ = next_begin;
	
	return true;
}
/**
  @brief removes the last element from the end of the container.
 */
template <hryky_template_param>
bool hryky::Deque<hryky_template_arg>::pop_back()
{
	if (this->empty()) {
		return false;
	}

	this->allocator_.destroy(
		&this->buffer_[this->after_begin(this->size_ - 1)]);

	--this->size_;
	
	return true;
}
/**
  @brief removes the first element from the beginning of the container.
 */
template <hryky_template_param>
bool hryky::Deque<hryky_template_arg>::pop_front()
{
	if (this->empty()) {
		return false;
	}

	this->allocator_.destroy(&this->buffer_[this->begin_]);

	--this->size_;
	this->begin_ = this->after_begin(1);
	
	return true;
}
/**
  @brief inserts a new value just before the specified position.
 */
template <hryky_template_param>
typename hryky::Deque<hryky_template_arg>::iterator
hryky::Deque<hryky_template_arg>::insert(
	const_iterator position, const_reference value)
{
	if (this->begin() > position || this->end() < position) {
		return this->end();
	}

	/// @attention reserve() can invalidate @a position.
	size_type const insertion_distance = static_cast<size_type>(
		position - this->begin());
	
	if (!this->reserve(this->size_ + 1)) {
		return this->end();
	}

	size_type const insertion_begin =
		this->expand(insertion_distance);

	this->allocator_.construct(&this->buffer_[insertion_begin], value);
	++this->size_;

	return this->begin()
		+ static_cast<difference_type>(insertion_distance);
}
/**
  @brief inserts new same values just before the specified position.
 */
template <hryky_template_param>
typename hryky::Deque<hryky_template_arg>::iterator 
hryky::Deque<hryky_template_arg>::insert(
	const_iterator position, size_type const size, const_reference value)
{
	if (this->begin() > position || this->end() < position) {
		return this->end();
	}

	/// @attention reserve() can invalidate @a position.
	size_type const insertion_distance = static_cast<size_type>(
		position - this->begin());
	
	if (!this->reserve(this->size_ + size)) {
		return this->end();
	}

	size_type const insertion_begin =
		this->expand(insertion_distance, size);

	this->construct(insertion_begin, size, value);

	this->size_ += size;

	return this->begin()
		+ static_cast<difference_type>(insertion_distance);
}
/**
  @brief inserts new values just before the specified position.
 */
template <hryky_template_param>
template <typename InputIteratorT>
typename hryky::Deque<hryky_template_arg>::iterator 
hryky::Deque<hryky_template_arg>::insert(
	const_iterator position, InputIteratorT first, InputIteratorT last)
{
	if (this->begin() > position || this->end() < position) {
		return this->end();
	}

	difference_type const size = ::std::distance(first, last);

	if (0 >= size) {
		return this->end();
	}

	/// @attention reserve() can invalidate @a position.
	size_type const insertion_distance = static_cast<size_type>(
		position - this->begin());
	
	if (!this->reserve(this->size_ + size)) {
		return this->end();
	}

	size_type const insertion_begin =
		this->expand(insertion_distance, static_cast<size_type>(size));

	this->construct(insertion_begin, static_cast<size_type>(size), first);

	this->size_ += size;

	return this->begin() + static_cast<difference_type>(insertion_distance);
}
/**
  @brief inserts a new value just before the specified position by rvalue reference.
 */
template <hryky_template_param>
typename hryky::Deque<hryky_template_arg>::iterator 
hryky::Deque<hryky_template_arg>::insert(
	const_iterator position, value_type && value)
{
	if (this->begin() > position || this->end() < position) {
		return this->end();
	}

	/// @attention reserve() can invalidate @a position.
	size_type const insertion_distance = position - this->begin();
	
	if (!this->reserve(this->size_ + 1)) {
		return this->end();
	}

	size_type const insertion_begin =
		this->expand(insertion_distance);

	this->allocator_.construct(&this->buffer_[insertion_begin], value);
	++this->size_;

	return this->begin() + insertion_distance;
}
/**
  @brief removes an element.
 */
template <hryky_template_param>
typename hryky::Deque<hryky_template_arg>::iterator 
hryky::Deque<hryky_template_arg>::erase(const_iterator position)
{
	if (this->begin() > position || this->end() <= position) {
		return this->end();
	}

	size_type const erase_distance = static_cast<size_type>(
		position - this->begin());
	size_type const erase_begin = this->after_begin(erase_distance);

	this->allocator_.destroy(&this->buffer_[erase_begin]);

	this->shorten(erase_distance);

	this->size_ = static_cast<size_type>(this->size_ - 1u);

	return ::std::next(
		this->begin(),
		static_cast<difference_type>(erase_distance));
}
/**
  @brief removes elements.
 */
template <hryky_template_param>
template <typename InputIteratorT>
typename hryky::Deque<hryky_template_arg>::iterator
hryky::Deque<hryky_template_arg>::erase(
	InputIteratorT first, InputIteratorT last)
{
	const_iterator const begin = this->begin();
	const_iterator const end = this->end();
	if (begin > first || begin > last || end < first || end < last) {
		return this->end();
	}

	difference_type const size = ::std::distance(first, last);

	if (0 >= size) {
		return this->end();
	}

	size_type const erase_distance = static_cast<size_type>(
		::std::distance(this->begin(), first));
	size_type const erase_begin = this->after_begin(erase_distance);

	this->destroy(erase_begin, static_cast<size_type>(size));

	this->shorten(erase_distance, static_cast<size_type>(size));

	this->size_ -= size;

	typedef ::std::iterator_traits<InputIteratorT>::difference_type
		iterator_difference_type;

	return ::std::next(
		this->begin(),
		static_cast<iterator_difference_type>(erase_distance));
}
/**
  @brief retrieves the allocator used in this instance.
 */
template <hryky_template_param>
AllocatorT hryky::Deque<hryky_template_arg>::get_allocator() const
{
	return this->allocator_;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief retrieves an index of the internal buffer by distance from the beginning.
 */
template <hryky_template_param>
typename hryky::Deque<hryky_template_arg>::size_type 
hryky::Deque<hryky_template_arg>::after_begin(size_type const index) const
{
	if (this->begin_ + index < this->capacity_) {
		return this->begin_ + index;
	}
	else {
		return this->begin_ + index - this->capacity_;
	}
}
/**
  @brief retrieves an internal index preceding the beginning.
 */
template <hryky_template_param>
typename hryky::Deque<hryky_template_arg>::size_type 
hryky::Deque<hryky_template_arg>::before_begin(size_type const index) const
{
	if (index > this->begin_) {
		return this->begin_ + this->capacity_ - index;
	}
	else {
		return this->begin_ - index;
	}
}
/**
  @brief replaces a range of the buffer.
 */
template <hryky_template_param>
void hryky::Deque<hryky_template_arg>::memmove(
	size_type const dest, size_type const src, size_type const size)
{
	hryky::memmove(
		&this->buffer_[dest],
		&this->buffer_[src],
		sizeof(value_type) * size);
}
/**
  @brief copies a range of the buffer.
 */
template <hryky_template_param>
void hryky::Deque<hryky_template_arg>::memcpy(
	size_type const dest, size_type const src, size_type const size)
{
	hryky::memcpy(
		&this->buffer_[dest],
		&this->buffer_[src],
		sizeof(value_type) * size);
}
/**
  @brief makes a space for an insertion of a signle value.
 */
template <hryky_template_param>
typename hryky::Deque<hryky_template_arg>::size_type
hryky::Deque<hryky_template_arg>::expand(
	size_type const insertion_distance)
{
	/**
	  [-|ABCD|-] => [!ABCD|-|]
	  [ABCD|--|] => [ABCD|-|!]
	  This pattern avoids the memory operation.
	 */
	if (0 == insertion_distance) {
		this->begin_ = this->before_begin(1);
		return this->begin_;
	}
	
	size_type const insertion_begin = this->after_begin(
		insertion_distance);
	
	/**
	  [-|ABCD|-] => [-|ABCD!|]
	  [|--|ABCD] => [!|-|ABCD]
	  This pattern avoids the memory operation.
	 */
	if (insertion_distance == this->size_) {
		return insertion_begin;
	}

	/**
	  [|---|ABCD] => [D|--|ABC!]
	  [-|ABCD|--] => [-|ABC!D|-]
	  This pattern can use memcpy instead of memmove.
	 */
	if (insertion_distance + 1 == this->size_) {
		// D
		this->memcpy(
			this->after_begin(this->size_), insertion_begin, 1);
		return insertion_begin;
	}

	/**
	  [--|ABCD|-] => [-|A!BCD|-]
	  [|ABCD|---] => [!BCD|--|A]
	  This pattern can use memcpy instead of memmove.
	 */
	if (1 == insertion_distance) {
		size_type const prev_begin = this->begin_;
		size_type const next_begin = this->before_begin(1);
		// A
		this->memcpy(next_begin, prev_begin, 1);
		this->begin_ = next_begin;
		return prev_begin;
	}

	size_type const insertion_end = insertion_begin + 1;
	size_type const end = this->after_begin(this->size_);

	/**
	  [CDE|--|AB] => [C!DE|-|AB]
	 */
	if (insertion_begin < this->begin_) {
		// DE
		this->memmove(
			insertion_end, insertion_begin, end - insertion_begin);
		return insertion_begin;
	}
	
	/**
	  [EF|--|ABCD] => [EF|-|AB!CD]
	 */
	if (insertion_begin > end) {
		// AB
		this->memmove(this->begin_ - 1, this->begin_, insertion_distance);
		this->begin_ -= 1;
		return insertion_begin - 1;
	}

	/**
	  [|--|ABCDE] => [|-|AB!CDE]
	 */
	if (this->begin_ + this->size_ == this->capacity_) {
		// AB
		this->memmove(this->begin_ - 1, this->begin_, insertion_distance);
		this->begin_ -= 1;
		return insertion_begin - 1;
	}
	
	/**
	  [-|ABCDE|-] => [-|AB!CDE|]
	 */
	// CDE
	this->memmove(
		insertion_end, insertion_begin, end - insertion_begin);
	return insertion_begin;

}
/**
  @brief makes a space for an insertion.
 */
template <hryky_template_param>
typename hryky::Deque<hryky_template_arg>::size_type
hryky::Deque<hryky_template_arg>::expand(
	size_type const insertion_distance, size_type const size)
{
	/**
	  [---|ABCD|-] => [!!!ABCD|-|]
	  [-|ABCD|---] => [!ABCD|-|!!]
	  This pattern avoids the memory operation.
	 */
	if (0 == insertion_distance) {
		// ABCD
		this->begin_ = this->before_begin(size);
		return this->begin_;
	}

	size_type const insertion_begin = this->after_begin(insertion_distance);

	/**
	  [-|ABCD|---] => [|-|ABCD!!!]
	  [---|ABCD|-] => [!!|-|ABCD!]
	  This pattern avoids the memory operation.
	 */
	if (insertion_distance == this->size_) {
		return insertion_begin;
	}

	size_type const end = this->after_begin(this->size_);
	
	/**
	  [CDE|----|AB] => [C!!!DE|-|AB]
	 */
	if (insertion_begin < this->begin_) {
		// DE
		this->memmove(
			insertion_begin + size,
			insertion_begin,
			end - insertion_begin);
		return insertion_begin;
	}

	/**
	  [DE|----|ABC] => [CDE|-|AB!!!C]
	 */
	if (insertion_begin > end) {
		// AB
		this->memmove(this->begin_ - size, this->begin_, insertion_distance);
		this->begin_ -= size;
		return insertion_begin - size;
	}

	/**
	  [-|ABC|---] => [-|A!!BC|-]
	 */
	if (this->capacity_ - end >= size) {
		// BC
		this->memmove(
			insertion_begin + size, insertion_begin, end - insertion_begin);
		return insertion_begin;
	}

	/**
	  [---|ABC|-] => [-|AB!!C|-]
	 */
	if (this->begin_ >= size) {
		// size_type const next_begin = this->before_begin(size);
		// AB
		this->memmove(this->begin_ - size, this->begin_, insertion_distance);
		this->begin_ -= size;
		return insertion_begin - size;
	}

	/**
	   At this point the buffer has capacities at the both size. The
	  capacities at the both sides are not available to store the
	  inserted data by itself. The whole of the buffer is aligned in
	  order to retrieve the space to store the data.

	  [--|ABCD|--] => [AB!!!CD|-|]
	 */

	this->memmove(0, this->begin_, insertion_distance);
	this->memmove(
		insertion_distance + size, insertion_begin, end - insertion_begin);
	this->begin_ = 0;
	return insertion_distance;
}
/**
  @brief instantiates new values at a range of the container.
 */
template <hryky_template_param>
template <typename InputIteratorT>
void hryky::Deque<hryky_template_arg>::construct(
	size_type const insertion_begin,
	size_type const size,
	InputIteratorT itr)
{
	size_type const insertion_end = insertion_begin + size;
	
	/**
	  [DEF|-|AB!!C]
	 */
	if (insertion_end <= this->capacity_) {
		hryky::repeat(insertion_begin, insertion_end).foreach_at([this, &itr](
			size_type const index) {
			this->allocator_.construct(&this->buffer_[index], *(itr++));
		});
	}
	/**
	  [!EF|-|ABCD!]
	 */
	else {
		// constructs the first half.
		hryky::repeat(insertion_begin, this->capacity_).foreach_at([this, &itr](
			size_type const index) {
			this->allocator_.construct(&this->buffer_[index], *(itr++));
		});
		// constructs the last half.
		hryky::repeat(insertion_end - this->capacity_).foreach_at([this, &itr](
			size_type const index) {
			this->allocator_.construct(&this->buffer_[index], *(itr++));
		});
	}
}
/**
  @brief instantiates new same values at a range of the container.
 */
template <hryky_template_param>
void hryky::Deque<hryky_template_arg>::construct(
	size_type const insertion_begin,
	size_type const size,
	const_reference value)
{
	size_type const insertion_end = insertion_begin + size;
	
	/**
	  [DEF|-|AB!!C]
	 */
	if (insertion_end <= this->capacity_) {
		hryky::repeat(insertion_begin, insertion_end).foreach_at([this, &value](
			size_type const index) {
			this->allocator_.construct(&this->buffer_[index], value);
		});
	}
	/**
	  [!EF|-|ABCD!]
	 */
	else {
		// constructs the first half.
		hryky::repeat(insertion_begin, this->capacity_).foreach_at([this, &value](
			size_type const index) {
			this->allocator_.construct(&this->buffer_[index], value);
		});
		// constructs the last half.
		hryky::repeat(insertion_end - this->capacity_).foreach_at([this, &value](
			size_type const index) {
			this->allocator_.construct(&this->buffer_[index], value);
		});
	}
}
/**
  @brief closes up the space from which the element is erased.
 */
template <hryky_template_param>
void hryky::Deque<hryky_template_arg>::shorten(size_type const erase_distance)
{
	/**
	  [-|!ABC|-] => [--|ABC|-]
	  [ABC|--|!] => [ABC|---|]
	  This pattern avoids the memory operation.
	 */
	if (0 == erase_distance) {
		this->begin_ = this->after_begin(1);
		return;
	}

	/**
	  [-|ABC!|-] => [-|ABC|--]
	  [!|--|ABC] => [|---|ABC]
	  This pattern avoids the memory operation.
	 */
	if (erase_distance + 1 == this->size_) {
		return;
	}

	size_type const erase_begin = this->after_begin(erase_distance);
	
	/**
	  [-|A!BC|-] => [--|ABC|-]
	  [!BC|--|A] => [ABC|---|]
	  This pattern can use memcpy instead of memmove.
	 */
	if (1 == erase_distance) {
		// A
		this->memcpy(erase_begin, this->begin_, 1);
		this->begin_ = this->after_begin(1);
		return;
	}

	/**
	  [-|AB!C|-] => [-|ABC|--]
	  [C|--|AB!] => [|---|ABC]
	  This pattern can use memcpy instead of memmove.
	 */
	if (erase_distance + 2 == this->size_) {
		// C
		this->memcpy(erase_begin, this->after_begin(this->size_ - 1), 1);
		return;
	}
	
	size_type const end = this->after_begin(this->size_);

	/**
	  [C!DE|-|AB] => [CDE|--|AB]
	 */
	if (erase_begin < this->begin_) {
		// DE
		this->memmove(erase_begin, erase_begin + 1, end - erase_begin);
		return;
	}

	/**
	  [DE|-|AB!C] => [DE|--|ABC]
	 */
	if (erase_begin > end) {
		// AB
		this->memmove(this->begin_ + 1, this->begin_, erase_distance);
		this->begin_ = this->begin_ + 1;
		return;
	}

	/**
	  [-|AB!CD|-] => [-|ABCD|--]
	 */
	// CD
	this->memmove(erase_begin, erase_begin + 1, end - erase_begin);
	return;
}
/**
  @brief applies destructors to the range of the container.
 */
template <hryky_template_param>
void hryky::Deque<hryky_template_arg>::destroy(
	size_type const erase_begin, size_type const size)
{
	size_type const erase_end = erase_begin + size;
	
	/**
	  [DEF|-|AB!!C]
	 */
	if (erase_end <= this->capacity_) {
		hryky::repeat(erase_begin, erase_end).foreach_at([this](
			size_type const index) {
			this->allocator_.destroy(&this->buffer_[index]);
		});
	}
	/**
	  [!EF|-|ABCD!]
	 */
	else {
		// constructs the first half.
		hryky::repeat(erase_begin, this->capacity_).foreach_at([this](
			size_type const index) {
			this->allocator_.destroy(&this->buffer_[index]);
		});
		// constructs the last half.
		hryky::repeat(erase_end - this->capacity_).foreach_at([this](
			size_type const index) {
			this->allocator_.destroy(&this->buffer_[index]);
		});
	}
}
/**
  @brief closes up the space from which the elements are erased.
 */
template <hryky_template_param>
void hryky::Deque<hryky_template_arg>::shorten(
	size_type const erase_distance, size_type const size)
{
	/**
	  [-|!!ABC|-] => [---|ABC|-]
	  [!ABC|--|!] => [|ABC|----]
	  This pattern can avoid the memory operation.
	 */
	if (0 == erase_distance) {
		this->begin_ = this->after_begin(size);
		return;
	}

	/**
	  [-|ABC!!|-] => [-|ABC|---]
	  [!|--|ABC!] => [----|ABC|]
	  This pattern can avoid the memory operation.
	 */
	if (erase_distance + size == this->size_) {
		return;
	}

	size_type const erase_begin = this->after_begin(erase_distance);
	size_type const end = this->after_begin(this->size_);

	/**
	  [B!!CD|-|A] => [BCD|---|A]
	 */
	if (erase_begin < this->begin_) {
		// CD
		this->memmove(erase_begin, erase_begin + size, end - erase_begin);
		return;
	}

	/**
	  [D|-|AB!!C] => [D|---|ABC]
	  [!CD|-|AB!] => [CD|---|AB]
	 */
	if (erase_begin > end) {
		size_type const erase_end = this->after_begin(erase_distance + size);
		/**
		  [!CD|-|AB!] => [CD|---|AB]
		 */
		if (erase_end < erase_begin) {
			size_type const first_offset = this->capacity_ - erase_begin;
			
			// AB
			this->memmove(
				this->begin_ + first_offset, this->begin_, erase_distance);
			
			// CD
			this->memmove(0, erase_end, end - erase_end);

			this->begin_ += first_offset;
		}
		/**
		  [D|-|AB!!C] => [D|---|ABC]
		 */
		else {
			// AB
			this->memmove(
				this->begin_ + size, this->begin_, erase_distance);

			this->begin_ += size;
		}
		return;
	}

	size_type const erase_end = erase_begin + size;

	/**
	  [-|AB!!CD|-] => [-|ABCD|---]
	 */
	// CD
	this->memmove(erase_begin, erase_end, end - erase_end);
	return;
}
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
#undef hryky_deque_resize
#undef hryky_iterator
#undef hryky_const_iterator
#endif // DEQUE_H_20130402193845485
// end of file
