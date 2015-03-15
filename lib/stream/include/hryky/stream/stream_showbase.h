/**
  @file     stream_showbase.h
  @brief    prescribes a stream to represent a number with the specifier of the radix.
  @author   HRYKY
  @version  $Id: stream_showbase.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef STREAM_SHOWBASE_H_20131005192225473
#define STREAM_SHOWBASE_H_20131005192225473
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
	/**
	  prescribes a stream to represent a number with the specifier of the radix.
	 */
	class Showbase;

} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief prescribes a stream to represent a number with the specifier of
    the radix.
 */
class hryky::stream::Showbase
{
public :

	/// default constructor.
	Showbase();

	/// constructs with availability.
	explicit Showbase(bool const src);

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
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
inline
hryky::stream::Showbase::Showbase()
	: value_(true)
{
}
/**
  @brief constructs with availability.
 */
inline
hryky::stream::Showbase::Showbase(bool const src)
	: value_(src)
{
}
/**
  @brief retrieves the availability.
 */
inline
bool hryky::stream::Showbase::value() const
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
	/**
	  prescribes a stream to represent a number with the specifier of the radix.
	 */
	template <typename StringT>
	ostream::String<StringT> & operator<<(
		ostream::String<StringT> & lhs, Showbase const & rhs);

} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief prescribes a stream to represent a number with the specifier of the radix.
 */
template <typename StringT>
hryky::ostream::String<StringT> &
hryky::stream::operator<<(
	ostream::String<StringT> & lhs, Showbase const & rhs)
{
	lhs.showbase(rhs.value());
	return lhs;
}
#endif // STREAM_SHOWBASE_H_20131005192225473
// end of file
