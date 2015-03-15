/**
  @file     binder.h
  @brief    creates a functor binding arguments.
  @author   HRYKY
  @version  $Id: binder.h 380 2014-08-24 07:41:16Z hryky.private@gmail.com $
 */
#ifndef BINDER_H_20140617102608101
#define BINDER_H_20140617102608101
#include "hryky/type_traits/result_of.h"
#include "hryky/function_traits.h"
#include "hryky/tuple/tuple_n.h"
#include "hryky/functional/placeholder.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// binds a callable object with return type.
	template <
		typename OpT,
		typename ResultT = typename ResultOf<OpT>::type
	>
	class Binder0;

	/// binds a callable object with an argument.
	template <
		typename OpT,
		typename To1T,
		typename ResultT = typename ResultOf<OpT>::type
	>
	class Binder1;

	/// binds a callable object with two arguments.
	template <
		typename OpT,
		typename To1T,
		typename To2T,
		typename ResultT = typename ResultOf<OpT>::type
	>
	class Binder2;

	/// binds a callable object with three arguments.
	template <
		typename OpT,
		typename To1T,
		typename To2T,
		typename To3T,
		typename ResultT = typename ResultOf<OpT>::type
	>
	class Binder3;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  binds a callable object with return type.
 */
template <typename OpT, typename ResultT>
class hryky::Binder0 :
	public FunctionTraits0<ResultT>
{
public :
	
	Binder0(OpT const & op)
		: op_(op)
	{
	}

	result_type operator()()
	{
		return static_cast<result_type>(this->op_());
	}

private :
	OpT op_;
};
/**
  binds a callable object with an argument.
 */
template <typename OpT, typename To1T, typename ResultT>
class hryky::Binder1 :
	public FunctionTraits1<ResultT, To1T>
{
public :
	
	Binder1(OpT const & op, To1T to1)
		: op_(op)
		  , tos_(to1)
	{
	}

	result_type operator()()
	{
		return static_cast<result_type>(
			this->op_(this->tos_.at<0>()));
	}

	template <typename From1T>
	result_type operator()(From1T from1)
	{
		Tuple1<From1T> froms(from1);
		
		return static_cast<result_type>(
			this->op_(bind_arg(froms, this->tos_.at<0>())));
	}
	
private :
	OpT op_;
	Tuple1<To1T> tos_;
};
/**
  binds a callable object with two arguments.
 */
template <
	typename OpT, typename To1T, typename To2T, typename ResultT>
class hryky::Binder2 :
	public FunctionTraits2<ResultT, To1T, To2T>
{
public :
	
	Binder2(OpT const & op, To1T to1, To2T to2)
		: op_(op)
		  , tos_(to1, to2)
	{
	}

	result_type operator()()
	{
		return static_cast<result_type>(
			this->op_(this->tos_.at<0>(), this->tos_.at<1>()));
	}

	template <typename From1T>
	result_type operator()(From1T from1)
	{
		Tuple1<From1T> froms(from1);
		
		return static_cast<result_type>(
			this->op_(
				bind_arg(froms, this->tos_.at<0>()),
				bind_arg(froms, this->tos_.at<1>())));
	}
	
	template <typename From1T, typename From2T>
	result_type operator()(From1T from1, From2T from2)
	{
		Tuple2<From1T, From2T> froms(from1, from2);
		
		return static_cast<result_type>(
			this->op_(
				bind_arg(froms, this->tos_.at<0>()),
				bind_arg(froms, this->tos_.at<1>())));
	}
	
private :
	OpT op_;
	Tuple2<To1T, To2T> tos_;
};
/**
  binds a callable object with three arguments.
 */
template <
	typename OpT, typename To1T, typename To2T, typename To3T,
	typename ResultT
>
class hryky::Binder3 :
	public FunctionTraits3<ResultT, To1T, To2T, To3T>
{
public :
	
	Binder3(OpT const & op, To1T to1, To2T to2, To3T to3)
		: op_(op)
		  , tos_(to1, to2, to3)
	{
	}

	result_type operator()()
	{
		return static_cast<result_type>(
			this->op_(
				this->tos_.at<0>(),
				this->tos_.at<1>(),
				this->tos_.at<2>()));
	}

	template <typename From1T>
	result_type operator()(From1T from1)
	{
		Tuple1<From1T> froms(from1);
		
		return static_cast<result_type>(
			this->op_(
				bind_arg(froms, this->tos_.at<0>()),
				bind_arg(froms, this->tos_.at<1>()),
				bind_arg(froms, this->tos_.at<2>())));
	}
	
	template <typename From1T, typename From2T>
	result_type operator()(From1T from1, From2T from2)
	{
		Tuple2<From1T, From2T> froms(from1, from2);
		
		return static_cast<result_type>(
			this->op_(
				bind_arg(froms, this->tos_.at<0>()),
				bind_arg(froms, this->tos_.at<1>()),
				bind_arg(froms, this->tos_.at<2>())));
	}
	
	template <typename From1T, typename From2T, typename From3T>
	result_type operator()(
		From1T from1, From2T from2, From3T from3)
	{
		Tuple3<From1T, From2T, From3T> froms(from1, from2, from3);
		
		return static_cast<result_type>(
			this->op_(
				bind_arg(froms, this->tos_.at<0>()),
				bind_arg(froms, this->tos_.at<1>()),
				bind_arg(froms, this->tos_.at<2>())));
	}
	
private :
	OpT op_;
	Tuple3<To1T, To2T, To3T> tos_;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
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
	/// creates a functor bound with two arguments.
	template <typename OpT, typename To1T, typename To2T>
	Binder2<OpT, To1T, To2T> bind(
		OpT const & op, To1T to1, To2T to2);

	/// creates a functor bound with two arguments.
	template <
		typename OpT, typename To1T, typename To2T, typename To3T
	>
	Binder3<OpT, To1T, To2T, To3T> bind(
		OpT const & op, To1T to1, To2T to2, To3T to3);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates a functor bound with two arguments.
 */
template <typename OpT, typename To1T, typename To2T>
hryky::Binder2<OpT, To1T, To2T>
hryky::bind(OpT const & op, To1T to1, To2T to2)
{
	return Binder2<OpT, To1T, To2T>(op, to1, to2);
}
/**
  @brief creates a functor bound with three arguments.
 */
template <typename OpT, typename To1T, typename To2T, typename To3T>
hryky::Binder3<OpT, To1T, To2T, To3T>
hryky::bind(OpT const & op, To1T to1, To2T to2, To3T to3)
{
	return Binder3<OpT, To1T, To2T, To3T>(op, to1, to2, to3);
}
#endif // BINDER_H_20140617102608101
// end of file
