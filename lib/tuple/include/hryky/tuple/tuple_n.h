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
#define hryky_template_param1 typename A1T
#define hryky_template_param2 hryky_template_param1, typename A2T
#define hryky_template_param3 hryky_template_param2, typename A3T
#define hryky_template_param4 hryky_template_param3, typename A4T
#define hryky_template_param5 hryky_template_param4, typename A5T
#define hryky_template_param6 hryky_template_param5, typename A6T
#define hryky_template_param7 hryky_template_param6, typename A7T
#define hryky_template_param8 hryky_template_param7, typename A8T

#define hryky_rval_arg1 A1T && v1
#define hryky_rval_arg2 hryky_rval_arg1, A2T && v2
#define hryky_rval_arg3 hryky_rval_arg2, A3T && v3
#define hryky_rval_arg4 hryky_rval_arg3, A4T && v4
#define hryky_rval_arg5 hryky_rval_arg4, A5T && v5
#define hryky_rval_arg6 hryky_rval_arg5, A6T && v6
#define hryky_rval_arg7 hryky_rval_arg6, A7T && v7
#define hryky_rval_arg8 hryky_rval_arg7, A8T && v8

#define hryky_rval_init1() v1_(::std::forward<A1T>(v1))
#define hryky_rval_init2() hryky_rval_init1(), v2_(::std::forward<A2T>(v2))
#define hryky_rval_init3() hryky_rval_init2(), v3_(::std::forward<A3T>(v3))
#define hryky_rval_init4() hryky_rval_init3(), v4_(::std::forward<A4T>(v4))

#define hryky_const_init1() v1_(v1)
#define hryky_const_init2() hryky_const_init1(), v2_(v2)
#define hryky_const_init3() hryky_const_init2(), v3_(v3)
#define hryky_const_init4() hryky_const_init3(), v4_(v4)

#define hryky_copy_init1() hryky_copy_member(v1)
#define hryky_copy_init2() hryky_copy_init1(), hryky_copy_member(v2)
#define hryky_copy_init3() hryky_copy_init2(), hryky_copy_member(v3)
#define hryky_copy_init4() hryky_copy_init3(), hryky_copy_member(v4)

#define hryky_move_init1() hryky_move_member(v1)
#define hryky_move_init2() hryky_move_init1(), hryky_move_member(v2)
#define hryky_move_init3() hryky_move_init2(), hryky_move_member(v3)
#define hryky_move_init4() hryky_move_init3(), hryky_move_member(v4)

#define hryky_write1 this->v1_
#define hryky_write2 hryky_write1 << this->v2_
#define hryky_write3 hryky_write2 << this->v3_
#define hryky_write4 hryky_write3 << this->v4_

#define hryky_def1 A1T v1_;
#define hryky_def2 hryky_def1; A2T v2_;
#define hryky_def3 hryky_def2; A3T v3_;
#define hryky_def4 hryky_def3; A4T v4_;

#define hryky_rest2 A2T
#define hryky_rest3 hryky_rest2, A3T
#define hryky_rest4 hryky_rest3, A4T

#define hryky_make1 typename hryky::RemoveConstReference<A1T>::type
#define hryky_make2 hryky_make1, typename hryky::RemoveConstReference<A2T>::type
#define hryky_make3 hryky_make2, typename hryky::RemoveConstReference<A3T>::type
#define hryky_make4 hryky_make3, typename hryky::RemoveConstReference<A4T>::type

#define hryky_template_arg1 A1T
#define hryky_template_arg2 hryky_template_arg1, A2T
#define hryky_template_arg3 hryky_template_arg2, A3T
#define hryky_template_arg4 hryky_template_arg3, A4T
#define hryky_template_arg5 hryky_template_arg4, A5T
#define hryky_template_arg6 hryky_template_arg5, A6T
#define hryky_template_arg7 hryky_template_arg6, A7T
#define hryky_template_arg8 hryky_template_arg7, A8T

#define hryky_const_arg1 \
	typename AddConstReference<A1T>::type v1
#define hryky_const_arg2 \
	hryky_const_arg1, typename AddConstReference<A2T>::type v2
#define hryky_const_arg3 \
	hryky_const_arg2, typename AddConstReference<A3T>::type v3
#define hryky_const_arg4 \
	hryky_const_arg3, typename AddConstReference<A4T>::type v4
#define hryky_const_arg5 \
	hryky_const_arg4, typename AddConstReference<A5T>::type v5
#define hryky_const_arg6 \
	hryky_const_arg5, typename AddConstReference<A6T>::type v6
#define hryky_const_arg7 \
	hryky_const_arg6, typename AddConstReference<A7T>::type v7
#define hryky_const_arg8 \
	hryky_const_arg7, typename AddConstReference<A8T>::type v8

#define hryky_forward_arg1 ::std::forward<A1T>(v1)
#define hryky_forward_arg2 hryky_forward_arg1, ::std::forward<A2T>(v2)
#define hryky_forward_arg3 hryky_forward_arg2, ::std::forward<A3T>(v3)
#define hryky_forward_arg4 hryky_forward_arg3, ::std::forward<A4T>(v4)
#define hryky_forward_arg5 hryky_forward_arg4, ::std::forward<A5T>(v5)
#define hryky_forward_arg6 hryky_forward_arg5, ::std::forward<A6T>(v6)
#define hryky_forward_arg7 hryky_forward_arg6, ::std::forward<A7T>(v7)
#define hryky_forward_arg8 hryky_forward_arg7, ::std::forward<A8T>(v8)

//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// tuple which has no value.
	class Tuple0;

	/// tuple which has a value.
	template < hryky_template_param1 >
	class Tuple1;

	/// tuple which has 2 values.
	template < hryky_template_param2 >
	class Tuple2;

	/// tuple which has 3 values.
	template < hryky_template_param3 >
	class Tuple3;

	/// tuple which has 4 values.
	template < hryky_template_param4 >
	class Tuple4;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief tuple which has no value.
 */
class hryky::Tuple0 : public Tuple< Tuple0 >
{
public :

	typedef hryky::Tuple0 this_type;
	typedef Null first_type;
	typedef Tuple0 rest_type;

	Tuple0()
	{}

	Tuple0(this_type const &)
	{
	}

	Tuple0(this_type &&)
	{
	}

	template <typename StreamT>
	StreamT & write_to(StreamT & out) const
	{
		return out;
	}

protected :

private :


};
/**
  @brief tuple which has one value.
 */
template < hryky_template_param1 >
class hryky::Tuple1 : public Tuple< Tuple1<hryky_template_arg1> >
{
public :

	typedef hryky::Tuple1<hryky_template_arg1> this_type;
	typedef A1T first_type;
	typedef Tuple0 rest_type;
	typedef Tuple<Tuple1> base_type;

	Tuple1(hryky_rval_arg1)
		: hryky_rval_init1()
	{}

	Tuple1(hryky_const_arg1)
		: hryky_const_init1()
	{}

	template <typename StreamT>
	StreamT & write_to(StreamT & out) const
	{
		out << hryky_write1;
		return out;
	}

	hryky_def1;
	
protected :

private :


};
/**
  @brief tuple which has two values.
 */
template < hryky_template_param2 >
class hryky::Tuple2 : public Tuple< Tuple2<hryky_template_arg2> >
{
public :
	typedef hryky::Tuple2<hryky_template_arg2> this_type;
	typedef A1T first_type;
	typedef Tuple1<hryky_rest2> rest_type;
	typedef Tuple<Tuple2> base_type;

	/// constructor with parameters
	Tuple2(hryky_rval_arg2)
		: hryky_rval_init2()
	{}

	Tuple2(hryky_const_arg2)
		: hryky_const_init2()
	{}

	template <typename RhsT>
	Tuple2(RhsT const & rhs)
		: hryky_copy_init2()
	{
	}

	template <typename RhsT>
	Tuple2(RhsT && rhs)
		: hryky_move_init2()
	{
	}

	template <typename StreamT>
	StreamT & write_to(StreamT & out) const
	{
		out << hryky_write2;
		return out;
	}

	hryky_def2;

protected :

private :

};
/**
  @brief tuple which has three values.
 */
template < hryky_template_param3 >
class hryky::Tuple3 : public hryky::Tuple< Tuple3<hryky_template_arg3> >
{
public :

	typedef Tuple3<hryky_template_arg3> this_type;
	typedef A1T first_type;
	typedef Tuple2<hryky_rest3> rest_type;
	typedef Tuple<Tuple3> base_type;

	/// constructor with parameters
	Tuple3(hryky_rval_arg3)
		: hryky_rval_init3()
	{}

	Tuple3(hryky_const_arg3)
		: hryky_const_init3()
	{}

	template <typename RhsT>
	Tuple3(RhsT const & rhs)
		: hryky_copy_init3()
	{
	}

	template <typename RhsT>
	Tuple3(RhsT && rhs)
		: hryky_move_init3()
	{
	}

	template <typename StreamT>
	StreamT & write_to(StreamT & out) const
	{
		out << hryky_write3;
		return out;
	}

	hryky_def3;

protected :

private :

};
/**
  @brief tuple which has 4 values.
 */
template < hryky_template_param4 >
class hryky::Tuple4 : public hryky::Tuple< Tuple4<hryky_template_arg4> >
{
public :

	typedef Tuple4<hryky_template_arg4> this_type;
	typedef A1T first_type;
	typedef Tuple3<hryky_rest4> rest_type;
	typedef Tuple<Tuple4> base_type;

	/// constructor with parameters
	Tuple4(hryky_rval_arg4)
		: hryky_rval_init4()
	{}

	Tuple4(hryky_const_arg4)
		: hryky_const_init4()
	{}

	template <typename RhsT>
	Tuple4(RhsT const & rhs)
		: hryky_copy_init4()
	{
	}

	template <typename RhsT>
	Tuple4(RhsT && rhs)
		: hryky_move_init4()
	{
	}

	template <typename StreamT>
	StreamT & write_to(StreamT & out) const
	{
		out << hryky_write4;
		return out;
	}

	hryky_def4;

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
	/// creates a tuple which has no value.
	Tuple0 make_tuple();

	/// creates a tuple which has one value.
	template <hryky_template_param1 >
	Tuple1<hryky_make1> make_tuple(hryky_rval_arg1);

	/// creates a tuple which has two values.
	template <hryky_template_param2 >
	Tuple2<hryky_make2> make_tuple(hryky_rval_arg2);

	/// creates a tuple which has three values.
	template <hryky_template_param3 >
	Tuple3<hryky_make3> make_tuple(hryky_rval_arg3);

	/// creates a tuple which has three values.
	template <hryky_template_param4 >
	Tuple4<hryky_make4> make_tuple(hryky_rval_arg4);


} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates a tuple which has no value.
 */
inline
hryky::Tuple0
hryky::make_tuple()
{
	return Tuple0();
}
/**
  @brief creates a tuple which has one value.
 */
template <hryky_template_param1 >
hryky::Tuple1<hryky_make1>
hryky::make_tuple(hryky_rval_arg1)
{
	return Tuple1<hryky_make1>(hryky_forward_arg1);
}
/**
  @brief creates a tuple which has two values.
 */
template <hryky_template_param2 >
hryky::Tuple2<hryky_make2>
hryky::make_tuple(hryky_rval_arg2)
{
	return Tuple2<hryky_make2>(hryky_forward_arg2);
}
/**
  @brief creates a tuple which has three values.
 */
template <hryky_template_param3 >
hryky::Tuple3<hryky_make3>
hryky::make_tuple(hryky_rval_arg3)
{
	return Tuple3<hryky_make3>(hryky_forward_arg3);
}
/**
  @brief creates a tuple which has 4 values.
 */
template <hryky_template_param4 >
hryky::Tuple4<hryky_make4>
hryky::make_tuple(hryky_rval_arg4)
{
	return Tuple4<hryky_make4>(hryky_forward_arg4);
}
//------------------------------------------------------------------------------
// revokes macros
//------------------------------------------------------------------------------
#undef hryky_template_param1
#undef hryky_template_param2
#undef hryky_template_param3
#undef hryky_template_param4
#undef hryky_template_param5
#undef hryky_template_param6
#undef hryky_template_param7
#undef hryky_template_param8

#undef hryky_rval_arg1
#undef hryky_rval_arg2
#undef hryky_rval_arg3
#undef hryky_rval_arg4
#undef hryky_rval_arg5
#undef hryky_rval_arg6
#undef hryky_rval_arg7
#undef hryky_rval_arg8

#undef hryky_rval_init1
#undef hryky_rval_init2
#undef hryky_rval_init3
#undef hryky_rval_init4

#undef hryky_const_init1
#undef hryky_const_init2
#undef hryky_const_init3
#undef hryky_const_init4

#undef hryky_copy_init1
#undef hryky_copy_init2
#undef hryky_copy_init3
#undef hryky_copy_init4

#undef hryky_move_init1
#undef hryky_move_init2
#undef hryky_move_init3
#undef hryky_move_init4

#undef hryky_write1
#undef hryky_write2
#undef hryky_write3
#undef hryky_write4

#undef hryky_def1
#undef hryky_def2
#undef hryky_def3
#undef hryky_def4

#undef hryky_rest2
#undef hryky_rest3
#undef hryky_rest4

#undef hryky_make1
#undef hryky_make2
#undef hryky_make3
#undef hryky_make4

#undef hryky_template_arg1
#undef hryky_template_arg2
#undef hryky_template_arg3
#undef hryky_template_arg4
#undef hryky_template_arg5
#undef hryky_template_arg6
#undef hryky_template_arg7
#undef hryky_template_arg8

#undef hryky_const_arg1
#undef hryky_const_arg2
#undef hryky_const_arg3
#undef hryky_const_arg4
#undef hryky_const_arg5
#undef hryky_const_arg6
#undef hryky_const_arg7
#undef hryky_const_arg8

#undef hryky_forward_arg1
#undef hryky_forward_arg2
#undef hryky_forward_arg3
#undef hryky_forward_arg4
#undef hryky_forward_arg5
#undef hryky_forward_arg6
#undef hryky_forward_arg7
#undef hryky_forward_arg8

#endif // TUPLE_N_H_20131015230751630
// end of file
