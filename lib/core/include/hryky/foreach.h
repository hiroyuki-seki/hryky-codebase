/**
  @file         foreach.h
  @brief        utility for the iteration of a container.
  @author       HRYKY
  @version      $Id: foreach.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef FOREACH_H_20120906225616622
#define FOREACH_H_20120906225616622
#include "hryky/definition.h"
#include "hryky/std/std_iterator.h"
#include "hryky/type_traits/iterator_of.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ContainerT, typename IteratorT
#define hryky_template_arg \
	ContainerT, IteratorT

#define hryky_foreach(ref, container, func) { \
	Foreach<decltype(container)> foreach(container);\
	for (; foreach.valid(); ++foreach) { \
		::std::iterator_traits<\
			hryky::IteratorOf<\
				decltype(container)>::type>::reference ref = *foreach; \
		func; \
	}\
}

//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// utility for the iteration of a container.
	template <hryky_template_param>
	class Foreach;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief utility for the iteration of a container.

   This class can be useful rather than foreach() function of each container
  if the unit of iteration is not one by one.
 */
template <
	typename ContainerT,
	typename IteratorT = typename hryky::IteratorOf<ContainerT>::type >
class hryky::Foreach :
	public WithStreamOut<Foreach<hryky_template_arg> >,
	public WithSwap<Foreach<hryky_template_arg> >
{
public :

	typedef Foreach<hryky_template_arg> this_type;
	typedef IteratorT iterator;
	typedef typename ContainerT::size_type size_type;

	typedef typename ::std::iterator_traits<IteratorT>::difference_type
		difference_type;
	typedef typename ::std::iterator_traits<IteratorT>::reference
		reference;
	typedef typename ::std::iterator_traits<IteratorT>::pointer
		pointer;
	

	/// container with the container which is iterated.
	Foreach(ContainerT & container);

	/// copy constructor.
	Foreach(this_type const &);

	/// move constructor.
	Foreach(this_type && rhs);

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// outputs the information formatted as string.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// forwards the internal iterator by the specified steps.
	this_type & operator+=(size_type const size);

	/// backs the internal iterator by the specified steps.
	this_type & operator-=(size_type const size);

	/// pre-increment operator.
	this_type & operator++();

	/// post-increment operator.
	this_type operator++(int);

	/// dereferences the current iterator.
	reference operator*() const;

	/// dereferences the current iterator as pointer.
	pointer operator->() const;

	/// forwards the current iterator.
	this_type operator+(difference_type const rhs) const;

	/// confirms whether the current iterator doesn't reached at the end.
	bool valid() const;

	/**
	  retrieves the distance from the beginning of the container to
	  the current position.
	 */
	size_type offset() const;

	/// retrieves the beginning of the range.
	iterator begin() const;

	/// retrieves the end of the range.
	iterator end() const;

	/// retrieves the current iterator.
	iterator itr() const;

	/// retrieves the length of the range.
	size_type size() const;

	/// resets the iterator at the beginning of the range.
	void restart();

protected :

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

private :

	hryky_delete_default_constructor(Foreach);

	iterator begin_;
	iterator end_;
	iterator itr_;
	size_type offset_;

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
  @brief constructor with the container which is iterated.
 */
template <hryky_template_param>
hryky::Foreach<hryky_template_arg>::Foreach(ContainerT & container)
	: begin_(container.begin())
	  , end_(container.end())
	  , itr_(begin_)
	  , offset_()
{
	return;
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::Foreach<hryky_template_arg>::Foreach(this_type const & rhs)
	: hryky_copy_member(begin)
	  , hryky_copy_member(end)
	  , hryky_copy_member(itr)
	  , hryky_copy_member(offset)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::Foreach<hryky_template_arg>::Foreach(this_type && rhs)
	: hryky_move_member(begin)
	  , hryky_move_member(end)
	  , hryky_move_member(itr)
	  , hryky_move_member(offset)
{
}
/**
  @brief outputs the information formatted as string.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::Foreach<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(begin);
	hryky_write_member(end);
	hryky_write_member(itr);
	hryky_write_member(offset);
	
	return out;
}
/**
  @brief forwards the internal iterator by the specified steps.
 */
template <hryky_template_param>
hryky::Foreach<hryky_template_arg> & 
hryky::Foreach<hryky_template_arg>::operator+=(
	size_type const size)
{
	::std::advance(this->itr_, size);
	this->offset_ += size;
	return *this;
}
/**
  @brief backs the internal iterator by the specified steps.
 */
template <hryky_template_param>
hryky::Foreach<hryky_template_arg> & 
hryky::Foreach<hryky_template_arg>::operator-=(
	size_type const size)
{
	::std::advance(this->itr_, -size);
	this->offset_ -= size;
	return *this;
}
/**
  @brief pre-increment operator.
 */
template <hryky_template_param>
hryky::Foreach<hryky_template_arg> & 
hryky::Foreach<hryky_template_arg>::operator++()
{
	return this->operator+=(1);
}
/**
  @brief post-increment operator.
 */
template <hryky_template_param>
hryky::Foreach<hryky_template_arg>
hryky::Foreach<hryky_template_arg>::operator++(int)
{
	this_type const result(*this);

	this->operator++();
	
	return result;
}
/**
  @brief dereferences the current iterator.
 */
template <hryky_template_param>
typename hryky::Foreach<hryky_template_arg>::reference 
hryky::Foreach<hryky_template_arg>::operator*() const
{
	return *this->itr_;
}
/**
  @brief dereferences the current iterator as pointer.
 */
template <hryky_template_param>
typename hryky::Foreach<hryky_template_arg>::pointer 
hryky::Foreach<hryky_template_arg>::operator->() const
{
	return &*(this->itr_);
}
/**
  @brief retrieves a new advanced iterator.
 */
template <hryky_template_param>
hryky::Foreach<hryky_template_arg> 
hryky::Foreach<hryky_template_arg>::operator+(
	difference_type const rhs) const
{
	this_type result(*this);

	result += rhs;
	
	return result;
}
/**
  @brief confirms whether the current iterator doesn't reached at the end.
 */
template <hryky_template_param>
bool hryky::Foreach<hryky_template_arg>::valid() const
{
	return this->end_ != this->itr_;
}
/**
  @brief retrieves the distance from the beginning of the container to
   the current position.
 */
template <hryky_template_param>
typename hryky::Foreach<hryky_template_arg>::size_type
hryky::Foreach<hryky_template_arg>::offset() const
{
	return this->offset_;
}
/**
  @brief retrieves the beginning of the range.
 */
template <hryky_template_param>
IteratorT hryky::Foreach<hryky_template_arg>::begin() const
{
	return this->begin_;
}
/**
  @brief retrieves the end of the range.
 */
template <hryky_template_param>
IteratorT hryky::Foreach<hryky_template_arg>::end() const
{
	return this->end_;
}
/**
  @brief retrieves the current iterator.
 */
template <hryky_template_param>
IteratorT hryky::Foreach<hryky_template_arg>::itr() const
{
	return this->itr_;
}
/**
  @brief retrieves the length of the range.
 */
template <hryky_template_param>
typename hryky::Foreach<hryky_template_arg>::size_type 
hryky::Foreach<hryky_template_arg>::size() const
{
	return ::std::distance(this->begin(), this->end());
}
/**
  @brief resets the iterator at the beginning of the range.
 */
template <hryky_template_param>
void hryky::Foreach<hryky_template_arg>::restart()
{
	this->itr_ = this->begin_;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::Foreach<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(begin);
	hryky_swap_member(end);
	hryky_swap_member(itr);
	hryky_swap_member(offset);
}
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{

	/// iterates each element with an arbitrary function.
	template <typename ContainerT, typename FunctorT>
	void foreach(ContainerT & container, FunctorT const & functor);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief iterates each element with an arbitrary function.
 */
template <typename ContainerT, typename FunctorT>
void hryky::foreach(ContainerT & container, FunctorT const & functor)
{
	Foreach<ContainerT> foreach(container);
	for (; foreach.valid(); ++foreach) {
		functor(*foreach);
	}
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // FOREACH_H_20120906225616622
// end of file
