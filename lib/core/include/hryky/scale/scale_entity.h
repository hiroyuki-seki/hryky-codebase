/**
  @file         scale_entity.h
  @brief        retains the value on the scale.
  @author       HRYKY
  @version      $Id: scale_entity.h 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#ifndef SCALE_ENTITY_H_20130101143242272
#define SCALE_ENTITY_H_20130101143242272
#include "hryky/nullptr.h"
#include "hryky/scale/scale_is_lower.h"
#include "hryky/scale/scale_lower_of.h"
#include "hryky/swap.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename RawT, typename HigherT, hryky::int64_t Radix
#define hryky_template_arg \
	RawT, HigherT, Radix
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace scale
{
	/// retains the value on the scale.
	template <hryky_template_param>
	class Entity;

} // namespace scale
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the value on the scale.
 */
template <hryky_template_param>
class hryky::scale::Entity :
	public WithStreamOut<Entity<hryky_template_arg> >,
	public WithSwap<Entity<hryky_template_arg> >
{
public :

	typedef Entity<hryky_template_arg> this_type;
	typedef RawT raw_type;
	typedef HigherT higher_type;

	static int64_t const higher_radix = Radix;

	/// default constructor.
	Entity();

	/// copy constructor.
	Entity(this_type const &);

	/// move constructor.
	Entity(this_type && rhs);

	/// constructor with a raw value.
	Entity(raw_type const rhs);

	/// constructor with a value on the higher scale.
	template <typename ValueT>
	Entity(
		ValueT const & rhs,
		typename EnableIf<
			scale::IsLowerEqual<typename this_type::higher_type, ValueT >
		>::type * = hryky_nullptr);

	/// constructor with a value on the lower scale.
	template <typename ValueT>
	Entity(
		ValueT const & rhs,
		typename EnableIf<
			scale::IsLowerEqual<typename ValueT::higher_type, this_type >
		>::type * = hryky_nullptr);

	/// destructor.
	~Entity();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// add two instance on the scales.
	template <typename ValueT>
	typename scale::LowerOf<this_type, ValueT>::type
		operator+(ValueT const & rhs) const;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// retrieves the raw value.
	RawT raw() const;

protected :

private :

	raw_type raw_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace scale
{
} // namespace scale
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::scale::Entity<hryky_template_arg>::Entity()
	: raw_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::scale::Entity<hryky_template_arg>::Entity(this_type const & rhs)
	: hryky_copy_member(raw)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::scale::Entity<hryky_template_arg>::Entity(this_type && rhs)
	: hryky_move_member(raw)
{
}
/**
  @brief constructor with a raw value.
 */
template <hryky_template_param>
hryky::scale::Entity<hryky_template_arg>::Entity(raw_type const raw)
	: raw_(raw)
{
}
/**
  @brief constructor with a value on the higher scale.
 */
template <hryky_template_param>
template <typename ValueT>
hryky::scale::Entity<hryky_template_arg>::Entity(
	ValueT const & rhs,
	typename EnableIf<
		scale::IsLowerEqual<typename this_type::higher_type, ValueT > >::type *)
	: raw_(scale::Radix<this_type, ValueT>::value * rhs.raw())
{
}
/**
  @brief constructor with a value on the lower scale.
 */
template <hryky_template_param>
template <typename ValueT>
hryky::scale::Entity<hryky_template_arg>::Entity(
	ValueT const & rhs,
	typename EnableIf<
		scale::IsLowerEqual<typename ValueT::higher_type, this_type > >::type *)
	: raw_(static_cast<raw_type>(
		rhs.raw() / scale::Radix<ValueT, this_type>::value))
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::scale::Entity<hryky_template_arg>::~Entity()
{
}
/**
  @brief add two instance on the scales.
 */
template <hryky_template_param>
template <typename ValueT>
typename hryky::scale::LowerOf<hryky::scale::Entity<hryky_template_arg>, ValueT>::type 
hryky::scale::Entity<hryky_template_arg>::operator+(ValueT const & rhs) const
{
	return scale::add(*this, rhs);
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::scale::Entity<hryky_template_arg>::clear()
{
	hryky::clear(this->raw_);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::scale::Entity<hryky_template_arg>::write_to(
	StreamT & out) const
{
	out << this->raw_;
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::scale::Entity<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(raw);
}
/**
  @brief retrieves the raw value.
 */
template <hryky_template_param>
RawT hryky::scale::Entity<hryky_template_arg>::raw() const
{
	return this->raw_;
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
namespace scale
{

	/// adds the two scales. The LHS is on the lower scale.
	template <typename LhsT, typename RhsT>
	LhsT add(
		LhsT const & lhs,
		RhsT const & rhs,
		typename EnableIf<
			scale::IsLowerEqual<typename LhsT::higher_type, RhsT>
		>::type * = hryky_nullptr);

	/// adds the two scales. The LHS is on the higher scale.
	template <typename LhsT, typename RhsT>
	RhsT add(
		LhsT const & lhs,
		RhsT const & rhs,
		typename EnableIf<
			scale::IsLowerEqual<typename RhsT::higher_type, LhsT>
		>::type * = hryky_nullptr);

} // namespace scale
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief adds the two scales. The LHS is on the lower scale.
 */
template <typename LhsT, typename RhsT>
LhsT hryky::scale::add(
	LhsT const & lhs,
	RhsT const & rhs,
	typename EnableIf<
		scale::IsLowerEqual<typename LhsT::higher_type, RhsT>
	>::type *)
{
	return LhsT(lhs.raw() + scale::Radix<LhsT, RhsT>::value * rhs.raw());
}
/**
  @brief adds the two scales. The LHS is on the higher scale.
 */
template <typename LhsT, typename RhsT>
RhsT hryky::scale::add(
	LhsT const & lhs,
	RhsT const & rhs,
	typename EnableIf<
		scale::IsLowerEqual<typename RhsT::higher_type, LhsT>
	>::type *)
{
	return RhsT(scale::Radix<RhsT, LhsT>::value * lhs.raw() + rhs.raw());
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // SCALE_ENTITY_H_20130101143242272
// end of file
