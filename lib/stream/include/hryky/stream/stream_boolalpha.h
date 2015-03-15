/**
  @file     stream_boolalpha.h
  @brief    represents a boolean value as string.
  @author   HRYKY
  @version  $Id: stream_boolalpha.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef STREAM_BOOLALPHA_H_20131005152933312
#define STREAM_BOOLALPHA_H_20131005152933312
#include "hryky/stream/ostream_string.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// represents a boolean value as string.
	class Boolalpha;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief represents a boolean value as string.
 */
class hryky::Boolalpha
{
public :

	/// constructs with availability.
	Boolalpha(bool const src);

	/// retrieves the availability.
	bool value() const;

private :

	hryky_delete_default_constructor(Boolalpha);

	bool value_;

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
  @brief constructs with availability.
 */
inline hryky::Boolalpha::Boolalpha(bool const src)
	: value_(src)
{
}
/**
  @brief retrieves the availability.
 */
inline bool hryky::Boolalpha::value() const
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
	Boolalpha const boolalpha(true);

	/// prescribes a stream to represent a boolean value as string.
	template <typename StringT>
	ostream::String<StringT> & operator<<(
		ostream::String<StringT> & lhs, Boolalpha const & rhs);
	
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief prescribes a stream to represent a boolean value as string.
 */
template <typename StringT>
hryky::ostream::String<StringT> &
hryky::operator<<(
	ostream::String<StringT> & lhs, Boolalpha const & rhs)
{
	lhs.boolalpha(rhs.value());
	return lhs;
}
#endif // STREAM_BOOLALPHA_H_20131005152933312
// end of file
