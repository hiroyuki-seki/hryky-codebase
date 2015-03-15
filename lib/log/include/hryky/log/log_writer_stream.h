/**
  @file         log_writer_stream.h
  @brief        writes log messages to an arbitrary output stream.
  @author       HRYKY
  @version      $Id: log_writer_stream.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef LOG_WRITER_STREAM_H_20120519080909006
#define LOG_WRITER_STREAM_H_20120519080909006
#include "hryky/log/log_writer_base.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_virtual_destructor
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace log
{
namespace writer
{
	/// writes log messages to an arbitrary output stream.
	template < typename ValueT >
	class Stream;

} // namespace writer
} // namespace log
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief writes log messages to an arbitrary output stream.
 */
template < typename ValueT >
class hryky::log::writer::Stream
	: public hryky::log::writer::Base
{
public :

	typedef ValueT          value_type;
	typedef value_type &    reference;

	typedef Stream this_type;
	typedef Base base_type;

	/// constructor with the reference of output stream.
	Stream(reference ref);

protected :

private :

	hryky_delete_default_constructor(Stream);
	hryky_delete_this_copy_constructor(Stream);
	hryky_delete_this_copy_assign_op(Stream);

	/// writes out a string.
	virtual bool write_impl(
		char const * const str, size_t const size);

	/// writes out the bufferred messages.
	virtual void flush_impl();

	reference stream_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace log
{
namespace writer
{
} // namespace writer
} // namespace log
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief constructor with the reference of output stream.
 */
template < typename ValueT >
hryky::log::writer::Stream<ValueT>::Stream(reference stream)
	: stream_(stream)
{
	return;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief writes out a string.
 */
template < typename ValueT >
bool hryky::log::writer::Stream<ValueT>::write_impl(
	char const * const str, size_t const size)
{
	this->stream_.write(str, static_cast< ::std::streamsize>(size));
	return true;
}
/**
  @brief writes out the bufferred messages.
 */
template < typename ValueT >
void hryky::log::writer::Stream<ValueT>::flush_impl()
{
	this->stream_.flush();
}
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace log
{
namespace writer
{
} // namespace writer
} // namespace log
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // LOG_WRITER_STREAM_H_20120519080909006
// end of file
