/**
  @file     unsigned_of.h
  @brief    retrieves the type of unsinged integer which has the same size.
  @author   HRYKY
  @version  $Id: unsigned_of.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef UNSIGNED_OF_H_20130416224337613
#define UNSIGNED_OF_H_20130416224337613
#include "hryky/stdint.h"
#include "hryky/integer/unsigned_enough.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retrieves the type of unsinged integer which has the same size.
	template <typename ValueT>
	class UnsignedOf;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the type of unsinged integer which has the same size.
 */
template <typename ValueT>
class hryky::UnsignedOf
{
public :
	typedef typename UnsignedEnoughBytes<sizeof(ValueT)>::type type;

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
#endif // UNSIGNED_OF_H_20130416224337613
// end of file
