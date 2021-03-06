/**
  @file     rtiow_hit.h
  @brief    records the information where a ray hits.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef RTIOW_HIT_H_20160717103855110
#define RTIOW_HIT_H_20160717103855110
#include "./rtiow_vec3.h"
#include "./rtiow_scatter.h"
#include "hryky/with_is_null.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ScatterT, typename PosT, typename NormalT, typename RateT
#define hryky_template_arg \
	ScatterT, PosT, NormalT, RateT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
	/// records the information where a ray hits.
	template <hryky_template_param>
	class Hit;

} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief records the information where a ray hits.
 */
template <
	typename ScatterT = hryky::rtiow::Scatter<>,
	typename PosT = hryky::rtiow::Vec3<>,
	typename NormalT = PosT,
	typename RateT = float
>
class hryky::rtiow::Hit
	: public hryky::WithIsNull<Hit<hryky_template_arg> >
{
public :

	typedef Hit<hryky_template_arg> this_type;
	typedef ScatterT scatter_type;
	typedef PosT pos_type;
	typedef NormalT normal_type;
	typedef RateT rate_type;

	/// default constructor.
	Hit();

	/// instantiates with parameters.
	Hit(
		scatter_type const & scatter,
		pos_type const & pos,
		normal_type const & normal,
		rate_type const & rate);

	/// copy constructor.
	Hit(this_type const &);

	/// move constructor.
	Hit(this_type &&);

	/// destructor.
	~Hit();

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

	/// retrieves the scattered ray.
	scatter_type const & scatter() const;

	/// retrieves the position where the ray intersected.
	pos_type const & pos() const;

	/// retrieves the normal where the ray intersected.
	normal_type const & normal() const;

	/// retrieves the rate of direction.
	RateT rate() const;

	/// confirms whether resources are invalid.
	bool is_null() const;

protected :

private :

	scatter_type scatter_;
	pos_type pos_;
	normal_type normal_;
	rate_type rate_;

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
hryky::rtiow::Hit<hryky_template_arg>::Hit()
	: scatter_()
	  , pos_()
	  , normal_()
	  , rate_()
{
}

/**
  @brief instantiates with parameters.
 */
template <hryky_template_param>
hryky::rtiow::Hit<hryky_template_arg>::Hit(
	scatter_type const & scatter,
	pos_type const & pos,
	normal_type const & normal,
	rate_type const & rate)
	: scatter_(scatter)
	  , pos_(pos)
	  , normal_(normal)
	  , rate_(rate)
{
}

/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::rtiow::Hit<hryky_template_arg>::Hit(this_type const & rhs)
	: hryky_copy_member(scatter)
	  , hryky_copy_member(pos)
	  , hryky_copy_member(normal)
	  , hryky_copy_member(rate)
{
}

/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::rtiow::Hit<hryky_template_arg>::Hit(this_type && rhs)
	: hryky_move_member(scatter)
	  , hryky_move_member(pos)
	  , hryky_move_member(normal)
	  , hryky_move_member(rate)
{
}

/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::rtiow::Hit<hryky_template_arg>::~Hit()
{
}

/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::rtiow::Hit<hryky_template_arg>::clear()
{
	hryky::clear(this->rate_);
	hryky::clear(this->normal_);
	hryky::clear(this->pos_);
	hryky::clear(this->scatter_);
}

/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::rtiow::Hit<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(scatter);
	hryky_swap_member(pos);
	hryky_swap_member(normal);
	hryky_swap_member(rate);
}

/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::rtiow::Hit<hryky_template_arg>::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	return out;
}

/**
  @brief retrieves the scattered ray.
 */
template <hryky_template_param>
typename hryky::rtiow::Hit<hryky_template_arg>::scatter_type const & 
hryky::rtiow::Hit<hryky_template_arg>::scatter() const
{
	return this->scatter_;
}

/**
  @brief retrieves the position where the ray intersected.
 */
template <hryky_template_param>
typename hryky::rtiow::Hit<hryky_template_arg>::pos_type const & 
hryky::rtiow::Hit<hryky_template_arg>::pos() const
{
	return this->pos_;
}

/**
  @brief retrieves the normal where the ray intersected.
 */
template <hryky_template_param>
typename hryky::rtiow::Hit<hryky_template_arg>::normal_type const & 
hryky::rtiow::Hit<hryky_template_arg>::normal() const
{
	return this->normal_;
}

/**
  @brief retrieves the rate of direction.
 */
template <hryky_template_param>
typename hryky::rtiow::Hit<hryky_template_arg>::rate_type
hryky::rtiow::Hit<hryky_template_arg>::rate() const
{
	return this->rate_;
}

/**
  @brief confirms whether resources are invalid.
 */
template <hryky_template_param>
bool hryky::rtiow::Hit<hryky_template_arg>::is_null() const
{
	return normal_type() == this->normal_;
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
namespace rtiow
{
	/// prints values to a stream.
	template <typename StreamT, hryky_template_param>
	StreamT & operator<<(
		StreamT & lhs, Hit<hryky_template_arg> const & rhs);

} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief prints values to a stream.
 */
template <typename StreamT, hryky_template_param>
StreamT &
hryky::rtiow::operator<<(
	StreamT & lhs, Hit<hryky_template_arg> const & rhs)
{
	return (
		lhs 
		<< "{pos:[" << rhs.pos() << "]"
		<< ",normal:[" << rhs.normal() << "]"
		<< ",rate:" << rhs.rate()
		<< ",scatter:" << rhs.scatter()
		<< "}");
}

//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // RTIOW_HIT_H_20160717103855110
// end of file
