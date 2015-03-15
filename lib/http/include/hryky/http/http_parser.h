/**
  @file         http_parser.h
  @brief        writes out a HTTP Message.
  @author       HRYKY
  @version      $Id: http_parser.h 360 2014-07-05 06:59:57Z hryky.private@gmail.com $
 */
#ifndef HTTP_PARSER_H_20121126101051090
#define HTTP_PARSER_H_20121126101051090
#include "hryky/http/http_header_parser.h"
#include "hryky/http/http_entity.h"
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
	/// writes out a HTTP Message.
	class Parser;

	typedef Parser parser_type;

} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief writes out a HTTP Message.
 */
class hryky::http::Parser :
	public WithStreamOut<Parser>,
	public WithSwap<Parser>
{
public :

	typedef Parser this_type;
	typedef Entity entity_type;

	/// default constructor.
	Parser();

	/// constructor.
	Parser(mempool_type const mempool);

	/// copy constructor.
	Parser(this_type const &);

	/// move constructor.
	Parser(this_type && rhs);

	/// destructor.
	~Parser();

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

	/**
	  parses a range between two iterators.
	  @param begin is the beginning of the range.
	  @param end is the end of the range.
	  @return the number of the parsed token_ids.
	 */
	template <typename InputIteratorT>
	size_t parse(InputIteratorT begin, InputIteratorT end);
	
	/**
	  @brief        parses an array of characters as a part of HTTP Message.
	  @param        octets is the array of parsed characters.
	  @return       the number of the parsed units.
		 */
	template <size_t Size>
	size_t parse(octet_type const (&octets)[Size]);
	
	/// assignes the destination to be written the HTTP Message.
	void entity(entity_type * src);

	/// confirms the HTTP Message is parsed completely.
	bool accepted() const;

	/// finishes the parsing.
	bool complete();

	/// confirms whether the parsing is failed.
	bool fail() const;

protected :

private :

	header::parser_type header_parser_;
	Entity * entity_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace http
{
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief    parses an array of characters as a part of HTTP Message.
  @param    octets is the array of parsed characters.
  @return   the number of the parsed units.
 */
template <size_t Size>
hryky::size_t hryky::http::Parser::parse(octet_type const (&octets)[Size])
{
	return this->header_parser_.parse(octets);
}
/**
  parses a range between two iterators.
  @param begin is the beginning of the range.
  @param end is the end of the range.
  @return the number of the parsed token_ids.
 */
template <typename InputIteratorT>
hryky::size_t
hryky::http::Parser::parse(InputIteratorT begin, InputIteratorT end)
{
	return static_cast<size_t>(
		this->header_parser_.parse(begin, end));
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::http::Parser::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(header_parser);

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
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_PARSER_H_20121126101051090
// end of file
