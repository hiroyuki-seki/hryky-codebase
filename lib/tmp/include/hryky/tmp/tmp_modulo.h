/**
  @file     tmp_modulo.h
  @brief    operates modular arithmetic between two terms.
  @author   HRYKY
  @version  $Id: tmp_modulo.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef TMP_MODULO_H_20131221224238612
#define TMP_MODULO_H_20131221224238612
#include "hryky/tmp/tmp_eval.h"
#include "hryky/type_traits/integral_constant.h"
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
	/// The alias for Modulo.
	template <hryky_template_param>
	class Mod;

	/// operates modular arithmetic between two terms.
	template <hryky_template_param>
	class Modulo;

	/// implements Modulo<> for the actual types.
	template <hryky_template_param>
	class ModuloImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief The alias for Modulo.
 */
template <hryky_template_param>
class hryky::tmp::Mod
{
public :
	typedef typename Modulo<hryky_template_arg>::type type;
};
/**
  @brief operates modular arithmetic between two terms.
 */
template <hryky_template_param>
class hryky::tmp::Modulo
{
public :
	typedef typename ModuloImpl<
		typename LhsT::type, typename RhsT::type>::type type;
};
/**
  @brief implements Modulo<> for the actual types.
 */
template <hryky_template_param>
class hryky::tmp::ModuloImpl
{
public :
	typedef ModuloImpl<hryky_template_arg> type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  calculates the remainder of division between integral values.
 */
template <typename LhsT, LhsT Lhs, typename RhsT, RhsT Rhs>
class ModuloImpl<
	IntegralConstant<LhsT, Lhs>,
	IntegralConstant<RhsT, Rhs>
>
{
public :
	typedef IntegralConstant<
		decltype(Lhs % Rhs), (Lhs % Rhs)> type;
};
/**
  propagates the lazy evaluation.
 */
template <hryky_template_param>
class EvalImpl<ModuloImpl<hryky_template_arg> >
{
public :
	typedef typename Modulo<Eval<LhsT>, Eval<RhsT> >::type type;
};
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
#endif // TMP_MODULO_H_20131221224238612
// end of file
