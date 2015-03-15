/**
  @file     tmp_list.h
  @brief    container of types.
  @author   HRYKY
  @version  $Id: tmp_list.h 376 2014-07-29 10:46:52Z hryky.private@gmail.com $
 */
#ifndef TMP_LIST_H_20131216222506600
#define TMP_LIST_H_20131216222506600
#include "hryky/tmp/tmp_null.h"
#include "hryky/tmp/tmp_eval.h"
#include "hryky/tmp/tmp_type_of.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename FirstT, typename RestT
#define hryky_template_arg \
	FirstT, RestT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	/// container of types.
	template <
		typename FirstT,
		typename RestT
	>
	class List;

	typedef List<null_type, null_type> null_list_type;

	/// A list retaining no element.
	typedef null_list_type List0;

	/// A list retaining one element.
	template <typename E1T>
	class List1;

	/// A list retaining two elements.
	template <typename E1T, typename E2T>
	class List2;

	/// A list retaining three elements.
	template <typename E1T, typename E2T, typename E3T>
	class List3;

	/// A list retaining four elements.
	template <typename E1T, typename E2T, typename E3T, typename E4T>
	class List4;

	/// A list retaining five elements.
	template <
		typename E1T, typename E2T, typename E3T, typename E4T, typename E5T
	>
	class List5;

	/// A list retaining six elements.
	template <
		typename E1T, typename E2T, typename E3T, typename E4T, typename E5T,
		typename E6T
	>
	class List6;

	/// A list retaining seven elements.
	template <
		typename E1T, typename E2T, typename E3T, typename E4T, typename E5T,
		typename E6T, typename E7T
	>
	class List7;

	/// A list retaining eight elements.
	template <
		typename E1T, typename E2T, typename E3T, typename E4T, typename E5T,
		typename E6T, typename E7T, typename E8T
	>
	class List8;

	/// A list retaining nine elements.
	template <
		typename E1T, typename E2T, typename E3T, typename E4T, typename E5T,
		typename E6T, typename E7T, typename E8T, typename E9T
	>
	class List9;

	

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief container of types.
 */
template <hryky_template_param>
class hryky::tmp::List
{
public :
	typedef typename TypeOf<FirstT>::type first_type;
	typedef typename RestT::type rest_type;
	typedef List<first_type, rest_type> type;
};
/**
  @brief A list retaining one element.
 */
template <typename E1T>
class hryky::tmp::List1
{
public :
	typedef typename List<E1T, null_list_type>::type type;
};
/**
  @brief A list retaining two elements.
 */
template <typename E1T, typename E2T>
class hryky::tmp::List2
{
public :
	typedef typename List<E1T, List1<E2T> >::type type;
};
/**
  @brief A list retaining three elements.
 */
template <typename E1T, typename E2T, typename E3T>
class hryky::tmp::List3
{
public :
	typedef typename List<E1T, List2<E2T, E3T> >::type type;
};
/**
  @brief A list retaining four elements.
 */
template <typename E1T, typename E2T, typename E3T, typename E4T>
class hryky::tmp::List4
{
public :
	typedef typename List<E1T, List3<E2T, E3T, E4T> >::type type;
};
/**
  @brief A list retaining five elements.
 */
template <typename E1T, typename E2T, typename E3T, typename E4T, typename E5T>
class hryky::tmp::List5
{
public :
	typedef typename List<E1T, List4<E2T, E3T, E4T, E5T> >::type type;
};
/**
  @brief A list retaining six elements.
 */
template <
	typename E1T, typename E2T, typename E3T, typename E4T, typename E5T,
	typename E6T
>
class hryky::tmp::List6
{
public :
	typedef typename List<E1T, List5<E2T, E3T, E4T, E5T, E6T> >::type type;
};
/**
  @brief A list retaining seven elements.
 */
template <
	typename E1T, typename E2T, typename E3T, typename E4T, typename E5T,
	typename E6T, typename E7T
>
class hryky::tmp::List7
{
public :
	typedef typename List<E1T, List6<
		E2T, E3T, E4T, E5T, E6T, E7T> >::type type;
};
/**
  @brief A list retaining eight elements.
 */
template <
	typename E1T, typename E2T, typename E3T, typename E4T, typename E5T,
	typename E6T, typename E7T, typename E8T
>
class hryky::tmp::List8
{
public :
	typedef typename List<E1T, List7<
		E2T, E3T, E4T, E5T, E6T, E7T, E8T> >::type type;
};
/**
  @brief A list retaining nine elements.
 */
template <
	typename E1T, typename E2T, typename E3T, typename E4T, typename E5T,
	typename E6T, typename E7T, typename E8T, typename E9T
>
class hryky::tmp::List9
{
public :
	typedef typename List<E1T, List8<
		E2T, E3T, E4T, E5T, E6T, E7T, E8T, E9T> >::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  @brief empty list.
 */
template <>
class List<null_type, null_type>
{
public :
	typedef List<null_type, null_type> type;
};
/**
  propagates the lazy evaluation.
 */
template <hryky_template_param>
class EvalImpl<List<hryky_template_arg> >
{
public :
	typedef typename List<Eval<FirstT>, Eval<RestT> >::type type;
};
} // namespace tmp
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
namespace tmp
{
} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // TMP_LIST_H_20131216222506600
// end of file
