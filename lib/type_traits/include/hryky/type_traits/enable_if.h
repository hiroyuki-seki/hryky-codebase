/**
  @file         enable_if.h
  @brief        substitutes for ::std::enable_if.
  @author       HRYKY
  @version      $Id: enable_if.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
  @addtogroup   generic_programming
  @{
 */
#ifndef ENABLE_IF_H_20120317191826471
#define ENABLE_IF_H_20120317191826471
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// substitutes for ::std::enable_if_c.
	template < bool boolean, typename valueT  >
	class EnableIfC;
	
	/// substitutes for ::std::enable_if.
	template < typename ConditionT, typename ValueT >
	class EnableIf;

	/// substitutes for ::std::disable_if_c.
	template < bool boolean, typename valueT  >
	class DisableIfC;
	
	/// substitutes for ::std::disable_if.
	template < typename ConditionT, typename ValueT >
	class DisableIf;

}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief substitutes for ::std::enable_if_c.

  If @a boolean is true, hryky::EnableIfC::type is defined as @a ValueT.
 */
template < bool boolean, typename ValueT = void >
class hryky::EnableIfC
{
};
/**
  @brief substitutes for ::std::enable_if.

  If @a ConditionT::value is true, hryky::EnableIf::type is defined as @a ValueT.
 */
template < typename ConditionT, typename ValueT = void >
class hryky::EnableIf :
	public hryky::EnableIfC<ConditionT::type::value, ValueT>
{
};
/**
  @brief substitutes for ::std::disable_if_c.
  
  If @a boolean is false, hryky::DisableIfC::type is defined as @a ValueT.
 */
template < bool boolean, typename ValueT = void >
class hryky::DisableIfC
{
};
/**
  @brief substitutes for ::std::disable_if.

  If @a ConditionT::value is false, hryky::DisableIf::type is defined as @a ValueT.
 */
template < typename ConditionT, typename ValueT = void >
class hryky::DisableIf :
	public hryky::DisableIfC<ConditionT::type::value, ValueT>
{
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @internal
  @brief specializes hryky::EnableIfC when boolean is true.
  @endinternal
 */
template < typename ValueT >
class EnableIfC<true, ValueT>
{
public :
	typedef ValueT  type;
};
/**
  @internal
  @brief specializes hryky::DisableIfC when boolean is true.
  @endinternal
 */
template < typename ValueT >
class DisableIfC<false, ValueT>
{
public :
	typedef ValueT  type;
};
}
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
}
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // ENABLE_IF_H_20120317191826471
/// @}
// end of file
