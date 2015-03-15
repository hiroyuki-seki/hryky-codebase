/**
  @file     popcount_none.h
  @brief    The policiy NOT to count the number of bits.
  @author   HRYKY
  @version  $Id: popcount_none.h 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#ifndef POPCOUNT_NONE_H_20130518234945659
#define POPCOUNT_NONE_H_20130518234945659
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
	/// The policiy NOT to count the number of bits.
	template <hryky_template_param>
	class None;

} // namespace popcount
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief The policiy NOT to count the number of bits.
 */
template <size_t Size>
class hryky::popcount::None :
	public WithStreamOut<None<hryky_template_arg> >,
	public WithSwap<None<hryky_template_arg> >
{
public :

	typedef None<hryky_template_arg> this_type;

	typedef typename UnsignedEnoughUint<Size>::type size_type;

	/// default constructor.
	None();

	/// copy constructor.
	None(this_type const &);

	/// move constructor.
	None(this_type &&);

	/// destructor.
	~None();

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
	size_type count(BitsetT const & bitset) const;

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

	static size_type const dummy_;

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
hryky::popcount::None<hryky_template_arg>::None()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::popcount::None<hryky_template_arg>::None(this_type const & rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::popcount::None<hryky_template_arg>::None(this_type && rhs)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::popcount::None<hryky_template_arg>::~None()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::popcount::None<hryky_template_arg>::clear()
{
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::popcount::None<hryky_template_arg>::write_to(
	StreamT & out) const
{
	out << "N/A";
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::popcount::None<hryky_template_arg>::swap(this_type & src)
{
}
/**
  @brief retrieves the calculated number of bits.
 */
template <hryky_template_param>
template <typename BitsetT>
typename hryky::popcount::None<hryky_template_arg>::size_type 
hryky::popcount::None<hryky_template_arg>::count(BitsetT const &) const
{
	return dummy_;
}
/**
  @brief applies the result of assigning a new bit.
 */
template <hryky_template_param>
template <typename BitsetT>
void hryky::popcount::None<hryky_template_arg>::set(
	BitsetT const &,
	typename BitsetT::index_type const,
	typename BitsetT::bitpos_type const,
	typename BitsetT::value_type const)
{
}
/**
  @brief applies the result of enabling a bit.
 */
template <hryky_template_param>
template <typename BitsetT>
void hryky::popcount::None<hryky_template_arg>::on(
	BitsetT const &,
	typename BitsetT::index_type const,
	typename BitsetT::bitpos_type const)
{
}
/**
  @brief applies the result of disabling a bit.
 */
template <hryky_template_param>
template <typename BitsetT>
void hryky::popcount::None<hryky_template_arg>::off(
	BitsetT const &,
	typename BitsetT::index_type const,
	typename BitsetT::bitpos_type const)
{
}
/**
  @brief applies the result of reversing a bit.
 */
template <hryky_template_param>
template <typename BitsetT>
void hryky::popcount::None<hryky_template_arg>::flip(
	BitsetT const &,
	typename BitsetT::index_type const,
	typename BitsetT::bitpos_type const)
{
}
/**
  @brief updates the number of bits.
 */
template <hryky_template_param>
template <typename BitsetT>
void hryky::popcount::None<hryky_template_arg>::update(
	BitsetT const &)
{
}
/**
  @brief overwrites the existing value by an arbitrary value.
 */
template <hryky_template_param>
template <typename ValueT>
void hryky::popcount::None<hryky_template_arg>::assign(ValueT)
{
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
#endif // POPCOUNT_NONE_H_20130518234945659
// end of file
