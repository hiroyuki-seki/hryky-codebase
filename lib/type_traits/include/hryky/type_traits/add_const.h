/**
  @file         add_const.h
  @brief        adds const qualifier to any type.
  @author       HRYKY
  @version      $Id: add_const.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
  @addtogroup   generic_programming
  @{
 */
#ifndef TYPE_ADD_CONST_H_20120226152038305
#define TYPE_ADD_CONST_H_20120226152038305
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// add const qualifier.
	template < typename ValueT >
	class AddConst;

}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief    add const qualifier.

 */
template < typename ValueT >
class hryky::AddConst
{
public :
	/// represents the type qualified by "const".
	typedef ValueT const    type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @internal
  @brief        add const qualifier.
  @note
  - specializes AddConst for constant parameter
  @endinternal
 */
template < typename ValueT >
class AddConst<ValueT const>
{
public :
	typedef ValueT const    type;
};
/**
  @internal
  @brief        add const qualifier.
  @note
  - specializes AddConst for reference parameter
  @endinternal
 */
template < typename ValueT >
class AddConst<ValueT &>
{
public :
	typedef ValueT &        type;
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
} /// namespace hry;y
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // TYPE_ADD_CONST_H_20120226152038305
/// @}
// end of file
