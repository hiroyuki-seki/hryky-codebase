/**
  @file     with_size.h
  @brief    provides hryky::size() function.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef WITH_SIZE_H_20151109170841381
#define WITH_SIZE_H_20151109170841381
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ContainerT, typename SizeT
#define hryky_template_arg \
	ContainerT, SizeT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// provides hryky::size() function.
	template <typename ContainerT, typename SizeT>
	class WithSize;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief provides hryky::size() function.
 */
template <hryky_template_param>
class hryky::WithSize
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
	/// retrieves the size of elements in a container.
	template <hryky_template_param>
	SizeT size(WithSize<hryky_template_arg> const & container);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the size of elements in a container.
 */
template <hryky_template_param>
SizeT hryky::size(WithSize<hryky_template_arg> const & container)
{
	return static_cast<ContainerT const &>(container).size();
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // WITH_SIZE_H_20151109170841381
// end of file
