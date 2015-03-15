/**
  @file     ip_v6_parser.h
  @brief    parses characters representing an IPv6 Address.
  @author   HRYKY
  @version  $Id: ip_v6_parser.h 328 2014-02-24 02:40:42Z hryky.private@gmail.com $
 */
#ifndef IP_V6_PARSER_H_20130813090353044
#define IP_V6_PARSER_H_20130813090353044
#include "hryky/parser/parser_base.h"
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
namespace ip
{
namespace v6
{
	/// parses characters representing an IPv6 Address.
	class Parser;

	typedef Parser parser_type;

namespace kmyacc
{
#include "hryky/ip/ip_v6.y.h"
}

} // namespace v6
} // namespace ip
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief parses characters representing an IPv6 Address.
 */
class hryky::ip::v6::Parser :
	public hryky::parser::Base<
		hryky::ip::v6::kmyacc::Parser<hryky::ip::v6::Parser> >,
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
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::ip::v6::Parser::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
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
#endif // IP_V6_PARSER_H_20130813090353044
// end of file
