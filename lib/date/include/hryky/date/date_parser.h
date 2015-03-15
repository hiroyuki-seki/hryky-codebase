/**
  @file     date_parser.h
  @brief    parses the representation of date.
  @author   HRYKY
  @version  $Id: date_parser.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef DATE_PARSER_H_20130812181015423
#define DATE_PARSER_H_20130812181015423
#include "hryky/parser.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_padded
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace date
{
	/// parses the representation of date.
	class Parser;

	class Entity;

namespace kmyacc
{
#include "hryky/date/date.y.h"
}
} // namespace date
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief parses the representation of date.
 */
class hryky::date::Parser :
	public hryky::parser::Base<
		hryky::date::kmyacc::Parser<hryky::date::Parser> >,
	public WithStreamOut<Parser>,
	public WithSwap<Parser>
{
public :

	typedef Parser this_type;
	typedef hryky::parser::Base<kmyacc::Parser<this_type> >
		base_type;
	typedef Entity entity_type;

	/// default constructor.
	Parser();

	/// constructor with a memory pool.
	Parser(mempool_type const mempool);

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

	/// assigns the destination to which the result is written.
	void entity(entity_type * const src);

protected :

private :

	entity_type * entity_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace date
{
} // namespace date
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::date::Parser::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	out << stream::denote("base") << static_cast<base_type const>(*this);

	hryky_write_pointer_member(entity);
	
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
namespace date
{
} // namespace date
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // DATE_PARSER_H_20130812181015423
// end of file
