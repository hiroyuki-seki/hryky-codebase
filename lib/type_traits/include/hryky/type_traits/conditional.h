/**
  @file     conditional.h
  @brief    selects a type based on boolean.
  @author   HRYKY
  @version  $Id: conditional.h 351 2014-05-27 10:18:20Z hryky.private@gmail.com $
 */
#ifndef CONDITIONAL_H_20131012152701310
#define CONDITIONAL_H_20131012152701310
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename BooleanT, typename TrueT, typename FalseT
#define hryky_template_arg \
	BooleanT, TrueT, FalseT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// selects a type based on boolean as BooleanT::value.
	template <hryky_template_param>
	class Conditional;

	/// selects a type based on boolean.
	template <bool Boolean, typename TrueT, typename FalseT>
	class ConditionalC;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief selects a type based on boolean as BooleanT::value.
 */
template <typename BooleanT, typename TrueT, typename FalseT>
class hryky::Conditional
{
public :
	typedef typename ConditionalC<
		BooleanT::type::value, TrueT, FalseT>::type type;
};
/**
  @brief selects a type based on boolean.
 */
template <bool Boolean, typename TrueT, typename FalseT>
class hryky::ConditionalC
{
public :
	typedef FalseT type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief selects the type for true.
 */
template <typename TrueT, typename FalseT>
class ConditionalC<true, TrueT, FalseT>
{
public :
	typedef TrueT type;
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
#endif // CONDITIONAL_H_20131012152701310
// end of file
