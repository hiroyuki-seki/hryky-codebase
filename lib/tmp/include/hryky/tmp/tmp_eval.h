/**
  @file     tmp_eval.h
  @brief    retrives the evaluated value or type.
  @author   HRYKY
  @version  $Id: tmp_eval.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef TMP_EVAL_H_20131217215220578
#define TMP_EVAL_H_20131217215220578
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
namespace hryky
{
namespace tmp
{
	/// retrives the evaluated value or type.
	template <hryky_template_param>
	class Eval;

	/// implements Eval<> for the actual type.
	template <hryky_template_param>
	class EvalImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrives the evaluated value or type.
 */
template <hryky_template_param>
class hryky::tmp::Eval
{
public :
	typedef typename EvalImpl<typename ValueT::type>::type type;
};
/**
  @brief implements Eval<> for the actual type.
 */
template <hryky_template_param>
class hryky::tmp::EvalImpl
{
public :
	typedef typename ValueT::type type;
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
#endif // TMP_EVAL_H_20131217215220578
// end of file
