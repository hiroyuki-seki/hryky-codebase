/**
  @file         ip_vf_entity.h
  @brief        retains the information about IP Address of future version.
  @author       HRYKY
  @version      $Id: ip_vf_entity.h 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#ifndef IP_VF_ENTITY_H_20130104101501093
#define IP_VF_ENTITY_H_20130104101501093
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
namespace ip
{
namespace vf
{
	/// retains the information about IP Address of future version.
	class Entity;

} // namespace vf

typedef vf::Entity vf_type;

} // namespace ip
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information about IP Address of future version.
 */
class hryky::ip::vf::Entity :
	public WithStreamOut<Entity>,
	public WithSwap<Entity>
{
public :

	typedef Entity              this_type;
	typedef mempool_type           mempool_type;
	typedef uint32_t            major_type;
	typedef Vector<octet_type>  minor_type;

	/// default constructor.
	Entity();

	/// copy constructor.
	Entity(this_type const &);

	/// move constructor.
	Entity(this_type && rhs);

	/// constructor.
	Entity(mempool_type const mempool);

	/// constructor with a major version and a minor version.
	Entity(major_type const major, minor_type const & minor);

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

protected :

private :

	major_type major_;
	minor_type minor_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace ip
{
namespace vf
{
} // namespace vf
} // namespace ip
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::ip::vf::Entity::write_to(
	StreamT & out) const
{
	out << this->minor_;
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
namespace ip
{
namespace vf
{
} // namespace vf
} // namespace ip
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // IP_VF_ENTITY_H_20130104101501093
// end of file
