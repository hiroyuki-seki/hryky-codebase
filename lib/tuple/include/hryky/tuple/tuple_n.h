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
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// tuple which has one value.
	template < typename Arg1T >
	class Tuple1;

	/// tuple which has two values.
	template < typename Arg1T, typename Arg2T >
	class Tuple2;

	/// tuple which has three values.
	template < typename Arg1T, typename Arg2T, typename Arg3T >
	class Tuple3;

	/// tuple which has four values.
	template <
		typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T >
	class Tuple4;

	/// tuple which has five values.
	template <
		typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T,
		typename Arg5T>
	class Tuple5;

	/// tuple which has six values.
	template <
		typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T,
		typename Arg5T, typename Arg6T>
	class Tuple6;

	/// tuple which has seven values.
	template <
		typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T,
		typename Arg5T, typename Arg6T, typename Arg7T>
	class Tuple7;

	/// tuple which has eight values.
	template <
		typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T,
		typename Arg5T, typename Arg6T, typename Arg7T, typename Arg8T>
	class Tuple8;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief tuple which has one value.
 */
template < typename Arg1T >
class Tuple1 :
	public hryky::Tuple< Arg1T >
{
public :

	typedef hryky::Tuple1<Arg1T> this_type;
	typedef hryky::Tuple<Arg1T>  base_type;

	/// constructor with parameter
	Tuple1(Arg1T && arg1)
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
template < typename Arg1T, typename Arg2T >
class Tuple2 :
	public hryky::Tuple< Arg1T, Tuple<Arg2T> >
{
private :
	typedef hryky::Tuple<Arg1T, Tuple<Arg2T> > rest1;
	typedef typename rest1::rest_type rest2;
	
public :
	typedef hryky::Tuple2<Arg1T, Arg2T> this_type;
	typedef rest1 base_type;

	/// constructor with parameters
	Tuple2(
		Arg1T && arg1,
		Arg2T && arg2)
		: base_type(
			::std::forward<Arg1T>(arg1), rest2(
				::std::forward<Arg2T>(arg2)))
	{}

	Tuple2(
		typename AddConstReference<Arg1T>::type arg1,
		typename AddConstReference<Arg2T>::type arg2)
		: base_type(arg1, rest2(arg2))
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
template < typename Arg1T, typename Arg2T, typename Arg3T >
class Tuple3 :
	public hryky::Tuple<Arg1T, Tuple<Arg2T, Tuple<Arg3T> > >
{
private :
	typedef Tuple<Arg1T, Tuple<Arg2T, Tuple<Arg3T> > >
		rest1;
	typedef typename rest1::rest_type rest2;
	typedef typename rest2::rest_type rest3;

public :

	typedef Tuple3<Arg1T, Arg2T, Arg3T>
		this_type;
	typedef rest1 base_type;

	/// constructor with parameters
	Tuple3(
		Arg1T && arg1,
		Arg2T && arg2,
		Arg3T && arg3)
		: base_type(
			::std::forward<Arg1T>(arg1), rest2(
				::std::forward<Arg2T>(arg2), rest3(
					::std::forward<Arg3T>(arg3))))
	{}

	Tuple3(
		typename AddConstReference<Arg1T>::type arg1,
		typename AddConstReference<Arg2T>::type arg2,
		typename AddConstReference<Arg3T>::type arg3)
		: base_type(
			arg1, rest2(
				arg2, rest3(
					arg3)))
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
template < typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T >
class Tuple4 :
	public hryky::Tuple<
		Arg1T, Tuple<Arg2T, Tuple<Arg3T, Tuple<Arg4T> > >
	>
{
private :
	typedef Tuple<
		Arg1T, Tuple<Arg2T, Tuple<Arg3T, Tuple<Arg4T > > > >
			rest1;
	typedef typename rest1::rest_type rest2;
	typedef typename rest2::rest_type rest3;
	typedef typename rest3::rest_type rest4;
public :

	typedef Tuple4<Arg1T, Arg2T, Arg3T, Arg4T>
		this_type;
	typedef rest1 base_type;

	/// constructor with parameters
	Tuple4(
		Arg1T && arg1,
		Arg2T && arg2,
		Arg3T && arg3,
		Arg4T && arg4)
		: base_type(
			::std::forward<Arg1T>(arg1), rest2(
				::std::forward<Arg2T>(arg2), rest3(
					::std::forward<Arg3T>(arg3), rest4(
						::std::forward<Arg4T>(arg4)))))
	{}

	Tuple4(
		typename AddConstReference<Arg1T>::type arg1,
		typename AddConstReference<Arg2T>::type arg2,
		typename AddConstReference<Arg3T>::type arg3,
		typename AddConstReference<Arg4T>::type arg4)
		: base_type(
			arg1, rest2(
				arg2, rest3(
					arg3, rest4(
						arg4))))
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
template <
	typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T,
	typename Arg5T
>
class Tuple5 :
	public hryky::Tuple<
		Arg1T, Tuple<Arg2T, Tuple<Arg3T, Tuple<Arg4T, Tuple<
			Arg5T> > >
		>
	>
{
private :
	typedef Tuple<
		Arg1T, Tuple<Arg2T, Tuple<Arg3T, Tuple<Arg4T, Tuple<
			Arg5T> > > > > rest1;
	typedef typename rest1::rest_type rest2;
	typedef typename rest2::rest_type rest3;
	typedef typename rest3::rest_type rest4;
	typedef typename rest4::rest_type rest5;
public :

	typedef Tuple5<Arg1T, Arg2T, Arg3T, Arg4T, Arg5T>
		this_type;
	typedef rest1 base_type;

	/// constructor with parameters
	Tuple5(
		Arg1T && arg1,
		Arg2T && arg2,
		Arg3T && arg3,
		Arg4T && arg4,
		Arg5T && arg5)
		: base_type(
			::std::forward<Arg1T>(arg1), rest2(
				::std::forward<Arg2T>(arg2), rest3(
					::std::forward<Arg3T>(arg3), rest4(
						::std::forward<Arg4T>(arg4), rest5(
							::std::forward<Arg5T>(arg5))))))
	{}

	Tuple5(
		typename AddConstReference<Arg1T>::type arg1,
		typename AddConstReference<Arg2T>::type arg2,
		typename AddConstReference<Arg3T>::type arg3,
		typename AddConstReference<Arg4T>::type arg4,
		typename AddConstReference<Arg5T>::type arg5)
		: base_type(
			arg1, rest2(
				arg2, rest3(
					arg3, rest4(
						arg4, rest5(
							arg5)))))
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
template <
	typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T,
	typename Arg5T, typename Arg6T
>
class Tuple6 :
	public hryky::Tuple<
		Arg1T, Tuple<Arg2T, Tuple<Arg3T, Tuple<Arg4T, Tuple<
			Arg5T, Tuple<Arg6T> > > >
		>
	>
{
private :
	typedef Tuple<
		Arg1T, Tuple<Arg2T, Tuple<Arg3T, Tuple<Arg4T, Tuple<
			Arg5T, Tuple<Arg6T> > > > > > rest1;
	typedef typename rest1::rest_type rest2;
	typedef typename rest2::rest_type rest3;
	typedef typename rest3::rest_type rest4;
	typedef typename rest4::rest_type rest5;
	typedef typename rest5::rest_type rest6;
	
public :

	typedef Tuple6<Arg1T, Arg2T, Arg3T, Arg4T, Arg5T, Arg6T>
		this_type;
	typedef rest1 base_type;

	/// constructor with parameters
	Tuple6(
		Arg1T && arg1,
		Arg2T && arg2,
		Arg3T && arg3,
		Arg4T && arg4,
		Arg5T && arg5,
		Arg6T && arg6)
		: base_type(
			::std::forward<Arg1T>(arg1), rest2(
				::std::forward<Arg2T>(arg2), rest3(
					::std::forward<Arg3T>(arg3), rest4(
						::std::forward<Arg4T>(arg4), rest5(
							::std::forward<Arg5T>(arg5), rest6(
								::std::forward<Arg6T>(arg6)))))))
	{}

	Tuple6(
		typename AddConstReference<Arg1T>::type arg1,
		typename AddConstReference<Arg2T>::type arg2,
		typename AddConstReference<Arg3T>::type arg3,
		typename AddConstReference<Arg4T>::type arg4,
		typename AddConstReference<Arg5T>::type arg5,
		typename AddConstReference<Arg6T>::type arg6)
		: base_type(
			arg1, rest2(
				arg2, rest3(
					arg3, rest4(
						arg4, rest5(
							arg5, rest6(
								arg6))))))
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
template <
	typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T,
	typename Arg5T, typename Arg6T, typename Arg7T
>
class Tuple7 :
	public hryky::Tuple<
		Arg1T, Tuple<Arg2T, Tuple<Arg3T, Tuple<Arg4T, Tuple<
			Arg5T, Tuple<Arg6T, Tuple<Arg7T> > > > > > >
{
private :
	typedef Tuple<
		Arg1T, Tuple<Arg2T, Tuple<Arg3T, Tuple<Arg4T, Tuple<
			Arg5T, Tuple<Arg6T, Tuple<Arg7T> > > > > > > rest1;
	typedef typename rest1::rest_type rest2;
	typedef typename rest2::rest_type rest3;
	typedef typename rest3::rest_type rest4;
	typedef typename rest4::rest_type rest5;
	typedef typename rest5::rest_type rest6;
	typedef typename rest6::rest_type rest7;
	
public :

	typedef Tuple7<Arg1T, Arg2T, Arg3T, Arg4T, Arg5T, Arg6T, Arg7T>
		this_type;
	typedef rest1 base_type;

	/// constructor with parameters
	Tuple7(
		Arg1T && arg1,
		Arg2T && arg2,
		Arg3T && arg3,
		Arg4T && arg4,
		Arg5T && arg5,
		Arg6T && arg6,
		Arg7T && arg7)
		: base_type(
			::std::forward<Arg1T>(arg1), rest2(
				::std::forward<Arg2T>(arg2), rest3(
					::std::forward<Arg3T>(arg3), rest4(
						::std::forward<Arg4T>(arg4), rest5(
							::std::forward<Arg5T>(arg5), rest6(
								::std::forward<Arg6T>(arg6), rest7(
									::std::forward<Arg7T>(arg7))))))))
	{}

	Tuple7(
		typename AddConstReference<Arg1T>::type arg1,
		typename AddConstReference<Arg2T>::type arg2,
		typename AddConstReference<Arg3T>::type arg3,
		typename AddConstReference<Arg4T>::type arg4,
		typename AddConstReference<Arg5T>::type arg5,
		typename AddConstReference<Arg6T>::type arg6,
		typename AddConstReference<Arg7T>::type arg7)
		: base_type(
			arg1, rest2(
				arg2, rest3(
					arg3, rest4(
						arg4, rest5(
							arg5, rest6(
								arg6, rest7(
									arg7)))))))
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
template <
	typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T,
	typename Arg5T, typename Arg6T, typename Arg7T, typename Arg8T
>
class Tuple8 :
	public hryky::Tuple<
		Arg1T, Tuple<Arg2T, Tuple<Arg3T, Tuple<Arg4T, Tuple<
			Arg5T, Tuple<Arg6T, Tuple<Arg7T, Tuple<
				Arg8T> > > > > > > >
{
private :
	typedef Tuple<
		Arg1T, Tuple<Arg2T, Tuple<Arg3T, Tuple<Arg4T, Tuple<
			Arg5T, Tuple<Arg6T, Tuple<Arg7T, Tuple<
				Arg8T> > > > > > > >
					rest1;
	typedef typename rest1::rest_type rest2;
	typedef typename rest2::rest_type rest3;
	typedef typename rest3::rest_type rest4;
	typedef typename rest4::rest_type rest5;
	typedef typename rest5::rest_type rest6;
	typedef typename rest6::rest_type rest7;
	typedef typename rest7::rest_type rest8;
	
public :
	typedef Tuple8<
		Arg1T, Arg2T, Arg3T, Arg4T, Arg5T, Arg6T, Arg7T, Arg8T>
			this_type;
	typedef rest1 base_type;

	/// constructor with parameters
	Tuple8(
		Arg1T && arg1,
		Arg2T && arg2,
		Arg3T && arg3,
		Arg4T && arg4,
		Arg5T && arg5,
		Arg6T && arg6,
		Arg7T && arg7,
		Arg8T && arg8)
		: base_type(
			::std::forward<Arg1T>(arg1), rest2(
				::std::forward<Arg2T>(arg2), rest3(
					::std::forward<Arg3T>(arg3), rest4(
						::std::forward<Arg4T>(arg4), rest5(
							::std::forward<Arg5T>(arg5), rest6(
								::std::forward<Arg6T>(arg6), rest7(
									::std::forward<Arg7T>(arg7), rest8(
										::std::forward<Arg8T>(arg8)))))))))
	{}

	Tuple8(
		typename AddConstReference<Arg1T>::type arg1,
		typename AddConstReference<Arg2T>::type arg2,
		typename AddConstReference<Arg3T>::type arg3,
		typename AddConstReference<Arg4T>::type arg4,
		typename AddConstReference<Arg5T>::type arg5,
		typename AddConstReference<Arg6T>::type arg6,
		typename AddConstReference<Arg7T>::type arg7,
		typename AddConstReference<Arg8T>::type arg8)
		: base_type(
			arg1, rest2(
				arg2, rest3(
					arg3, rest4(
						arg4, rest5(
							arg5, rest6(
								arg6, rest7(
									arg7, rest8(
										arg8))))))))
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
	template <typename Arg1T>
	Tuple1<Arg1T> make_tuple(
		Arg1T && arg1);

	/// creates a tuple which has two values.
	template <typename Arg1T, typename Arg2T>
	Tuple2<Arg1T, Arg2T> make_tuple(
		Arg1T && arg1,
		Arg2T && arg2);

	/// creates a tuple which has three values.
	template <typename Arg1T, typename Arg2T, typename Arg3T>
	Tuple3<Arg1T, Arg2T, Arg3T> make_tuple(
		Arg1T && arg1,
		Arg2T && arg2,
		Arg3T && arg3);

	/// creates a tuple which has four values.
	template <typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T>
	Tuple4<Arg1T, Arg2T, Arg3T, Arg4T> make_tuple(
		Arg1T && arg1,
		Arg2T && arg2,
		Arg3T && arg3,
		Arg4T && arg4);

	/// creates a tuple which has five values.
	template <
		typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T,
		typename Arg5T>
	Tuple5<Arg1T, Arg2T, Arg3T, Arg4T, Arg5T> make_tuple(
		Arg1T && arg1,
		Arg2T && arg2,
		Arg3T && arg3,
		Arg4T && arg4,
		Arg5T && arg5);

	/// creates a tuple which has six values.
	template <
		typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T,
		typename Arg5T, typename Arg6T>
	Tuple6<Arg1T, Arg2T, Arg3T, Arg4T, Arg5T, Arg6T> make_tuple(
		Arg1T && arg1,
		Arg2T && arg2,
		Arg3T && arg3,
		Arg4T && arg4,
		Arg5T && arg5,
		Arg6T && arg6);

	/// creates a tuple which has seven values.
	template <
		typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T,
		typename Arg5T, typename Arg6T, typename Arg7T>
	Tuple7<Arg1T, Arg2T, Arg3T, Arg4T, Arg5T, Arg6T, Arg7T>
		make_tuple(
			Arg1T && arg1,
			Arg2T && arg2,
			Arg3T && arg3,
			Arg4T && arg4,
			Arg5T && arg5,
			Arg6T && arg6,
			Arg7T && arg7);

	/// creates a tuple which has eight values.
	template <
		typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T,
		typename Arg5T, typename Arg6T, typename Arg7T, typename Arg8T>
	Tuple8<Arg1T, Arg2T, Arg3T, Arg4T, Arg5T, Arg6T, Arg7T, Arg8T>
		make_tuple(
			Arg1T && arg1,
			Arg2T && arg2,
			Arg3T && arg3,
			Arg4T && arg4,
			Arg5T && arg5,
			Arg6T && arg6,
			Arg7T && arg7,
			Arg8T && arg8);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates a tuple which has one value.
 */
template <
	typename Arg1T
>
hryky::Tuple1<Arg1T> hryky::make_tuple(
	Arg1T && arg1)
{
	return Tuple1<Arg1T>(::std::forward<Arg1T>(arg1));
}
/**
  @brief creates a tuple which has two values.
 */
template <
	typename Arg1T, typename Arg2T
>
hryky::Tuple2<Arg1T, Arg2T> hryky::make_tuple(
	Arg1T && arg1,
	Arg2T && arg2)
{
	return Tuple2<Arg1T, Arg2T>(
		::std::forward<Arg1T>(arg1),
		::std::forward<Arg2T>(arg2));
}
/**
  @brief creates a tuple which has three values.
 */
template <
	typename Arg1T, typename Arg2T, typename Arg3T
>
hryky::Tuple3<Arg1T, Arg2T, Arg3T> hryky::make_tuple(
	Arg1T && arg1,
	Arg2T && arg2,
	Arg3T && arg3)
{
	return Tuple3<Arg1T, Arg2T, Arg3T>(
		::std::forward<Arg1T>(arg1),
		::std::forward<Arg2T>(arg2),
		::std::forward<Arg3T>(arg3));
}
/**
  @brief creates a tuple which has five values.
 */
template <
	typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T
>
hryky::Tuple4<Arg1T, Arg2T, Arg3T, Arg4T> hryky::make_tuple(
	Arg1T && arg1,
	Arg2T && arg2,
	Arg3T && arg3,
	Arg4T && arg4)
{
	return Tuple4<Arg1T, Arg2T, Arg3T, Arg4T>(
		::std::forward<Arg1T>(arg1),
		::std::forward<Arg2T>(arg2),
		::std::forward<Arg3T>(arg3),
		::std::forward<Arg4T>(arg4));
}
/**
  @brief creates a tuple which has five values.
 */
template <
	typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T,
	typename Arg5T
>
hryky::Tuple5<Arg1T, Arg2T, Arg3T, Arg4T, Arg5T> hryky::make_tuple(
	Arg1T && arg1,
	Arg2T && arg2,
	Arg3T && arg3,
	Arg4T && arg4,
	Arg5T && arg5)
{
	return Tuple5<Arg1T, Arg2T, Arg3T, Arg4T, Arg5T>(
		::std::forward<Arg1T>(arg1),
		::std::forward<Arg2T>(arg2),
		::std::forward<Arg3T>(arg3),
		::std::forward<Arg4T>(arg4),
		::std::forward<Arg5T>(arg5));
}
/**
  @brief creates a tuple which has six values.
 */
template <
	typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T,
	typename Arg5T, typename Arg6T
>
hryky::Tuple6<Arg1T, Arg2T, Arg3T, Arg4T, Arg5T, Arg6T>
hryky::make_tuple(
	Arg1T && arg1,
	Arg2T && arg2,
	Arg3T && arg3,
	Arg4T && arg4,
	Arg5T && arg5,
	Arg6T && arg6)
{
	return Tuple6<Arg1T, Arg2T, Arg3T, Arg4T, Arg5T, Arg6T>(
		::std::forward<Arg1T>(arg1),
		::std::forward<Arg2T>(arg2),
		::std::forward<Arg3T>(arg3),
		::std::forward<Arg4T>(arg4),
		::std::forward<Arg5T>(arg5),
		::std::forward<Arg6T>(arg6));
}
/**
  @brief creates a tuple which has seven values.
 */
template <
	typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T,
	typename Arg5T, typename Arg6T, typename Arg7T
>
hryky::Tuple7<Arg1T, Arg2T, Arg3T, Arg4T, Arg5T, Arg6T, Arg7T>
hryky::make_tuple(
	Arg1T && arg1,
	Arg2T && arg2,
	Arg3T && arg3,
	Arg4T && arg4,
	Arg5T && arg5,
	Arg6T && arg6,
	Arg7T && arg7)
{
	return Tuple7<Arg1T, Arg2T, Arg3T, Arg4T, Arg5T, Arg6T, Arg7T>(
		::std::forward<Arg1T>(arg1),
		::std::forward<Arg2T>(arg2),
		::std::forward<Arg3T>(arg3),
		::std::forward<Arg4T>(arg4),
		::std::forward<Arg5T>(arg5),
		::std::forward<Arg6T>(arg6),
		::std::forward<Arg7T>(arg7));
}
/**
  @brief creates a tuple which has eight values.
 */
template <
	typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T,
	typename Arg5T, typename Arg6T, typename Arg7T, typename Arg8T
>
hryky::Tuple8<Arg1T, Arg2T, Arg3T, Arg4T, Arg5T, Arg6T, Arg7T, Arg8T>
hryky::make_tuple(
	Arg1T && arg1,
	Arg2T && arg2,
	Arg3T && arg3,
	Arg4T && arg4,
	Arg5T && arg5,
	Arg6T && arg6,
	Arg7T && arg7,
	Arg8T && arg8)
{
	return Tuple8<
		Arg1T, Arg2T, Arg3T, Arg4T, Arg5T, Arg6T, Arg7T, Arg8T>(
			::std::forward<Arg1T>(arg1),
			::std::forward<Arg2T>(arg2),
			::std::forward<Arg3T>(arg3),
			::std::forward<Arg4T>(arg4),
			::std::forward<Arg5T>(arg5),
			::std::forward<Arg6T>(arg6),
			::std::forward<Arg7T>(arg7),
			::std::forward<Arg8T>(arg8));
}
#endif // TUPLE_N_H_20131015230751630
// end of file
