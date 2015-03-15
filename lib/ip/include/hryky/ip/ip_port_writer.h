/**
  @file         ip_port_writer.h
  @brief        parses characters representing a port number of TCP/IP.
  @author       HRYKY
  @version      $Id: ip_port_writer.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef IP_PORT_WRITER_H_20120818195407495
#define IP_PORT_WRITER_H_20120818195407495
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
namespace port
{
	/// parses characters representing a port number of TCP/IP.
	class Writer;

} // namespace port
} // namespace ip
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief parses characters representing a port number of TCP/IP.
 */
class hryky::ip::port::Writer
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

	/// retrieves the port number.
	uint16_t result() const;

	/// confirms whether reading a port number is complete correctly.
	bool complete();

	/// appends a character and parses it.
	bool operator()(octet_type const octet);

	/// create the information formatted as string.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

private :

	uint16_t    port_;
	bool        read_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace ip
{
namespace port
{
} // namespace port
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
namespace port
{
} // namespace port
} // namespace ip
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // IP_PORT_WRITER_H_20120818195407495
// end of file
