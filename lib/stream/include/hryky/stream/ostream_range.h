/**
  @file     ostream_range.h
  @brief    creates an output-stream from the range between two iterators.
  @author   HRYKY
  @version  $Id: ostream_range.h 341 2014-03-29 06:35:02Z hryky.private@gmail.com $
 */
#ifndef OSTREAM_RANGE_H_20140325225712623
#define OSTREAM_RANGE_H_20140325225712623
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/type_traits/as_parameter.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename IteratorT
#define hryky_template_arg \
	IteratorT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace ostream
{
	/// creates an output-stream from the range between two iterators.
	template <hryky_template_param>
	class Range;

} // namespace ostream
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief creates an output-stream from the range between two iterators.
 */
template <hryky_template_param>
class hryky::ostream::Range :
	public WithStreamOut<Range<hryky_template_arg> >,
	public WithSwap<Range<hryky_template_arg> >
{
public :

	typedef Range<hryky_template_arg>               this_type;
	typedef typename AsParameter<IteratorT>::type   param_type;

	/// default constructor.
	Range();

	/// copy constructor.
	Range(this_type const &);

	/// move constructor.
	Range(this_type &&);

	/// instantiates with the range between two iterators.
	Range(param_type begin, param_type end);

	/// destructor.
	~Range();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// confirms whether the iterator reach the end.
	bool eof() const;

	/// appends a value of arbitrary type.
	template <typename RhsT>
	this_type & operator<<(RhsT rhs);

protected :

private :

	IteratorT itr_;
	IteratorT end_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace ostream
{
} // namespace ostream
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::ostream::Range<hryky_template_arg>::Range()
	: itr_()
	  , end_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::ostream::Range<hryky_template_arg>::Range(this_type const & rhs)
	: hryky_copy_member(itr)
	  , hryky_copy_member(end)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::ostream::Range<hryky_template_arg>::Range(this_type && rhs)
	: hryky_move_member(itr)
	  , hryky_move_member(end)
{
}
/**
  @brief instantiates with the range between two iterators.
 */
template <hryky_template_param>
hryky::ostream::Range<hryky_template_arg>::Range(
	param_type begin, param_type end)
	: itr_(begin)
	  , end_(end)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::ostream::Range<hryky_template_arg>::~Range()
{
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::ostream::Range<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(itr);
	hryky_swap_member(end);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::ostream::Range<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(itr);
	hryky_write_member(end);
	return out;
}
/**
  @brief confirms whether the iterator reach the end.
 */
template <hryky_template_param>
bool hryky::ostream::Range<hryky_template_arg>::eof() const
{
	return this->end_ == this->itr_;
}
/**
  @brief appends a value of arbitrary type.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::ostream::Range<hryky_template_arg> & 
hryky::ostream::Range<hryky_template_arg>::operator<<(
	RhsT rhs)
{
	if (this->eof()) {
		return *this;
	}

	*(this->itr_++) = rhs;
	
	return *this;
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
namespace ostream
{
	/// instantiates ostream::Range.
	template <hryky_template_param>
	Range<hryky_template_arg> range(
		IteratorT begin, IteratorT end);

	/// creates an ostream::Range from an iteratable container.
	template <typename ContainerT>
	Range<typename ContainerT::iterator> range(
		ContainerT & container);

} // namespace ostream
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief instantiates ostream::Range.
 */
template <hryky_template_param>
hryky::ostream::Range<hryky_template_arg>
hryky::ostream::range(IteratorT begin, IteratorT end)
{
	return Range<hryky_template_arg>(begin, end);
}
/**
  @brief creates an ostream::Range from an iteratable container.
 */
template <typename ContainerT>
hryky::ostream::Range<typename ContainerT::iterator>
hryky::ostream::range(ContainerT & container)
{
	return Range<typename ContainerT::iterator>(
		container.begin(), container.end());
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // OSTREAM_RANGE_H_20140325225712623
// end of file
