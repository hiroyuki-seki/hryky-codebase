/**
  @file         scale_radix.h
  @brief        retrieves the radix from a lower scale to a higher scale.
  @author       HRYKY
  @version      $Id: scale_radix.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SCALE_RADIX_H_20130101104944117
#define SCALE_RADIX_H_20130101104944117
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace scale
{
	/// retrieves the radix from a lower scale to a higher scale.
	template < typename LowT, typename HighT >
	class Radix;

} // namespace scale
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the radix from a lower scale to a higher scale.
 */
template < typename LowT, typename HighT >
class hryky::scale::Radix
{
public :

	static int64_t const value = (
		typename LowT::higher_radix
		* typename Radix<typename LowT::higher_type, HighT>::value);
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace scale
{
/**
  @brief specializes if the template arguments are same.
 */
template <typename ValueT>
class Radix<ValueT, ValueT>
{
public :

	static int64_t const value = 1;
};
} // namespace scale
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
namespace scale
{
} // namespace scale
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // SCALE_RADIX_H_20130101104944117
// end of file
