/**
  @file         geometry_rect.h
  @brief        retains the information of a rectangle.
  @author       HRYKY
  @version      $Id: geometry_rect.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef GEOMETRY_RECT_H_20120130100046083
#define GEOMETRY_RECT_H_20120130100046083
#include "hryky/clear.h"
#include "hryky/definition.h"
#include "hryky/std/std_algorithm.h"
#include "hryky/swap.h"
#include "hryky/type_traits/as_parameter.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename CoordT
#define hryky_template_arg \
	CoordT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace geometry
{
	/// retains the information of a rectangle.
	template <hryky_template_param>
	class Rect;

	
}
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information of a rectangle.
 */
template <hryky_template_param>
class hryky::geometry::Rect :
	public WithStreamOut<Rect<hryky_template_arg> >,
	public WithSwap<Rect<hryky_template_arg> >
{
public :

	typedef CoordT          coord_type;///< type of coordinates.
	typedef CoordT          value_type;
	typedef CoordT *        pointer;
	typedef CoordT &        reference;
	typedef CoordT const *  const_pointer;
	typedef CoordT const &  const_reference;

	/// self.
	typedef hryky::geometry::Rect<coord_type> this_type;

	/// default constructor.
	Rect();

	/// copy constructor.
	Rect(this_type const & rhs);

	/// move constructor.
	Rect(this_type && rhs);

	/// constructs with parameters.
	Rect(const_reference left_top, const_reference right_bottom);

	/// destructor.
	~Rect();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// releases the internal resources.
	void clear();

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// multiplies a scalar.
	template <typename RhsT>
	this_type operator*(typename AsParameter<RhsT>::type rhs) const;

	/// retrieves the immutable coordinate at left-top corner.
	const_reference left_top() const;

	/// retrieves the immutable coordinate at right-bottom corner.
	const_reference right_bottom() const;

	/**
	  retrieves the difference between the left-top corner and the
	  right-bottom corner.
	 */
	value_type size() const;

	/// retrieves the mutable coordinate at left-top corner.
	reference left_top();

	/// retrieves the mutable coordinate at right-bottom corner.
	reference right_bottom();

protected :

private :

	coord_type      left_top_;
	coord_type      right_bottom_;

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::geometry::Rect<hryky_template_arg>::Rect()
	: left_top_()
	  , right_bottom_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::geometry::Rect<hryky_template_arg>::Rect(this_type const & rhs)
	: hryky_copy_member(left_top)
	  , hryky_copy_member(right_bottom)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::geometry::Rect<hryky_template_arg>::Rect(this_type && rhs)
	: hryky_move_member(left_top)
	  , hryky_move_member(right_bottom)
{
}
/**
  @brief constructs with parameters.
 */
template <hryky_template_param>
hryky::geometry::Rect<hryky_template_arg>::Rect(
	const_reference left_top, const_reference right_bottom)
	: left_top_(left_top)
	  , right_bottom_(right_bottom)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::geometry::Rect<hryky_template_arg>::~Rect()
{
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::geometry::Rect<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(left_top);
	hryky_swap_member(right_bottom);
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::geometry::Rect<hryky_template_arg>::clear()
{
	hryky::clear(this->right_bottom_);
	hryky::clear(this->left_top_);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::geometry::Rect<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(left_top);
	hryky_write_member(right_bottom);
	return out;
}
/**
  @brief retrieves the immutable coordinate at left-top corner.
 */
template <hryky_template_param>
typename hryky::geometry::Rect<hryky_template_arg>::const_reference 
hryky::geometry::Rect<hryky_template_arg>::left_top() const
{
	return this->left_top_;
}
/**
  @brief retrieves the immutable coordinate at right-bottom corner.
 */
template <hryky_template_param>
typename hryky::geometry::Rect<hryky_template_arg>::const_reference 
hryky::geometry::Rect<hryky_template_arg>::right_bottom() const
{
	return this->right_bottom_;
}
/**
  @brief retrieves the difference between the left-top corner and the
    right-bottom corner.
 */
template <hryky_template_param>
typename hryky::geometry::Rect<hryky_template_arg>::value_type 
hryky::geometry::Rect<hryky_template_arg>::size() const
{
	return this->right_bottom_ - this->left_top_;
}
/**
  @brief retrieves the mutable coordinate at left-top corner.
 */
template <hryky_template_param>
typename hryky::geometry::Rect<hryky_template_arg>::reference 
hryky::geometry::Rect<hryky_template_arg>::left_top()
{
	return this->left_top_;
}
/**
  @brief retrieves the mutable coordinate at right-bottom corner.
 */
template <hryky_template_param>
typename hryky::geometry::Rect<hryky_template_arg>::reference 
hryky::geometry::Rect<hryky_template_arg>::right_bottom()
{
	return this->right_bottom_;
}
/**
  @brief multiplies a scalar.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::geometry::Rect<hryky_template_arg>
hryky::geometry::Rect<hryky_template_arg>::operator*(
	typename AsParameter<RhsT>::type rhs) const
{
	return this_type(this->left_top_ * rhs, this->right_bottom_ * rhs);
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // GEOMETRY_RECT_H_20120130100046083
// end of file
