/**
  @file     socket_protocol.h
  @brief    retains a protocol. e.g. TCP or UDP.
  @author   HRYKY
  @version  $Id: socket_protocol.h 345 2014-04-06 09:44:45Z hryky.private@gmail.com $
 */
#ifndef SOCKET_PROTOCOL_H_20140223155854332
#define SOCKET_PROTOCOL_H_20140223155854332
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
	/// retains a protocol. e.g. TCP or UDP.
	class Protocol;

} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains a protocol. e.g. TCP or UDP.
 */
class hryky::socket::Protocol :
	public WithStreamOut<Protocol>,
	public WithSwap<Protocol>
{
public :

	typedef Protocol this_type;
	typedef int raw_type;

	struct Kind
	{
		enum Raw
		{
			any,
			tcp,
			udp,
			num,
		};
	};

	static LiteralString<> const tokens[Kind::num];

	typedef hryky::Kind<
		Kind, Kind::tcp, Kind::num, LiteralString<>, tokens>
			kind_type;

	/// default constructor.
	Protocol();

	/// constructs this instance with a value.
	explicit Protocol(Kind::Raw const kind);

	/// constructs this instance with a raw protocol.
	explicit Protocol(raw_type const src);

	/// copy constructor.
	Protocol(this_type const &);

	/// move constructor.
	Protocol(this_type &&);

	/// destructor.
	~Protocol();

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

	/// retrieves the raw value of protocol.
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
StreamT & hryky::socket::Protocol::write_to(StreamT & out) const
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
#endif // SOCKET_PROTOCOL_H_20140223155854332
// end of file
