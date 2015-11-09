/**
  @file     with_data.h
  @brief    provides hryky::data() function.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef WITH_DATA_H_20151109165109368
#define WITH_DATA_H_20151109165109368
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ContainerT, typename PointerT, typename ConstPointerT
#define hryky_template_arg \
	ContainerT, PointerT, ConstPointerT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// provides hryky::data() function.
	template <hryky_template_param>
	class WithData;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief provides hryky::data() function.
 */
template <hryky_template_param>
class hryky::WithData
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
	/// retrieves the mutable raw data of LiteralString.
	template <hryky_template_param>
	PointerT data(WithData<hryky_template_arg> & container);

	/// retrieves the immutable raw data of LiteralString.
	template <hryky_template_param>
	ConstPointerT data(WithData<hryky_template_arg> const & container);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the mutable raw data of LiteralString.
 */
template <hryky_template_param>
PointerT
hryky::data(WithData<hryky_template_arg> & container)
{
	return static_cast<ContainerT &>(container).data();
}
/**
  @brief retrieves the mutable raw data of LiteralString.
 */
template <hryky_template_param>
ConstPointerT
hryky::data(WithData<hryky_template_arg> const & container)
{
	return static_cast<ContainerT const &>(container).data();
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // WITH_DATA_H_20151109165109368
// end of file
