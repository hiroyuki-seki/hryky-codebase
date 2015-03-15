/**
  @file     tmp_abs.h
  @brief    retrieves the absolute value.
  @author   HRYKY
  @version  $Id: tmp_abs.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef TMP_ABS_H_20140713140907256
#define TMP_ABS_H_20140713140907256
#include "hryky/tmp/tmp_conditional.h"
#include "hryky/tmp/tmp_is_negative.h"
#include "hryky/tmp/tmp_complement.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename TermT
#define hryky_template_arg \
	TermT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	/// retrieves the absolute value.
	template <typename TermT>
	class Abs;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the absolute value.
 */
template <hryky_template_param>
class hryky::tmp::Abs
{
public :
	typedef typename Conditional<
		IsNegative<TermT>,
		Complement<TermT>,
		TermT
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
#endif // TMP_ABS_H_20140713140907256
// end of file
