/**
  @file     path_entity.h
  @brief    represents a path of filesystem.
  @author   HRYKY
  @version  $Id: path_entity.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef PATH_ENTITY_H_20140705161324342
#define PATH_ENTITY_H_20140705161324342
#include "hryky/config.h"
#include "hryky/with_swap.h"
#include "hryky/with_stream_out.h"
#if HRYKY_PLATFORM_WINDOWS
#   include "hryky/path/path_win32_entity.h"
#endif
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
	/// represents a path of filesystem.
	class Entity;

} // namespace path
typedef path::Entity path_type;


} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief represents a path of filesystem.
 */
class hryky::path::Entity :
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

	/// creates an instance with memory pool.
	Entity(mempool::Ptr const & mempool);

	/// creates a path from a null-terminated character encoded by UTF-8.
	Entity(
		char const * const c_str,
		mempool::Ptr const & mempool = mempool::Ptr());

	/// creates a path from a null-terminated widt character.
	Entity(
		wchar_t const * const c_str,
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

	/// appends components by operator.
	this_type & operator<<(char const * const c_str);

	/// creates a new path to which a component is appended.
	this_type operator+(char const * const c_str) const;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// appends components.
	bool append(char const * const c_str);

	/// confirms whether the path exists.
	bool exists() const;

	/// creates a directory.
	bool mkdir() const;

	/// removes the component described by this path.
	bool rm() const;

	/// retrieves the platform-specific implementation as immutable.
	impl_type const & impl() const;

	/// retrieves the representation of path as null-terminated character.
	char const * c_str() const;

protected :

private :

	impl_type impl_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace path
{
} // namespace path
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::path::Entity::write_to(StreamT & out) const
{
	return this->impl_.write_to(out);
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
} // namespace path
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // PATH_ENTITY_H_20140705161324342
// end of file
