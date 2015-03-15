/**
  @file     file_win32_mode.h
  @brief    retains the Windows-specific attributes to open file.
  @author   HRYKY
  @version  $Id: file_win32_mode.h 360 2014-07-05 06:59:57Z hryky.private@gmail.com $
 */
#ifndef FILE_WIN32_MODE_H_20140705060355919
#define FILE_WIN32_MODE_H_20140705060355919
#include "hryky/bitfield.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace file
{
namespace win32
{
	/// retains the Windows-specific attributes to open file.
	class Mode;

} // namespace win32
} // namespace file
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the Windows-specific attributes to open file.
 */
class hryky::file::win32::Mode :
	public WithStreamOut<Mode>,
	public WithSwap<Mode>
{
public :

	typedef Mode this_type;

	/// default constructor.
	Mode();

	/// copy constructor.
	Mode(this_type const &);

	/// move constructor.
	Mode(this_type &&);

	/// destructor.
	~Mode();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// retrieves the 'DesiredAccess' parameter.
	DWORD desired_access() const;

	/// retrieves the 'ShareMode' parameter.
	DWORD share_mode() const;

	/// retrieves the 'CreationDisposition' parameter.
	DWORD creation_disposition() const;

	/// retrieves the 'SecurityAttributes' parameter.
	SECURITY_ATTRIBUTES * security_attributes() const;

	/// retrieves the 'FlagsAndAttributes' parameter.
	DWORD flags_and_attributes() const;

	/// retrieves the 'TemplateFile' parameter.
	HANDLE template_file() const;

protected :

private :

	struct Flags {
		bool read_:1;
		bool write_:1;
		
		bool share_read_:1;
		bool share_write_:1;
		bool share_delete_:1;

		bool create_new_:1;
		bool open_existing_:1;
		bool truncate_:1;

		bool normal_:1;
		bool hidden_:1;
		bool read_only_:1;
		bool no_buffering_:1;
		bool async_:1;
		bool random_:1;
		bool sequential_:1;
		bool write_through_:1;
	};
	typedef Bitfield<Flags> flags_type;

	flags_type flags_;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace file
{
namespace win32
{
} // namespace win32
} // namespace file
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::file::win32::Mode::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(flags);
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
namespace file
{
namespace win32
{
} // namespace win32
} // namespace file
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // FILE_WIN32_MODE_H_20140705060355919
// end of file
