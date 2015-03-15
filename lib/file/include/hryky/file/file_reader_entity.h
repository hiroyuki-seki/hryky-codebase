/**
  @file     file_reader_entity.h
  @brief    reads out data from a file.
  @author   HRYKY
  @version  $Id: file_reader_entity.h 363 2014-07-10 10:46:29Z hryky.private@gmail.com $
 */
#ifndef FILE_READER_ENTITY_H_20140705144040278
#define FILE_READER_ENTITY_H_20140705144040278
#include "hryky/config.h"
#include "hryky/stdint.h"
#include "hryky/path.h"
#include "hryky/with_is_null.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#if HRYKY_PLATFORM_WINDOWS
#   include "hryky/file/file_reader_win32_entity.h"
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
namespace reader
{
	/// reads out data from a file.
	class Entity;

} // namespace reader
typedef reader::Entity reader_type;

} // namespace file
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief reads out data from a file.
 */
class hryky::file::reader::Entity :
	public WithIsNull<Entity>,
	public WithStreamOut<Entity>,
	public WithSwap<Entity>
{
public :

	typedef Entity this_type;
#if HRYKY_PLATFORM_WINDOWS
	typedef win32::Entity impl_type;
#endif

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

	/// retrieves the platform-specific implementation.
	impl_type & impl();

	/// retrieves the platform-specific implementation as immutable.
	impl_type const & impl() const;

	/// reads out data from file.
	size_t read(void * const dest, size_t const size);

	/// confirms whether this instance is regarded as null.
	bool is_null() const;

protected :

private :
	hryky_delete_copy_constructor(Entity);
	hryky_delete_copy_assign_op(Entity);

	impl_type impl_;

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
StreamT & hryky::file::reader::Entity::write_to(StreamT & out) const
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
namespace reader
{
} // namespace reader
} // namespace file
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // FILE_READER_ENTITY_H_20140705144040278
// end of file
