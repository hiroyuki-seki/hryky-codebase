/**
  @file     symbolic_computation_search.h
  @brief    searches the operation.
  @author   HRYKY
  @version  $Id: symbolic_computation_search.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_SEARCH_H_20131201135804248
#define SYMBOLIC_COMPUTATION_SEARCH_H_20131201135804248
#include "hryky/type_traits/is_same.h"
#include "hryky/symbolic_computation/symbolic_computation_some.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename TargetT, typename WrtT
#define hryky_template_arg \
	TargetT, WrtT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// searches the operation.
	template <hryky_template_param>
	class Search;

	/// implements Search.
	template <hryky_template_param>
	class SearchImpl;

	/// traverses the tree of operations.
	template <hryky_template_param>
	class SearchOp;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief searches the operation.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Search
{
private :
	typedef SearchImpl<typename TargetT::type, typename WrtT::type> impl;
public :
	typedef typename impl::type type;
	static bool const value = type::value;
};
/**
  @brief implements Search.
 */
template <hryky_template_param>
class hryky::symbolic_computation::SearchImpl
{
public :
	template <typename TermT>
	class Op
	{
	public :
		static bool const value = IsSame<TermT, WrtT>::type::value;
		typedef Op<TermT> type;
	};

	typedef typename SomeIf<Op<TargetT>, TargetT, Op>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
} // namespace symbolic_computation
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
namespace symbolic_computation
{
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // SYMBOLIC_COMPUTATION_SEARCH_H_20131201135804248
// end of file
