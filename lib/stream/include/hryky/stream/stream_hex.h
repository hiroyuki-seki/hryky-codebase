/**
  @file     stream_hex.h
  @brief    prescribes a stream to represent a number as hexadecimal.
  @author   HRYKY
  @version  $Id: stream_hex.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef STREAM_HEX_H_20131005174235404
#define STREAM_HEX_H_20131005174235404
#include "hryky/stream/ostream_string.h"
#include "hryky/stream/stream_manip.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace stream
{
	/// prescribes a stream to represent a number as hexadecimal.
	class Hex;

} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief prescribes a stream to represent a number as hexadecimal.
 */
class hryky::stream::Hex :
	public Manip
{
public :

	/// default constructor.
	Hex();

	/// constructs with availability.
	explicit Hex(bool const src);

	/// retrieves the availability.
	bool value() const;

private :

	bool value_;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace stream
{
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
inline
hryky::stream::Hex::Hex()
	: value_(true)
{
}
/**
  @brief constructs with availability.
 */
inline
hryky::stream::Hex::Hex(bool const src)
	: value_(src)
{
}
/**
  @brief retrieves the availability.
 */
inline
bool hryky::stream::Hex::value() const
{
	return this->value_;
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
namespace stream
{
	/// prescribes a stream to represent a number as hexadecimal.
	template <typename StringT>
	ostream::String<StringT> & operator<<(
		ostream::String<StringT> & lhs, Hex const & rhs);

} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief prescribes a stream to represent a number as hexadecimal.
 */
template <typename StringT>
hryky::ostream::String<StringT> &
hryky::stream::operator<<(
	ostream::String<StringT> & lhs, Hex const & rhs)
{
	lhs.hex(rhs.value());
	return lhs;
}
#endif // STREAM_HEX_H_20131005174235404
// end of file
