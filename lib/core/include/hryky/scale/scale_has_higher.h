/**
  @file         scale_has_higher.h
  @brief        confirms whether the type has higher type.
  @author       HRYKY
  @version      $Id: scale_has_higher.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SCALE_HAS_HIGHER_H_20130101140100250
#define SCALE_HAS_HIGHER_H_20130101140100250
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// workaround for msvc10 internal compile error.
	template <typename ValueT>
	class HasHigher;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief workaround for msvc10 internal compile error.
 */
template <typename ValueT>
class hryky::HasHigher
{
private :
	typedef uint16_t    yes;
	typedef uint8_t     no;

	template < typename TargetT >
	static yes test(typename TargetT::higher_type const * const);
	
	template < typename TargetT >
	static no test(...);
	
public :

	static bool const value = sizeof(test<ValueT>(0)) == sizeof(yes);

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace scale
{
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
#endif // SCALE_HAS_HIGHER_H_20130101140100250
// end of file
