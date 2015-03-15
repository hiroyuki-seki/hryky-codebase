/**
  @file         file_mode.h
  @brief        retains the access mode for file descriptor.
  @author       HRYKY
  @version      $Id: file_mode.h 360 2014-07-05 06:59:57Z hryky.private@gmail.com $
 */
#ifndef FILE_DESCRIPTOR_MODE_H_20130209135355245
#define FILE_DESCRIPTOR_MODE_H_20130209135355245
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#if HRYKY_PLATFORM_WINDOWS
#   include "hryky/file/file_win32_mode.h"
#endif
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
	/// retains the access mode for file descriptor.
	class Mode;

} // namespace file
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the access mode for file descriptor.
 */
class hryky::file::Mode :
	public WithStreamOut<Mode>,
	public WithSwap<Mode>
{
public :

	typedef Mode this_type;
#if HRYKY_PLATFORM_WINDOWS
	typedef win32::Mode impl_type;
#endif

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

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

protected :

private :

	impl_type impl_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace file
{
} // namespace file
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::file::Mode::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
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
} // namespace file
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // FILE_DESCRIPTOR_MODE_H_20130209135355245
// end of file
