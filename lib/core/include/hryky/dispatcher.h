/**
  @file     dispatcher.h
  @brief    passes the concrete class to polymorphic implementation.
  @author   HRYKY
  @version  $Id: dispatcher.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef DISPATCHER_H_20140819130725213
#define DISPATCHER_H_20140819130725213
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_typename_cls(id) typename Cls##id
#define hryky_typename_cls1 hryky_typename_cls(1)
#define hryky_typename_cls2 hryky_typename_cls1, hryky_typename_cls(2)
#define hryky_typename_cls3 hryky_typename_cls2, hryky_typename_cls(3)
#define hryky_typename_cls4 hryky_typename_cls3, hryky_typename_cls(4)
#define hryky_typename_cls5 hryky_typename_cls4, hryky_typename_cls(5)
#define hryky_typename_cls6 hryky_typename_cls5, hryky_typename_cls(6)
#define hryky_typename_cls7 hryky_typename_cls6, hryky_typename_cls(7)
#define hryky_typename_cls8 hryky_typename_cls7, hryky_typename_cls(8)
#define hryky_typename_cls9 hryky_typename_cls8, hryky_typename_cls(9)
#define hryky_typename_cls10 hryky_typename_cls9, hryky_typename_cls(10)
#define hryky_typename_cls11 hryky_typename_cls10, hryky_typename_cls(11)
#define hryky_typename_cls12 hryky_typename_cls11, hryky_typename_cls(12)
#define hryky_typename_cls13 hryky_typename_cls12, hryky_typename_cls(13)
#define hryky_typename_cls14 hryky_typename_cls13, hryky_typename_cls(14)
#define hryky_typename_cls15 hryky_typename_cls14, hryky_typename_cls(15)
#define hryky_typename_cls16 hryky_typename_cls15, hryky_typename_cls(16)
#define hryky_typename_cls17 hryky_typename_cls16, hryky_typename_cls(17)
#define hryky_typename_cls18 hryky_typename_cls17, hryky_typename_cls(18)
#define hryky_typename_cls19 hryky_typename_cls18, hryky_typename_cls(19)
#define hryky_typename_cls20 hryky_typename_cls19, hryky_typename_cls(20)
#define hryky_typename_cls21 hryky_typename_cls20, hryky_typename_cls(21)
#define hryky_typename_cls22 hryky_typename_cls21, hryky_typename_cls(22)
#define hryky_typename_cls23 hryky_typename_cls22, hryky_typename_cls(23)
#define hryky_typename_cls24 hryky_typename_cls23, hryky_typename_cls(24)
#define hryky_typename_cls25 hryky_typename_cls24, hryky_typename_cls(25)
#define hryky_typename_cls26 hryky_typename_cls25, hryky_typename_cls(26)
#define hryky_typename_cls27 hryky_typename_cls26, hryky_typename_cls(27)
#define hryky_typename_cls28 hryky_typename_cls27, hryky_typename_cls(28)
#define hryky_typename_cls29 hryky_typename_cls28, hryky_typename_cls(29)
#define hryky_typename_cls30 hryky_typename_cls29, hryky_typename_cls(30)
#define hryky_typename_cls31 hryky_typename_cls30, hryky_typename_cls(31)
#define hryky_typename_cls32 hryky_typename_cls31, hryky_typename_cls(32)

#define hryky_dispatch(id) \
	virtual RetT dispatch(Cls##id &)\
	{\
		return RetT();\
	}
#define hryky_dispatch1 hryky_dispatch(1)
#define hryky_dispatch2 hryky_dispatch1 hryky_dispatch(2)
#define hryky_dispatch3 hryky_dispatch2 hryky_dispatch(3)
#define hryky_dispatch4 hryky_dispatch3 hryky_dispatch(4)
#define hryky_dispatch5 hryky_dispatch4 hryky_dispatch(5)
#define hryky_dispatch6 hryky_dispatch5 hryky_dispatch(6)
#define hryky_dispatch7 hryky_dispatch6 hryky_dispatch(7)
#define hryky_dispatch8 hryky_dispatch7 hryky_dispatch(8)
#define hryky_dispatch9 hryky_dispatch8 hryky_dispatch(9)
#define hryky_dispatch10 hryky_dispatch9 hryky_dispatch(10)
#define hryky_dispatch11 hryky_dispatch10 hryky_dispatch(11)
#define hryky_dispatch12 hryky_dispatch11 hryky_dispatch(12)
#define hryky_dispatch13 hryky_dispatch12 hryky_dispatch(13)
#define hryky_dispatch14 hryky_dispatch13 hryky_dispatch(14)
#define hryky_dispatch15 hryky_dispatch14 hryky_dispatch(15)
#define hryky_dispatch16 hryky_dispatch15 hryky_dispatch(16)
#define hryky_dispatch17 hryky_dispatch16 hryky_dispatch(17)
#define hryky_dispatch18 hryky_dispatch17 hryky_dispatch(18)
#define hryky_dispatch19 hryky_dispatch18 hryky_dispatch(19)
#define hryky_dispatch20 hryky_dispatch19 hryky_dispatch(20)
#define hryky_dispatch21 hryky_dispatch20 hryky_dispatch(21)
#define hryky_dispatch22 hryky_dispatch21 hryky_dispatch(22)
#define hryky_dispatch23 hryky_dispatch22 hryky_dispatch(23)
#define hryky_dispatch24 hryky_dispatch23 hryky_dispatch(24)
#define hryky_dispatch25 hryky_dispatch24 hryky_dispatch(25)
#define hryky_dispatch26 hryky_dispatch25 hryky_dispatch(26)
#define hryky_dispatch27 hryky_dispatch26 hryky_dispatch(27)
#define hryky_dispatch28 hryky_dispatch27 hryky_dispatch(28)
#define hryky_dispatch29 hryky_dispatch28 hryky_dispatch(29)
#define hryky_dispatch30 hryky_dispatch29 hryky_dispatch(30)
#define hryky_dispatch31 hryky_dispatch30 hryky_dispatch(31)
#define hryky_dispatch32 hryky_dispatch31 hryky_dispatch(32)

#define hryky_typedef_cls(id) typedef Cls##id cls##id##_type;
#define hryky_typedef_cls1 hryky_typedef_cls(1)
#define hryky_typedef_cls2 hryky_typedef_cls1 hryky_typedef_cls(2)
#define hryky_typedef_cls3 hryky_typedef_cls2 hryky_typedef_cls(3)
#define hryky_typedef_cls4 hryky_typedef_cls3 hryky_typedef_cls(4)
#define hryky_typedef_cls5 hryky_typedef_cls4 hryky_typedef_cls(5)
#define hryky_typedef_cls6 hryky_typedef_cls5 hryky_typedef_cls(6)
#define hryky_typedef_cls7 hryky_typedef_cls6 hryky_typedef_cls(7)
#define hryky_typedef_cls8 hryky_typedef_cls7 hryky_typedef_cls(8)
#define hryky_typedef_cls9 hryky_typedef_cls8 hryky_typedef_cls(9)
#define hryky_typedef_cls10 hryky_typedef_cls9 hryky_typedef_cls(10)
#define hryky_typedef_cls11 hryky_typedef_cls10 hryky_typedef_cls(11)
#define hryky_typedef_cls12 hryky_typedef_cls11 hryky_typedef_cls(12)
#define hryky_typedef_cls13 hryky_typedef_cls12 hryky_typedef_cls(13)
#define hryky_typedef_cls14 hryky_typedef_cls13 hryky_typedef_cls(14)
#define hryky_typedef_cls15 hryky_typedef_cls14 hryky_typedef_cls(15)
#define hryky_typedef_cls16 hryky_typedef_cls15 hryky_typedef_cls(16)
#define hryky_typedef_cls17 hryky_typedef_cls16 hryky_typedef_cls(17)
#define hryky_typedef_cls18 hryky_typedef_cls17 hryky_typedef_cls(18)
#define hryky_typedef_cls19 hryky_typedef_cls18 hryky_typedef_cls(19)
#define hryky_typedef_cls20 hryky_typedef_cls19 hryky_typedef_cls(20)
#define hryky_typedef_cls21 hryky_typedef_cls20 hryky_typedef_cls(21)
#define hryky_typedef_cls22 hryky_typedef_cls21 hryky_typedef_cls(22)
#define hryky_typedef_cls23 hryky_typedef_cls22 hryky_typedef_cls(23)
#define hryky_typedef_cls24 hryky_typedef_cls23 hryky_typedef_cls(24)
#define hryky_typedef_cls25 hryky_typedef_cls24 hryky_typedef_cls(25)
#define hryky_typedef_cls26 hryky_typedef_cls25 hryky_typedef_cls(26)
#define hryky_typedef_cls27 hryky_typedef_cls26 hryky_typedef_cls(27)
#define hryky_typedef_cls28 hryky_typedef_cls27 hryky_typedef_cls(28)
#define hryky_typedef_cls29 hryky_typedef_cls28 hryky_typedef_cls(29)
#define hryky_typedef_cls30 hryky_typedef_cls29 hryky_typedef_cls(30)
#define hryky_typedef_cls31 hryky_typedef_cls30 hryky_typedef_cls(31)
#define hryky_typedef_cls32 hryky_typedef_cls31 hryky_typedef_cls(32)

#define hryky_dispatch_impl(id) \
	virtual typename BaseT::result_type dispatch(\
		typename BaseT::cls##id##_type & cls)\
	{\
		return static_cast<DerivedT &>(*this)(cls);\
	}
#define hryky_dispatch_impl1 hryky_dispatch_impl(1)
#define hryky_dispatch_impl2 hryky_dispatch_impl1 hryky_dispatch_impl(2)
#define hryky_dispatch_impl3 hryky_dispatch_impl2 hryky_dispatch_impl(3)
#define hryky_dispatch_impl4 hryky_dispatch_impl3 hryky_dispatch_impl(4)
#define hryky_dispatch_impl5 hryky_dispatch_impl4 hryky_dispatch_impl(5)
#define hryky_dispatch_impl6 hryky_dispatch_impl5 hryky_dispatch_impl(6)
#define hryky_dispatch_impl7 hryky_dispatch_impl6 hryky_dispatch_impl(7)
#define hryky_dispatch_impl8 hryky_dispatch_impl7 hryky_dispatch_impl(8)
#define hryky_dispatch_impl9 hryky_dispatch_impl8 hryky_dispatch_impl(9)
#define hryky_dispatch_impl10 hryky_dispatch_impl9 hryky_dispatch_impl(10)
#define hryky_dispatch_impl11 hryky_dispatch_impl10 hryky_dispatch_impl(11)
#define hryky_dispatch_impl12 hryky_dispatch_impl11 hryky_dispatch_impl(12)
#define hryky_dispatch_impl13 hryky_dispatch_impl12 hryky_dispatch_impl(13)
#define hryky_dispatch_impl14 hryky_dispatch_impl13 hryky_dispatch_impl(14)
#define hryky_dispatch_impl15 hryky_dispatch_impl14 hryky_dispatch_impl(15)
#define hryky_dispatch_impl16 hryky_dispatch_impl15 hryky_dispatch_impl(16)
#define hryky_dispatch_impl17 hryky_dispatch_impl16 hryky_dispatch_impl(17)
#define hryky_dispatch_impl18 hryky_dispatch_impl17 hryky_dispatch_impl(18)
#define hryky_dispatch_impl19 hryky_dispatch_impl18 hryky_dispatch_impl(19)
#define hryky_dispatch_impl20 hryky_dispatch_impl19 hryky_dispatch_impl(20)
#define hryky_dispatch_impl21 hryky_dispatch_impl20 hryky_dispatch_impl(21)
#define hryky_dispatch_impl22 hryky_dispatch_impl21 hryky_dispatch_impl(22)
#define hryky_dispatch_impl23 hryky_dispatch_impl22 hryky_dispatch_impl(23)
#define hryky_dispatch_impl24 hryky_dispatch_impl23 hryky_dispatch_impl(24)
#define hryky_dispatch_impl25 hryky_dispatch_impl24 hryky_dispatch_impl(25)
#define hryky_dispatch_impl26 hryky_dispatch_impl25 hryky_dispatch_impl(26)
#define hryky_dispatch_impl27 hryky_dispatch_impl26 hryky_dispatch_impl(27)
#define hryky_dispatch_impl28 hryky_dispatch_impl27 hryky_dispatch_impl(28)
#define hryky_dispatch_impl29 hryky_dispatch_impl28 hryky_dispatch_impl(29)
#define hryky_dispatch_impl30 hryky_dispatch_impl29 hryky_dispatch_impl(30)
#define hryky_dispatch_impl31 hryky_dispatch_impl30 hryky_dispatch_impl(31)
#define hryky_dispatch_impl32 hryky_dispatch_impl31 hryky_dispatch_impl(32)

#define hryky_dispatcher(id) \
	namespace hryky\
	{\
		template <hryky_typename_cls##id, typename RetT = void>\
		class Dispatcher##id;\
		template <typename DerivedT, typename BaseT>\
		class DispatcherImpl##id;\
	}\
	template <hryky_typename_cls##id, typename RetT>\
	class hryky::Dispatcher##id\
	{\
	public :\
		hryky_dispatch##id;\
	protected :\
		typedef RetT result_type;\
		hryky_typedef_cls##id;\
	};\
	template <typename DerivedT, typename BaseT>\
	class hryky::DispatcherImpl##id :\
		public BaseT\
	{\
	public :\
		hryky_dispatch_impl##id;\
	};

hryky_dispatcher(1);
hryky_dispatcher(2);
hryky_dispatcher(3);
hryky_dispatcher(4);
hryky_dispatcher(5);
hryky_dispatcher(6);
hryky_dispatcher(7);
hryky_dispatcher(8);
hryky_dispatcher(9);
hryky_dispatcher(10);
hryky_dispatcher(11);
hryky_dispatcher(12);
hryky_dispatcher(13);
hryky_dispatcher(14);
hryky_dispatcher(15);
hryky_dispatcher(16);
hryky_dispatcher(17);
hryky_dispatcher(18);
hryky_dispatcher(19);
hryky_dispatcher(20);
hryky_dispatcher(21);
hryky_dispatcher(22);
hryky_dispatcher(23);
hryky_dispatcher(24);
hryky_dispatcher(25);
hryky_dispatcher(26);
hryky_dispatcher(27);
hryky_dispatcher(28);
hryky_dispatcher(29);
hryky_dispatcher(30);
hryky_dispatcher(31);
hryky_dispatcher(32);

//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
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
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_typename_cls
#undef hryky_typename_cls1
#undef hryky_typename_cls2
#undef hryky_typename_cls3
#undef hryky_typename_cls4
#undef hryky_typename_cls5
#undef hryky_typename_cls6
#undef hryky_typename_cls7
#undef hryky_typename_cls8
#undef hryky_typename_cls9
#undef hryky_typename_cls10
#undef hryky_typename_cls11
#undef hryky_typename_cls12
#undef hryky_typename_cls13
#undef hryky_typename_cls14
#undef hryky_typename_cls15
#undef hryky_typename_cls16
#undef hryky_typename_cls17
#undef hryky_typename_cls18
#undef hryky_typename_cls19
#undef hryky_typename_cls20
#undef hryky_typename_cls21
#undef hryky_typename_cls22
#undef hryky_typename_cls23
#undef hryky_typename_cls24
#undef hryky_typename_cls25
#undef hryky_typename_cls26
#undef hryky_typename_cls27
#undef hryky_typename_cls28
#undef hryky_typename_cls29
#undef hryky_typename_cls30
#undef hryky_typename_cls31
#undef hryky_typename_cls32

#undef hryky_dispatch
#undef hryky_dispatch1
#undef hryky_dispatch2
#undef hryky_dispatch3
#undef hryky_dispatch4
#undef hryky_dispatch5
#undef hryky_dispatch6
#undef hryky_dispatch7
#undef hryky_dispatch8
#undef hryky_dispatch9
#undef hryky_dispatch10
#undef hryky_dispatch11
#undef hryky_dispatch12
#undef hryky_dispatch13
#undef hryky_dispatch14
#undef hryky_dispatch15
#undef hryky_dispatch16
#undef hryky_dispatch17
#undef hryky_dispatch18
#undef hryky_dispatch19
#undef hryky_dispatch20
#undef hryky_dispatch21
#undef hryky_dispatch22
#undef hryky_dispatch23
#undef hryky_dispatch24
#undef hryky_dispatch25
#undef hryky_dispatch26
#undef hryky_dispatch27
#undef hryky_dispatch28
#undef hryky_dispatch29
#undef hryky_dispatch30
#undef hryky_dispatch31
#undef hryky_dispatch32

#undef hryky_typedef_cls
#undef hryky_typedef_cls1
#undef hryky_typedef_cls2
#undef hryky_typedef_cls3
#undef hryky_typedef_cls4
#undef hryky_typedef_cls5
#undef hryky_typedef_cls6
#undef hryky_typedef_cls7
#undef hryky_typedef_cls8
#undef hryky_typedef_cls9
#undef hryky_typedef_cls10
#undef hryky_typedef_cls11
#undef hryky_typedef_cls12
#undef hryky_typedef_cls13
#undef hryky_typedef_cls14
#undef hryky_typedef_cls15
#undef hryky_typedef_cls16
#undef hryky_typedef_cls17
#undef hryky_typedef_cls18
#undef hryky_typedef_cls19
#undef hryky_typedef_cls20
#undef hryky_typedef_cls21
#undef hryky_typedef_cls22
#undef hryky_typedef_cls23
#undef hryky_typedef_cls24
#undef hryky_typedef_cls25
#undef hryky_typedef_cls26
#undef hryky_typedef_cls27
#undef hryky_typedef_cls28
#undef hryky_typedef_cls29
#undef hryky_typedef_cls30
#undef hryky_typedef_cls31
#undef hryky_typedef_cls32

#undef hryky_dispatch_impl
#undef hryky_dispatch_impl1
#undef hryky_dispatch_impl2
#undef hryky_dispatch_impl3
#undef hryky_dispatch_impl4
#undef hryky_dispatch_impl5
#undef hryky_dispatch_impl6
#undef hryky_dispatch_impl7
#undef hryky_dispatch_impl8
#undef hryky_dispatch_impl9
#undef hryky_dispatch_impl10
#undef hryky_dispatch_impl11
#undef hryky_dispatch_impl12
#undef hryky_dispatch_impl13
#undef hryky_dispatch_impl14
#undef hryky_dispatch_impl15
#undef hryky_dispatch_impl16
#undef hryky_dispatch_impl17
#undef hryky_dispatch_impl18
#undef hryky_dispatch_impl19
#undef hryky_dispatch_impl20
#undef hryky_dispatch_impl21
#undef hryky_dispatch_impl22
#undef hryky_dispatch_impl23
#undef hryky_dispatch_impl24
#undef hryky_dispatch_impl25
#undef hryky_dispatch_impl26
#undef hryky_dispatch_impl27
#undef hryky_dispatch_impl28
#undef hryky_dispatch_impl29
#undef hryky_dispatch_impl30
#undef hryky_dispatch_impl31
#undef hryky_dispatch_impl32

#undef hryky_dispatcher

#endif // DISPATCHER_H_20140819130725213
// end of file
