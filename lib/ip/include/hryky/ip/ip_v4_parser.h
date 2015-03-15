/**
  @file     ip_v4_parser.h
  @brief    parses characters representing an IPv4 Address.
  @author   HRYKY
  @version  $Id: ip_v4_parser.h 328 2014-02-24 02:40:42Z hryky.private@gmail.com $
 */
#ifndef IP_V4_PARSER_H_20130813090547045
#define IP_V4_PARSER_H_20130813090547045
#include "hryky/parser.h"
#include "hryky/vector.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/parser/parser_base.h"
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
namespace v4
{
	/// parses characters representing an IPv4 Address.
	class Parser;

	typedef Parser parser_type;

namespace kmyacc
{
#include "hryky/ip/ip_v4.y.h"
}

} // namespace v4
} // namespace ip
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief parses characters representing an IPv4 Address.
 */
class hryky::ip::v4::Parser :
	public hryky::parser::Base<
		hryky::ip::v4::kmyacc::Parser<hryky::ip::v4::Parser> >,
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
namespace v4
{
} // namespace v4
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
hryky::ip::v4::Parser::write_to(
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
namespace ip
{
namespace v4
{
} // namespace v4
} // namespace ip
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // IP_V4_PARSER_H_20130813090547045
// end of file
