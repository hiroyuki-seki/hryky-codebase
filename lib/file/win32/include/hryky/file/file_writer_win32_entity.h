/**
  @file     file_writer_win32_entity.h
  @brief    writes out data from a file on Windows Platform.
  @author   HRYKY
  @version  $Id: file_writer_win32_entity.h 363 2014-07-10 10:46:29Z hryky.private@gmail.com $
 */
#ifndef FILE_WRITER_WIN32_ENTITY_H_20140705145954291
#define FILE_WRITER_WIN32_ENTITY_H_20140705145954291
#include "hryky/win32/win32_handle.h"
#include "hryky/with_is_null.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/path.h"
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
namespace writer
{
namespace win32
{
	/// writes out data from a file on Windows Platform.
	class Entity;

} // namespace win32
} // namespace writer
} // namespace file
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief writes out data from a file on Windows Platform.
 */
class hryky::file::writer::win32::Entity :
	public WithStreamOut<Entity>,
	public WithSwap<Entity>,
	public WithIsNull<Entity>
{
public :

	typedef Entity this_type;

	/// default constructor.
	Entity();

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
	  @brief writes out data.
	 */
	size_t write(void const * const src, size_t const size);
	
	/// opens a file.
	bool open(path_type const & path);

	/// creates an instance with the path.
	Entity(path_type const & path);

	/// confirms whether this instance is regarded as null.
	bool is_null() const;

protected :

private :
	hryky_delete_copy_constructor(Entity);
	hryky_delete_copy_assign_op(Entity);

	typedef hryky::win32::Handle handle_type;

	/// saves the temporary data to the target file.
	void materialize();

	handle_type temp_handle_;
	path_type   path_;
	path_type   temp_path_;
	uint64_t    written_size_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace file
{
namespace writer
{
namespace win32
{
} // namespace win32
} // namespace writer
} // namespace file
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::file::writer::win32::Entity::write_to(StreamT & out) const
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
namespace writer
{
namespace win32
{
} // namespace win32
} // namespace writer
} // namespace file
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // FILE_WRITER_WIN32_ENTITY_H_20140705145954291
// end of file
