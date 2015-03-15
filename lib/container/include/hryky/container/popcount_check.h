/**
  @file     popcount_check.h
  @brief    The policiy to count the number of bits if changed.
  @author   HRYKY
  @version  $Id: popcount_check.h 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#ifndef POPCOUNT_CHECK_H_20130518210513545
#define POPCOUNT_CHECK_H_20130518210513545
#include "hryky/hamming_weight.h"
#include "hryky/type_traits/as_parameter.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	size_t Size
#define hryky_template_arg \
	Size
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace popcount
{
	/// The policiy to count the number of bits if changed.
	template <hryky_template_param>
	class Check;

} // namespace popcount
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief The policiy to count the number of bits if changed.
 */
template <size_t Size>
class hryky::popcount::Check :
	public WithStreamOut<Check<hryky_template_arg> >,
	public WithSwap<Check<hryky_template_arg> >
{
public :

	typedef Check<hryky_template_arg> this_type;

	typedef typename UnsignedEnoughUint<Size>::type size_type;

	/// default constructor.
	Check();

	/// copy constructor.
	Check(this_type const &);

	/// move constructor.
	Check(this_type &&);

	/// destructor.
	~Check();

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

	/// calculates the number of bits.
	template <typename BitsetT>
	size_type count(BitsetT const & bitset);

	/// confirms the change in cosequence of assigning a new bit.
	template <typename BitsetT>
	void set(
		BitsetT const & bitset,
		typename BitsetT::index_type const index,
		typename BitsetT::bitpos_type const bitpos,
		typename BitsetT::value_type const src);

	/// confirms the change in consequence of enabling a bit.
	template <typename BitsetT>
	void on(
		BitsetT const & bitset,
		typename BitsetT::index_type const index,
		typename BitsetT::bitpos_type const bitpos);

	/// confirms the change in consequence of disabling a bit.
	template <typename BitsetT>
	void off(
		BitsetT const & bitset,
		typename BitsetT::index_type const index,
		typename BitsetT::bitpos_type const bitpos);

	/// confirms the change in consequence of reversing a bit.
	template <typename BitsetT>
	void flip(
		BitsetT const & bitset,
		typename BitsetT::index_type const index,
		typename BitsetT::bitpos_type const bitpos);

	/// updates the number of bits.
	template <typename BitsetT>
	void update(BitsetT const & bitset);

	/// overwrites the existing value by an arbitrary value.
	template <typename ValueT>
	void assign(ValueT value);

protected :

private :

	size_type count_;
	bool dirty_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace popcount
{
} // namespace popcount
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::popcount::Check<hryky_template_arg>::Check()
	: count_()
	  , dirty_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::popcount::Check<hryky_template_arg>::Check(this_type const & rhs)
	: hryky_copy_member(count)
	  , hryky_copy_member(dirty)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::popcount::Check<hryky_template_arg>::Check(this_type && rhs)
	: hryky_move_member(count)
	  , hryky_move_member(dirty)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::popcount::Check<hryky_template_arg>::~Check()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::popcount::Check<hryky_template_arg>::clear()
{
	hryky::clear(this->dirty_);
	hryky::clear(this->count_);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::popcount::Check<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(count);
	hryky_write_member(dirty);

	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::popcount::Check<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(count);
	hryky_swap_member(dirty);
}
/**
  @brief calculates the number of bits.
 */
template <hryky_template_param>
template <typename BitsetT>
typename hryky::popcount::Check<hryky_template_arg>::size_type 
hryky::popcount::Check<hryky_template_arg>::count(
	BitsetT const & bitset)
{
	if (!this->dirty_) {
		return this->count_;
	}

	typedef typename AsParameter<typename BitsetT::element_type>::type
		param_type;

	hryky::clear(this->count_);

	bitset.buffer_.foreach([this](param_type value) {
		this->count_ += static_cast<size_type>(hryky::hamming_weight(value));
	});

	hryky::clear(this->dirty_);
	
	return this->count_;
}
/**
  @brief confirms the change in cosequence of assigning a new bit.
 */
template <hryky_template_param>
template <typename BitsetT>
void hryky::popcount::Check<hryky_template_arg>::set(
	BitsetT const & bitset,
	typename BitsetT::index_type const index,
	typename BitsetT::bitpos_type const bitpos,
	typename BitsetT::value_type const src)
{
	this->dirty_ = (0 != (bitset.bit_at(index, bitpos) ^ (src ? 1 : 0)));
}
/**
  @brief confirms the change in consequence of enabling a bit.
 */
template <hryky_template_param>
template <typename BitsetT>
void hryky::popcount::Check<hryky_template_arg>::on(
	BitsetT const & bitset,
	typename BitsetT::index_type const index,
	typename BitsetT::bitpos_type const bitpos)
{
	this->dirty_ = (0 == bitset.bit_at(index, bitpos));
}
/**
  @brief confirms the change in consequence of disabling a bit.
 */
template <hryky_template_param>
template <typename BitsetT>
void hryky::popcount::Check<hryky_template_arg>::off(
	BitsetT const & bitset,
	typename BitsetT::index_type const index,
	typename BitsetT::bitpos_type const bitpos)
{
	this->dirty_ = (0 != bitset.bit_at(index, bitpos));
}
/**
  @brief confirms the change in consequence of reversing a bit.
 */
template <hryky_template_param>
template <typename BitsetT>
void hryky::popcount::Check<hryky_template_arg>::flip(
	BitsetT const &,
	typename BitsetT::index_type const,
	typename BitsetT::bitpos_type const)
{
	this->dirty_ = true;
}
/**
  @brief updates the number of bits.
 */
template <hryky_template_param>
template <typename BitsetT>
void hryky::popcount::Check<hryky_template_arg>::update(
	BitsetT const & bitset)
{
	this->dirty_ = true;
}
/**
  @brief overwrites the existing value by an arbitrary value.
 */
template <hryky_template_param>
template <typename ValueT>
void hryky::popcount::Check<hryky_template_arg>::assign(ValueT value)
{
	this->count_ = value;
	hryky::clear(this->dirty_);
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
namespace popcount
{

} // namespace popcount
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // POPCOUNT_CHECK_H_20130518210513545
// end of file
