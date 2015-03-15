/**
  @file     ip_vf_parser.h
  @brief    parses characters representing a future IP Address.
  @author   HRYKY
  @version  $Id: ip_vf_parser.h 328 2014-02-24 02:40:42Z hryky.private@gmail.com $
 */
#ifndef IP_VF_PARSER_H_20130813103910110
#define IP_VF_PARSER_H_20130813103910110
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
namespace vf
{
	/// parses characters representing a future IP Address.
	class Parser;

namespace kmyacc
{
#include "hryky/ip/ip_vf.y.h"
}

} // namespace vf
} // namespace ip
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief parses characters representing a future IP Address.
 */
class hryky::ip::vf::Parser :
	public hryky::parser::Base<
		hryky::ip::vf::kmyacc::Parser<hryky::ip::vf::Parser> >,
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
namespace vf
{
} // namespace vf
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
hryky::ip::vf::Parser::write_to(
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
namespace vf
{
} // namespace vf
} // namespace ip
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // IP_VF_PARSER_H_20130813103910110
// end of file
