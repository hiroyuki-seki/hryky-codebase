/**
  @file     rtiow_tuple.h
  @brief    checks if a ray intersects with any hitable objects in tuple.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef RTIOW_TUPLE_H_20160717131411218
#define RTIOW_TUPLE_H_20160717131411218
#include "hryky/tuple.h"
#include "hryky/is_null.h"
#include "./rtiow_hit.h"
#include "./rtiow_segment.h"
#include "./rtiow_randomizer.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename TupleT
#define hryky_template_arg \
	TupleT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
	/// checks if a ray intersects with any hitable objects in tuple.
	template <hryky_template_param>
	class Tuple;

} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief checks if a ray intersects with any hitable objects in tuple.
 */
template <typename TupleT>
class hryky::rtiow::Tuple
{
public :

	typedef Tuple<hryky_template_arg> this_type;

	/// default constructor.
	Tuple();

	/// instantiates with a tuple.
	Tuple(TupleT const & tuple);

	/// copy constructor.
	Tuple(this_type const &);

	/// move constructor.
	Tuple(this_type &&);

	/// destructor.
	~Tuple();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// checks if a ray intersects with any hitable objects in tuple.
	template <typename RayT, typename RandomizerT>
	Hit<> hit(RayT const & ray, RandomizerT & randomizer) const;

	template <typename RayT>
	Hit<> hit(RayT const & ray) const
	{
		Randomizer<> randomizer;
		return this->hit(ray, randomizer);
	}

protected :

private :

	/// checks if a ray intersects with any hitable objects in tuple.
	template <
		typename RayT,
		typename RandomizerT,
		typename FirstT,
		typename RestT
	>
	static Hit<> hit(
		RayT const & ray,
		RandomizerT & randomizer,
		FirstT const & first,
		RestT const & rest);

	/// checks if a ray intersects with the last hitable object in tuple.
	template <
		typename RayT,
		typename RandomizerT,
		typename FirstT
	>
	static Hit<> hit(
		RayT const & ray,
		RandomizerT & randomizer,
		FirstT const & first,
		Null const &);

	/// checks intersection against the empty tuple.
	template <typename RayT, typename RandomizerT>
	static Hit<> hit(
		RayT const & ray,
		RandomizerT & randomizer,
		Null const &,
		Null const &);

	TupleT tuple_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::rtiow::Tuple<hryky_template_arg>::Tuple()
	: tuple_()
{
}
/**
  @brief instantiates with a tuple.
 */
template <hryky_template_param>
hryky::rtiow::Tuple<hryky_template_arg>::Tuple(TupleT const & tuple)
	: tuple_(tuple)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::rtiow::Tuple<hryky_template_arg>::Tuple(this_type const & rhs)
	: hryky_copy_member(tuple)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::rtiow::Tuple<hryky_template_arg>::Tuple(this_type && rhs)
	: hryky_move_member(tuple)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::rtiow::Tuple<hryky_template_arg>::~Tuple()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::rtiow::Tuple<hryky_template_arg>::clear()
{
	hryky::clear(this->tuple_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::rtiow::Tuple<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(tuple);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::rtiow::Tuple<hryky_template_arg>::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	return out;
}
/**
  @brief checks if a ray intersects with any hitable objects in tuple.
 */
template <hryky_template_param>
template <typename RayT, typename RandomizerT>
hryky::rtiow::Hit<>
hryky::rtiow::Tuple<hryky_template_arg>::hit(
	RayT const & ray, RandomizerT & randomizer) const
{
	return this_type::hit(
		ray, randomizer, this->tuple_.first(), this->tuple_.rest());
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief checks if a ray intersects with any hitable objects in tuple.
 */
template <hryky_template_param>
template <typename RayT, typename RandomizerT, typename FirstT, typename RestT>
hryky::rtiow::Hit<>
hryky::rtiow::Tuple<hryky_template_arg>::hit(
	RayT const & ray,
	RandomizerT & randomizer,
	FirstT const & first,
	RestT const & rest)
{
	auto const hit = first.hit(ray, randomizer);
	if (hryky_is_null(hit)) {
		return this_type::hit(ray, randomizer, rest.first(), rest.rest());
	}

	auto const next = this_type::hit(
		Segment<typename RayT::vector_type>(
			ray.origin(), hit.pos() - ray.origin()),
		randomizer,
		rest.first(),
		rest.rest());
	
	return hryky_is_null(next) ? hit : next;
}
/**
  @brief checks if a ray intersects with the last hitable object in tuple.
 */
template <hryky_template_param>
template <typename RayT, typename RandomizerT, typename FirstT>
hryky::rtiow::Hit<>
hryky::rtiow::Tuple<hryky_template_arg>::hit(
	RayT const & ray,
	RandomizerT & randomizer,
	FirstT const & first,
	hryky::Null const &)
{
	return first.hit(ray, randomizer);
}
/**
  @brief checks intersection against the empty tuple.
 */
template <hryky_template_param>
template <typename RayT, typename RandomizerT>
hryky::rtiow::Hit<>
hryky::rtiow::Tuple<hryky_template_arg>::hit(
	RayT const &,
	RandomizerT &,
	hryky::Null const &,
	hryky::Null const &)
{
	return Hit<>();
}
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
	/// creates a new rtiow::Tuple instance.
	template <hryky_template_param>
	Tuple<hryky_template_arg> tuple(TupleT const & tuple);

} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates a new rtiow::Tuple instance.
 */
template <hryky_template_param>
hryky::rtiow::Tuple<hryky_template_arg>
hryky::rtiow::tuple(TupleT const & tuple)
{
	return Tuple<TupleT>(tuple);
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // RTIOW_TUPLE_H_20160717131411218
// end of file
