/**
  @file     list_index.h
  @brief    An index of the array in a list.
  @author   HRYKY
  @version  $Id: list_index.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef LIST_INDEX_H_20130414122732185
#define LIST_INDEX_H_20130414122732185
#include "hryky/type_traits/as_parameter.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename RawT
#define hryky_template_arg \
	RawT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// An index of the array in a list.
	template <hryky_template_param>
	class ListIndex;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief An index of the array in a list.
 */
template <hryky_template_param>
class hryky::ListIndex :
	public WithStreamOut<ListIndex<hryky_template_arg> >,
	public WithSwap<ListIndex<hryky_template_arg> >
{
public :

	typedef ListIndex<hryky_template_arg>                   this_type;
	typedef RawT                                            raw_type;
	typedef typename AsParameter<hryky_template_arg>::type  param_type;
	typedef ::std::ptrdiff_t                                difference_type;

	/// default constructor.
	ListIndex();

	/// constructor with a raw index.
	ListIndex(param_type raw);

	/// copy constructor.
	ListIndex(this_type const &);

	/// move constructor.
	ListIndex(this_type &&);

	/// destructor.
	~ListIndex();

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

	/// confirms whether this index is invalid.
	bool is_null() const;

	/// retrieves the raw index.
	param_type raw() const;

	/// assigns a new raw index.
	this_type & operator=(param_type rhs);

	/// confirms the equality between two instances.
	bool operator==(this_type const & rhs) const;

	/// confirms the inequality between two instances.
	bool operator!=(this_type const & rhs) const;

	/// retrieves the difference between two indices.
	difference_type operator-(this_type const & rhs) const;

	/// retrieves the sum of a raw index and this index.
	this_type operator+(param_type rhs) const;

protected :

private :

	static raw_type const invalid_raw_ = static_cast<raw_type>(-1);

	raw_type raw_;

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
hryky::ListIndex<hryky_template_arg>::ListIndex()
	: raw_(this_type::invalid_raw_)
{
}
/**
  @brief constructor with a raw index.
 */
template <hryky_template_param>
hryky::ListIndex<hryky_template_arg>::ListIndex(param_type raw)
	: raw_(raw)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::ListIndex<hryky_template_arg>::ListIndex(this_type const & rhs)
	: hryky_copy_member(raw)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::ListIndex<hryky_template_arg>::ListIndex(this_type && rhs)
	: hryky_move_member(raw)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::ListIndex<hryky_template_arg>::~ListIndex()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::ListIndex<hryky_template_arg>::clear()
{
	this->raw_ = this_type::invalid_raw_;
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::ListIndex<hryky_template_arg>::write_to(
	StreamT & out) const
{
	out << this->raw_;
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::ListIndex<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(raw);
}
/**
  @brief confirms whether this index is invalid.
 */
template <hryky_template_param>
bool hryky::ListIndex<hryky_template_arg>::is_null() const
{
	return this_type::invalid_raw_ == this->raw_;
}
/**
  @brief retrieves the raw index.
 */
template <hryky_template_param>
typename hryky::ListIndex<hryky_template_arg>::param_type
hryky::ListIndex<hryky_template_arg>::raw() const
{
	return this->raw_;
}
/**
  @brief assigns a new raw index.
 */
template <hryky_template_param>
hryky::ListIndex<hryky_template_arg> &
hryky::ListIndex<hryky_template_arg>::operator=(param_type rhs)
{
	this->raw_ = rhs;
	return *this;
}
/**
  @brief confirms the equality between two instances.
 */
template <hryky_template_param>
bool hryky::ListIndex<hryky_template_arg>::operator==(
	this_type const & rhs) const
{
	return this->raw_ == rhs.raw_;
}
/**
  @brief confirms the inequality between two instances.
 */
template <hryky_template_param>
bool hryky::ListIndex<hryky_template_arg>::operator!=(
	this_type const & rhs) const
{
	return this->raw_ != rhs.raw_;
}
/**
  @brief retrieves the difference between two indices.
 */
template <hryky_template_param>
typename hryky::ListIndex<hryky_template_arg>::difference_type 
hryky::ListIndex<hryky_template_arg>::operator-(this_type const & rhs) const
{
	return this->raw_ - rhs.raw_;
}
/**
  @brief retrieves the sum of a raw index and this index.
 */
template <hryky_template_param>
hryky::ListIndex<hryky_template_arg>
hryky::ListIndex<hryky_template_arg>::operator+(param_type rhs) const 
{
	return static_cast<raw_type>(this->raw_ + rhs);
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
// revokes macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // LIST_INDEX_H_20130414122732185
// end of file
