/**
  @file     win32_handle.h
  @brief    retains the HANDLE value.
  @author   HRYKY
  @version  $Id: win32_handle.h 363 2014-07-10 10:46:29Z hryky.private@gmail.com $
 */
#ifndef WIN32_HANDLE_H_20140705120658171
#define WIN32_HANDLE_H_20140705120658171
#include "hryky/windows.h"
#include "hryky/definition.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/with_is_null.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace win32
{
	/// retains the HANDLE value.
	class Handle;

} // namespace win32
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the HANDLE value.
 */
class hryky::win32::Handle :
	public WithStreamOut<Handle>,
	public WithSwap<Handle>,
	public WithIsNull<Handle>
{
public :

	typedef Handle this_type;
	typedef ::HANDLE raw_type;

	/// default constructor.
	Handle();

	/// creates an instance from the raw handle.
	Handle(raw_type const raw);

	/// move constructor.
	Handle(this_type &&);

	/// destructor.
	~Handle();

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// retrieves the internal raw handle.
	HANDLE raw() const;

	/// confirms whether the internal handle is invalid.
	bool is_null() const;

protected :

private :
	hryky_delete_copy_constructor(Handle);
	hryky_delete_copy_assign_op(Handle);

	raw_type raw_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace win32
{
} // namespace win32
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::win32::Handle::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(raw);
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
namespace win32
{
} // namespace win32
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // WIN32_HANDLE_H_20140705120658171
// end of file
