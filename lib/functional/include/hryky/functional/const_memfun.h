/**
  @file     const_memfun.h
  @brief    wraps an immutable member function pointer as a callable functor without an argument.
  @author   HRYKY
  @version  $Id: const_memfun.h 380 2014-08-24 07:41:16Z hryky.private@gmail.com $
 */
#ifndef CONST_MEMFUN_H_20140112152109306
#define CONST_MEMFUN_H_20140112152109306
#include "hryky/retention/retention_value.h"
#include "hryky/type_traits/add_const_reference.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/**
	  raps an immutable member function pointer as a callable functor
	  without an argument.
	 */
	template <typename ClsT, typename RetT>
	class ConstMemfun0;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief wraps an immutable member function pointer as a callable functor
    without an argument.
 */
template <typename ClsT, typename RetT>
class hryky::ConstMemfun0 :
	public retention::Value<RetT (ClsT::*)()const>,
	public FunctionTraits1<
		RetT,
		typename AddConstReference<ClsT>::type
	>
{
public :
	typedef retention::Value<RetT (ClsT::*)()const> retention_type;
	
	ConstMemfun0(value_type const memfun)
		: retention_type(memfun)
	{
	}

	result_type operator()(arg1_type cls) const
	{
		return (cls.*(*this->get()))();
	}
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace functional
{
} // namespace functional
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
	/// creates a functor from an immutable member function.
	template <typename ClsT, typename RetT>
	ConstMemfun0<ClsT, RetT> function(
		RetT (ClsT::* const raw)()const);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates a functor from an immutable member function.
 */
template <typename ClsT, typename RetT>
hryky::ConstMemfun0<ClsT, RetT>
hryky::function(RetT (ClsT::* const raw)()const)
{
	return ConstMemfun0<ClsT, RetT>(raw);
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#endif // CONST_MEMFUN_H_20140112152109306
// end of file
