/**
  @file     placeholder.h
  @brief    defines the indices of the actual arguments.
  @author   HRYKY
  @version  $Id: placeholder.h 353 2014-06-17 04:55:19Z hryky.private@gmail.com $
 */
#ifndef PLACEHOLDER_H_20140617105737123
#define PLACEHOLDER_H_20140617105737123
#include "hryky/type_traits/integral_constant.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	size_t Index
#define hryky_template_arg \
	Index
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// defines the indices of the actual arguments.
	template <size_t Index>
	class Placeholder;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief defines the indices of the actual arguments.
 */
template <hryky_template_param>
class hryky::Placeholder :
	public IntegralConstant<size_t, Index>
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
	/// binds the actual arguments.
	template <typename FromsT, size_t Index>
	typename AsParameter<
		typename tuple::At<FromsT, Index>::type::first_type>::type
		bind_arg(FromsT const & froms, Placeholder<Index> const &);

	/// binds the actual arguments with the specified valud.
	template <typename FromsT, typename ToT>
	ToT bind_arg(FromsT const &, ToT to);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief binds the actual arguments.
 */
template <typename FromsT, size_t Index>
typename hryky::AsParameter<
	typename hryky::tuple::At<FromsT, Index>::type::first_type>::type
hryky::bind_arg(
	FromsT const & froms, Placeholder<Index> const &)
{
	return froms.at<Index>();
}
/**
  @brief binds the actual arguments with the specified valud.
 */
template <typename FromsT, typename ToT>
ToT hryky::bind_arg(FromsT const &, ToT to)
{
	return to;
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // PLACEHOLDER_H_20140617105737123
// end of file
