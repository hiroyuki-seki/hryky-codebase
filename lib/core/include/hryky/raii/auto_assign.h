/**
  @file     auto_assign.h
  @brief    assigns a new value at the end of the current scope.
  @author   HRYKY
  @version  $Id: auto_assign.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef AUTO_ASSIGN_H_20140316085627039
#define AUTO_ASSIGN_H_20140316085627039
#include "hryky/type_traits/as_parameter.h"
#include "hryky/with_stream_out.h"
#include "hryky/without_copy.h"
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
	/// assigns a new value at the end of the current scope.
	template <
		typename LhsT, typename RhsT = LhsT
	>
	class AutoAssign;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief assigns a new value at the end of the current scope.
 */
template <hryky_template_param>
class hryky::AutoAssign :
	public WithStreamOut<AutoAssign<hryky_template_arg> >,
	private WithoutCopy
{
public :

	typedef AutoAssign<hryky_template_arg>      this_type;
	typedef typename AsParameter<RhsT>::type    rhs_type;

	/// instantiates with the terms at LHS and RHS.
	AutoAssign(LhsT & lhs, rhs_type rhs);

	/// move constructor.
	AutoAssign(this_type &&);

	/// destructor.
	~AutoAssign();

	/// releases the internal resources.
	void clear();

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// cancels the assignment.
	void disable();

protected :

private :

	hryky_delete_default_constructor(AutoAssign);
	hryky_delete_this_copy_constructor(AutoAssign);
	hryky_delete_this_copy_assign_op(AutoAssign);
	
	LhsT &      lhs_;
	rhs_type    rhs_;
	bool        disabled_;

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
/**
  @brief instantiates with the terms at LHS and RHS.
 */
template <hryky_template_param>
hryky::AutoAssign<hryky_template_arg>::AutoAssign(
	LhsT & lhs, rhs_type rhs)
	: lhs_(lhs)
	  , rhs_(rhs)
	  , disabled_()
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::AutoAssign<hryky_template_arg>::AutoAssign(this_type && rhs)
	: hryky_move_member(lhs)
	  , hryky_move_member(rhs)
	  , hryky_move_member(disabled)
{
	rhs.disable();
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::AutoAssign<hryky_template_arg>::~AutoAssign()
{
	if (!this->disabled_) {
		this->lhs_ = this->rhs_;
	}
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::AutoAssign<hryky_template_arg>::clear()
{
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::AutoAssign<hryky_template_arg>::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(lhs);
	hryky_write_member(rhs);
	hryky_write_member(disabled);
	return out;
}
/**
  @brief cancels the assignment.
 */
template <hryky_template_param>
void hryky::AutoAssign<hryky_template_arg>::disable()
{
	this->disabled_ = true;
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
	/// creates a AutoAssign instance.
	template <hryky_template_param>
	AutoAssign<hryky_template_arg> auto_assign(LhsT & lhs, RhsT const & rhs);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates a AutoAssign instance.
 */
template <hryky_template_param>
hryky::AutoAssign<hryky_template_arg> hryky::auto_assign(
	LhsT & lhs, RhsT const & rhs)
{
	return AutoAssign<LhsT, RhsT>(lhs, rhs);
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // AUTO_ASSIGN_H_20140316085627039
// end of file
