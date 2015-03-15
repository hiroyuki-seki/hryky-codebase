/**
  @file     shader_dispatcher.h
  @brief    receives the concrete class from virtual function of Node.
  @author   HRYKY
  @version  $Id: shader_dispatcher.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_DISPATCHER_H_20140819115033160
#define SHADER_DISPATCHER_H_20140819115033160
#include "hryky/dispatcher.h"
#include "hryky/retention/retention_value.h"
#include "hryky/literal_string.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_dispatcher \
	hryky::Dispatcher12<\
		Arguments,\
		Assign,\
		Function,\
		Functions,\
		Inputs,\
		Literal<float>,\
		Matrix<4,4>,\
		Multiply,\
		Outputs,\
		type::Base,\
		Uniforms,\
		Vector<float,4>\
	>
#define hryky_const_dispatcher \
	hryky::Dispatcher12<\
		Arguments const,\
		Assign const,\
		Function const,\
		Functions const,\
		Inputs const,\
		Literal<float> const,\
		Matrix<4,4> const,\
		Multiply const,\
		Outputs const,\
		type::Base const,\
		Uniforms const,\
		Vector<float,4> const\
	>
#define hryky_dispatcher_impl \
	hryky::DispatcherImpl12<\
		DerivedT,\
		Dispatcher\
	>
#define hryky_const_dispatcher_impl \
	hryky::DispatcherImpl12<\
		DerivedT,\
		ImmutableDispatcher\
	>
#define hryky_template_param \
	typename DerivedT
#define hryky_template_arg \
	DerivedT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
	template <
		size_t Rows,
		size_t Columns
	>
	class Matrix;

	template <
		typename TypeT,
		size_t Dimension
	>
	class Vector;

	template <
		typename ValueT
	>
	class Literal;

	class Arguments;
	class Assign;
	class Function;
	class Functions;
	class Multiply;
	class Inputs;
	class Outputs;
	class Uniforms;
	
	/// receives the concrete class from virtual function of Node.
	class Dispatcher;

	/// receives the immutable concrete class from virtual function of Node.
	class ImmutableDispatcher;

	/// implements Dispatcher
	template <hryky_template_param>
	class DispatcherImpl;

	/// implements ImmutableDispatcher
	template <hryky_template_param>
	class ImmutableDispatcherImpl;

namespace type
{
	class Base;
} // namespace type

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief receives the concrete class from virtual function of Node.
 */
class hryky::shader::Dispatcher :
	public hryky_dispatcher
{
public :
	typedef hryky_dispatcher base_type;

	typedef Dispatcher this_type;

};
/**
  @brief receives the immutable concrete class from virtual function of Node.
 */
class hryky::shader::ImmutableDispatcher :
	public hryky_const_dispatcher
{
public :
	typedef hryky_const_dispatcher base_type;

	typedef ImmutableDispatcher this_type;
};
/**
  @brief implements Dispatcher
 */
template <hryky_template_param>
class hryky::shader::DispatcherImpl :
	public hryky_dispatcher_impl
{
public :
	typedef hryky_dispatcher_impl base_type;

	typedef DispatcherImpl<hryky_template_arg> this_type;

};
/**
  @brief implements ImmutableDispatcher
 */
template <hryky_template_param>
class hryky::shader::ImmutableDispatcherImpl :
	public hryky_const_dispatcher_impl
{
public :
	typedef hryky_const_dispatcher_impl base_type;

	typedef ImmutableDispatcherImpl<hryky_template_arg> this_type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
} // namespace shader
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
namespace shader
{
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_dispatcher
#undef hryky_const_dispatcher
#undef hryky_dispatcher_impl
#undef hryky_const_dispatcher_impl
#undef hryky_template_param
#undef hryky_template_arg
#endif // SHADER_DISPATCHER_H_20140819115033160
// end of file
