/**
  @file     with_stream_out.h
  @brief    appends the feature to output information to a stream.
  @author   HRYKY
  @version  $Id: with_stream_out.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef WITH_STREAM_OUT_H_20140204222106597
#define WITH_STREAM_OUT_H_20140204222106597
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
	/// appends the feature to output information to a stream.
	template <hryky_template_param>
	class WithStreamOut;

namespace stream
{
namespace map
{
	template <typename>
	class Scope;
	
} // namespace map
} // namespace stream

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief appends the feature to output information to a stream.
 */
template <typename DerivedT>
class hryky::WithStreamOut
{
public :
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
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // WITH_STREAM_OUT_H_20140204222106597
// end of file
