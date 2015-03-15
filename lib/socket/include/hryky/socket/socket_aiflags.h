/**
  @file     socket_aiflags.h
  @brief    retaints the combination of flags for getaddrinfo.
  @author   HRYKY
  @version  $Id: socket_aiflags.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef SOCKET_AIFLAGS_H_20140223165224369
#define SOCKET_AIFLAGS_H_20140223165224369
#include "hryky/flag.h"
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
	/// retaints the combination of flags for getaddrinfo.
	class Aiflags;

} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retaints the combination of flags for getaddrinfo.
 */
class hryky::socket::Aiflags :
	public WithStreamOut<Aiflags>,
	public WithSwap<Aiflags>
{
public :

	typedef Aiflags this_type;
	typedef int raw_type;

	struct Kind
	{
		enum Raw
		{
			passive,
			canonical_name,
			numeric_host,
			numeric_service,
			both_v4_v6,
			addr_config,
			map_v4_to_v6,
			num,
		};
	};

	static LiteralString<> const tokens[Kind::num];

	typedef hryky::Flag<
		Kind, Kind::num, LiteralString<>, tokens> flag_type;

	/// default constructor.
	Aiflags();

	/// constructs this instance with a raw ai_flags.
	explicit Aiflags(raw_type const src);

	/// copy constructor.
	Aiflags(this_type const &);

	/// move constructor.
	Aiflags(this_type &&);

	/// destructor.
	~Aiflags();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// enables a flag.
	Aiflags & operator|=(Kind::Raw const kind);

	/// disables a flag.
	Aiflags & operator^=(Kind::Raw const kind);

	/// releases the internal resources.
	void clear();

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// retrieves the raw value of ai_flags.
	raw_type raw() const;

protected :

private :

	flag_type flag_;

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
StreamT & hryky::socket::Aiflags::write_to(StreamT & out) const
{
	out << this->flag_;
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
#endif // SOCKET_AIFLAGS_H_20140223165224369
// end of file
