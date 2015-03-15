/**
  @file     socket_family.h
  @brief    retains an address family.
  @author   HRYKY
  @version  $Id: socket_family.h 345 2014-04-06 09:44:45Z hryky.private@gmail.com $
 */
#ifndef SOCKET_FAMILY_H_20140223152626310
#define SOCKET_FAMILY_H_20140223152626310
#include "hryky/socket/socket_common.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/kind.h"
#include "hryky/literal_string.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace socket
{
	/// retains an address family.
	class Family;

} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains an address family.
 */
class hryky::socket::Family :
	public WithStreamOut<Family>,
	public WithSwap<Family>
{
public :

	typedef Family this_type;
	typedef int raw_type;

	struct Kind
	{
		enum Raw
		{
			unspec,
			inet,
			inet6,
			num,
		};
	};

	static LiteralString<> const tokens[Kind::num];
	
	typedef hryky::Kind<
		Kind, Kind::inet, Kind::num, LiteralString<>, tokens>
			kind_type;

	/// default constructor.
	Family();

	/// constrcts this instance with a value.
	explicit Family(Kind::Raw const kind);

	/// constructs this instance with a raw address family.
	explicit Family(raw_type const src);

	/// copy constructor.
	Family(this_type const &);

	/// move constructor.
	Family(this_type &&);

	/// destructor.
	~Family();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// assigns a new value.
	this_type & operator=(Kind::Raw const rhs);

	/// releases the internal resources.
	void clear();

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// retrieves the raw value of address family.
	raw_type raw() const;

protected :

private :

	kind_type kind_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace socket
{
} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::socket::Family::write_to(StreamT & out) const
{
	out << this->kind_;
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
namespace socket
{
} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // SOCKET_FAMILY_H_20140223152626310
// end of file
