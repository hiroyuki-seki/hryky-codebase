/**
  @file         as_parameter.h
  @brief        retrieves the type as parameter of function.
  @author       HRYKY
  @version      $Id: as_parameter.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef AS_PARAMETER_H_20130105164357363
#define AS_PARAMETER_H_20130105164357363
#include "hryky/boost.h"
#include "hryky/type_traits/is_arithmetic.h"
#include "hryky/type_traits/is_enum.h"
#include "hryky/type_traits/is_pointer.h"
#include "hryky/type_traits/conditional.h"
#include "hryky/type_traits/add_const_reference.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retrieves the type as parameter of function.
	template <typename ValueT>
	class AsParameter;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the type as parameter of function.
 */
template <typename ValueT>
class hryky::AsParameter
{
public :
#if HRYKY_USE_BOOST
	typedef typename boost::call_traits<ValueT>::param_type type;
#else
	typedef typename Conditional<
		tmp::Or<
			IsArithmetic<ValueT>,
			tmp::Or<IsEnum<ValueT>, IsPointer<ValueT> >
		>,
		typename AddConst<ValueT>::type,
		typename AddConstReference<ValueT>::type
	>::type type;
#endif
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
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
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // AS_PARAMETER_H_20130105164357363
// end of file
