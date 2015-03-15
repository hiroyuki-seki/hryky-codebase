/**
  @file         coord_cartesian.h
  @brief        retains the information of a coordinate specified by Cartesian coordinate system.
  @author       HRYKY
  @version      $Id: coord_cartesian.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef COORD_CARTESIAN_H_20120130112458142
#define COORD_CARTESIAN_H_20120130112458142
#include "hryky/coord/coord_cartesian_base.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT, size_t Dimension
#define hryky_template_arg \
	ValueT, Dimension
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace coord
{
	/// retains the information of a coordinate specified by Cartesian coordinate system.
	template <hryky_template_param>
	class Cartesian;
	
	template <typename ValueT>
	class Cartesian2;

	template <typename ValueT>
	class Cartesian3;

	template <typename ValueT>
	class Cartesian4;

} // namespace coord
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information of a coordinate specified by Cartesian coordinate system.
 */
template <hryky_template_param>
class hryky::coord::Cartesian
	: public hryky::coord::cartesian::Base<
		ValueT, Dimension, Cartesian<hryky_template_arg> >
{
public :

	typedef Cartesian<hryky_template_arg>                   this_type;
	typedef cartesian::Base<ValueT, Dimension, this_type>   base_type;

	/// default constructor.
	Cartesian();

	/// copy constructor.
	Cartesian(this_type const & rhs);

	/// move constructor.
	Cartesian(this_type && rhs);

	/// constructs with a scalar.
	explicit Cartesian(scalar_param_type scalar);

protected :

private :

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::coord::Cartesian<hryky_template_arg>::Cartesian()
	: base_type()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::coord::Cartesian<hryky_template_arg>::Cartesian(this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::coord::Cartesian<hryky_template_arg>::Cartesian(this_type && rhs)
	: base_type(::std::move(rhs))
{
}
/**
  @brief constructs with a scalar.
 */
template <hryky_template_param>
hryky::coord::Cartesian<hryky_template_arg>::Cartesian(scalar_param_type scalar)
	: base_type(scalar)
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
namespace coord
{
} // namespace coord
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // COORD_CARTESIAN_H_20120130112458142
// end of file
