/**
  @file     exclusion_queue.h
  @brief    synchronizes the modification of a queue.
  @author   HRYKY
  @version  $Id: exclusion_queue.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef EXCLUSION_QUEUE_H_20130407152025305
#define EXCLUSION_QUEUE_H_20130407152025305
#include "hryky/definition.h"
#include "hryky/clear.h"
#include "hryky/exclusion/exclusion_mutex.h"
#include "hryky/type_traits/as_parameter.h"
#include "hryky/type_traits/add_reference.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ContainerT, typename LockableT
#define hryky_template_arg \
	ContainerT, LockableT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace exclusion
{
	/// synchronizes the modification of a queue.
	template <hryky_template_param>
	class Queue;

} // namespace exclusion
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief synchronizes the modification of a queue.
 */
template <
	typename ContainerT,
	typename LockableT = Mutex>
class hryky::exclusion::Queue
{
public :

	typedef Queue<hryky_template_arg>               this_type;
	typedef ContainerT                              container_type;
	typedef typename container_type::value_type     value_type;
	typedef typename container_type::reference      reference;
	typedef typename AsParameter<value_type>::type  parameter_type;
	typedef typename container_type::size_type      size_type;

	/// default constructor.
	Queue();

	/// constructor with a container.
	Queue(container_type const & container);

	/// copy constructor.
	Queue(this_type const &);

	/// move constructor.
	Queue(this_type &&);

	/// destructor.
	~Queue();

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the containers.
	void swap(container_type & src);

	/// retrieves the internal container.
	ContainerT const & container() const;

	/// appends a new value to the end of the container.
	bool push(parameter_type src);

	/// appends new values to the end of the container.
	template <typename InputIteratorT>
	bool push(InputIteratorT first, InputIteratorT last);

	/// removes the value from the beginning of the container.
	bool pop(reference dest);

	/// removes the values from the beginning of the container.
	template <typename OutputIterator>
	size_type pop(OutputIterator dest, size_type const size);

	/// retrieves the size of the container.
	size_type size() const;

	/// confirms whether there is no value in the container.
	bool empty() const;

protected :

private :

	typedef Lock<LockableT> lock_type;

	hryky_delete_this_copy_assign_op(Queue);
	
	container_type container_;
	LockableT lockable_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace exclusion
{
} // namespace exclusion
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::exclusion::Queue<hryky_template_arg>::Queue()
	: container_()
	  , lockable_()
{
}
/**
  @brief constructor with a container.
 */
template <hryky_template_param>
hryky::exclusion::Queue<hryky_template_arg>::Queue(
	container_type const &)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::exclusion::Queue<hryky_template_arg>::Queue(this_type const & rhs)
	: hryky_copy_member(container)
	  , lockable_()
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::exclusion::Queue<hryky_template_arg>::Queue(this_type && rhs)
	: hryky_move_member(container)
	  , lockable_()
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::exclusion::Queue<hryky_template_arg>::~Queue()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::exclusion::Queue<hryky_template_arg>::clear()
{
	lock_type const lock(this->lockable_);
	
	hryky::clear(this->container_);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & 
hryky::exclusion::Queue<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(container);
	return out;
}
/**
  @brief interchanges the containers.
 */
template <hryky_template_param>
void hryky::exclusion::Queue<hryky_template_arg>::swap(container_type & src)
{
	lock_type const lock(this->lockable_);
	this->container_.swap(src);
}
/**
  @brief retrieves the internal container.
 */
template <hryky_template_param>
ContainerT const & 
hryky::exclusion::Queue<hryky_template_arg>::container() const
{
	return this->container_;
}
/**
  @brief appends a new value to the end of the container.
 */
template <hryky_template_param>
bool hryky::exclusion::Queue<hryky_template_arg>::push(parameter_type src)
{
	lock_type const lock(this->lockable_);

	return this->container_.push_back(src);
}
/**
  @brief appends new values to the end of the container.
 */
template <hryky_template_param>
template <typename InputIteratorT>
bool hryky::exclusion::Queue<hryky_template_arg>::push(
	InputIteratorT first, InputIteratorT last)
{
	lock_type const lock(this->lockable_);

	ContainerT::iterator const result = 
		this->container_.insert(this->container_.end(), first, last);

	return result != this->container_.end();
}
/**
  @brief removes the value from the beginning of the container.
 */
template <hryky_template_param>
bool hryky::exclusion::Queue<hryky_template_arg>::pop(reference dest)
{
	if (this->empty()) {
		return false;
	}

	lock_type const lock(this->lockable_);

	if (this->empty()) {
		return false;
	}

	dest = this->container_.back();

	this->container_.pop_back();
	
	return dest;
}
/**
  @brief removes the values from the beginning of the container.
 */
template <hryky_template_param>
template <typename OutputIterator>
typename ContainerT::size_type 
hryky::exclusion::Queue<hryky_template_arg>::pop(
	OutputIterator dest, size_type const size)
{
	if (this->empty()) {
		return 0;
	}

	lock_type const lock(this->lockable_);

	if (this->empty()) {
		return 0;
	}

	typedef container_type::iterator        iterator;
	typedef container_type::difference_type difference_type;

	size_type const container_size = this->size();
	size_type const popped_size =
		::std::min<size_type>(container_size, size);

	iterator const first = this->container_.begin();
	iterator const last = ::std::next(
		first, static_cast<difference_type>(popped_size));

	hryky::range(first, last).foreach([&dest](
		container_type::const_reference ref) {
		*(dest++) = ref;
	});
	this->container_.erase(first, last);

	return popped_size;
}
/**
  @brief retrieves the size of the container.
 */
template <hryky_template_param>
typename ContainerT::size_type 
hryky::exclusion::Queue<hryky_template_arg>::size() const
{
	return this->container_.size();
}
/**
  @brief confirms whether there is no value in the container.
 */
template <hryky_template_param>
bool hryky::exclusion::Queue<hryky_template_arg>::empty() const
{
	return this->container_.empty();
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
namespace exclusion
{

} // namespace exclusion
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // EXCLUSION_QUEUE_H_20130407152025305
// end of file
