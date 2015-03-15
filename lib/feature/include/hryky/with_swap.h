/**
  @file     with_swap.h
  @brief    appends the functionality to interchange internal resources.
  @author   HRYKY
  @version  $Id: with_swap.h 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#ifndef WITH_SWAP_H_20140209142948270
#define WITH_SWAP_H_20140209142948270
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
	/// appends the functionality to interchange internal resources.
	template <hryky_template_param>
	class WithSwap;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief appends the functionality to interchange internal resources.
 */
template <typename DerivedT>
class hryky::WithSwap
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
	/// interchanges two instances of the same type.
	template <hryky_template_param>
	void swap(
		WithSwap<hryky_template_arg> & lhs,
		WithSwap<hryky_template_arg> & rhs);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief interchanges two instances of the same type.
 */
template <hryky_template_param>
void hryky::swap(
	WithSwap<hryky_template_arg> & lhs,
	WithSwap<hryky_template_arg> & rhs)
{
	static_cast<DerivedT &>(lhs).swap(static_cast<DerivedT &>(rhs));
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // WITH_SWAP_H_20140209142948270
// end of file
