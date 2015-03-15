/**
  @file         remove_const.h
  @brief        removes const qualifier.
  @author       HRYKY
  @version      $Id: remove_const.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef REMOVE_CONST_H_20130105175814415
#define REMOVE_CONST_H_20130105175814415
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// removes const qualifier.
	template <typename ValueT>
	class RemoveConst;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief removes const qualifier.
 */
template <typename ValueT>
class hryky::RemoveConst
{
public :

	typedef ValueT type;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief specialize RemoveConst for the type which has const qualifier.
 */
template <typename ValueT>
class RemoveConst<const ValueT>
{
public :

	typedef ValueT type;

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
#endif // REMOVE_CONST_H_20130105175814415
// end of file
