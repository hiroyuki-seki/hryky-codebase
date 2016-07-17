/**
  @file     tuple_call.h
  @brief    calls a functor with tuple as arguments.
  @author   HRYKY
  @version  $Id: tuple_call.h 376 2014-07-29 10:46:52Z hryky.private@gmail.com $
 */
#ifndef TUPLE_CALL_H_20140729174626407
#define TUPLE_CALL_H_20140729174626407
#include "hryky/tmp/tmp_size.h"
#include "hryky/tuple/tuple_types.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename RetT, typename ArgsT, size_t ArgsSize
#define hryky_template_arg \
	RetT, ArgsT, ArgsSize
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace tuple
{
	/// calls a functor with tuple as arguments.
	template <
		typename RetT,
		typename ArgsT,
		size_t ArgsSize
			= tmp::Size<typename Types<ArgsT>::type>::type::value
	>
	class Call;

} // namespace tuple
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief calls a functor with tuple as arguments.
 */
template <hryky_template_param>
class hryky::tuple::Call
{
public :
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tuple
{
/**
  @brief calls a functor without an argument.
 */
template <typename RetT, typename ArgsT>
class Call<RetT, ArgsT, 0>
{
public :
	template <typename FunctorT>
	static RetT by(FunctorT & functor, ArgsT const &)
	{
		return functor();
	}
	
	template <typename FunctorT>
	static RetT by(FunctorT const & functor, ArgsT const &)
	{
		return functor();
	}
};
/**
  @brief calls a functor with an argument.
 */
template <typename RetT, typename ArgsT>
class Call<RetT, ArgsT, 1>
{
public :
	template <typename FunctorT>
	static RetT by(FunctorT & functor, ArgsT const & args)
	{
		return functor(args.template at<0>());
	}
};
/**
  @brief calls a functor with two arguments.
 */
template <typename RetT, typename ArgsT>
class Call<RetT, ArgsT, 2>
{
public :
	template <typename FunctorT>
	static RetT by(FunctorT & functor, ArgsT const & args)
	{
		return functor(args.template at<0>(), args.template at<1>());
	}
};
/**
  @brief calls a functor with three arguments.
 */
template <typename RetT, typename ArgsT>
class Call<RetT, ArgsT, 3>
{
public :
	template <typename FunctorT>
	static RetT by(FunctorT & functor, ArgsT const & args)
	{
		return functor(
			args.template at<0>(),
			args.template at<1>(),
			args.template at<2>());
	}
	
	template <typename FunctorT>
	static RetT by(FunctorT const & functor, ArgsT const & args)
	{
		return functor(
			args.template at<0>(),
			args.template at<1>(),
			args.template at<2>());
	}
};
} // namespace tuple
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
namespace tuple
{
} // namespace tuple
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // TUPLE_CALL_H_20140729174626407
// end of file
