/**
  @file     file_reader_win32_entity.h
  @brief    retains the Windows-specific file.
  @author   HRYKY
  @version  $Id: file_reader_win32_entity.h 363 2014-07-10 10:46:29Z hryky.private@gmail.com $
 */
#ifndef FILE_READER_WIN32_ENTITY_H_20140705062442933
#define FILE_READER_WIN32_ENTITY_H_20140705062442933
#include "hryky/path.h"
#include "hryky/win32/win32_handle.h"
#include "hryky/with_is_null.h"
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
namespace reader
{
namespace win32
{
	/// retains the Windows-specific file.
	class Entity;

} // namespace win32
} // namespace reader
} // namespace file
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the Windows-specific file.
 */
class hryky::file::reader::win32::Entity :
	public WithStreamOut<Entity>,
	public WithSwap<Entity>,
	public WithIsNull<Entity>
{
public :

	typedef Entity this_type;

	/// default constructor.
	Entity();

	/// creates an instance with opening a file.
	Entity(path_type const & path);

	/// move constructor.
	Entity(this_type &&);

	/// destructor.
	~Entity();

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/**
	  @brief reads out data.
	 */
	size_t read(void * const dest, size_t const size);
	
	/// opens a file.
	bool open(path_type const & path);

	/// confirms whether this instance is regarded as null.
	bool is_null() const;

protected :

private :
	hryky_delete_copy_constructor(Entity);
	hryky_delete_copy_assign_op(Entity);
	
	typedef hryky::win32::Handle handle_type;

	handle_type handle_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace file
{
namespace reader
{
namespace win32
{
} // namespace win32
} // namespace reader
} // namespace file
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::file::reader::win32::Entity::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(handle);
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
namespace reader
{
namespace win32
{
} // namespace win32
} // namespace reader
} // namespace file
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // FILE_READER_WIN32_ENTITY_H_20140705062442933
// end of file
