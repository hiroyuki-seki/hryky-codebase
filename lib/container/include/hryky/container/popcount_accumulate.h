/**
  @file     popcount_accumulate.h
  @brief    The policiy to count the number of bits point by point.
  @author   HRYKY
  @version  $Id: popcount_accumulate.h 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#ifndef POPCOUNT_ACCUMULATE_H_20130518204214529
#define POPCOUNT_ACCUMULATE_H_20130518204214529
#include "hryky/hamming_weight.h"
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
	/// The policiy to count the number of bits point by point.
	template <hryky_template_param>
	class Accumulate;

} // namespace popcount
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief The policiy to count the number of bits point by point.
 */
template <hryky_template_param>
class hryky::popcount::Accumulate :
	public WithStreamOut<Accumulate<hryky_template_arg> >,
	public WithSwap<Accumulate<hryky_template_arg> >
{
public :

	typedef Accumulate<hryky_template_arg> this_type;

	typedef typename UnsignedEnoughUint<Size>::type size_type;

	/// default constructor.
	Accumulate();

	/// copy constructor.
	Accumulate(this_type const &);

	/// move constructor.
	Accumulate(this_type &&);

	/// destructor.
	~Accumulate();

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

	/// retrieves the calculated number of bits.
	template <typename BitsetT>
	size_type count(BitsetT const & bitset);

	/// applies the result of assigning a new bit.
	template <typename BitsetT>
	void set(
		BitsetT const & bitset,
		typename BitsetT::index_type const index,
		typename BitsetT::bitpos_type const bitpos,
		typename BitsetT::value_type const value);

	/// applies the result of enabling a bit.
	template <typename BitsetT>
	void on(
		BitsetT const & bitset,
		typename BitsetT::index_type const index,
		typename BitsetT::bitpos_type const bitpos);

	/// applies the result of disabling a bit.
	template <typename BitsetT>
	void off(
		BitsetT const & bitset,
		typename BitsetT::index_type const index,
		typename BitsetT::bitpos_type const bitpos);

	/// applies the result of reversing a bit.
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
hryky::popcount::Accumulate<hryky_template_arg>::Accumulate()
	: count_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::popcount::Accumulate<hryky_template_arg>::Accumulate(this_type const & rhs)
	: hryky_copy_member(count)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::popcount::Accumulate<hryky_template_arg>::Accumulate(this_type && rhs)
	: hryky_move_member(count)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::popcount::Accumulate<hryky_template_arg>::~Accumulate()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::popcount::Accumulate<hryky_template_arg>::clear()
{
	hryky::clear(this->count_);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::popcount::Accumulate<hryky_template_arg>::write_to(
	StreamT & out) const
{
	out << this->count_;
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::popcount::Accumulate<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(count);
}
/**
  @brief retrieves the calculated number of bits.
 */
template <hryky_template_param>
template <typename BitsetT>
typename hryky::popcount::Accumulate<hryky_template_arg>::size_type 
hryky::popcount::Accumulate<hryky_template_arg>::count(BitsetT const &)
{
	return this->count_;
}
/**
  @brief applies the result of assigning a new bit.
 */
template <hryky_template_param>
template <typename BitsetT>
void hryky::popcount::Accumulate<hryky_template_arg>::set(
	BitsetT const & bitset,
	typename BitsetT::index_type const index,
	typename BitsetT::bitpos_type const bitpos,
	typename BitsetT::value_type const value)
{
	/**
	            to_on   to_off
	  from_on   0       -1
	  from_off  +1      0
	 */
	this->count_ += static_cast<int8_t>(
		(bitset.bit_at(index, bitpos) ^ (value ? 1 : 0)) * (value ? 1 : -1));
}
/**
  @brief applies the result of enabling a bit.
 */
template <hryky_template_param>
template <typename BitsetT>
void hryky::popcount::Accumulate<hryky_template_arg>::on(
	BitsetT const & bitset,
	typename BitsetT::index_type const index,
	typename BitsetT::bitpos_type const bitpos)
{
	this->count_ +=
		static_cast<uint8_t>(bitset.bit_at(index, bitpos) ^ 1);
}
/**
  @brief applies the result of disabling a bit.
 */
template <hryky_template_param>
template <typename BitsetT>
void hryky::popcount::Accumulate<hryky_template_arg>::off(
	BitsetT const & bitset,
	typename BitsetT::index_type const index,
	typename BitsetT::bitpos_type const bitpos)
{
	this->count_ -=
		static_cast<uint8_t>(bitset.bit_at(index, bitpos));
}
/**
  @brief applies the result of reversing a bit.
 */
template <hryky_template_param>
template <typename BitsetT>
void hryky::popcount::Accumulate<hryky_template_arg>::flip(
	BitsetT const & bitset,
	typename BitsetT::index_type const index,
	typename BitsetT::bitpos_type const bitpos)
{
	this->count_ +=
		static_cast<int8_t>(1 - (bitset.bit_at(index, bitpos) << 1));
}
/**
  @brief updates the number of bits.
 */
template <hryky_template_param>
template <typename BitsetT>
void hryky::popcount::Accumulate<hryky_template_arg>::update(
	BitsetT const & bitset)
{
	typedef typename AsParameter<typename BitsetT::element_type>::type
		param_type;

	hryky::clear(this->count_);
	bitset.buffer_.foreach([this](param_type value) {
		this->count_ += hryky::hamming_weight(value);
	});
}
/**
  @brief overwrites the existing value by an arbitrary value.
 */
template <hryky_template_param>
template <typename ValueT>
void hryky::popcount::Accumulate<hryky_template_arg>::assign(ValueT value)
{
	this->count_ = value;
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
#endif // POPCOUNT_ACCUMULATE_H_20130518204214529
// end of file
