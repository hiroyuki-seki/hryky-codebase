/**
  @file     uri_authority_parser.h
  @brief    parses characters representing the authority part of URI.
  @author   HRYKY
  @version  $Id: uri_authority_parser.h 333 2014-03-10 00:32:43Z hryky.private@gmail.com $
 */
#ifndef URI_AUTHORITY_PARSER_H_20130813113219147
#define URI_AUTHORITY_PARSER_H_20130813113219147
#include "hryky/parser.h"
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
namespace uri
{
namespace authority
{
	/// parses characters representing the authority part of URI.
	class Parser;

namespace kmyacc
{
#include "hryky/uri/uri_authority.y.h"
}

} // namespace authority
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief parses characters representing the authority part of URI.
 */
class hryky::uri::authority::Parser :
	public parser::Base<kmyacc::Parser<Parser> >,
	public WithStreamOut<Parser>,
	public WithSwap<Parser>
{
public :

	typedef Parser this_type;
	typedef hryky::parser::Base<kmyacc::Parser<this_type> > base_type;

	/// default constructor.
	Parser();

	/// copy constructor.
	Parser(this_type const &);

	/// move constructor.
	Parser(this_type &&);

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

protected :

private :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace uri
{
namespace authority
{
} // namespace authority
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::uri::authority::Parser::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << static_cast<base_type const>(*this);
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
namespace authority
{
} // namespace authority
} // namespace uri
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // URI_AUTHORITY_PARSER_H_20130813113219147
// end of file
