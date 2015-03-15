/**
  @file     remove_reference.h
  @brief    removes the modifier for reference.
  @author   HRYKY
  @version  $Id: remove_reference.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef REMOVE_REFERENCE_H_20130413130753213
#define REMOVE_REFERENCE_H_20130413130753213
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// removes the modifier for reference.
	template <typename ValueT>
	class RemoveReference;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief removes the modifier for reference.
 */
template <typename ValueT>
class hryky::RemoveReference
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
  @brief removes the modifier for reference from the type including reference.
 */
template <typename ValueT>
class RemoveReference<ValueT &>
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
#endif // REMOVE_REFERENCE_H_20130413130753213
// end of file
