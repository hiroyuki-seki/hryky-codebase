/**
  @file         uri_userinfo_entity.h
  @brief        retains the information about the 'userinfo' of URI.
  @author       HRYKY
  @version      $Id: uri_userinfo_entity.h 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#ifndef URI_USERINFO_ENTITY_H_20130104080451003
#define URI_USERINFO_ENTITY_H_20130104080451003
#include "hryky/mempool/mempool_base.h"
#include "hryky/vector.h"
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
namespace uri
{
namespace userinfo
{
	/// retains the information about the 'userinfo' of URI.
	class Entity;

} // namespace userinfo

typedef userinfo::Entity userinfo_type;

} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information about the 'userinfo' of URI.
 */
class hryky::uri::userinfo::Entity :
	public WithStreamOut<Entity>,
	public WithSwap<Entity>
{
public :

	typedef Entity this_type;
	typedef mempool_type mempool_type;
	typedef Vector<octet_type> octets_type;

	/// default constructor.
	Entity();

	/// copy constructor.
	Entity(this_type const &);

	/// move constructor.
	Entity(this_type && rhs);

	/// constructor.
	Entity(mempool_type const mempool);

	/// constructor with octets.
	Entity(octets_type const & octets);

	/// destructor.
	~Entity();

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

	/// appends the range of octets to the end of this userinfo.
	template <typename InputIteratorT>
	bool append(InputIteratorT begin, InputIteratorT end);

protected :

private :

	octets_type octets_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace uri
{
namespace userinfo
{
} // namespace userinfo
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief appends the range of octets to the end of this userinfo.
 */
template <typename InputIteratorT>
bool hryky::uri::userinfo::Entity::append(
	InputIteratorT begin, InputIteratorT end)
{
	return this->octets_.insert(this->octets_.end(), begin, end);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::uri::userinfo::Entity::write_to(
	StreamT & out) const
{
	out << this->octets_;
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
namespace uri
{
namespace userinfo
{
} // namespace userinfo
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // URI_USERINFO_ENTITY_H_20130104080451003
// end of file
