/**
  @file         error_string.h
  @brief        holds the message about the error as string.
  @author       HRYKY
  @version      $Id: hryky-template.l 63 2012-05-01 03:42:24Z hryky.private@gmail.com $
 */
#ifndef ERROR_STRING_H_20120610122417183
#define ERROR_STRING_H_20120610122417183
#include "hryky/error/error_base.h"
#include "hryky/error/error_holder.h"
#include "hryky/string.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace error
{
	/// holds the message about the error as string.
	class String;

} // namespace error
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief holds the message about the error as string.
 */
class hryky::error::String :
	public hryky::error::Base
{
public :

	typedef Base                                base_type;
	typedef String                              this_type;
	typedef hryky::String<>::allocator_type     allocator_type;

	/// default constructor.
	String();

	/// copy constructor.
	String(this_type const &);

	/// constructor with the initial string as an array of characters.
	String(
		char const * const src,
		size_t const src_size);

	/// constructor with the initial string as a null-terminated string.
	String(char const * const src);

	/// destructor.
	~String();

	/// assignment operator
	hryky_assign_op;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

private :

	typedef hryky::String<> string_type;

	/// retrieves the description about this error.
	virtual char const * what_impl() const;

	string_type raw_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace error
{
} // namespace error
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::error::String::write_to(
	StreamT & out) const
{
	out << this->raw_;
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
namespace error
{
	/// creates an error represented by string.
	error_type string(char const * const c_str);

} // namespace error
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // ERROR_STRING_H_20120610122417183
// end of file
