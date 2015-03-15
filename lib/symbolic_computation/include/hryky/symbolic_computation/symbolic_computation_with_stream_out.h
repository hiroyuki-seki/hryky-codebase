/**
  @file     symbolic_computation_with_stream_out.h
  @brief    appends the feature to stringifiy an operation.
  @author   HRYKY
  @version  $Id: symbolic_computation_with_stream_out.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_STRINGIFIABLE_H_20131010190610462
#define SYMBOLIC_COMPUTATION_STRINGIFIABLE_H_20131010190610462
#include "hryky/with_stream_out.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename DerivedT
#define hryky_template_arg \
	DerivedT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// appends the feature to stringifiy an operation.
	template <hryky_template_param>
	class WithStreamOut;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief appends the feature to stringifiy an operation.
 */
template <hryky_template_param>
class hryky::symbolic_computation::WithStreamOut :
	public hryky::WithStreamOut<WithStreamOut<hryky_template_arg> >
{
public :
	/// prints the information of the implementation.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
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
/**
  @brief prints the information of the implementation.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::symbolic_computation::WithStreamOut<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return out << DerivedT::type();
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // SYMBOLIC_COMPUTATION_STRINGIFIABLE_H_20131010190610462
// end of file
