/**
  @file     tmp_is_iterator.h
  @brief    confirms the term is an iterator.
  @author   HRYKY
  @version  $Id: tmp_is_iterator.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef TMP_IS_ITERATOR_H_20131228113643150
#define TMP_IS_ITERATOR_H_20131228113643150
#include "hryky/tmp/tmp_iterator.h"
#include "hryky/tmp/tmp_reverse_iterator.h"
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
	/// confirms the term is an iterator.
	template <hryky_template_param>
	class IsIterator;

	/// implements IsIterator for the actual type.
	template <hryky_template_param>
	class IsIteratorImpl;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms the term is an iterator.
 */
template <hryky_template_param>
class hryky::tmp::IsIterator
{
public :
	typedef typename IsIteratorImpl<typename TermT::type>::type type;
};
/**
  @brief implements IsIterator for the actual type.
 */
template <hryky_template_param>
class hryky::tmp::IsIteratorImpl
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
  The term is an iterator.
 */
template <typename ListT, typename IndexT>
class IsIteratorImpl<IteratorImpl<ListT, IndexT> >
{
public :
	typedef true_type type;
};
/**
  The term is a reverse iterator.
 */
template <typename ListT, typename IndexT>
class IsIteratorImpl<ReverseIteratorImpl<ListT, IndexT> >
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
#endif // TMP_IS_ITERATOR_H_20131228113643150
// end of file
