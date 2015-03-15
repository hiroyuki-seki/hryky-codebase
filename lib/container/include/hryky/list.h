/**
  @file     list.h
  @brief    A bidirectional list.
  @author   HRYKY
  @version  $Id: list.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef LIST_H_20130413170355377
#define LIST_H_20130413170355377
#include "hryky/allocator/allocator_mempool.h"
#include "hryky/clear.h"
#include "hryky/definition.h"
#include "hryky/foreach.h"
#include "hryky/integer/signed_of.h"
#include "hryky/iterator/iterator_bidirectional_immutable.h"
#include "hryky/list_index.h"
#include "hryky/repeat.h"
#include "hryky/std/std_cassert.h"
#include "hryky/with_iteration.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/is_null.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT,\
	typename AllocatorT,\
	typename SizeT
#define hryky_template_arg \
	ValueT, AllocatorT, SizeT
#define hryky_list_resize(...) \
	if (size == this->size_) {\
		return true;\
	}\
	\
	if (this->size_ < size) {\
		if (!this->reserve(size)) {\
			return false;\
		}\
		size_type index = this->size_;\
		for (; size != index; ++index) {\
			this->push_back(value_type(__VA_ARGS__));\
		}\
	}\
	else {\
		hryky::repeat(size, this->size_).foreach([this]() {\
			this->pop_back();\
		});\
	}\
	this->size_ = size;
#define hryky_iterator \
	hryky::iterator::bidirectional::Mutable<\
		List<hryky_template_arg>, ListIndex<SizeT> >
#define hryky_const_iterator \
	hryky::iterator::bidirectional::Immutable<\
		List<hryky_template_arg>, ListIndex<SizeT> >
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// A bidirectional list.
	template <
		typename ValueT,
		typename AllocatorT = allocator::Mempool<ValueT>,
		typename SizeT = uint16_t
	>
	class List;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief A bidirectional list.
 */
template <hryky_template_param>
class hryky::List :
	public WithIteration<
		List<hryky_template_arg>,
		hryky_iterator,
		hryky_const_iterator >,
	public WithStreamOut<List<hryky_template_arg> >,
	public WithSwap<List<hryky_template_arg> >
{
public :

	typedef ListIndex<SizeT> index_type;

	typedef List<hryky_template_arg>                    this_type;
	typedef ValueT                                      value_type;
	typedef typename AddPointer<ValueT>::type           pointer;
	typedef typename AddReference<ValueT>::type         reference;
	typedef typename AddConstPointer<ValueT>::type      const_pointer;
	typedef typename AddConstReference<ValueT>::type    const_reference;
	typedef typename SignedOf<SizeT>::type              difference_type;
	typedef SizeT                                       size_type;
	typedef AllocatorT                                  allocator_type;
	typedef hryky_iterator                              iterator;
	typedef hryky_const_iterator                        const_iterator;
	typedef ::std::reverse_iterator<iterator>             reverse_iterator;
	typedef ::std::reverse_iterator<const_iterator>       const_reverse_iterator;
	

	/// default constructor.
	List();

	/// constructor with an allocator.
	explicit List(allocator_type const & allocator);

	/// constructor with the default size.
	List(size_type const size, allocator_type const & allocator);

	/// constructor with the default size.
	List(
		size_type const size,
		const_reference value,
		allocator_type const & allocator);

	/// constructor with values between two iterators.
	template <typename InputIteratorT>
	List(
		InputIteratorT begin,
		InputIteratorT end,
		allocator_type const & allocator);

	/// constructor with values between two iterators.
	template <typename InputIteratorT>
	List(InputIteratorT begin, InputIteratorT end);

	/// copy constructor.
	List(this_type const &);

	/// move constructor.
	List(this_type &&);

	/// destructor.
	~List();

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

	/// allocates memory region in advance.
	bool reserve(size_type const capacity);

	/// changes the size of the available elements.
	bool resize(size_type const size);

	/// appends a new value at the end of this list.
	bool push_back(const_reference addition);

	/// moves a value to the end of this list.
	bool push_back(value_type && addition);

	/// appends a new value at the beginning of this list.
	bool push_front(const_reference addition);

	/// moves a value to the beginning of this list.
	bool push_front(value_type && addition);

	/// removes the last value from the end of this list.
	bool pop_back();

	/// removes the last value from the beginning of this list.
	bool pop_front();

	/// retrieves the mutable iterator to beginning of the values.
	iterator begin();

	/// retrieves the immutable iterator to beginning of the values.
	const_iterator begin() const;

	/// retrieves the mutable iterator to end of the values.
	iterator end();

	/// retrieves the immutable iterator to end of the values.
	const_iterator end() const;

	/// retrieves the reversal mutable iterator to beginning of the values.
	reverse_iterator rbegin();

	/// retrieves the reversal immutable iterator to beginning of the values.
	const_reverse_iterator rbegin() const;

	/// retrieves the reversal mutable iterator to end of the values.
	reverse_iterator rend();

	/// retrieves the reversal immutable iterator to end of the values.
	const_reverse_iterator rend() const;

	/// confirms whether there is no value.
	bool empty() const;

	/// retrieves the size of values.
	size_type size() const;

	/// retrieves the maximum number of values to be allocated at this context.
	size_type max_size() const;

	/// retrieves the capacity of the current buffer.
	size_type capacity() const;

	/// retrieves the mutable front value.
	reference front();

	/// retrieves the immutable front value.
	const_reference front() const;

	/// retrieves the mutable last value.
	reference back();

	/// retrieves the immutable last value.
	const_reference back() const;

	/// assigns values in the range between two iterators.
	template <typename InputIteratorT>
	bool assign(InputIteratorT begin, InputIteratorT end);

	/// assigns multiple same values.
	bool assign(size_type const size, const_reference value);

	/// inserts a value.
	iterator insert(
		const_iterator position, const_reference value);

	/// inserts multiple same values.
	iterator insert(
		const_iterator position, size_type const size, const_reference value);

	/// inserts values in the range between two iterators.
	template <typename InputIteratorT>
	iterator insert(
		const_iterator position, InputIteratorT begin, InputIteratorT end);

	/// removes the value located at the specified position.
	iterator erase(const_iterator position);

	/// removes the values between two iterators.
	iterator erase(const_iterator begin, const_iterator end);

	/// rerieves the allocator.
	allocator_type get_allocator() const;

	/// confirms the equality between two instances.
	bool operator==(this_type const & rhs) const;

	/// confirms the inequality between two instances.
	bool operator!=(this_type const & rhs) const;

protected :

private :

	friend class iterator;
	friend typename iterator::base_type;
	friend class const_iterator;
	friend typename const_iterator::base_type;

	struct Node
	{
		Node()
			: prev_()
			  , next_()
			  , value_()
		{}

		Node(const_reference value)
			: prev_()
			  , next_()
			  , value_(value)
		{}

		index_type prev_;
		index_type next_;
		value_type value_;
	};
	typedef Node node_type;
	typedef node_type * node_pointer;
	typedef typename allocator_type::template rebind<node_type>::other
		node_allocator_type;

	/// instantiates a new value.
	node_pointer construct_value(
		index_type const & index);

	/// instantiates a new value with a copied resource.
	node_pointer construct_value(
		index_type const & index, const_reference src);

	/// instantiates a new value with a movable resource.
	node_pointer construct_value(
		index_type const & index, value_type && src);

	/// instantiates a new vacancy.
	node_pointer construct_vacancy(
		index_type const & index);

	/// retrieves the pointer to a mutable value.
	pointer inquire(index_type const & index);

	/// retrieves the pointer to a immutable value.
	const_pointer inquire(index_type const & index) const;

	/// retrieves the next node of the specified index.
	index_type next(index_type const & src) const;

	/// retrieves the previous node of the specified index.
	index_type prev(index_type const & src) const;

	/// retrieves the node specified by an index.
	node_pointer node(index_type const & index) const;

	/// retrieves the first vacant node.
	node_pointer front_vacancy() const;

	/// retrieves the last vacant node.
	node_pointer back_vacancy() const;

	/// retrieves the first filled node.
	node_pointer front_value() const;

	/// retrieves the last filled node.
	node_pointer back_value() const;

	/// consumes one unit of the vacant nodes.
	void acquire();

	/// reproduces one unit of vacant nodes.
	void restore(index_type const & index);

	/// connects a value at the end of values.
	void connect_back(node_pointer const value, index_type const & index);

	/// connects a value at the beginning of values.
	void connect_front(node_pointer const value, index_type const & index);

	node_allocator_type allocator_;
	node_pointer buffer_;
	index_type front_value_;
	index_type back_value_;
	index_type front_vacancy_;
	index_type back_vacancy_;
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
hryky::List<hryky_template_arg>::List()
	: allocator_()
	  , buffer_()
	  , front_value_()
	  , back_value_()
	  , front_vacancy_()
	  , back_vacancy_()
	  , size_()
	  , capacity_()
{
}
/**
  @brief constructor with an allocator.
 */
template <hryky_template_param>
hryky::List<hryky_template_arg>::List(allocator_type const & allocator)
	: allocator_(allocator)
	  , buffer_()
	  , front_value_()
	  , back_value_()
	  , front_vacancy_()
	  , back_vacancy_()
	  , size_()
	  , capacity_()
{
}
/**
  @brief constructor with the default size.
 */
template <hryky_template_param>
hryky::List<hryky_template_arg>::List(
	size_type const size,
	allocator_type const & allocator)
	: allocator_(allocator)
	  , buffer_()
	  , front_value_()
	  , back_value_()
	  , front_vacancy_()
	  , back_vacancy_()
	  , size_()
	  , capacity_()
{
	if (0u == size) {
		return;
	}

	this->buffer_ = this->allocator_.allocate(size);
	
	if (hryky_is_null(this->buffer_)) {
		return;
	}
	this->capacity_ = size;

	size_type index = 0u;
	node_pointer prev = this->construct_value(index);
	++index;

	for (; size != index; ++index) {
		node_pointer const next = this->construct_value(index);
		prev->next_ = index;
		next->prev_ = index - 1u;
		prev = next;
	}

	this->front_value_ = 0;
	this->back_value_ = size - 1u;
	this->size_ = size;
}
/**
  @brief constructor with the default size and value.
 */
template <hryky_template_param>
hryky::List<hryky_template_arg>::List(
	size_type const size,
	const_reference value,
	allocator_type const & allocator)
	: allocator_(allocator)
	  , buffer_()
	  , front_value_()
	  , back_value_()
	  , front_vacancy_()
	  , back_vacancy_()
	  , size_()
	  , capacity_()
{
	if (0u == size) {
		return;
	}

	this->buffer_ = this->allocator_.allocate(size);
	
	if (hryky_is_null(this->buffer_)) {
		return;
	}
	this->capacity_ = size;

	size_type index = 0u;
	node_pointer prev = this->construct_value(index, value);
	++index;

	for (; size != index; ++index) {
		node_pointer const next = this->construct_value(index, value);
		prev->next_ = index;
		next->prev_ = index - 1u;
		prev = next;
	}

	this->front_value_ = 0;
	this->back_value_ = size - 1u;
	this->size_ = size;
}
/**
  @brief constructor with values between two iterators.
 */
template <hryky_template_param>
template <typename InputIteratorT>
hryky::List<hryky_template_arg>::List(
	InputIteratorT begin,
	InputIteratorT end,
	allocator_type const & allocator)
	: allocator_(allocator)
	  , buffer_()
	  , front_value_()
	  , back_value_()
	  , front_vacancy_()
	  , back_vacancy_()
	  , size_()
	  , capacity_()
{
	size_type const size = static_cast<size_type>(::std::distance(begin, end));

	if (0u == size) {
		return;
	}

	this->buffer_ = this->allocator_.allocate(size);
	
	if (hryky_is_null(this->buffer_)) {
		return;
	}
	this->capacity_ = size;

	size_type index = 0;
	InputIteratorT itr = begin;
	node_pointer prev = this->construct_value(0, *itr);
	++itr;
	++index;

	for (; end != itr; ++itr, ++index) {
		node_pointer const next = this->construct_value(index, *itr);
		prev->next_ = index;
		next->prev_ = index - 1u;
		prev = next;
	}

	this->front_value_ = 0;
	this->back_value_ = size - 1u;
	this->size_ = size;
}
/**
  @brief constructor with values between two iterators.
 */
template <hryky_template_param>
template <typename InputIteratorT>
hryky::List<hryky_template_arg>::List(
	InputIteratorT begin, InputIteratorT end)
	: allocator_()
	  , buffer_()
	  , front_value_()
	  , back_value_()
	  , front_vacancy_()
	  , back_vacancy_()
	  , size_()
	  , capacity_()
{
	size_type const size = static_cast<size_type>(::std::distance(begin, end));

	if (0u == size) {
		return;
	}

	this->buffer_ = this->allocator_.allocate(size);
	
	if (hryky_is_null(this->buffer_)) {
		return;
	}
	this->capacity_ = size;

	size_type index = 0;
	InputIteratorT itr = begin;
	node_pointer prev = this->construct_value(0, *itr);
	++itr;
	++index;

	for (; end != itr; ++itr, ++index) {
		node_pointer const next = this->construct_value(index, *itr);
		prev->next_ = index;
		next->prev_ = index - 1u;
		prev = next;
	}

	this->front_value_ = 0;
	this->back_value_ = size - 1u;
	this->size_ = size;
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::List<hryky_template_arg>::List(this_type const & rhs)
	: hryky_copy_member(allocator)
	  , buffer_()
	  , front_value_()
	  , back_value_()
	  , front_vacancy_()
	  , back_vacancy_()
	  , size_()
	  , capacity_()
{
	size_type const size = rhs.size();

	if (0u == size) {
		return;
	}

	this->buffer_ = this->allocator_.allocate(rhs.capacity_);
	
	if (hryky_is_null(this->buffer_)) {
		return;
	}
	this->capacity_ = size;

	Foreach<this_type const> foreach(rhs);

	node_pointer prev = this->construct_value(0, *foreach);
	++foreach;

	for (; foreach.valid(); ++foreach) {
		size_type const index = foreach.offset();
		node_pointer const next = this->construct_value(index, *foreach);
		prev->next_ = index;
		next->prev_ = index - 1u;
		prev = next;
	}

	this->front_value_ = 0;
	this->back_value_ = size - 1u;
	this->size_ = size;
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::List<hryky_template_arg>::List(this_type && rhs)
	: allocator_()
	  , buffer_()
	  , front_value_()
	  , back_value_()
	  , front_vacancy_()
	  , back_vacancy_()
	  , size_()
	  , capacity_()
{
	this->swap(rhs);
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::List<hryky_template_arg>::~List()
{
	if (hryky_is_null(this->buffer_)) {
		return;
	}

	index_type index = this->front_value_;

	// workaround for unexpected condition.
	size_type count = this->size();
	
	while (!index.is_null() && 0 < count) {
		node_pointer const node = this->node(index);

		if (hryky_is_null(node)) {
			// unexpected.
			break;
		}
		
		index = node->next_;
		this->allocator_.destroy(node);
		--count;
	}
	hryky::clear(this->size_);
	hryky::clear(this->front_value_);
	hryky::clear(this->back_value_);
	hryky::clear(this->front_vacancy_);
	hryky::clear(this->back_vacancy_);

	this->allocator_.deallocate(this->buffer_, this->capacity_);
	hryky::clear(this->buffer_);
	hryky::clear(this->capacity_);
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::List<hryky_template_arg>::clear()
{
	this->resize(0);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::List<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(size);
	hryky_write_member(capacity);
	hryky_write_member(front_value);
	hryky_write_member(back_value);
	hryky_write_member(front_vacancy);
	hryky_write_member(back_vacancy);
	hryky_write_member(buffer);
	hryky_write_member(allocator);

	{
		out << stream::denote("values");
		stream::array::Scope<StreamT> const array(out);
		size_type const size = this->size();
		size_type count = 0;
		node_pointer node = this->front_value();
		while (!hryky_is_null(node) && count < size) {
			stream::map::Scope<StreamT> const node_map(out);

			out << stream::denote("prev") << node->prev_;
			out << stream::denote("next") << node->next_;
			out << stream::denote("value") << node->value_;
			
			node = this->node(node->next_);
			++count;
		}
	}

	{
		out << stream::denote("vacancies");
		stream::array::Scope<StreamT> const array(out);
		size_type const size = static_cast<size_type>(
			this->capacity() - this->size());
		size_type count = 0u;
		node_pointer node = this->front_vacancy();
		while (!hryky_is_null(node) && count < size) {
			stream::map::Scope<StreamT> const node_map(out);

			out << stream::denote("prev") << node->prev_;
			out << stream::denote("next") << node->next_;
			
			node = this->node(node->next_);
			++count;
		}
	}
	
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::List<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(allocator);
	hryky_swap_member(buffer);
	hryky_swap_member(front_value);
	hryky_swap_member(back_value);
	hryky_swap_member(front_vacancy);
	hryky_swap_member(back_vacancy);
	hryky_swap_member(size);
	hryky_swap_member(capacity);
}
/**
  @brief allocates memory region in advance.
 */
template <hryky_template_param>
bool hryky::List<hryky_template_arg>::reserve(size_type const capacity)
{
	if (this->capacity_ >= capacity) {
		return true;
	}

	node_pointer const buffer = this->allocator_.allocate(capacity);
	if (hryky_is_null(buffer)) {
		return false;
	}

	if (!this->empty()) {
		// copies the region including the vacancies.
		hryky::memcpy(
			buffer, this->buffer_, sizeof(node_type) * this->capacity_);
	}

	if (!hryky_is_null(this->buffer_)) {
		this->allocator_.deallocate(this->buffer_, this->capacity_);
	}

	// saves the size of the previous capacity.
	index_type const new_vacancy_index = this->capacity_;

	this->buffer_ = buffer;
	this->capacity_ = capacity;

	index_type const end_index = this->capacity_;
	index_type const back_vacancy_index = this->back_vacancy_;
	node_pointer const back_vacancy = this->back_vacancy();
	
	if (hryky_is_null(back_vacancy)) {
		// There is no vacant node.
		node_pointer const new_vacancy =
			this->construct_vacancy(new_vacancy_index);
		new_vacancy->next_ = end_index;
		this->back_vacancy_ = new_vacancy_index;
		this->front_vacancy_ = new_vacancy_index;
	}
	else if (new_vacancy_index == back_vacancy->next_) {
		// The last vacant node hasn't been used in the past.
		back_vacancy->next_ = end_index;
	}
	else {
		assert(back_vacancy->next_.is_null());
		
		// appends a new vacant node at the end of vacant nodes.
		back_vacancy->next_ = new_vacancy_index;
		this->back_vacancy_ = new_vacancy_index;
	}
	
	return true;
}
/**
  @brief changes the size of the available elements.
 */
template <hryky_template_param>
bool hryky::List<hryky_template_arg>::resize(size_type const size)
{
	hryky_list_resize();
	return true;
}
/**
  @brief appends a new value at the end of this list.
 */
template <hryky_template_param>
bool hryky::List<hryky_template_arg>::push_back(
	const_reference addition)
{
	if (this->size() == this->capacity()) {
		if (!this->reserve(static_cast<size_type>(
			(this->capacity() + 1u) << 1))) {
			return false;
		}
	}

	/**
	   The index of the new value has to be determined before the chain of
	  vacant nodes are modified.
	 */
	index_type const new_value_index = this->front_vacancy_;

	// consumes the first vacancy.
	this->acquire();

	/**
	  instantiates a new node. The region of the old vacancy is modified.
	 */
	node_pointer const new_value =
		this->construct_value(new_value_index, addition);

	// connects the new value to the end of the values.
	this->connect_back(new_value, new_value_index);

	++this->size_;
	
	return true;
}
/**
  @brief moves a value to the end of this list.
 */
template <hryky_template_param>
bool hryky::List<hryky_template_arg>::push_back(value_type && addition)
{
	if (this->size() == this->capacity()) {
		if (!this->reserve(static_cast<size_type>(
			(this->capacity() + 1u) << 1))) {
			return false;
		}
	}

	/**
	   The index of the new value has to be determined before the chain of
	  vacant nodes are modified.
	 */
	index_type const new_value_index = this->front_vacancy_;

	// consumes the first vacancy.
	this->acquire();

	/**
	  instantiates a new node. The region of the old vacancy is modified.
	 */
	node_pointer const new_value =
		this->construct_value(new_value_index, ::std::move(addition));

	// connects the new value to the end of the values.
	this->connect_back(new_value, new_value_index);

	++this->size_;
	
	return true;
}
/**
  @brief appends a new value at the beginning of this list.
 */
template <hryky_template_param>
bool hryky::List<hryky_template_arg>::push_front(
	const_reference addition)
{
	if (this->size() == this->capacity()) {
		if (!this->reserve(static_cast<size_type>(
			(this->capacity() + 1u) << 1))) {
			return false;
		}
	}

	/**
	   The index of the new value has to be determined before the chain of
	  vacant nodes are modified.
	 */
	index_type const new_value_index = this->front_vacancy_;

	// consumes the first vacancy.
	this->acquire();

	/**
	  instantiates a new node. The region of the old vacancy is modified.
	 */
	node_pointer const new_value =
		this->construct_value(new_value_index, addition);

	// connects the new value to the beginning of the values.
	this->connect_front(new_value, new_value_index);

	++this->size_;
	
	return true;
}
/**
  @brief moves a value to the beginning of this list.
 */
template <hryky_template_param>
bool hryky::List<hryky_template_arg>::push_front(value_type && addition)
{
	if (this->size() == this->capacity()) {
		if (!this->reserve((this->capacity() + 1u) << 1)) {
			return false;
		}
	}

	/**
	   The index of the new value has to be determined before the chain of
	  vacant nodes are modified.
	 */
	index_type const new_value_index = this->front_vacancy_;

	// consumes the first vacancy.
	this->acquire();

	/**
	  instantiates a new node. The region of the old vacancy is modified.
	 */
	node_pointer const new_value =
		this->construct_value(new_value_index, ::std::move(addition));

	// connects the new value to the beginning of the values.
	this->connect_front(new_value, new_value_index);

	++this->size_;
	
	return true;
}
/**
  @brief removes the last value from the end of this list.
 */
template <hryky_template_param>
bool hryky::List<hryky_template_arg>::pop_back()
{
	if (this->empty()) {
		return false;
	}

	index_type const old_value_index = this->back_value_;
	node_pointer const old_value = this->node(old_value_index);

	assert(old_value->next_.is_null());

	// removes a node from the end of the values.
	{
		this->back_value_ = old_value->prev_;
		if (old_value_index == this->front_value_) {
			// accommodates the front value to the back value.
			this->front_value_ = this->back_value_;
		}
		node_pointer const back_value = this->back_value();
		if (!hryky_is_null(back_value)) {
			assert(back_value->next_ == old_value_index);
			hryky::clear(back_value->next_);
		}
	}

	// destroies the removed node.
	this->allocator_.destroy(old_value);

	// reproduce a vacant node.
	this->restore(old_value_index);

	--this->size_;

	return true;
}
/**
  @brief removes the last value from the beginning of this list.
 */
template <hryky_template_param>
bool hryky::List<hryky_template_arg>::pop_front()
{
	if (this->empty()) {
		return false;
	}

	index_type const old_value_index = this->front_value_;
	node_pointer const old_value = this->node(old_value_index);

	assert(old_value->prev_.is_null());

	// removes a node from the beginning of the values.
	{
		this->front_value_ = old_value->next_;
		if (old_value_index == this->back_value_) {
			// accommodates the back value to the front value.
			this->back_value_ = this->front_value_;
		}
		node_pointer const front_value = this->front_value();
		if (!hryky_is_null(front_value)) {
			assert(front_value->prev_ == old_value_index);
			hryky::clear(front_value->prev_);
		}
	}

	// destroies the removed node.
	this->allocator_.destroy(old_value);

	// reproduce a vacant node.
	this->restore(old_value_index);

	--this->size_;

	return true;
}
/**
  @brief retrieves the mutable iterator to the beginning of the values.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::iterator 
hryky::List<hryky_template_arg>::begin()
{
	return iterator(this, this->front_value_);
}
/**
  @brief retrieves the immutable iterator to the beginning of the values.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::const_iterator 
hryky::List<hryky_template_arg>::begin() const
{
	return const_iterator(this, this->front_value_);
}
/**
  @brief retrieves the mutable iterator to the end of the values.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::iterator 
hryky::List<hryky_template_arg>::end()
{
	return iterator(this, index_type());
}
/**
  @brief retrieves the immutable iterator to the end of the values.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::const_iterator 
hryky::List<hryky_template_arg>::end() const
{
	return const_iterator(this, index_type());
}
/**
  @brief retrieves the reversal mutable iterator to the beginning of the values.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::reverse_iterator 
hryky::List<hryky_template_arg>::rbegin()
{
	return reverse_iterator(this->end());
}
/**
  @brief retrieves the reversal immutable iterator to the beginning of the values.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::const_reverse_iterator 
hryky::List<hryky_template_arg>::rbegin() const
{
	return const_reverse_iterator(this->end());
}
/**
  @brief retrieves the reversal mutable iterator to the end of the values.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::reverse_iterator 
hryky::List<hryky_template_arg>::rend()
{
	return reverse_iterator(this->begin());
}
/**
  @brief retrieves the reversal immutable iterator to the end of the values.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::const_reverse_iterator 
hryky::List<hryky_template_arg>::rend() const
{
	return const_reverse_iterator(this->begin());
}
/**
  @brief confirms whether there is no value.
 */
template <hryky_template_param>
bool hryky::List<hryky_template_arg>::empty() const
{
	return 0 == this->size_;
}
/**
  @brief retrieves the size of values.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::size_type 
hryky::List<hryky_template_arg>::size() const
{
	return this->size_;
}
/**
  @brief retrieves the capacity of the current buffer.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::size_type 
hryky::List<hryky_template_arg>::capacity() const
{
	return this->capacity_;
}
/**
  @brief retrieves the maximum number of values to be allocated at this context.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::size_type 
hryky::List<hryky_template_arg>::max_size() const
{
	return static_cast<size_type>(this->allocator_.max_size());
}
/**
  @brief retrieves the mutable front value.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::reference 
hryky::List<hryky_template_arg>::front()
{
	return this->front_value()->value_;
}
/**
  @brief retrieves the immutable front value.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::const_reference 
hryky::List<hryky_template_arg>::front() const
{
	return this->front_value()->value_;
}
/**
  @brief retrieves the mutable last value.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::reference 
hryky::List<hryky_template_arg>::back()
{
	return this->back_value()->value_;
}
/**
  @brief retrieves the immutable last value.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::const_reference 
hryky::List<hryky_template_arg>::back() const
{
	return this->back_value()->value_;
}
/**
  @brief assigns values in the range between two iterators.
 */
template <hryky_template_param>
template <typename InputIteratorT>
bool hryky::List<hryky_template_arg>::assign(
	InputIteratorT begin, InputIteratorT end)
{
	typedef ::std::iterator_traits<InputIteratorT> iterator_traits;
	
	iterator_traits::difference_type const size = ::std::distance(begin, end);

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

	hryky::range(begin, end).foreach([this](iterator_traits::reference ref) {
		this->push_back(ref);
	});
	return true;
}
/**
  @brief assigns multiple same values.
 */
template <hryky_template_param>
bool hryky::List<hryky_template_arg>::assign(
	size_type const size, const_reference value)
{
	if (!this->reserve(size)) {
		return false;
	}

	this->resize(0);

	hryky::repeat(size).foreach([this, &value]() {
		this->push_back(value);
	});
	
	return true;
}
/**
  @brief inserts a value.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::iterator 
hryky::List<hryky_template_arg>::insert(
	const_iterator position, const_reference value)
{
	index_type const index = position.index();

	if (this->end() != position
		&& hryky_is_null(this->node(index))) {
		// The argument is invalid.
		return this->end();
	}
	
	if (!this->reserve(this->size() + 1u)) {
		return this->end();
	}

	/**
	   The index of the new value has to be determined before the chain of
	  vacant nodes are modified.
	 */
	index_type const new_value_index = this->front_vacancy_;

	// consumes the first vacancy.
	this->acquire();

	/**
	  instantiates a new node. The region of the old vacancy is modified.
	 */
	node_pointer const new_value =
		this->construct_value(new_value_index, value);

	if (index.is_null()) {
		// The new node is inserted at the end of values.
		node_pointer const back_value = this->back_value();
		if (hryky_is_null(back_value)) {
			// The new value is the first value.
			this->front_value_ = new_value_index;
			this->back_value_ = new_value_index;
		}
		else {
			// updates the connection.
			assert(back_value->next_.is_null());
			
			back_value->next_ = new_value_index;
			new_value->prev_ = this->back_value_;
			this->back_value_ = new_value_index;
		}
	}
	else if (index == this->front_value_) {
		// The new node is inserted at the beginning of values.
		node_pointer const front_value = this->front_value();
		assert(front_value->prev_.is_null());
		
		new_value->next_ = this->front_value_;
		front_value->prev_ = new_value_index;
		this->front_value_ = new_value_index;
	}
	else {
		// The new node is inserted in the middle of values.
		node_pointer const next_value = this->node(index);
		assert(!next_value->prev_.is_null());
		
		node_pointer const prev_value = this->node(next_value->prev_);
		assert(!prev_value->next_.is_null());
		
		prev_value->next_ = new_value_index;
		new_value->prev_ = next_value->prev_;
		new_value->next_ = index;
		next_value->prev_ = new_value_index;
	}

	++this->size_;
	
	return iterator(this, new_value_index);
}
/**
  @brief inserts multiple same values.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::iterator 
hryky::List<hryky_template_arg>::insert(
	const_iterator position, size_type const size, const_reference value)
{
	if (0u == size) {
		return this->end();
	}
	
	if (!this->reserve(this->size() + size)) {
		return this->end();
	}

	const_iterator inserted = position;

	hryky::repeat(size).foreach([this, &inserted, &value]() {
		inserted = this->insert(inserted, value);
	});
	
	return inserted;
}
/**
  @brief inserts values in the range between two iterators.
 */
template <hryky_template_param>
template <typename InputIteratorT>
typename hryky::List<hryky_template_arg>::iterator 
hryky::List<hryky_template_arg>::insert(
	const_iterator position, InputIteratorT begin, InputIteratorT end)
{
	size_type const size = static_cast<size_type>(
		::std::distance(begin, end));
	if (0u == size) {
		return this->end();
	}

	InputIteratorT itr = begin;

	iterator inserted = this->insert(position, *itr);
	iterator const ret = inserted;
	++itr;
	++inserted;

	for (; end != itr; ++itr) {
		inserted = this->insert(inserted, *itr);
		++inserted;
	}
	
	return ret;
}
/**
  @brief removes the value located at the specified position.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::iterator 
hryky::List<hryky_template_arg>::erase(
	const_iterator position)
{
	if (this->empty()) {
		return this->end();
	}

	index_type const index = position.index();
	node_pointer const value = this->node(index);
	if (hryky_is_null(value)) {
		return this->end();
	}

	index_type const ret = value->next_;

	if (index == this->back_value_) {
		// The value is removed from the end of values.
		assert(value->next_.is_null());
		
		index_type const prev_index = value->prev_;
		node_pointer const prev = this->node(prev_index);
		if (!hryky_is_null(prev)) {
			assert(prev->next_ == index);
			hryky::clear(prev->next_);
		}

		this->back_value_ = prev_index;

		if (index == this->front_value_) {
			// accommodates the front value to the back value.
			this->front_value_ = this->back_value_;
		}
	}
	else if (index == this->front_value_) {
		// The value is removed from the beginning of values.
		assert(value->prev_.is_null());
		
		index_type const next_index = value->next_;
		node_pointer const next = this->node(next_index);
		if (!hryky_is_null(next)) {
			assert(next->prev_ == index);
			hryky::clear(next->prev_);
		}

		this->front_value_ = next_index;
	}
	else {
		// The value is removed from the middle of values.
		assert(!value->prev_.is_null());
		assert(!value->next_.is_null());
		
		node_pointer const prev = this->node(value->prev_);
		node_pointer const next = this->node(value->next_);
		
		prev->next_ = value->next_;
		next->prev_ = value->prev_;
	}
	

	this->allocator_.destroy(value);

	// reproduce a vacant node.
	this->restore(index);

	--this->size_;
	
	return iterator(this, ret);
}
/**
  @brief removes the values between two iterators.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::iterator 
hryky::List<hryky_template_arg>::erase(
	const_iterator begin, const_iterator end)
{
	const_iterator itr = begin;
	const_iterator const terminal = this->end();
	for (; terminal != itr && end != itr;) {
		itr = this->erase(itr);
	}
	return iterator(this, itr.index());
}
/**
  @brief rerieves the allocator.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::allocator_type 
hryky::List<hryky_template_arg>::get_allocator() const
{
	return allocator_type(this->allocator_);
}
/**
  @brief confirms the equality between two instances.
 */
template <hryky_template_param>
bool hryky::List<hryky_template_arg>::operator==(
	this_type const & rhs) const
{
	if (this->size() != rhs.size()) {
		return false;
	}

	const_iterator lhs_itr = this->begin();
	const_iterator const lhs_end = this->end();
	const_iterator rhs_itr = rhs.begin();

	for(; lhs_end != lhs_itr; ++lhs_itr, ++rhs_itr) {
		if (*lhs_itr != *rhs_itr) {
			return false;
		}
	}
	
	return true;
}
/**
  @brief confirms the inequality between two instances.
 */
template <hryky_template_param>
bool hryky::List<hryky_template_arg>::operator!=(
	this_type const & rhs) const
{
	return !this->operator==(rhs);
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief instantiates a new value.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::node_pointer 
hryky::List<hryky_template_arg>::construct_value(
	index_type const & index)
{
	node_pointer const node = this->node(index);
	if (hryky_is_null(node)) {
		return node;
	}
	this->allocator_.construct(node, value_type());

	return node;
}
/**
  @brief instantiates a new value with a copied resource.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::node_pointer 
hryky::List<hryky_template_arg>::construct_value(
	index_type const & index, const_reference src)
{
	node_pointer const node = this->node(index);
	if (hryky_is_null(node)) {
		return node;
	}
	this->allocator_.construct(node, src);

	return node;
}
/**
  @brief instantiates a new value with a movable resource.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::node_pointer 
hryky::List<hryky_template_arg>::construct_value(
	index_type const & index, value_type && src)
{
	node_pointer const node = this->node(index);
	if (hryky_is_null(node)) {
		return node;
	}
	this->allocator_.construct(node, ::std::move(src));
	
	return node;
}
/**
  @brief instantiates a new vacancy.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::node_pointer 
hryky::List<hryky_template_arg>::construct_vacancy(
	index_type const & index)
{
	node_pointer const node = this->node(index);
	if (hryky_is_null(node)) {
		return node;
	}

	this->allocator_.construct(node, node_type());

	return node;
}
/**
  @brief retrieves the pointer to a mutable value.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::pointer 
hryky::List<hryky_template_arg>::inquire(
	index_type const & index)
{
	node_pointer const node = this->node(index);
	
	return hryky_is_null(node) ? pointer() : &node->value_;
}
/**
  @brief retrieves the pointer to a immutable value.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::const_pointer 
hryky::List<hryky_template_arg>::inquire(
	index_type const & index) const
{
	node_pointer const node = this->node(index);
	
	return hryky_is_null(node) ? pointer() : &node->value_;
}
/**
  @brief retrieves the next node of the specified index.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::index_type 
hryky::List<hryky_template_arg>::next(
	index_type const & src) const
{
	return src.is_null() ? this->front_value_ : this->node(src)->next_;
}
/**
  @brief retrieves the previous node of the specified index.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::index_type 
hryky::List<hryky_template_arg>::prev(
	index_type const & src) const
{
	return src.is_null() ? this->back_value_ : this->node(src)->prev_;
}
/**
  @brief retrieves the node specified by an index.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::node_pointer 
hryky::List<hryky_template_arg>::node(
	index_type const & index) const
{
	return index.is_null() || this->capacity_ <= index.raw() ?
		node_pointer() : &this->buffer_[index.raw()];
}
/**
  @brief retrieves the first node of vacancy.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::node_pointer 
hryky::List<hryky_template_arg>::front_vacancy() const
{
	return this->node(this->front_vacancy_);
}
/**
  @brief retrieves the last node of vacancy.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::node_pointer 
hryky::List<hryky_template_arg>::back_vacancy() const
{
	return this->node(this->back_vacancy_);
}
/**
  @brief retrieves the first node of value.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::node_pointer 
hryky::List<hryky_template_arg>::front_value() const
{
	return this->node(this->front_value_);
}
/**
  @brief retrieves the last node of value.
 */
template <hryky_template_param>
typename hryky::List<hryky_template_arg>::node_pointer 
hryky::List<hryky_template_arg>::back_value() const
{
	return this->node(this->back_value_);
}
/**
  @brief consumes one unit of the vacant nodes.
 */
template <hryky_template_param>
void hryky::List<hryky_template_arg>::acquire()
{
	index_type const old_vacancy_index = this->front_vacancy_;
	node_pointer const old_vacancy = this->front_vacancy();

	assert(old_vacancy->prev_.is_null());

	if (old_vacancy->next_ == this->capacity_) {
		/**
		   There is only one vacant node at the end of the buffer.
		  The vacant node is shorten.
		 */
		index_type const new_vacancy_index = old_vacancy_index + 1;
		if (new_vacancy_index == this->capacity_) {
			hryky::clear(this->front_vacancy_);
		}
		else {
			node_pointer const new_vacancy =
				this->construct_vacancy(new_vacancy_index);
			new_vacancy->next_ = this->capacity_;
			this->front_vacancy_ = new_vacancy_index;
		}
	}
	else {
		/**
		   The consumed node is at the middle of the buffer. The node
		  is used up.
		 */
		index_type const new_vacancy_index = old_vacancy->next_;
		node_pointer const new_vacancy = this->node(new_vacancy_index);
		if (!hryky_is_null(new_vacancy)) {
			hryky::clear(new_vacancy->prev_);
		}
		this->front_vacancy_ = new_vacancy_index;
	}

	if (old_vacancy_index == this->back_vacancy_) {
		// accommodates the last vacant node to the first vacant node.
		this->back_vacancy_ = this->front_vacancy_;
	}
}
/**
  @brief reproduces one unit of vacant nodes.
 */
template <hryky_template_param>
void hryky::List<hryky_template_arg>::restore(index_type const & index)
{
	// instantiates a new vacant node.
	node_pointer const new_vacancy = this->construct_vacancy(index);

	// connects the new vacant node with the chain of the vacant nodes.
	index_type const old_vacancy_index = this->front_vacancy_;
	node_pointer const old_vacancy = this->front_vacancy();

	if (hryky_is_null(old_vacancy)) {
		// The removed node becames the first vacant node.
		this->back_vacancy_ = index;
		if (index + 1 == this->capacity_) {
			// The removed node is at the end of buffer.
			new_vacancy->next_ = this->capacity_;
		}
	}
	else {
		assert(old_vacancy->prev_.is_null());
		
		// connect the new vacant node at the beginning.
		new_vacancy->next_ = old_vacancy_index;
		old_vacancy->prev_ = index;
	}

	this->front_vacancy_ = index;
}
/**
  @brief connects a value at the end of values.
 */
template <hryky_template_param>
void hryky::List<hryky_template_arg>::connect_back(
	node_pointer const value, index_type const & index)
{
	node_pointer const back_value = this->back_value();
	if (hryky_is_null(back_value)) {
		// The new value is the first value.
		this->front_value_ = index;
		this->back_value_ = index;
	}
	else {
		// updates the last value.
		assert(back_value->next_.is_null());
		back_value->next_ = index;
		value->prev_ = this->back_value_;
		this->back_value_ = index;
	}
}
/**
  @brief connects a value at the beginning of values.
 */
template <hryky_template_param>
void hryky::List<hryky_template_arg>::connect_front(
	node_pointer const value, index_type const & index)
{
	node_pointer const front_value = this->front_value();
	if (hryky_is_null(front_value)) {
		// The new value is the first value.
		this->front_value_ = index;
		this->back_value_ = index;
	}
	else {
		// updates the last value.
		assert(front_value->prev_.is_null());
		value->next_ = this->front_value_;
		front_value->prev_ = index;
		this->front_value_ = index;
	}
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
#undef hryky_list_resize
#undef hryky_iterator
#undef hryky_const_iterator
#endif // LIST_H_20130413170355377
// end of file
