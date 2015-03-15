/**
  @file     auto_call.h
  @brief    calls an arbitrary function at the end of the current scope.
  @author   HRYKY
  @version  $Id: auto_call.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef AUTO_CALL_H_20140310162308349
#define AUTO_CALL_H_20140310162308349
#include "hryky/without_copy.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename FunctorT
#define hryky_template_arg \
	FunctorT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// calls an arbitrary function at the end of the current scope.
	template <hryky_template_param>
	class AutoCall;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief calls an arbitrary function at the end of the current scope.
 */
template <typename FunctorT>
class hryky::AutoCall :
	private WithoutCopy
{
public :

	typedef AutoCall<hryky_template_arg> this_type;

	/// instantiates with a functor.
	AutoCall(FunctorT const & functor);

	/// destructor.
	~AutoCall();

	/// move constructor.
	AutoCall(this_type && rhs);

	/// disables to invoke the functor.
	void disable();

protected :

private :

	hryky_delete_default_constructor(AutoCall);
	hryky_delete_this_copy_constructor(AutoCall);
	hryky_delete_this_copy_assign_op(AutoCall);

	FunctorT functor_;
	bool disable_;

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
  @brief instantiates with a functor.
 */
template <hryky_template_param>
hryky::AutoCall<hryky_template_arg>::AutoCall(FunctorT const & functor)
	: functor_(functor)
	  , disable_()
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::AutoCall<hryky_template_arg>::AutoCall(this_type && rhs)
	: hryky_move_member(functor)
	  , disable_()
{
	rhs.disable();
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::AutoCall<hryky_template_arg>::~AutoCall()
{
	if (!this->disable_) {
		this->functor_();
	}
}
/**
  @brief disables to invoke the functor.
 */
template <hryky_template_param>
void hryky::AutoCall<hryky_template_arg>::disable()
{
	this->disable_ = true;
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
	/// instantiates an AutoCall.
	template <hryky_template_param>
	AutoCall<hryky_template_arg>
		auto_call(FunctorT const & functor);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief instantiates an AutoCall.
 */
template <hryky_template_param>
hryky::AutoCall<hryky_template_arg>
hryky::auto_call(FunctorT const & functor)
{
	return AutoCall<FunctorT>(functor);
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // AUTO_CALL_H_20140310162308349
// end of file
