/**
  @file     vec3.h
  @brief    contains three elements.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef VEC3_H_20160628180738421
#define VEC3_H_20160628180738421
#include "hryky/definition.h"
#include "hryky/clear.h"
#include "hryky/swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT
#define hryky_template_arg \
	ValueT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace rtiow
{
	/// contains three elements.
	template <typename ValueT>
	class Vec3;

} // namespace rtiow
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief contains three elements.
 */
template <hryky_template_param>
class rtiow::Vec3
{
public :

	typedef Vec3<hryky_template_arg> this_type;
	typedef ValueT value_type;

	/// default constructor.
	Vec3();

	/// copy constructor.
	Vec3(this_type const &);

	/// move constructor.
	Vec3(this_type &&);

	/// destructor.
	~Vec3();

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

protected :

private :

	value_type x_;
	value_type y_;
	value_type z_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace rtiow
{
} // namespace rtiow
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
rtiow::Vec3<hryky_template_arg>::Vec3()
	: x_()
	  , y_()
	  , z_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
rtiow::Vec3<hryky_template_arg>::Vec3(this_type const & rhs)
	: hryky_copy_member(x)
	  , hryky_copy_member(y)
	  , hryky_copy_member(z)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
rtiow::Vec3<hryky_template_arg>::Vec3(this_type && rhs)
	: hryky_move_member(x)
	  , hryky_move_member(y)
	  , hryky_move_member(z)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
rtiow::Vec3<hryky_template_arg>::~Vec3()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void rtiow::Vec3<hryky_template_arg>::clear()
{
	hryky::clear(this->z_);
	hryky::clear(this->y_);
	hryky::clear(this->x_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void rtiow::Vec3<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(x);
	hryky_swap_member(y);
	hryky_swap_member(z);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & rtiow::Vec3<hryky_template_arg>::write_to(StreamT & out) const
{
	return out;
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
namespace rtiow
{
} // namespace rtiow
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // VEC3_H_20160628180738421
// end of file
