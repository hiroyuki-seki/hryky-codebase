/**
  @file     coord_cartesian_base.h
  @brief    base class for Cartesian coordinate system.
  @author   HRYKY
  @version  $Id: coord_cartesian_base.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef COORD_CARTESIAN_BASE_H_20130819162829353
#define COORD_CARTESIAN_BASE_H_20130819162829353
#include "hryky/array.h"
#include "hryky/vector_space/vector_space_axiom.h"
#include "hryky/vector_space/vector_space_with_multiply.h"
#include "hryky/vector_space/vector_space_with_assign.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_padded
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT, size_t Dimension, typename DerivedT
#define hryky_template_arg \
	ValueT, Dimension, DerivedT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace coord
{
	template <typename ValueT>
	class Cartesian2;

	template <typename ValueT>
	class Cartesian3;

	template <typename ValueT>
	class Cartesian4;

	template <typename ValueT, size_t Size>
	class Cartesian;

namespace cartesian
{
	/// base class for Cartesian coordinate system.
	template <hryky_template_param>
	class Base;

} // namespace cartesian
} // namespace coord
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief base class for Cartesian coordinate system.
 */
template <hryky_template_param>
class hryky::coord::cartesian::Base :
	public Array<ValueT, Dimension>,
	public vector_space::Axiom<ValueT, DerivedT>,
	public vector_space::WithMultiply<DerivedT>,
	public vector_space::WithAssign<ValueT, DerivedT>
{
private :
	typedef vector_space::WithAssign<ValueT, DerivedT> with_assign_type;
public :
	
	typedef Base<hryky_template_arg>                this_type;
	typedef Array<ValueT, Dimension>                base_type;
	typedef vector_space::Axiom<ValueT, DerivedT>   axiom_type;
	typedef typename AsParameter<ValueT>::type      scalar_param_type;

	/// default constructor.
	Base();

	/// copy constructor.
	Base(this_type const &);

	/// move constructor.
	Base(this_type &&);

	/// constructs with a scalar value.
	explicit Base(scalar_param_type scalar);

	/// destructor.
	~Base();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

private :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief retrieves the cartesian coordinate with new size.
 */
template <hryky_template_param, size_t NewSize>
class Resize<coord::cartesian::Base<hryky_template_arg>, NewSize>
{
public :
	typedef coord::Cartesian<ValueT, NewSize> type;
};
/**
  @brief retrieves the 2D cartesian coordinate.
 */
template <hryky_template_param>
class Resize<coord::cartesian::Base<hryky_template_arg>, 2>
{
public :
	typedef coord::Cartesian2<ValueT> type;
};
/**
  @brief retrieves the 3D cartesian coordinate.
 */
template <hryky_template_param>
class Resize<coord::cartesian::Base<hryky_template_arg>, 3>
{
public :
	typedef coord::Cartesian3<ValueT> type;
};
/**
  @brief retrieves the 4D cartesian coordinate.
 */
template <hryky_template_param>
class Resize<coord::cartesian::Base<hryky_template_arg>, 4>
{
public :
	typedef coord::Cartesian4<ValueT> type;
};
namespace coord
{
namespace cartesian
{
} // namespace cartesian
} // namespace coord
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::coord::cartesian::Base<hryky_template_arg>::Base()
	: base_type()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::coord::cartesian::Base<hryky_template_arg>::Base(
	this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::coord::cartesian::Base<hryky_template_arg>::Base(
	this_type && rhs)
	: base_type(::std::move(rhs))
{
}
/**
  @brief constructs with a scalar value.
 */
template <hryky_template_param>
hryky::coord::cartesian::Base<hryky_template_arg>::Base(
	scalar_param_type scalar)
	: base_type()
{
	this->with_assign_type::assign(scalar);
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::coord::cartesian::Base<hryky_template_arg>::~Base()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::coord::cartesian::Base<hryky_template_arg>::clear()
{
	this->base_type::clear();
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & 
hryky::coord::cartesian::Base<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return this->base_type::write_to(out);
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
namespace cartesian
{

} // namespace cartesian
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
//------------------------------------------------------------------------------
// restores warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // COORD_CARTESIAN_BASE_H_20130819162829353
// end of file
