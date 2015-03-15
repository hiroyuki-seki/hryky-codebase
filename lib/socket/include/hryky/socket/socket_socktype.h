/**
  @file     socket_socktype.h
  @brief    retains a socket type. e.g. stream or datagram.
  @author   HRYKY
  @version  $Id: socket_socktype.h 345 2014-04-06 09:44:45Z hryky.private@gmail.com $
 */
#ifndef SOCKET_SOCKTYPE_H_20140223154907325
#define SOCKET_SOCKTYPE_H_20140223154907325
#include "hryky/kind.h"
#include "hryky/literal_string.h"
#include "hryky/socket/socket_common.h"
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
namespace socket
{
	/// retains a socket type. e.g. stream or datagram.
	class Socktype;

} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains a socket type. e.g. stream or datagram.
 */
class hryky::socket::Socktype :
	public WithStreamOut<Socktype>,
	public WithSwap<Socktype>
{
public :

	typedef Socktype this_type;
	typedef int raw_type;

	struct Kind
	{
		enum Raw
		{
			any,
			stream,
			dgram,
			num,
		};
	};

	static LiteralString<> const tokens[Kind::num];

	typedef hryky::Kind<
		Kind, Kind::stream, Kind::num, LiteralString<>, tokens>
			kind_type;

	/// default constructor.
	Socktype();

	/// constructs this instance with a value.
	explicit Socktype(Kind::Raw const kind);

	/// constructs this instance with a raw socket type.
	explicit Socktype(raw_type const src);

	/// copy constructor.
	Socktype(this_type const &);

	/// move constructor.
	Socktype(this_type &&);

	/// destructor.
	~Socktype();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// assigns a new kind.
	this_type & operator=(Kind::Raw const src);

	/// releases the internal resources.
	void clear();

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// retrieves the raw value of socket type.
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
StreamT & hryky::socket::Socktype::write_to(StreamT & out) const
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
#endif // SOCKET_SOCKTYPE_H_20140223154907325
// end of file
