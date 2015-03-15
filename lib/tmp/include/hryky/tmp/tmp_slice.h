/**
  @file     tmp_slice.h
  @brief    extracts the part of container.
  @author   HRYKY
  @version  $Id: tmp_slice.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef TMP_SLICE_H_20131223175715414
#define TMP_SLICE_H_20131223175715414
#include "hryky/tmp/tmp_is_list.h"
#include "hryky/tmp/tmp_is_iterator.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ListT, typename BeginIndexT, typename EndIndexT
#define hryky_template_arg \
	ListT, BeginIndexT, EndIndexT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
	/// extracts the elements as a new container.
	template <hryky_template_param>
	class Slice;

	/// extract the first part of container.
	template <typename EndT>
	class SliceBefore;

	/// extract the last part of container.
	template <typename BeginT>
	class SliceAfter;

	/// extracts the elements between two iterators as new container.
	template <typename BeginT, typename EndT>
	class SliceIn;

	/// implements Slice<> for the actual types.
	template <typename BeginT, typename EndT>
	class SliceInImpl;

	template <typename ListT>
	class Begin;

	template <typename ListT>
	class End;

	template <typename TermT>
	class Increment;

	template <typename TermT>
	class Dereference;

	template <typename LhsT, typename RhsT>
	class Add;

} // namespace tmp
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief extracts the elements as a new container.
 */
template <hryky_template_param>
class hryky::tmp::Slice
{
	static_assert(
		IsList<ListT>::type::value,
		"The first parameter has to be a list.");
public :
	typedef typename SliceIn<
		Add<Begin<ListT>, BeginIndexT>,
		Add<Begin<ListT>, EndIndexT>
	>::type type;
};
/**
  @brief extract the first part of container.
 */
template <typename EndT>
class hryky::tmp::SliceBefore
{
	static_assert(
		IsIterator<EndT>::type::value,
		"The first parameter has to be an iterator.");
public :
	typedef typename SliceIn<
		Begin<typename EndT::type::list_type>,
		EndT
	>::type type;
};
/**
  @brief extract the last part of container.
 */
template <typename BeginT>
class hryky::tmp::SliceAfter
{
	static_assert(
		IsIterator<BeginT>::type::value,
		"The first parameter has to be an iterator.");
public :
	typedef typename SliceIn<
		BeginT,
		End<typename BeginT::type::list_type>
	>::type type;
};
/**
  @brief extracts the elements between two iterators as new container.
 */
template <typename BeginT, typename EndT>
class hryky::tmp::SliceIn
{
	static_assert(
		IsIterator<BeginT>::type::value,
		"The first parameter has to be an iterator.");
	static_assert(
		IsIterator<EndT>::type::value,
		"The second parameter has to be an iterator.");
public :
	typedef typename SliceInImpl<
		typename BeginT::type,
		typename EndT::type
	>::type type;
};
/**
  @brief implements Slice<> for the actual types.
 */
template <typename BeginT, typename EndT>
class hryky::tmp::SliceInImpl
{
public :
	typedef typename List<
		Dereference<BeginT>,
		SliceIn<Increment<BeginT>, EndT>
	>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tmp
{
/**
  terminates the creation of a new container.
 */
template <typename EndT>
class SliceInImpl<EndT, EndT>
{
public :
	typedef null_list_type type;
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
#endif // TMP_SLICE_H_20131223175715414
// end of file
