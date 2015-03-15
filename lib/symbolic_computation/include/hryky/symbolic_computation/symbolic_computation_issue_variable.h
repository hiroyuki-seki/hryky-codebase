/**
  @file     symbolic_computation_issue_variable.h
  @brief    issues a new variable.
  @author   HRYKY
  @version  $Id: symbolic_computation_issue_variable.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_ISSUE_VARIABLE_H_20131201201907513
#define SYMBOLIC_COMPUTATION_ISSUE_VARIABLE_H_20131201201907513
#include "hryky/symbolic_computation/symbolic_computation_search.h"
#include "hryky/symbolic_computation/symbolic_computation_variable.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename TargetT, typename CandidateT
#define hryky_template_arg \
	TargetT, CandidateT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// issues a new variable.
	template <hryky_template_param>
	class IssueVariable;

	/// implements IssueVariable.
	template <
		hryky_template_param,
		bool Found = Search<TargetT, CandidateT>::value
	>
	class IssueVariableImpl;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief issues a new variable.
 */
template <hryky_template_param>
class hryky::symbolic_computation::IssueVariable
{
public :
	typedef typename IssueVariableImpl<
		typename TargetT::type, typename CandidateT::type>::type type;
};
/**
  @brief implements IssueVariable.
 */
template <hryky_template_param, bool Found>
class hryky::symbolic_computation::IssueVariableImpl
{
public :
	typedef typename IssueVariableImpl<
		TargetT,
		Variable<
			typename CandidateT::eval_type,
			CandidateT::index + 1u,
			CandidateT::symbol + 1
		>
	>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief The candidate is not used in target.
 */
template <hryky_template_param>
class IssueVariableImpl<hryky_template_arg, false>
{
public :
	typedef typename CandidateT::type type;
};
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
#endif // SYMBOLIC_COMPUTATION_ISSUE_VARIABLE_H_20131201201907513
// end of file
