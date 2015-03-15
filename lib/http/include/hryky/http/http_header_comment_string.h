/**
  @file         http_header_comment_string.h
  @brief        retains the octets as constituent of comment hierarchy.
  @author       HRYKY
  @version      $Id: http_header_comment_string.h 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_COMMENT_STRING_H_20130109235057660
#define HTTP_HEADER_COMMENT_STRING_H_20130109235057660
#include "hryky/vector.h"
#include "hryky/mempool/mempool_base.h"
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
namespace http
{
namespace header
{
namespace comment
{
	/// retains the octets as constituent of comment hierarchy.
	class String;

	typedef String string_type;

} // namespace comment
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the octets as constituent of comment hierarchy.
 */
class hryky::http::header::comment::String :
	public WithStreamOut<String>,
	public WithSwap<String>
{
public :

	typedef String this_type;

	/// default constructor.
	String();

	/// copy constructor.
	String(this_type const &);

	/// move constructor.
	String(this_type && rhs);

	/// constructor.
	String(mempool_type const mempool);

	/// destructor.
	~String();

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

	/// appends an octet to the end of string.
	bool push_back(octet_type const octet);

protected :

private :

	typedef Vector<octet_type> octets_type;

	octets_type octets_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace http
{
namespace header
{
namespace comment
{
} // namespace comment
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::http::header::comment::String::write_to(
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
namespace http
{
namespace header
{
namespace comment
{
} // namespace comment
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_COMMENT_STRING_H_20130109235057660
// end of file
