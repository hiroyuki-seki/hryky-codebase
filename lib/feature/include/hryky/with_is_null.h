/**
  @file     with_is_null.h
  @brief    appends the functionality to confirms the validity of instance.
  @author   HRYKY
  @version  $Id: with_is_null.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef WITH_IS_NULL_H_20140626103323106
#define WITH_IS_NULL_H_20140626103323106
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename DerivedT
#define hryky_template_arg \
	DerivedT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// appends the functionality to confirms the validity of instance.
	template <typename DerivedT>
	class WithIsNull;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief appends the functionality to confirms the validity of instance.
 */
template <hryky_template_param>
class hryky::WithIsNull
{
public :

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
	/// confirms whether the derived instance is regarded as null.
	template <hryky_template_param>
	bool is_null(WithIsNull<hryky_template_arg> const & src);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief confirms whether the derived instance is regarded as null.
 */
template <hryky_template_param>
bool hryky::is_null(WithIsNull<hryky_template_arg> const & src)
{
	return static_cast<DerivedT const &>(src).is_null();
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // WITH_IS_NULL_H_20140626103323106
// end of file
