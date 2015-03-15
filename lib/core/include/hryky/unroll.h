/**
  @file     unroll.h
  @brief    unrolls a repetition as far as possible.
  @author   HRYKY
  @version  $Id: unroll.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef UNROLL_H_20131031130546212
#define UNROLL_H_20131031130546212
#include "hryky/integer/unsigned_enough.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	size_t Size, size_t Begin
#define hryky_template_arg \
	Size, Begin
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// unrolls a repetition as far as possible.
	template <hryky_template_param>
	class Unroll;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief unrolls a repetition as far as possible.
 */
template <size_t Size, size_t Begin = 0>
class hryky::Unroll
{
private :
	typedef typename UnsignedEnoughUint<Size>::type size_type;
public :

	template <typename FunctorT>
	static void foreach(FunctorT const & functor) {
		functor();
		Unroll<Size - 1, Begin + 1>::foreach(functor);
	}

	template <typename FunctorT>
	static void foreach_at(FunctorT const & functor) {
		functor(static_cast<size_type>(Begin));
		Unroll<Size - 1, Begin + 1>::foreach_at(functor);
	}

	template <typename FunctorT>
	static void foreach_at_c(FunctorT const & functor) {
		functor.operator()<Begin>();
		Unroll<Size - 1, Begin + 1>::foreach_at_c(functor);
	}

	template <typename FunctorT>
	static bool every(FunctorT const & functor) {
		return functor() &&
			Unroll<Size - 1, Begin + 1>::every(functor);
	}

	template <typename FunctorT>
	static bool every_at(FunctorT const & functor) {
		return functor(static_cast<size_type>(Begin)) &&
			Unroll<Size - 1, Begin + 1>::every_at(functor);
	}

	template <typename FunctorT>
	static bool every_at_c(FunctorT const & functor) {
		return functor.operator()<Begin>() &&
			Unroll<Size - 1, Begin + 1>::every_at_c(functor);
	}

	template <typename FunctorT>
	static bool some(FunctorT const & functor) {
		return functor() ||
			Unroll<Size - 1, Begin + 1>::some(functor);
	}

	template <typename FunctorT>
	static bool some_at(FunctorT const & functor) {
		return functor(static_cast<size_type>(Begin)) ||
			Unroll<Size - 1, Begin + 1>::some_at(functor);
	}

	template <typename FunctorT>
	static bool some_at_c(FunctorT const & functor) {
		return functor.operator()<Begin>() ||
			Unroll<Size - 1, Begin + 1>::some_at_c(functor);
	}

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief unrolls an ineffective repetition.
 */
template <size_t Begin>
class Unroll<0, Begin>
{
public :

	template <typename FunctorT>
	static void foreach(FunctorT const &) {
	}

	template <typename FunctorT>
	static void foreach_at(FunctorT const &) {
	}

	template <typename FunctorT>
	static void foreach_at_c(FunctorT const &) {
	}

	template <typename FunctorT>
	static bool every(FunctorT const &) {
		return true;
	}

	template <typename FunctorT>
	static bool every_at(FunctorT const &) {
		return true;
	}

	template <typename FunctorT>
	static bool every_at_c(FunctorT const &) {
		return true;
	}

	template <typename FunctorT>
	static bool some(FunctorT const &) {
		return false;
	}

	template <typename FunctorT>
	static bool some_at(FunctorT const &) {
		return false;
	}

	template <typename FunctorT>
	static bool some_at_c(FunctorT const &) {
		return false;
	}

};
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
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // UNROLL_H_20131031130546212
// end of file
