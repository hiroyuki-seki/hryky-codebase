/**
  @file         min_of.h
  @brief        retrieves the maximum value.
  @author       HRYKY
  @version      $Id: min_of.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
  @addtogroup   generic_programming
  @{
 */
#ifndef TYPE_MIN_OF_H_20120308233909652
#define TYPE_MIN_OF_H_20120308233909652
#include "hryky/boost.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retrieves the maximum value.
	template < typename ValueT >
	class MinOf;
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the maximum value.
 */
template < typename ValueT >
class hryky::MinOf
{
public :

	/// the minimum number that ValueT can represent.
	static ValueT const value = boost::integer_traits<ValueT>::const_min;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace type
{
namespace traits
{
}
}
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
namespace type
{
namespace traits
{
}
}
}
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // TYPE_MIN_OF_H_20120308233909652
/// @}
// end of file
