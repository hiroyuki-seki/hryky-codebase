/**
  @file     function_traits.h
  @brief    retrieves the attributes of a callable type.
  @author   HRYKY
  @version  $Id: function_traits.h 376 2014-07-29 10:46:52Z hryky.private@gmail.com $
 */
#ifndef FUNCTION_TRAITS_H_20140113130102209
#define FUNCTION_TRAITS_H_20140113130102209
#include "hryky/tmp.h"
#include "hryky/type_traits/has_callable_op.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename FunctionT
#define hryky_template_arg \
	FunctionT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retrieves the attributes of a callable type.
	template <typename FunctionT>
	class FunctionTraits;

	/// retrieves the attributes of a function pointer.
	template <typename FunctionT>
	class FunctionPtrTraits;

	/// The internal type to retains the type without an argument.
	template <typename RetT>
	class FunctionTraits0;

	/// The internal type to retains the type with an argument.
	template <typename RetT, typename A1T>
	class FunctionTraits1;

	/// The internal type to retains the type with two arguments.
	template <typename RetT, typename A1T, typename A2T>
	class FunctionTraits2;

	/// The internal type to retains the type with three arguments.
	template <typename RetT, typename A1T, typename A2T, typename A3T>
	class FunctionTraits3;

	/// The internal type to retains the type with four arguments.
	template <
		typename RetT, typename A1T, typename A2T, typename A3T, typename A4T
	>
	class FunctionTraits4;

	/// The internal type to retains the type with five arguments.
	template <
		typename RetT, typename A1T, typename A2T, typename A3T, typename A4T,
		typename A5T
	>
	class FunctionTraits5;

	/// The internal type to retains the type with six arguments.
	template <
		typename RetT, typename A1T, typename A2T, typename A3T, typename A4T,
		typename A5T, typename A6T
	>
	class FunctionTraits6;

	/// The internal type to retains the type with seven arguments.
	template <
		typename RetT, typename A1T, typename A2T, typename A3T, typename A4T,
		typename A5T, typename A6T, typename A7T
	>
	class FunctionTraits7;

	/// The internal type to retains the type with eight arguments.
	template <
		typename RetT, typename A1T, typename A2T, typename A3T, typename A4T,
		typename A5T, typename A6T, typename A7T, typename A8T
	>
	class FunctionTraits8;

	/// The internal type to retains the type with nine arguments.
	template <
		typename RetT, typename A1T, typename A2T, typename A3T, typename A4T,
		typename A5T, typename A6T, typename A7T, typename A8T, typename A9T
	>
	class FunctionTraits9;

	/// defines the types of argument by Tuple.
	template <typename RetT, typename TupleT>
	class FunctionTraitsTuple;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the attributes of a callable type.
 */
template <typename FunctionT>
class hryky::FunctionTraits :
	public FunctionPtrTraits<FunctionT>
{
public :

};
/**
  @brief retrieves the attributes of a function pointer.
 */
template <typename FunctionT>
class hryky::FunctionPtrTraits
{
public :

};
/**
  @brief The internal type to retains the type without an argument.
 */
template <typename RetT>
class hryky::FunctionTraits0
{
public :
	typedef RetT                result_type;
	typedef tmp::null_list_type args_type;
	
	static const size_t arity = 0u;
};
/**
  @brief The internal type to retains the type with an argument.
 */
template <typename RetT, typename A1T>
class hryky::FunctionTraits1
{
public :
	typedef RetT        result_type;
	typedef A1T         arg1_type;
	typedef tmp::List1<A1T> args_type;

	static const size_t arity = 1u;
};
/**
  @brief The internal type to retains the type with two arguments.
 */
template <typename RetT, typename A1T, typename A2T>
class hryky::FunctionTraits2
{
public :
	typedef RetT        result_type;
	typedef A1T         arg1_type;
	typedef A2T         arg2_type;
	typedef tmp::List2<A1T, A2T> args_type;

	static const size_t arity = 2u;
};
/**
  @brief The internal type to retains the type with three arguments.
 */
template <typename RetT, typename A1T, typename A2T, typename A3T>
class hryky::FunctionTraits3
{
public :
	typedef RetT        result_type;
	typedef A1T         arg1_type;
	typedef A2T         arg2_type;
	typedef A3T         arg3_type;
	typedef tmp::List3<A1T, A2T, A3T> args_type;

	static const size_t arity = 3u;
};
/**
  @brief The internal type to retains the type with four arguments.
 */
template <
	typename RetT, typename A1T, typename A2T, typename A3T, typename A4T
>
class hryky::FunctionTraits4
{
public :
	typedef RetT        result_type;
	typedef A1T         arg1_type;
	typedef A2T         arg2_type;
	typedef A3T         arg3_type;
	typedef A4T         arg4_type;
	typedef tmp::List4<A1T, A2T, A3T, A4T> args_type;

	static const size_t arity = 4u;
};
/**
  @brief The internal type to retains the type with five arguments.
 */
template <
	typename RetT, typename A1T, typename A2T, typename A3T, typename A4T,
	typename A5T
>
class hryky::FunctionTraits5
{
public :
	typedef RetT        result_type;
	typedef A1T         arg1_type;
	typedef A2T         arg2_type;
	typedef A3T         arg3_type;
	typedef A4T         arg4_type;
	typedef A5T         arg5_type;
	typedef tmp::List5<A1T, A2T, A3T, A4T, A5T> args_type;

	static const size_t arity = 5u;
};
/**
  @brief The internal type to retains the type with six arguments.
 */
template <
	typename RetT, typename A1T, typename A2T, typename A3T, typename A4T,
	typename A5T, typename A6T
>
class hryky::FunctionTraits6
{
public :
	typedef RetT        result_type;
	typedef A1T         arg1_type;
	typedef A2T         arg2_type;
	typedef A3T         arg3_type;
	typedef A4T         arg4_type;
	typedef A5T         arg5_type;
	typedef A6T         arg6_type;
	typedef tmp::List6<A1T, A2T, A3T, A4T, A5T, A6T> args_type;

	static const size_t arity = 6u;
};
/**
  @brief The internal type to retains the type with seven arguments.
 */
template <
	typename RetT, typename A1T, typename A2T, typename A3T, typename A4T,
	typename A5T, typename A6T, typename A7T
>
class hryky::FunctionTraits7
{
public :
	typedef RetT        result_type;
	typedef A1T         arg1_type;
	typedef A2T         arg2_type;
	typedef A3T         arg3_type;
	typedef A4T         arg4_type;
	typedef A5T         arg5_type;
	typedef A6T         arg6_type;
	typedef A7T         arg7_type;
	typedef tmp::List7<A1T, A2T, A3T, A4T, A5T, A6T, A7T> args_type;

	static const size_t arity = 7u;
};
/**
  @brief The internal type to retains the type with eight arguments.
 */
template <
	typename RetT, typename A1T, typename A2T, typename A3T, typename A4T,
	typename A5T, typename A6T, typename A7T, typename A8T
>
class hryky::FunctionTraits8
{
public :
	typedef RetT        result_type;
	typedef A1T         arg1_type;
	typedef A2T         arg2_type;
	typedef A3T         arg3_type;
	typedef A4T         arg4_type;
	typedef A5T         arg5_type;
	typedef A6T         arg6_type;
	typedef A7T         arg7_type;
	typedef A8T         arg8_type;
	typedef tmp::List8<A1T, A2T, A3T, A4T, A5T, A6T, A7T, A8T> args_type;

	static const size_t arity = 8u;
};
/**
  @brief The internal type to retains the type with nine arguments.
 */
template <
	typename RetT, typename A1T, typename A2T, typename A3T, typename A4T,
	typename A5T, typename A6T, typename A7T, typename A8T, typename A9T
>
class hryky::FunctionTraits9
{
public :
	typedef RetT        result_type;
	typedef A1T         arg1_type;
	typedef A2T         arg2_type;
	typedef A3T         arg3_type;
	typedef A4T         arg4_type;
	typedef A5T         arg5_type;
	typedef A6T         arg6_type;
	typedef A7T         arg7_type;
	typedef A8T         arg8_type;
	typedef A9T         arg9_type;
	
	typedef tmp::List9<A1T, A2T, A3T, A4T, A5T, A6T, A7T, A8T, A9T> args_type;

	static const size_t arity = 9u;
};
/**
  @brief defines the types of argument by Tuple.
 */
template <typename RetT, typename TupleT>
class hryky::FunctionTraitsTuple
{
public :
	typedef RetT result_type;
	typedef TupleT args_type;
	typedef typename TupleT::first_type arg1_type;
	typedef typename FunctionTraitsTuple<
		RetT, typename TupleT::rest_type>::arg1_type arg2_type;
	typedef typename FunctionTraitsTuple<
		RetT, typename TupleT::rest_type>::arg2_type arg3_type;
	typedef typename FunctionTraitsTuple<
		RetT, typename TupleT::rest_type>::arg3_type arg4_type;
	typedef typename FunctionTraitsTuple<
		RetT, typename TupleT::rest_type>::arg4_type arg5_type;
	typedef typename FunctionTraitsTuple<
		RetT, typename TupleT::rest_type>::arg5_type arg6_type;
	typedef typename FunctionTraitsTuple<
		RetT, typename TupleT::rest_type>::arg6_type arg7_type;
	typedef typename FunctionTraitsTuple<
		RetT, typename TupleT::rest_type>::arg7_type arg8_type;
	typedef typename FunctionTraitsTuple<
		RetT, typename TupleT::rest_type>::arg8_type arg9_type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
//------------------------------------------------------------------------------
// specializes function pointer
//------------------------------------------------------------------------------
/**
  A function pointer without an argument.
 */
template <typename RetT>
class FunctionPtrTraits<RetT (*)()> :
	public FunctionTraits0<RetT>
{
public :
};
/**
  A function pointer with an argument.
 */
template <typename RetT, typename A1T>
class FunctionPtrTraits<RetT (*)(A1T)> :
	public FunctionTraits1<RetT, A1T>
{
public :
};
/**
  A function pointer with two arguments.
 */
template <typename RetT, typename A1T, typename A2T>
class FunctionPtrTraits<RetT (*)(A1T, A2T)> :
	public FunctionTraits2<RetT, A1T, A2T>
{
public :
};
/**
  A function pointer with three arguments.
 */
template <typename RetT, typename A1T, typename A2T, typename A3T>
class FunctionPtrTraits<RetT (*)(A1T, A2T, A3T)> :
	public FunctionTraits3<RetT, A1T, A2T, A3T>
{
public :
};
/**
  A function pointer with four arguments.
 */
template <typename RetT, typename A1T, typename A2T, typename A3T, typename A4T>
class FunctionPtrTraits<RetT (*)(A1T, A2T, A3T, A4T)> :
	public FunctionTraits4<RetT, A1T, A2T, A3T, A4T>
{
public :
};
/**
  A function pointer with five arguments.
 */
template <
	typename RetT, typename A1T, typename A2T, typename A3T, typename A4T,
	typename A5T
>
class FunctionPtrTraits<RetT (*)(A1T, A2T, A3T, A4T, A5T)> :
	public FunctionTraits5<RetT, A1T, A2T, A3T, A4T, A5T>
{
public :
};
/**
  A function pointer with six arguments.
 */
template <
	typename RetT, typename A1T, typename A2T, typename A3T, typename A4T,
	typename A5T, typename A6T
>
class FunctionPtrTraits<RetT (*)(A1T, A2T, A3T, A4T, A5T, A6T)> :
	public FunctionTraits6<RetT, A1T, A2T, A3T, A4T, A5T, A6T>
{
public :
};
/**
  A function pointer with seven arguments.
 */
template <
	typename RetT, typename A1T, typename A2T, typename A3T, typename A4T,
	typename A5T, typename A6T, typename A7T
>
class FunctionPtrTraits<RetT (*)(A1T, A2T, A3T, A4T, A5T, A6T, A7T)> :
	public FunctionTraits7<RetT, A1T, A2T, A3T, A4T, A5T, A6T, A7T>
{
public :
};
/**
  A function pointer with eight arguments.
 */
template <
	typename RetT, typename A1T, typename A2T, typename A3T, typename A4T,
	typename A5T, typename A6T, typename A7T, typename A8T
>
class FunctionPtrTraits<RetT (*)(A1T, A2T, A3T, A4T, A5T, A6T, A7T, A8T)> :
	public FunctionTraits8<RetT, A1T, A2T, A3T, A4T, A5T, A6T, A7T, A8T>
{
public :
};
/**
  A function pointer with nine arguments.
 */
template <
	typename RetT, typename A1T, typename A2T, typename A3T, typename A4T,
	typename A5T, typename A6T, typename A7T, typename A8T, typename A9T
>
class FunctionPtrTraits<RetT (*)(A1T, A2T, A3T, A4T, A5T, A6T, A7T, A8T, A9T)> :
	public FunctionTraits9<RetT, A1T, A2T, A3T, A4T, A5T, A6T, A7T, A8T, A9T>
{
public :
};
//------------------------------------------------------------------------------
// specializes mutable member function.
//------------------------------------------------------------------------------
/**
  A mutable member function pointer without an argument.
 */
template <typename ClsT, typename RetT>
class FunctionPtrTraits<RetT (ClsT::*)()> :
	public FunctionTraits0<RetT>
{
public :
	typedef ClsT cls_type;
	static bool const is_const = false;
};
/**
  A mutable member function pointer with an argument.
 */
template <typename ClsT, typename RetT, typename A1T>
class FunctionPtrTraits<RetT (ClsT::*)(A1T)> :
	public FunctionTraits1<RetT, A1T>
{
public :
	typedef ClsT cls_type;
	static bool const is_const = false;
};
/**
  A mutable member function pointer with two arguments.
 */
template <typename ClsT, typename RetT, typename A1T, typename A2T>
class FunctionPtrTraits<RetT (ClsT::*)(A1T, A2T)> :
	public FunctionTraits2<RetT, A1T, A2T>
{
public :
	typedef ClsT cls_type;
	static bool const is_const = false;
};
/**
  A mutable member function pointer with three arguments.
 */
template <
	typename ClsT, typename RetT, typename A1T, typename A2T, typename A3T
>
class FunctionPtrTraits<RetT (ClsT::*)(A1T, A2T, A3T)> :
	public FunctionTraits3<RetT, A1T, A2T, A3T>
{
public :
	typedef ClsT cls_type;
	static bool const is_const = false;
};
/**
  A mutable member function pointer with four arguments.
 */
template <
	typename ClsT, typename RetT, typename A1T, typename A2T, typename A3T,
	typename A4T
>
class FunctionPtrTraits<RetT (ClsT::*)(A1T, A2T, A3T, A4T)> :
	public FunctionTraits4<RetT, A1T, A2T, A3T, A4T>
{
public :
	typedef ClsT cls_type;
	static bool const is_const = false;
};
/**
  A mutable member function pointer with five arguments.
 */
template <
	typename ClsT, typename RetT, typename A1T, typename A2T, typename A3T,
	typename A4T, typename A5T
>
class FunctionPtrTraits<RetT (ClsT::*)(A1T, A2T, A3T, A4T, A5T)> :
	public FunctionTraits5<RetT, A1T, A2T, A3T, A4T, A5T>
{
public :
	typedef ClsT cls_type;
	static bool const is_const = false;
};
/**
  A mutable member function pointer with six arguments.
 */
template <
	typename ClsT, typename RetT, typename A1T, typename A2T, typename A3T,
	typename A4T, typename A5T, typename A6T
>
class FunctionPtrTraits<RetT (ClsT::*)(A1T, A2T, A3T, A4T, A5T, A6T)> :
	public FunctionTraits6<RetT, A1T, A2T, A3T, A4T, A5T, A6T>
{
public :
	typedef ClsT cls_type;
	static bool const is_const = false;
};
/**
  A mutable member function pointer with seven arguments.
 */
template <
	typename ClsT, typename RetT, typename A1T, typename A2T, typename A3T,
	typename A4T, typename A5T, typename A6T, typename A7T
>
class FunctionPtrTraits<RetT (ClsT::*)(A1T, A2T, A3T, A4T, A5T, A6T, A7T)> :
	public FunctionTraits7<RetT, A1T, A2T, A3T, A4T, A5T, A6T, A7T>
{
public :
	typedef ClsT cls_type;
	static bool const is_const = false;
};
/**
  A mutable member function pointer with eight arguments.
 */
template <
	typename ClsT, typename RetT, typename A1T, typename A2T, typename A3T,
	typename A4T, typename A5T, typename A6T, typename A7T, typename A8T
>
class FunctionPtrTraits<RetT (ClsT::*)(A1T, A2T, A3T, A4T, A5T, A6T, A7T, A8T)> :
	public FunctionTraits8<RetT, A1T, A2T, A3T, A4T, A5T, A6T, A7T, A8T>
{
public :
	typedef ClsT cls_type;
	static bool const is_const = false;
};
/**
  A mutable member function pointer with nine arguments.
 */
template <
	typename ClsT, typename RetT, typename A1T, typename A2T, typename A3T,
	typename A4T, typename A5T, typename A6T, typename A7T, typename A8T,
	typename A9T
>
class FunctionPtrTraits<
	RetT (ClsT::*)(A1T, A2T, A3T, A4T, A5T, A6T, A7T, A8T, A9T)
> :
	public FunctionTraits9<RetT, A1T, A2T, A3T, A4T, A5T, A6T, A7T, A8T, A9T>
{
public :
	typedef ClsT cls_type;
	static bool const is_const = false;
};
//------------------------------------------------------------------------------
// specializes immutable member function.
//------------------------------------------------------------------------------
/**
  A immutable member function pointer without an argument.
 */
template <typename ClsT, typename RetT>
class FunctionPtrTraits<RetT (ClsT::*)() const> :
	public FunctionTraits0<RetT>
{
public :
	typedef ClsT cls_type;
	static bool const is_const = true;
};
/**
  A immutable member function pointer with an argument.
 */
template <typename ClsT, typename RetT, typename A1T>
class FunctionPtrTraits<RetT (ClsT::*)(A1T) const> :
	public FunctionTraits1<RetT, A1T>
{
public :
	typedef ClsT cls_type;
	static bool const is_const = true;
};
/**
  A immutable member function pointer with two arguments.
 */
template <typename ClsT, typename RetT, typename A1T, typename A2T>
class FunctionPtrTraits<RetT (ClsT::*)(A1T, A2T) const> :
	public FunctionTraits2<RetT, A1T, A2T>
{
public :
	typedef ClsT cls_type;
	static bool const is_const = true;
};
/**
  A immutable member function pointer with three arguments.
 */
template <
	typename ClsT, typename RetT, typename A1T, typename A2T, typename A3T
>
class FunctionPtrTraits<RetT (ClsT::*)(A1T, A2T, A3T) const> :
	public FunctionTraits3<RetT, A1T, A2T, A3T>
{
public :
	typedef ClsT cls_type;
	static bool const is_const = true;
};
/**
  A immutable member function pointer with four arguments.
 */
template <
	typename ClsT, typename RetT, typename A1T, typename A2T, typename A3T,
	typename A4T
>
class FunctionPtrTraits<RetT (ClsT::*)(A1T, A2T, A3T, A4T) const> :
	public FunctionTraits4<RetT, A1T, A2T, A3T, A4T>
{
public :
	typedef ClsT cls_type;
	static bool const is_const = true;
};
/**
  A immutable member function pointer with five arguments.
 */
template <
	typename ClsT, typename RetT, typename A1T, typename A2T, typename A3T,
	typename A4T, typename A5T
>
class FunctionPtrTraits<RetT (ClsT::*)(A1T, A2T, A3T, A4T, A5T) const> :
	public FunctionTraits5<RetT, A1T, A2T, A3T, A4T, A5T>
{
public :
	typedef ClsT cls_type;
	static bool const is_const = true;
};
/**
  A immutable member function pointer with six arguments.
 */
template <
	typename ClsT, typename RetT, typename A1T, typename A2T, typename A3T,
	typename A4T, typename A5T, typename A6T
>
class FunctionPtrTraits<RetT (ClsT::*)(A1T, A2T, A3T, A4T, A5T, A6T) const> :
	public FunctionTraits6<RetT, A1T, A2T, A3T, A4T, A5T, A6T>
{
public :
	typedef ClsT cls_type;
	static bool const is_const = true;
};
/**
  A immutable member function pointer with seven arguments.
 */
template <
	typename ClsT, typename RetT, typename A1T, typename A2T, typename A3T,
	typename A4T, typename A5T, typename A6T, typename A7T
>
class FunctionPtrTraits<RetT (ClsT::*)(A1T, A2T, A3T, A4T, A5T, A6T, A7T) const> :
	public FunctionTraits7<RetT, A1T, A2T, A3T, A4T, A5T, A6T, A7T>
{
public :
	typedef ClsT cls_type;
	static bool const is_const = true;
};
/**
  A immutable member function pointer with eight arguments.
 */
template <
	typename ClsT, typename RetT, typename A1T, typename A2T, typename A3T,
	typename A4T, typename A5T, typename A6T, typename A7T, typename A8T
>
class FunctionPtrTraits<
	RetT (ClsT::*)(A1T, A2T, A3T, A4T, A5T, A6T, A7T, A8T) const
> :
	public FunctionTraits8<RetT, A1T, A2T, A3T, A4T, A5T, A6T, A7T, A8T>
{
public :
	typedef ClsT cls_type;
	static bool const is_const = true;
};
/**
  A immutable member function pointer with nine arguments.
 */
template <
	typename ClsT, typename RetT, typename A1T, typename A2T, typename A3T,
	typename A4T, typename A5T, typename A6T, typename A7T, typename A8T,
	typename A9T
>
class FunctionPtrTraits<
	RetT (ClsT::*)(A1T, A2T, A3T, A4T, A5T, A6T, A7T, A8T, A9T) const
> :
	public FunctionTraits9<RetT, A1T, A2T, A3T, A4T, A5T, A6T, A7T, A8T, A9T>
{
public :
	typedef ClsT cls_type;
	static bool const is_const = true;
};
//------------------------------------------------------------------------------
// specializes empty tuple as arguments.
//------------------------------------------------------------------------------
/**
  specializes empty tuple as arguments.
 */
template <typename RetT>
class FunctionTraitsTuple<RetT, Tuple<Null> >
{
public :
	typedef RetT result_type;
	typedef Tuple<Null> args_type;
	typedef void arg1_type;
	typedef void arg2_type;
	typedef void arg3_type;
	typedef void arg4_type;
	typedef void arg5_type;
	typedef void arg6_type;
	typedef void arg7_type;
	typedef void arg8_type;
	typedef void arg9_type;
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
#endif // FUNCTION_TRAITS_H_20140113130102209
// end of file
