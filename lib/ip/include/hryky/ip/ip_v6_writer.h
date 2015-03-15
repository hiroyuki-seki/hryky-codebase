/**
  @file         ip_v6_writer.h
  @brief        parses characters representing IPv6.
  @author       HRYKY
  @version      $Id: ip_v6_writer.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef IP_V6_WRITER_H_20120817141342259
#define IP_V6_WRITER_H_20120817141342259
#include "hryky/fixed_vector.h"
#include "hryky/ip/ip_v6_entity.h"
#include "hryky/ip/ip_v6_common.h"
#include "hryky/ip/ip_v4_writer.h"
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
namespace v6
{
	/// parses characters representing IPv6.
	class Writer;

} // namespace v6
} // namespace ip
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief parses characters representing IPv6.
 */
class hryky::ip::v6::Writer
{
public :

	typedef Writer this_type;

	/// default constructor.
	Writer();

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

	/// retrieves the result of parsing IPv6 Address.
	Entity const & result() const;

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
			segment_,
			delimiter_,
			complete_,
			ipv4_,
		};
	};
	typedef hryky::Kind<State> state_type;

	typedef FixedVector<segment_type, g_segments_size>          segments_type;
	typedef FixedVector<octet_type, sizeof(segment_type) * 8>   buffer_type;

	/// parses a character in State::segment_.
	bool parse_segment(octet_type const octet);

	/// parses a character in State::delimiter_.
	bool parse_delimiter(octet_type const octet);

	/// parses a character in State::ipv4_.
	bool parse_ipv4(octet_type const octet);

	/// finishes the processing in State::segment_.
	bool complete_segment();

	/// finishes the processing in State::ipv4_.
	bool complete_ipv4();

	/// extructs a hex-digits from the internal buffer.
	bool flush_segment();

	/// applies the segments to the entity.
	bool update_entity();

	Entity          entity_;
	v4::Writer      ipv4_writer_;
	segments_type   segments_;
	buffer_type     buffer_;
	state_type      state_;
	uint8_t         rank_;
	uint8_t         shorten_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace ip
{
namespace v6
{
} // namespace v6
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
namespace v6
{
} // namespace v6
} // namespace ip
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // IP_V6_WRITER_H_20120817141342259
// end of file
