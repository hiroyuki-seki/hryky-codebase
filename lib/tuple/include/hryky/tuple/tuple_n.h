/**
  @file     tuple_n.h
  @brief    facilitates an instantiation of Tuple<>.
  @author   HRYKY
  @version  $Id: tuple_n.h 376 2014-07-29 10:46:52Z hryky.private@gmail.com $
 */
#ifndef TUPLE_N_H_20131015230751630
#define TUPLE_N_H_20131015230751630
#include "hryky/tuple/tuple_primal.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_tuple_param1 typename Arg1T
#define hryky_tuple_param2 hryky_tuple_param1, typename Arg2T
#define hryky_tuple_param3 hryky_tuple_param2, typename Arg3T
#define hryky_tuple_param4 hryky_tuple_param3, typename Arg4T
#define hryky_tuple_param5 hryky_tuple_param4, typename Arg5T
#define hryky_tuple_param6 hryky_tuple_param5, typename Arg6T
#define hryky_tuple_param7 hryky_tuple_param6, typename Arg7T
#define hryky_tuple_param8 hryky_tuple_param7, typename Arg8T

#define hryky_tuple_rvalue1 Arg1T && arg1
#define hryky_tuple_rvalue2 hryky_tuple_rvalue1, Arg2T && arg2
#define hryky_tuple_rvalue3 hryky_tuple_rvalue2, Arg3T && arg3
#define hryky_tuple_rvalue4 hryky_tuple_rvalue3, Arg4T && arg4
#define hryky_tuple_rvalue5 hryky_tuple_rvalue4, Arg5T && arg5
#define hryky_tuple_rvalue6 hryky_tuple_rvalue5, Arg6T && arg6
#define hryky_tuple_rvalue7 hryky_tuple_rvalue6, Arg7T && arg7
#define hryky_tuple_rvalue8 hryky_tuple_rvalue7, Arg8T && arg8

#define hryky_tuple_arg1 Arg1T
#define hryky_tuple_arg2 hryky_tuple_arg1, Arg2T
#define hryky_tuple_arg3 hryky_tuple_arg2, Arg3T
#define hryky_tuple_arg4 hryky_tuple_arg3, Arg4T
#define hryky_tuple_arg5 hryky_tuple_arg4, Arg5T
#define hryky_tuple_arg6 hryky_tuple_arg5, Arg6T
#define hryky_tuple_arg7 hryky_tuple_arg6, Arg7T
#define hryky_tuple_arg8 hryky_tuple_arg7, Arg8T

#define hryky_tuple_const_reference1 \
	typename AddConstReference<Arg1T>::type arg1
#define hryky_tuple_const_reference2 \
	hryky_tuple_const_reference1, typename AddConstReference<Arg2T>::type arg2
#define hryky_tuple_const_reference3 \
	hryky_tuple_const_reference2, typename AddConstReference<Arg3T>::type arg3
#define hryky_tuple_const_reference4 \
	hryky_tuple_const_reference3, typename AddConstReference<Arg4T>::type arg4
#define hryky_tuple_const_reference5 \
	hryky_tuple_const_reference4, typename AddConstReference<Arg5T>::type arg5
#define hryky_tuple_const_reference6 \
	hryky_tuple_const_reference5, typename AddConstReference<Arg6T>::type arg6
#define hryky_tuple_const_reference7 \
	hryky_tuple_const_reference6, typename AddConstReference<Arg7T>::type arg7
#define hryky_tuple_const_reference8 \
	hryky_tuple_const_reference7, typename AddConstReference<Arg8T>::type arg8

#define hryky_tuple_base1 hryky::Tuple<Arg1T >
#define hryky_tuple_base2 hryky::Tuple<Arg2T, hryky_tuple_base1 >
#define hryky_tuple_base3 hryky::Tuple<Arg3T, hryky_tuple_base2 >
#define hryky_tuple_base4 hryky::Tuple<Arg4T, hryky_tuple_base3 >
#define hryky_tuple_base5 hryky::Tuple<Arg5T, hryky_tuple_base4 >
#define hryky_tuple_base6 hryky::Tuple<Arg6T, hryky_tuple_base5 >
#define hryky_tuple_base7 hryky::Tuple<Arg7T, hryky_tuple_base6 >
#define hryky_tuple_base8 hryky::Tuple<Arg8T, hryky_tuple_base7 >

#define hryky_tuple_initial1() hryky_tuple_base1(arg1)
#define hryky_tuple_initial2() hryky_tuple_base2(arg2, hryky_tuple_initial1())
#define hryky_tuple_initial3() hryky_tuple_base3(arg3, hryky_tuple_initial2())
#define hryky_tuple_initial4() hryky_tuple_base4(arg4, hryky_tuple_initial3())
#define hryky_tuple_initial5() hryky_tuple_base5(arg5, hryky_tuple_initial4())
#define hryky_tuple_initial6() hryky_tuple_base6(arg6, hryky_tuple_initial5())
#define hryky_tuple_initial7() hryky_tuple_base7(arg7, hryky_tuple_initial6())
#define hryky_tuple_initial8() hryky_tuple_base8(arg8, hryky_tuple_initial7())

#define hryky_tuple_rvalue_initial1() \
	hryky_tuple_base1(::std::forward<Arg1T>(arg1))
#define hryky_tuple_rvalue_initial2() \
	hryky_tuple_base2(::std::forward<Arg2T>(arg2), hryky_tuple_rvalue_initial1())
#define hryky_tuple_rvalue_initial3() \
	hryky_tuple_base3(::std::forward<Arg3T>(arg3), hryky_tuple_rvalue_initial2())
#define hryky_tuple_rvalue_initial4() \
	hryky_tuple_base4(::std::forward<Arg4T>(arg4), hryky_tuple_rvalue_initial3())
#define hryky_tuple_rvalue_initial5() \
	hryky_tuple_base5(::std::forward<Arg5T>(arg5), hryky_tuple_rvalue_initial4())
#define hryky_tuple_rvalue_initial6() \
	hryky_tuple_base6(::std::forward<Arg6T>(arg6), hryky_tuple_rvalue_initial5())
#define hryky_tuple_rvalue_initial7() \
	hryky_tuple_base7(::std::forward<Arg7T>(arg7), hryky_tuple_rvalue_initial6())
#define hryky_tuple_rvalue_initial8() \
	hryky_tuple_base8(::std::forward<Arg8T>(arg8), hryky_tuple_rvalue_initial7())

#define hryky_tuple_forward1 ::std::forward<Arg1T>(arg1)
#define hryky_tuple_forward2 hryky_tuple_forward1, ::std::forward<Arg2T>(arg2)
#define hryky_tuple_forward3 hryky_tuple_forward2, ::std::forward<Arg3T>(arg3)
#define hryky_tuple_forward4 hryky_tuple_forward3, ::std::forward<Arg4T>(arg4)
#define hryky_tuple_forward5 hryky_tuple_forward4, ::std::forward<Arg5T>(arg5)
#define hryky_tuple_forward6 hryky_tuple_forward5, ::std::forward<Arg6T>(arg6)
#define hryky_tuple_forward7 hryky_tuple_forward6, ::std::forward<Arg7T>(arg7)
#define hryky_tuple_forward8 hryky_tuple_forward7, ::std::forward<Arg8T>(arg8)

//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// tuple which has one value.
	template < hryky_tuple_param1 >
	class Tuple1;

	/// tuple which has two values.
	template < hryky_tuple_param2 >
	class Tuple2;

	/// tuple which has three values.
	template < hryky_tuple_param3 >
	class Tuple3;

	/// tuple which has four values.
	template <hryky_tuple_param4 >
	class Tuple4;

	/// tuple which has five values.
	template <hryky_tuple_param5>
	class Tuple5;

	/// tuple which has six values.
	template <hryky_tuple_param6>
	class Tuple6;

	/// tuple which has seven values.
	template <hryky_tuple_param7>
	class Tuple7;

	/// tuple which has eight values.
	template <hryky_tuple_param8>
	class Tuple8;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief tuple which has one value.
 */
template < hryky_tuple_param1 >
class hryky::Tuple1 : public hryky::Tuple< Arg1T >
{
public :

	typedef hryky::Tuple1<hryky_tuple_arg1> this_type;
	typedef hryky_tuple_base1 base_type;

	/// constructor with parameter
	Tuple1(hryky_tuple_rvalue1)
		: base_type(arg1)
	{}

	template <typename RhsT>
	Tuple1(RhsT const & rhs)
		: base_type(rhs)
	{
	}

	template <typename RhsT>
	Tuple1(RhsT && rhs)
		: base_type(::std::move(rhs))
	{
	}

protected :

private :

};
/**
  @brief tuple which has two values.
 */
template < hryky_tuple_param2 >
class hryky::Tuple2 : public hryky_tuple_base2
{
public :
	typedef hryky::Tuple2<hryky_tuple_arg2> this_type;
	typedef hryky_tuple_base2 base_type;

	/// constructor with parameters
	Tuple2(hryky_tuple_rvalue2)
		: hryky_tuple_rvalue_initial2()
	{}

	Tuple2(hryky_tuple_const_reference2)
		: hryky_tuple_initial2()
	{}

	template <typename RhsT>
	Tuple2(RhsT const & rhs)
		: base_type(rhs)
	{
	}

	template <typename RhsT>
	Tuple2(RhsT && rhs)
		: base_type(::std::move(rhs))
	{
	}

protected :

private :

};
/**
  @brief tuple which has three values.
 */
template < hryky_tuple_param3 >
class hryky::Tuple3 : public hryky_tuple_base3
{
public :

	typedef Tuple3<hryky_tuple_arg3> this_type;
	typedef hryky_tuple_base3 base_type;

	/// constructor with parameters
	Tuple3(hryky_tuple_rvalue3)
		: hryky_tuple_rvalue_initial3()
	{}

	Tuple3(hryky_tuple_const_reference3)
		: hryky_tuple_initial3()
	{}

	template <typename RhsT>
	Tuple3(RhsT const & rhs)
		: base_type(rhs)
	{
	}

	template <typename RhsT>
	Tuple3(RhsT && rhs)
		: base_type(::std::move(rhs))
	{
	}

protected :

private :

};
/**
  @brief tuple which has four values.
 */
template <hryky_tuple_param4 >
class hryky::Tuple4 : public hryky_tuple_base4
{
public :

	typedef Tuple4<hryky_tuple_arg4> this_type;
	typedef hryky_tuple_base4 base_type;

	/// constructor with parameters
	Tuple4(hryky_tuple_rvalue4)
		: hryky_tuple_rvalue_initial4()
	{}

	Tuple4(hryky_tuple_const_reference4)
		: hryky_tuple_initial4()
	{}

	template <typename RhsT>
	Tuple4(RhsT const & rhs)
		: base_type(rhs)
	{
	}

	template <typename RhsT>
	Tuple4(RhsT && rhs)
		: base_type(::std::move(rhs))
	{
	}

protected :

private :

};
/**
  @brief tuple which has five values.
 */
template <hryky_tuple_param5>
class hryky::Tuple5 : public hryky_tuple_base5
{
public :

	typedef Tuple5<hryky_tuple_arg5> this_type;
	typedef hryky_tuple_base5 base_type;

	/// constructor with parameters
	Tuple5(hryky_tuple_rvalue5)
		: hryky_tuple_rvalue_initial5()
	{}

	Tuple5(hryky_tuple_const_reference5)
		: hryky_tuple_initial5()
	{}

	template <typename RhsT>
	Tuple5(RhsT const & rhs)
		: base_type(rhs)
	{
	}

	template <typename RhsT>
	Tuple5(RhsT && rhs)
		: base_type(::std::move(rhs))
	{
	}

protected :

private :

};
/**
  @brief tuple which has six values.
 */
template <hryky_tuple_param6 >
class hryky::Tuple6 : public hryky_tuple_base6
{
public :

	typedef Tuple6<hryky_tuple_arg6> this_type;
	typedef hryky_tuple_base6 base_type;

	/// constructor with parameters
	Tuple6(hryky_tuple_rvalue6)
		: hryky_tuple_rvalue_initial6()
	{}

	Tuple6(hryky_tuple_const_reference6)
		: hryky_tuple_initial6()
	{}

	template <typename RhsT>
	Tuple6(RhsT const & rhs)
		: base_type(rhs)
	{
	}

	template <typename RhsT>
	Tuple6(RhsT && rhs)
		: base_type(::std::move(rhs))
	{
	}

protected :

private :

};
/**
  @brief tuple which has seven values.
 */
template <hryky_tuple_param7 >
class hryky::Tuple7 : public hryky_tuple_base7
{
public :

	typedef Tuple7<hryky_tuple_arg7> this_type;
	typedef hryky_tuple_base7 base_type;

	/// constructor with parameters
	Tuple7(hryky_tuple_rvalue7)
		: hryky_tuple_rvalue_initial7
	{}

	Tuple7(hryky_tuple_const_reference7)
		: hryky_tuple_initial7()
	{}

	template <typename RhsT>
	Tuple7(RhsT const & rhs)
		: base_type(rhs)
	{
	}

	template <typename RhsT>
	Tuple7(RhsT && rhs)
		: base_type(::std::move(rhs))
	{
	}

protected :

private :

};
/**
  @brief tuple which has eight values.
 */
template <hryky_tuple_param8 >
class hryky::Tuple8 : public hryky_tuple_base8
{
public :
	typedef Tuple8<hryky_tuple_arg8> this_type;
	typedef hryky_tuple_base8 base_type;

	/// constructor with parameters
	Tuple8(hryky_tuple_rvalue8)
		: hryky_tuple_rvalue_initial8()
	{}

	Tuple8(hryky_tuple_const_reference8)
		: hryky_tuple_initial8()
	{}

	template <typename RhsT>
	Tuple8(RhsT const & rhs)
		: base_type(rhs)
	{
	}

	template <typename RhsT>
	Tuple8(RhsT && rhs)
		: base_type(::std::move(rhs))
	{
	}

protected :

private :

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
	/// creates a tuple which has one value.
	template <hryky_tuple_param1 >
	Tuple1<hryky_tuple_arg1> make_tuple(hryky_tuple_rvalue1);

	/// creates a tuple which has two values.
	template <hryky_tuple_param2 >
	Tuple2<hryky_tuple_arg2> make_tuple(hryky_tuple_rvalue2);

	/// creates a tuple which has three values.
	template <hryky_tuple_param3 >
	Tuple3<hryky_tuple_arg3> make_tuple(hryky_tuple_rvalue3);

	/// creates a tuple which has four values.
	template <hryky_tuple_param4 >
	Tuple4<hryky_tuple_arg4> make_tuple(hryky_tuple_rvalue4);

	/// creates a tuple which has five values.
	template <hryky_tuple_param5 >
	Tuple5<hryky_tuple_arg5> make_tuple(hryky_tuple_rvalue5);

	/// creates a tuple which has six values.
	template <hryky_tuple_param6 >
	Tuple6<hryky_tuple_arg6> make_tuple(hryky_tuple_rvalue6);

	/// creates a tuple which has seven values.
	template <hryky_tuple_param7 >
	Tuple7<hryky_tuple_arg7>
		make_tuple(hryky_tuple_rvalue7);

	/// creates a tuple which has eight values.
	template <hryky_tuple_param8 >
	Tuple8<hryky_tuple_arg8>
		make_tuple(hryky_tuple_rvalue8);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates a tuple which has one value.
 */
template <hryky_tuple_param1 >
hryky::Tuple1<hryky_tuple_arg1>
hryky::make_tuple(hryky_tuple_rvalue1)
{
	return Tuple1<hryky_tuple_arg1>(hryky_tuple_forward1);
}
/**
  @brief creates a tuple which has two values.
 */
template <hryky_tuple_param2 >
hryky::Tuple2<hryky_tuple_arg2>
hryky::make_tuple(hryky_tuple_rvalue2)
{
	return Tuple2<hryky_tuple_arg2>(hryky_tuple_forward2);
}
/**
  @brief creates a tuple which has three values.
 */
template <hryky_tuple_param3 >
hryky::Tuple3<hryky_tuple_arg3>
hryky::make_tuple(hryky_tuple_rvalue3)
{
	return Tuple3<hryky_tuple_arg3>(hryky_tuple_forward3);
}
/**
  @brief creates a tuple which has five values.
 */
template <hryky_tuple_param4 >
hryky::Tuple4<hryky_tuple_arg4>
hryky::make_tuple(hryky_tuple_rvalue4)
{
	return Tuple4<hryky_tuple_arg4>(hryky_tuple_forward4);
}
/**
  @brief creates a tuple which has five values.
 */
template <hryky_tuple_param5 >
hryky::Tuple5<hryky_tuple_arg5>
hryky::make_tuple(hryky_tuple_rvalue5)
{
	return Tuple5<hryky_tuple_arg5>(hryky_tuple_forward5);
}
/**
  @brief creates a tuple which has six values.
 */
template <hryky_tuple_param6 >
hryky::Tuple6<hryky_tuple_arg6>
hryky::make_tuple(hryky_tuple_rvalue6)
{
	return Tuple6<hryky_tuple_arg6>(hryky_tuple_forward6);
}
/**
  @brief creates a tuple which has seven values.
 */
template <hryky_tuple_param7 >
hryky::Tuple7<hryky_tuple_arg7>
hryky::make_tuple(hryky_tuple_rvalue7)
{
	return Tuple7<hryky_tuple_arg7>(hryky_tuple_forward7);
}
/**
  @brief creates a tuple which has eight values.
 */
template <hryky_tuple_param8 >
hryky::Tuple8<hryky_tuple_arg8>
hryky::make_tuple(hryky_tuple_rvalue8)
{
	return Tuple8<hryky_tuple_arg8>(hryky_tuple_forward8);
}
//------------------------------------------------------------------------------
// revokes macros
//------------------------------------------------------------------------------
#undef hryky_tuple_param1
#undef hryky_tuple_param2
#undef hryky_tuple_param3
#undef hryky_tuple_param4
#undef hryky_tuple_param5
#undef hryky_tuple_param6
#undef hryky_tuple_param7
#undef hryky_tuple_param8

#undef hryky_tuple_rvalue1
#undef hryky_tuple_rvalue2
#undef hryky_tuple_rvalue3
#undef hryky_tuple_rvalue4
#undef hryky_tuple_rvalue5
#undef hryky_tuple_rvalue6
#undef hryky_tuple_rvalue7
#undef hryky_tuple_rvalue8

#undef hryky_tuple_arg1
#undef hryky_tuple_arg2
#undef hryky_tuple_arg3
#undef hryky_tuple_arg4
#undef hryky_tuple_arg5
#undef hryky_tuple_arg6
#undef hryky_tuple_arg7
#undef hryky_tuple_arg8

#undef hryky_tuple_const_reference1
#undef hryky_tuple_const_reference2
#undef hryky_tuple_const_reference3
#undef hryky_tuple_const_reference4
#undef hryky_tuple_const_reference5
#undef hryky_tuple_const_reference6
#undef hryky_tuple_const_reference7
#undef hryky_tuple_const_reference8

#undef hryky_tuple_base1
#undef hryky_tuple_base2
#undef hryky_tuple_base3
#undef hryky_tuple_base4
#undef hryky_tuple_base5
#undef hryky_tuple_base6
#undef hryky_tuple_base7
#undef hryky_tuple_base8

#undef hryky_tuple_initial1
#undef hryky_tuple_initial2
#undef hryky_tuple_initial3
#undef hryky_tuple_initial4
#undef hryky_tuple_initial5
#undef hryky_tuple_initial6
#undef hryky_tuple_initial7
#undef hryky_tuple_initial8

#undef hryky_tuple_rvalue_initial1
#undef hryky_tuple_rvalue_initial2
#undef hryky_tuple_rvalue_initial3
#undef hryky_tuple_rvalue_initial4
#undef hryky_tuple_rvalue_initial5
#undef hryky_tuple_rvalue_initial6
#undef hryky_tuple_rvalue_initial7
#undef hryky_tuple_rvalue_initial8

#undef hryky_tuple_forward1
#undef hryky_tuple_forward2
#undef hryky_tuple_forward3
#undef hryky_tuple_forward4
#undef hryky_tuple_forward5
#undef hryky_tuple_forward6
#undef hryky_tuple_forward7
#undef hryky_tuple_forward8

#endif // TUPLE_N_H_20131015230751630
// end of file
