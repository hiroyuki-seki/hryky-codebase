/**
  @file     ratio.h
  @brief    substitutes for ::std::ratio.
  @author   HRYKY
  @version  $Id: ratio.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef RATIO_H_20140713170349377
#define RATIO_H_20140713170349377
#include "hryky/std/std_ratio.h"
#include "hryky/tmp/tmp_gcd.h"
#include "hryky/tmp/tmp_sign.h"
#include "hryky/tmp/tmp_abs.h"
#include "hryky/tmp/tmp_multiply.h"
#include "hryky/tmp/tmp_divide.h"
#include "hryky/stdint.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	intmax_t Dividend, intmax_t Divisor
#define hryky_template_arg \
	Dividend, Divisor
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// substitutes for ::std::ratio.
	template <intmax_t Dividend, intmax_t Divisor = 1>
	class Ratio;

	typedef Ratio<1, 1000000000>    nano;
	typedef Ratio<1, 1000000>       micro;
	typedef Ratio<1, 1000>          milli;
	typedef Ratio<1000>             kilo;
	typedef Ratio<1000000>          mega;
	typedef Ratio<1000000000>       giga;

namespace std
{
	typedef ::std::micro    nano;
	typedef ::std::micro    micro;
	typedef ::std::milli    milli;
	typedef ::std::centi    centi;
	typedef ::std::deci     deci;
	typedef ::std::deca     deca;
	typedef ::std::hecto    hecto;
	typedef ::std::kilo     kilo;
	typedef ::std::mega     mega;
	typedef ::std::giga     giga;
	typedef ::std::tera     tera;
} // namespace std

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief substitutes for ::std::ratio.
 */
template <hryky_template_param>
class hryky::Ratio
{
	typedef IntegralConstant<intmax_t, Dividend> dividend;
	typedef IntegralConstant<intmax_t, Divisor> divisor;
	typedef tmp::Gcd<dividend, divisor> gcd;
public :

	typedef Ratio<hryky_template_arg> type;

	static intmax_t const num = tmp::Divide<
		tmp::Multiply<
			tmp::Multiply<
				tmp::Sign<dividend>,
				tmp::Sign<divisor>
			>,
			tmp::Abs<dividend>
		>,
		gcd
	>::type::value;
	
	static intmax_t const den = tmp::Divide<
		tmp::Abs<divisor>, gcd>::type::value;
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
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // RATIO_H_20140713170349377
// end of file
