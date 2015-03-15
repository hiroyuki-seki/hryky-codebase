/**
  @file         max_of.h
  @brief        retrieves the maximum value.
  @author       HRYKY
  @version      $Id: max_of.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
  @addtogroup   generic_programming
  @{
 */
#ifndef TYPE_MAX_OF_H_20120308233556649
#define TYPE_MAX_OF_H_20120308233556649
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
	class MaxOf;
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the maximum value.
 */
template < typename ValueT >
class hryky::MaxOf
{
public :

	/// the maximum number that ValueT can represent.
	static ValueT const value = boost::integer_traits<ValueT>::const_max;

protected :

private :

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
#endif // TYPE_MAX_OF_H_20120308233556649
/// @}
// end of file
