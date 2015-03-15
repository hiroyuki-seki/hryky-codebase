/**
  @file         debug_source.h
  @brief        retains a debugging information of source position.
  @author       HRYKY
  @version      $Id: debug_source.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef DEBUG_SOURCE_H_20120911150523295
#define DEBUG_SOURCE_H_20120911150523295
#include "hryky/pragma.h"
#include "hryky/string.h"
#include "hryky/with_stream_out.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_padded
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace debug
{
	/// retains a debugging information of source position.
	class Source;

} // namespace debug
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains a debugging information of source position.
 */
class hryky::debug::Source :
	public WithStreamOut<Source>
{
public :
	typedef Source      this_type;
	typedef String<>    filename_type;  ///< represents the name of file
	typedef String<>    function_type;  ///< represents the name of function
	typedef size_t      line_type;      ///< represents the number of line

	/// default constructor.
	Source();

	/// constructor with debug information.
	Source(char const * filename, char const * function, size_t line);

	/// destructor.
	~Source();

	/// writes the position to a stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & os) const;

protected :

private :

	hryky_delete_this_copy_constructor(Source);
	hryky_delete_this_copy_assign_op(Source);

	/// retrieves the name of file.
	filename_type const & filename() const;

	/// retrieves the name of function.
	function_type const & function() const;

	/// retrieves the number of lines.
	line_type line() const;

	filename_type   filename_;
	function_type   function_;
	line_type       line_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace debug
{
} // namespace debug
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief writes the position to a stream.
 */
template <typename StreamT>
StreamT &
hryky::debug::Source::write_to(StreamT & os) const
{
	if (!this->filename_.empty()) {
		os << this->filename_.c_str() << "(" << this->line_ << ") : ";
	}

	if (!this->function_.empty()) {
		os << this->function_.c_str() << " : ";
	}
	
	return os;
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
namespace debug
{
} // namespace debug
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// restores warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // DEBUG_SOURCE_H_20120911150523295
// end of file
