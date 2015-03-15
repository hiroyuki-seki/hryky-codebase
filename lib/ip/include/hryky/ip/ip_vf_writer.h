/**
  @file         ip_vf_writer.h
  @brief        parses characters representing the future version of IP Address.
  @author       HRYKY
  @version      $Id: ip_vf_writer.h 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#ifndef IP_VF_WRITER_H_20120818191150466
#define IP_VF_WRITER_H_20120818191150466
#include "hryky/mempool/mempool_base.h"
#include "hryky/ip/ip_v4_writer.h"
#include "hryky/ip/ip_v6_writer.h"
#include "hryky/vector.h"
#include "hryky/kind.h"
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
	/// parses characters representing the future version of IP Address.
	class Writer;

} // namespace vf
} // namespace ip
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief parses characters representing the future version of IP Address.
 */
class hryky::ip::vf::Writer
{
public :

	typedef Writer this_type;
	typedef mempool_type mempool_type;

	/// default constructor.
	Writer();

	/// constructor.
	Writer(mempool_type mempool);

	/// copy constructor.
	Writer(this_type const & rhs);

	/// destructor.
	~Writer();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// retrieves the version of the representation of IP.
	uint32_t version() const;

	/// retrieves the representation of IPv4.
	v4::Entity const & ipv4() const;

	/// retrieves the representation of IPv6 Address.
	v6::Entity const & ipv6() const;

	/// appends a character and parses it.
	bool operator()(octet_type const octet);

	/// directs the completion of processing.
	bool complete();

	/// outputs the information formatted as string.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

private :

	struct State
	{
		enum Raw
		{
			begin_,
			begin_version_,
			version_,
			ipv4_,
			ipv6_,
			complete_,
		};
	};
	typedef Kind<State> state_type;
	typedef Vector<octet_type> buffer_type;

	buffer_type buffer_;
	v4::Writer  ipv4_writer_;
	v6::Writer  ipv6_writer_;
	state_type  state_;
	uint32_t    version_;

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
#endif // IP_VF_WRITER_H_20120818191150466
// end of file
