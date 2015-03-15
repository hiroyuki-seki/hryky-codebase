/**
  @file     conjugate.h
  @brief    retrieves the complex conjugate.
  @author   HRYKY
  @version  $Id: conjugate.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef CONJUGATE_H_20131109002922687
#define CONJUGATE_H_20131109002922687
#include "hryky/std/std_complex.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
} // namespace hryky
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
	/// retrieves the conjugate of ::std::complex.
	template <typename ValueT>
	::std::complex<ValueT> conj(::std::complex<ValueT> const & src);

	/// does nothing about normal value.
	template <typename ValueT>
	ValueT const & conj(ValueT const & src);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the conjugate of ::std::complex.
 */
template <typename ValueT>
::std::complex<ValueT> hryky::conj(::std::complex<ValueT> const & src)
{
	return ::std::conj(src);
}
/**
  @brief does nothing about normal value.
 */
template <typename ValueT>
ValueT const & hryky::conj(ValueT const & src)
{
	return src;
}
#endif // CONJUGATE_H_20131109002922687
// end of file
