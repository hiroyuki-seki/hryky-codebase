/**
  @file     permutation_first.h
  @brief    creates the first permutation in terms of both lexicographic order and Plain Changes.
  @author   HRYKY
  @version  $Id: permutation_first.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef PERMUTATION_FIRST_H_20131229104616115
#define PERMUTATION_FIRST_H_20131229104616115
#include "hryky/type_traits/integral_constant.h"
#include "hryky/tmp/tmp_list.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename SizeT
#define hryky_template_arg \
	SizeT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	template <typename ListT>
	class PushFront;
}
namespace permutation
{
	/**
	  creates the first permutation in terms of both lexicographic order
	  and Plain Changes.
	 */
	template <hryky_template_param>
	class First;

	/// implements First<> for the actual type.
	template <hryky_template_param>
	class FirstImpl;

} // namespace permutation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief creates the first permutation in terms of both lexicographic order
    and Plain Changes.
 */
template <hryky_template_param>
class hryky::permutation::First
{
public :
	typedef FirstImpl<typename SizeT::type>::type type;
};
/**
  @brief implements First<> for the actual type.
 */
template <hryky_template_param>
class hryky::permutation::FirstImpl
{
public :
	typedef tmp::PushBack<
		First<tmp::Decrement<SizeT> >,
		tmp::Decrement<SizeT>
	>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace permutation
{
/**
  creates an empty permutation.
 */
template <typename ValueT>
class FirstImpl<IntegralConstant<ValueT, 0> >
{
public :
	typedef tmp::null_list_type type;
};
} // namespace permutation
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
namespace permutation
{
} // namespace permutation
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // PERMUTATION_FIRST_H_20131229104616115
// end of file
