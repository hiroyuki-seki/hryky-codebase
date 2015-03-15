/**
  @file     signed_of.h
  @brief    retrieves the type of signed integer which has the same size.
  @author   HRYKY
  @version  $Id: signed_of.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SIGNED_OF_H_20130416225517621
#define SIGNED_OF_H_20130416225517621
#include "hryky/stdint.h"
#include "hryky/integer/signed_enough.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retrieves the type of signed integer which has the same size.
	template <typename ValueT>
	class SignedOf;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the type of signed integer which has the same size.
 */
template <typename ValueT>
class hryky::SignedOf
{
public :
	typedef typename SignedEnoughBytes<sizeof(ValueT)>::type type;
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
#endif // SIGNED_OF_H_20130416225517621
// end of file
