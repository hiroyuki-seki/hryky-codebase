/**
  @file     istream_range.h
  @brief    creates an input-stream from the range between two iterators.
  @author   HRYKY
  @version  $Id: istream_range.h 341 2014-03-29 06:35:02Z hryky.private@gmail.com $
 */
#ifndef ISTREAM_RANGE_H_20140325223823609
#define ISTREAM_RANGE_H_20140325223823609
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
namespace istream
{
	/// creates an input-stream from the range between two iterators.
	template <typename IteratorT>
	class Range;

} // namespace istream
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief creates an input-stream from the range between two iterators.
 */
template <hryky_template_param>
class hryky::istream::Range :
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

	/// instantiates with two iterators.
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

	/// extracts a value of arbitrary type.
	template <typename RhsT>
	this_type & operator>>(RhsT & rhs);

	/// confirms whether the iterator reach the end.
	bool eof() const;

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
namespace istream
{
} // namespace istream
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::istream::Range<hryky_template_arg>::Range()
	: itr_()
	  , end_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::istream::Range<hryky_template_arg>::Range(
	this_type const & rhs)
	: hryky_copy_member(itr)
	  , hryky_copy_member(end)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::istream::Range<hryky_template_arg>::Range(
	this_type && rhs)
	: hryky_move_member(itr)
	  , hryky_move_member(end)
{
}
/**
  @brief instantiates with two iterators.
 */
template <hryky_template_param>
hryky::istream::Range<hryky_template_arg>::Range(
	param_type begin, param_type end)
	: itr_(begin)
	  , end_(end)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::istream::Range<hryky_template_arg>::~Range()
{
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::istream::Range<hryky_template_arg>::swap(
	this_type & src)
{
	hryky_swap_member(itr);
	hryky_swap_member(end);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::istream::Range<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(itr);
	hryky_write_member(end);
	return out;
}
/**
  @brief extracts a value of arbitrary type.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::istream::Range<hryky_template_arg> & 
hryky::istream::Range<hryky_template_arg>::operator>>(
	RhsT & rhs)
{
	if (this->eof()) {
		return *this;
	}

	rhs = *(this->itr_++);
	
	return *this;
}
/**
  @brief confirms whether the iterator reach the end.
 */
template <hryky_template_param>
bool hryky::istream::Range<hryky_template_arg>::eof() const
{
	return this->end_ == this->itr_;
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
namespace istream
{
	/// instantiates istream::Range.
	template <hryky_template_param>
	Range<hryky_template_arg> range(IteratorT begin, IteratorT end);

} // namespace istream
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief instantiates istream::Range.
 */
template <hryky_template_param>
hryky::istream::Range<hryky_template_arg>
hryky::istream::range(IteratorT begin, IteratorT end)
{
	return Range<hryky_template_arg>(begin, end);
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // ISTREAM_RANGE_H_20140325223823609
// end of file
