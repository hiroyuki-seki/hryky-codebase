/**
  @file     tmp_is_list.h
  @brief    confirms the term is list.
  @author   HRYKY
  @version  $Id: tmp_is_list.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef TMP_IS_LIST_H_20131223175209411
#define TMP_IS_LIST_H_20131223175209411
#include "hryky/tmp/tmp_list.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename TermT
#define hryky_template_arg \
	TermT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	/// confirms the term is list.
	template <hryky_template_param>
	class IsList;

	/// implements IsList<> for the actual type.
	template <hryky_template_param>
	class IsListImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms the term is list.
 */
template <hryky_template_param>
class hryky::tmp::IsList
{
public :
	typedef typename IsListImpl<typename TermT::type>::type type;
};
/**
  @brief implements IsList<> for the actual type.
 */
template <hryky_template_param>
class hryky::tmp::IsListImpl
{
public :
	typedef false_type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  The term is list.
 */
template <typename FirstT, typename RestT>
class IsListImpl<List<FirstT, RestT> >
{
public :
	typedef true_type type;
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
#endif // TMP_IS_LIST_H_20131223175209411
// end of file
