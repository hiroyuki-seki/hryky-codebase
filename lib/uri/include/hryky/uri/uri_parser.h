/**
  @file         uri_parser.h
  @brief        parses URI syntax.
  @author       HRYKY
  @version      $Id: uri_parser.h 360 2014-07-05 06:59:57Z hryky.private@gmail.com $
 */
#ifndef URI_PARSER_H_20130102144806283
#define URI_PARSER_H_20130102144806283
#include "hryky/parser.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/is_null.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace uri
{
	/// parses URI syntax.
	class Parser;

	typedef Parser parser_type;

	class Entity;

namespace kmyacc
{
#include "hryky/uri/uri.y.h"
}

} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief parses URI syntax.
 */
class hryky::uri::Parser :
	public parser::Base<kmyacc::Parser<Parser> >,
	public WithStreamOut<Parser>,
	public WithSwap<Parser>
{
public :

	
	typedef Parser this_type;
	typedef hryky::parser::Base<kmyacc::Parser<this_type> > base_type;
	typedef Entity entity_type;

	/// default constructor.
	Parser();

	/// constructor with a memory pool.
	Parser(mempool_type const mempool);

	/// move constructor.
	Parser(this_type && rhs);

	/// copy constructor.
	Parser(this_type const &);

	/// destructor.
	~Parser();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/**
	  @brief        parses an array of characters as a part of URI.
	  @param        octets is the array of parsed characters.
	  @return       the number of the parsed units.
	 */
	template <size_t Size>
	size_t operator()(octet_type const (&octets)[Size]);
	
	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// assigns the destination to which the result is written.
	void entity(entity_type * src);

protected :

private :

	entity_type * entity_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace uri
{
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief    parses an array of characters as a part of URI.
  @param    octets is the array of parsed characters.
  @return   the number of the parsed units.
 */
template <size_t Size>
hryky::size_t hryky::uri::Parser::operator()(octet_type const (&octets)[Size])
{
	return (
		2 > Size ? 0 :
		this->parse(Range<octet_type const *>(&octets[0], &octets[Size - 1])));
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::uri::Parser::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << static_cast<base_type const>(*this);


	if (!hryky_is_null(this->entity_)) {
		out << stream::denote("URI") << *this->entity_;
	}
	
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
namespace uri
{
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // URI_PARSER_H_20130102144806283
// end of file
