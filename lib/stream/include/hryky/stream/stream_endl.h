/**
  @file     stream_endl.h
  @brief    the end of line.
  @author   HRYKY
  @version  $Id: stream_endl.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef STREAM_ENDL_H_20131002225048618
#define STREAM_ENDL_H_20131002225048618
#include "hryky/with_stream_out.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// the end of line.
	class Endl;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief the end of line.
 */
class hryky::Endl :
	public WithStreamOut<Endl>
{
public :

	typedef Endl this_type;

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

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
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::Endl::write_to(StreamT & out) const
{
	out << "\n";
	return out;
}
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
	Endl const endl;
	
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // STREAM_ENDL_H_20131002225048618
// end of file
