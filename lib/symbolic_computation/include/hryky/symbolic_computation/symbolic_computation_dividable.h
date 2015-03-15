/**
  @file     symbolic_computation_dividable.h
  @brief    confirms whether the term can be divided by the specified type.
  @author   HRYKY
  @version  $Id: symbolic_computation_dividable.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_DIVIDABLE_H_20131119215112577
#define SYMBOLIC_COMPUTATION_DIVIDABLE_H_20131119215112577
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename TargetT, typename WrtT
#define hryky_template_arg \
	TargetT, WrtT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// confirms whether the term can be divided by the specified type.
	template <hryky_template_param>
	class Dividable;

	/// ignores invalid divisor.
	template <hryky_template_param>
	class DividableIgnore;

	/// The same type can be divided.
	template <hryky_template_param>
	class DividableSame;

	/// implements Dividable agaist the resolved types.
	template <hryky_template_param>
	class DividableImpl;

	template <typename EvalT, int Value>
	class Integer;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confirms whether the term can be divided by the specified type.
 */
template <hryky_template_param>
class hryky::symbolic_computation::Dividable
{
private :
	typedef DividableIgnore<typename TargetT::type, typename WrtT::type> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
/**
  @brief ignores invalid divisor.
 */
template <hryky_template_param>
class hryky::symbolic_computation::DividableIgnore
{
private :
	typedef DividableSame<typename TargetT::type, typename WrtT::type> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
/**
  @brief The same type can be divided.
 */
template <hryky_template_param>
class hryky::symbolic_computation::DividableSame
{
private :
	typedef DividableImpl<typename TargetT::type, typename WrtT::type> impl;
public :
	typedef typename impl::type type;
	static bool const value = impl::value;
};
/**
  @brief implements Dividable agaist the resolved types.
 */
template <hryky_template_param>
class hryky::symbolic_computation::DividableImpl
{
public :
	typedef TargetT type;
	static bool const value = false;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief The integer one is not valid for divisor.
 */
template <typename TargetT, typename EvalT>
class DividableIgnore<TargetT, Integer<EvalT, 1> >
{
public :
	typedef TargetT type;
	static bool const value = false;
};
/**
  @brief The integer zero is not valid for divisor.
 */
template <typename TargetT, typename EvalT>
class DividableIgnore<TargetT, Integer<EvalT, 0> >
{
public :
	typedef TargetT type;
	static bool const value = false;
};
/**
  @brief The same type can be divided.
 */
template <typename TargetT>
class DividableSame<TargetT, TargetT>
{
public :
	typedef Integer<typename TargetT::eval_type, 1> type;
	static bool const value = true;
};
} // namespace symbolic_computation
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
namespace symbolic_computation
{
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // SYMBOLIC_COMPUTATION_DIVIDABLE_H_20131119215112577
// end of file
