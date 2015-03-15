/**
  @file         range.h
  @brief        encloses the existing iterators as a new range.
  @author       HRYKY
  @version      $Id: range.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef RANGE_H_20120205174018402
#define RANGE_H_20120205174018402
#include "hryky/foreach.h"
#include "hryky/integer/unsigned_of.h"
#include "hryky/type_traits/as_parameter.h"
#include "hryky/type_traits/iterator_of.h"
#include "hryky/with_iteration.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename IteratorT, typename SizeT
#define hryky_template_arg \
	IteratorT, SizeT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// encloses the existing iterators as a new range.
	template <hryky_template_param>
	class Range;

}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief encloses the existing iterators as a new range.
 */
template <
	typename IteratorT,
	typename SizeT = typename UnsignedOf<
		typename ::std::iterator_traits<IteratorT>::difference_type>::type
>
class hryky::Range :
	public WithIteration<
		Range<hryky_template_arg>,
		IteratorT,
		IteratorT>,
	public WithStreamOut<Range<hryky_template_arg> >,
	public WithSwap<Range<hryky_template_arg> >
{
public :

	typedef Range<hryky_template_arg>                   this_type;
	typedef IteratorT                                   iterator;
	typedef typename AsParameter<iterator>::type        iterator_param_type;
	typedef ::std::iterator_traits<IteratorT>             iterator_traits;
	typedef typename iterator_traits::difference_type   difference_type;
	typedef typename iterator_traits::value_type        value_type;
	typedef typename iterator_traits::pointer           pointer;
	typedef typename iterator_traits::reference         reference;
	typedef SizeT                                       size_type;

	/// constructor with parameters
	Range(iterator_param_type begin, iterator_param_type end);

	/// copy constructor.
	Range(this_type const & rhs);

	/// move constructor.
	Range(this_type && rhs);

	/// destructor.
	~Range();

	/// copy-assignment operator.
	hryky_assign_op;

	/// move-assignment operator.
	hryky_move_assign_op;

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// retrieves the beginning of the range
	iterator begin() const;

	/// retrieves the end of the range
	iterator end() const;

	/// confirms whether the range is empty
	bool empty() const;

	/// retrieves the length of the range.
	size_type size() const;

	/// retrieves the immutable element with offset.
	reference operator[](size_type const index) const;

protected :

private :

	typedef WithIteration<
		Range<hryky_template_arg>,
		IteratorT,
		IteratorT> with_iteration;

	IteratorT   begin_;
	IteratorT   end_;

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  constructor with parameters
 */
template <hryky_template_param>
hryky::Range<hryky_template_arg>::Range(
	iterator_param_type begin, iterator_param_type end)
	: begin_(begin)
	  , end_(end)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::Range<hryky_template_arg>::Range(this_type const & rhs)
	: hryky_copy_member(begin)
	  , hryky_copy_member(end)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::Range<hryky_template_arg>::Range(this_type && rhs)
	: hryky_move_member(begin)
	  , hryky_move_member(end)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::Range<hryky_template_arg>::~Range()
{
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::Range<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	out << stream::denote("size") << this->size();

	return this->with_iteration::write_to(out);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::Range<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(begin);
	hryky_swap_member(end);
}
/**
  retrieves the beginning of the range
 */
template <hryky_template_param>
typename hryky::Range<hryky_template_arg>::iterator
hryky::Range<hryky_template_arg>::begin() const
{
	return this->begin_;
}
/**
  retrieves the end of the range
 */
template <hryky_template_param>
typename hryky::Range<hryky_template_arg>::iterator
hryky::Range<hryky_template_arg>::end() const
{
	return this->end_;
}
/**
  confirms whether the range is empty
 */
template <hryky_template_param>
bool hryky::Range<hryky_template_arg>::empty() const
{
	return this->begin_ == this->end_;
}
/**
  retrieves the length of the range.
 */
template <hryky_template_param>
typename hryky::Range<hryky_template_arg>::size_type
hryky::Range<hryky_template_arg>::size() const
{
	return static_cast<size_type>(
		::std::distance(this->begin(), this->end()));
}
/**
  @brief retrieves the immutable element with offset.
 */
template <hryky_template_param>
typename hryky::Range<hryky_template_arg>::reference
hryky::Range<hryky_template_arg>::operator[](size_type const index) const
{
	IteratorT itr = this->begin_;
	
	::std::advance(itr, index);

	return *itr;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// global functions prototypes
//------------------------------------------------------------------------------
namespace hryky
{
	/// creates hryky::Range.
	template <typename IteratorT>
	Range<IteratorT> range(IteratorT begin, IteratorT end);

	/// creates hryky::Range from an array.
	template < typename ValueT, size_t Size >
	Range<ValueT *> range(ValueT (&array)[Size]);

	/// creates hryky::Range from a container.
	template <typename ContainerT>
	Range<typename IteratorOf<ContainerT>::type>
		range(ContainerT & container);

} // namespace hryky
//------------------------------------------------------------------------------
// global functions definitions
//------------------------------------------------------------------------------
/**
  @brief creates hryky::Range.
 */
template <typename IteratorT>
hryky::Range<IteratorT>
hryky::range(IteratorT begin, IteratorT end)
{
	return Range<IteratorT>(begin, end);
}
/**
  @brief creates hryky::Range from an array.
 */
template < typename ValueT, size_t Size >
hryky::Range<ValueT *>
hryky::range(ValueT (&array)[Size])
{
	return Range<ValueT *>(&array[0], &array[Size]);
}
/**
  @brief creates hryky::Range from a container.
 */
template <typename ContainerT>
hryky::Range<typename hryky::IteratorOf<ContainerT>::type>
hryky::range(ContainerT & container)
{
	return Range<typename IteratorOf<ContainerT>::type>(
		container.begin(), container.end());
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // RANGE_H_20120205174018402
// end of file
