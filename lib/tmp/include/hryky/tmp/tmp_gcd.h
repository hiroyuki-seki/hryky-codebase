/**
  @file     tmp_gcd.h
  @brief    calculates the Greatest Common Divisor in the compile time.
  @author   HRYKY
  @version  $Id: tmp_gcd.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef TMP_GCD_H_20140713140625254
#define TMP_GCD_H_20140713140625254
#include "hryky/tmp/tmp_not.h"
#include "hryky/tmp/tmp_is_zero.h"
#include "hryky/tmp/tmp_greater.h"
#include "hryky/tmp/tmp_abs.h"
#include "hryky/tmp/tmp_modulo.h"
#include "hryky/tmp/tmp_conditional.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename LhsT, typename RhsT
#define hryky_template_arg \
	LhsT, RhsT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	/// calculates the Greatest Common Divisor in the compile time.
	template <typename LhsT, typename RhsT>
	class Gcd;

	/// calculates the Greatest Common Divisor between normalized values.
	template <typename LhsT, typename RhsT>
	class GcdNormalized;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief calculates the Greatest Common Divisor in the compile time.
 */
template <hryky_template_param>
class hryky::tmp::Gcd
{
public :
	typedef typename Conditional<
		Greater<Abs<LhsT>, Abs<RhsT> >,
		GcdNormalized<Abs<LhsT>, Abs<RhsT> >,
		GcdNormalized<Abs<RhsT>, Abs<LhsT> >
	>::type::type type;
};
/**
  @brief calculates the Greatest Common Divisor between normalized valued.
 */
template <hryky_template_param>
class hryky::tmp::GcdNormalized
{
public :
	typedef typename Conditional<
		IsZero<RhsT>,
		LhsT,
		GcdNormalized<RhsT, Modulo<LhsT, RhsT> >
	>::type::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
} // namespace tmp
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
namespace tmp
{
} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // TMP_GCD_H_20140713140625254
// end of file
