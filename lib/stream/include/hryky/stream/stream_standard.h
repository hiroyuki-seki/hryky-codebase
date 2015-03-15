/**
  @file     stream_standard.h
  @brief    overloads stream operation so that standard types can be utilized.
  @author   HRYKY
  @version  $Id: stream_standard.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef STREAM_STANDARD_H_20140209102007097
#define STREAM_STANDARD_H_20140209102007097
#include "hryky/std/std_utility.h"
#include "hryky/stream/stream_array_scope.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace stream
{
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// declares structs
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
	/// outputs ::std::pair.
	template <typename StreamT, typename FirstT, typename SecondT>
	StreamT & operator<<(
		StreamT & lhs, ::std::pair<FirstT, SecondT> const & rhs);

namespace stream
{
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief outputs ::std::pair.
 */
template <typename StreamT, typename FirstT, typename SecondT>
StreamT & hryky::operator<<(
	StreamT & lhs, ::std::pair<FirstT, SecondT> const & rhs)
{
	stream::array::Scope<StreamT> const array(lhs);

	lhs << rhs.first;
	lhs << rhs.second;
	
	return lhs;
}
#endif // STREAM_STANDARD_H_20140209102007097
// end of file
