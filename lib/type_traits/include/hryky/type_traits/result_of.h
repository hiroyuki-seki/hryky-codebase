/**
  @file     result_of.h
  @brief    retrieves the type of result from functional type.
  @author   HRYKY
  @version  $Id: result_of.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef RESULT_OF_H_20140617050418877
#define RESULT_OF_H_20140617050418877
#include "hryky/config.h"
#include "hryky/std/std_type_traits.h"
#include "hryky/type_traits/has_result_type.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename FunctionT, bool IsFunctor
#define hryky_template_arg \
	FunctionT, IsFunctor
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retrieves the type of result from functional type.
	template <
		typename FunctionT,
		bool IsFunctor = HasResultType<FunctionT>::value
	>
	class ResultOf;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the type of result from functional type.
 */
template <hryky_template_param>
class hryky::ResultOf
{
public :
	typedef typename FunctionT::result_type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief retrieves the type of result from functional type.
 */
template <typename RetT, typename Arg1T, typename Arg2T>
class ResultOf<RetT (*)(Arg1T, Arg2T), false>
{
public :
	typedef RetT type;
};
/**
  @brief retrieves the type of result from functional type.
 */
template <typename RetT, typename ClsT, typename Arg1T, typename Arg2T>
class ResultOf<RetT (ClsT::*)(Arg1T, Arg2T), false>
{
public :
	typedef RetT type;
};
/**
  @brief retrieves the type of result from functional type.
 */
template <typename RetT, typename ClsT, typename Arg1T, typename Arg2T>
class ResultOf<RetT (ClsT::*)(Arg1T, Arg2T) const, false>
{
public :
	typedef RetT type;
};
/**
  @brief retrieves the type of result from functional type.
 */
template <typename FunctionT>
class ResultOf<FunctionT, false>
{
public :
#if HRYKY_USE_STD_RESULT_OF
	typedef ::std::result_of<FunctionT> result_of_type;
	typedef typename result_of_type::type type;
#endif
};
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
#endif // RESULT_OF_H_20140617050418877
// end of file
