/**
  @file     exclusion_stack.h
  @brief    synchronizes the modification of a stack.
  @author   HRYKY
  @version  $Id: exclusion_stack.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef EXCLUSION_STACK_H_20130330211022548
#define EXCLUSION_STACK_H_20130330211022548
#include "hryky/definition.h"
#include "hryky/clear.h"
#include "hryky/exclusion/exclusion_mutex.h"
#include "hryky/type_traits/add_reference.h"
#include "hryky/type_traits/as_parameter.h"
#include "hryky/with_stream_out.h"
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
	/// synchronizes the modification of a stack.
	template <hryky_template_param>
	class Stack;

} // namespace exclusion
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief synchronizes the modification of a stack.
 */
template <
	typename ContainerT,
	typename LockableT = exclusion::Mutex>
class hryky::exclusion::Stack :
	public WithStreamOut<Stack<hryky_template_arg> >
{
public :

	typedef Stack<hryky_template_arg>               this_type;
	typedef ContainerT                              container_type;
	typedef typename container_type::value_type     value_type;
	typedef typename AddReference<value_type>::type reference;
	typedef typename AsParameter<value_type>::type  parameter_type;
	typedef typename container_type::size_type      size_type;

	/// default constructor.
	Stack();

	/// constructor with values in other container.
	Stack(container_type const & rhs);

	/// copy constructor.
	Stack(this_type const & rhs);

	/// move constructor.
	Stack(this_type && rhs);

	/// destructor.
	~Stack();

	/// assigns a new container.
	this_type & operator=(container_type const & rhs);

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// appends a new value at the end of the container.
	bool push(parameter_type src);

	/// appends new values at the end of the container.
	template <typename InputIteratorT>
	bool push(InputIteratorT first, InputIteratorT last);

	/// removes the value from the end of the container.
	bool pop(reference dest);

	/// removes the values from the end of the container.
	template <typename OutputIterator>
	size_type pop(OutputIterator dest, size_type const size);

	/// retrieves the size of the container.
	size_type size() const;

	/// confims whether there is no value in the container.
	bool empty() const;

	/// retrieves the immutable container.
	container_type const & container() const;

	/// interchanges the containers.
	void swap(container_type & src);

protected :

private :

	typedef LockableT lockable_type;
	typedef Lock<lockable_type> lock_type;

	hryky_delete_this_copy_assign_op(Stack);

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
hryky::exclusion::Stack<hryky_template_arg>::Stack()
	: container_()
	  , lockable_()
{
}
/**
  @brief constructor with values in other container.
 */
template <hryky_template_param>
hryky::exclusion::Stack<hryky_template_arg>::Stack(
	container_type const & container)
	: container_(container)
	  , lockable_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::exclusion::Stack<hryky_template_arg>::Stack(this_type const & rhs)
	: hryky_copy_member(container)
	  , lockable_()
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::exclusion::Stack<hryky_template_arg>::Stack(this_type && rhs)
	: hryky_move_member(container)
	  , lockable_()
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::exclusion::Stack<hryky_template_arg>::~Stack()
{
}
/**
  @brief assigns a new container.
 */
template <hryky_template_param>
hryky::exclusion::Stack<hryky_template_arg> & 
hryky::exclusion::Stack<hryky_template_arg>::operator=(
	container_type const & rhs)
{
	lock_type const lock(this->lockable_);

	this->container_ = rhs;
	
	return *this;
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::exclusion::Stack<hryky_template_arg>::clear()
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
hryky::exclusion::Stack<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(container);
	return out;
}
/**
  @brief appends a new value at the end of the container.
 */
template <hryky_template_param>
bool hryky::exclusion::Stack<hryky_template_arg>::push(
	parameter_type src)
{
	lock_type const lock(this->lockable_);

	return this->container_.push_back(src);
}
/**
  @brief appends new values at the end of the container.
 */
template <hryky_template_param>
template <typename InputIteratorT>
bool hryky::exclusion::Stack<hryky_template_arg>::push(
	InputIteratorT first, InputIteratorT last)
{
	lock_type const lock(this->lockable_);
	
	return this->container_.insert(
		this->container_.end(), first, last);
}
/**
  @brief removes the value from the end of the container.
 */
template <hryky_template_param>
bool hryky::exclusion::Stack<hryky_template_arg>::pop(
	reference dest)
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
	
	return true;
}
/**
  @brief removes the values from the end of the container.
 */
template <hryky_template_param>
template <typename OutputIterator>
typename ContainerT::size_type
hryky::exclusion::Stack<hryky_template_arg>::pop(
	OutputIterator dest, size_type const size)
{
	if (this->empty()) {
		return 0;
	}

	lock_type const lock(this->lockable_);

	if (this->empty()) {
		return 0;
	}

	size_type const container_size = this->size();
	size_type const popped_size =
		::std::min<size_type>(container_size, size);

	typedef container_type::difference_type difference_type;

	hryky::range(
		this->container_.rbegin(),
		::std::next(
			this->container_.rbegin(),
			static_cast<difference_type>(popped_size))).foreach(
				[&dest](container_type::const_reference ref) {
					*(dest++) = ref;
				});
	this->container_.resize(container_size - popped_size);
	
	return popped_size;
}
/**
  @brief retrieves the size of the container.
 */
template <hryky_template_param>
typename ContainerT::size_type 
hryky::exclusion::Stack<hryky_template_arg>::size() const
{
	return this->container_.size();
}
/**
  @brief confims whether there is no value in the container.
 */
template <hryky_template_param>
bool hryky::exclusion::Stack<hryky_template_arg>::empty() const
{
	return this->container_.empty();
}
/**
  @brief retrieves the immutable container.
 */
template <hryky_template_param>
ContainerT const & 
hryky::exclusion::Stack<hryky_template_arg>::container() const
{
	return this->container_;
}
/**
  @brief interchanges the containers.
 */
template <hryky_template_param>
void hryky::exclusion::Stack<hryky_template_arg>::swap(
	container_type & src)
{
	lock_type const lock(this->lockable_);
	this->container_.swap(src);
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
#endif // EXCLUSION_STACK_H_20130330211022548
// end of file
