/**
  @file     path_win32_entity.h
  @brief    represents a path of filesystem on Windows Platform.
  @author   HRYKY
  @version  $Id: path_win32_entity.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef PATH_WIN32_ENTITY_H_20140705161654345
#define PATH_WIN32_ENTITY_H_20140705161654345
#include "hryky/definition.h"
#include "hryky/string.h"
#include "hryky/vector.h"
#include "hryky/literal_string.h"
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
namespace path
{
namespace win32
{
	/// represents a path of filesystem on Windows Platform.
	class Entity;

} // namespace win32
} // namespace path
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief represents a path of filesystem on Windows Platform.
 */
class hryky::path::win32::Entity :
	public WithStreamOut<Entity>,
	public WithSwap<Entity>
{
public :

	typedef Entity this_type;
	typedef String<> string_type;

	/// default constructor.
	Entity();

	/// creates an instance with memory pool.
	Entity(mempool::Ptr const & mempool);

	/// creates an instance from a null-terminated characters.
	Entity(
		char const * const c_str,
		mempool::Ptr const & mempool = mempool::Ptr());

	/// copy constructor.
	Entity(this_type const &);

	/// move constructor.
	Entity(this_type &&);

	/// destructor.
	~Entity();

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

	/// appends components.
	bool append(char const * const c_str);

	/// retrieves the absolute path.
	string_type const & absolute() const;

	/// confirms whether the path exists.
	bool exists() const;

	/// creates a directory.
	bool mkdir() const;

	/// removes the component described by this path.
	bool rm() const;

	/// retrieves the memory pool.
	mempool_type mempool() const;

	/// retrieves the representation of path as null-terminated character.
	char const * c_str() const;

protected :

private :
	typedef string_type::size_type  size_type;
	typedef string_type             server_type;
	typedef string_type             component_type;
	typedef Vector<component_type>  components_type;
	typedef string_type::value_type drive_type;

	/// configures resources.
	bool reset(char const * const c_str);

	server_type         server_;
	components_type     components_;
	mutable string_type absolute_;
	mutable bool        cached_absolute_;
	drive_type          drive_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace path
{
namespace win32
{
} // namespace win32
} // namespace path
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::path::win32::Entity::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << "absolute" << this->absolute();
	hryky_write_member(server);
	if (0 != this->drive_) {
		hryky_write_member(drive);
	}
	hryky_write_member(components);
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
namespace path
{
namespace win32
{
} // namespace win32
} // namespace path
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // PATH_WIN32_ENTITY_H_20140705161654345
// end of file
