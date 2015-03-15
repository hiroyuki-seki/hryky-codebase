/**
  @file         parser_base.h
  @brief        base class for parsing syntax.
  @author       HRYKY
  @version      $Id: parser_base.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef PARSER_BASE_H_20130103094805075
#define PARSER_BASE_H_20130103094805075
#include "hryky/any.h"
#include "hryky/ascii.h"
#include "hryky/log/log_definition.h"
#include "hryky/mempool/mempool_base.h"
#include "hryky/mempool/mempool_ptr.h"
#include "hryky/pragma.h"
#include "hryky/range.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/without_new.h"
#include "hryky/without_placement_new.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_padded
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename GeneratedT
#define hryky_template_arg \
	GeneratedT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace parser
{
	/// base class for parsing syntax.
	template <hryky_template_param>
	class Base;

} // namespace parser
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief base class for parsing syntax.
 */
template <hryky_template_param>
class hryky::parser::Base :
	public GeneratedT,
	public WithStreamOut<Base<hryky_template_arg> >,
	public WithSwap<Base<hryky_template_arg> >,
	private WithoutNew,
	private WithoutPlacementNew
{
public :

	typedef GeneratedT base_type;
	typedef Base this_type;
	typedef mempool_type mempool_type;

	/// default constructor.
	Base();

	/// constructor.
	Base(mempool_type const mempool);

	/// copy constructor.
	Base(this_type const &);

	/// move constructor.
	Base(this_type && rhs);

	/**
	  destructor.
	  @attention
	  - The destructor is not virtual, because this class is not intended
	    for using polymorphism.
	 */
	~Base();

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

	/// retrieves the memory pool.
	mempool_type mempool() const;

	/// outputs an information about error.
	void trace(typename base_type::error_type const & error);

protected :

private :

	mempool::Ptr mempool_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace parser
{
} // namespace parser
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::parser::Base<hryky_template_arg>::Base()
	: base_type()
	  , mempool_()
{
	this->is_trace(true);
}
/**
  @brief constructor.
 */
template <hryky_template_param>
hryky::parser::Base<hryky_template_arg>::Base(mempool_type const mempool)
	: base_type()
	  , mempool_(mempool)
{
	this->is_trace(true);
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::parser::Base<hryky_template_arg>::Base(this_type const & rhs)
	: base_type(rhs)
	  , hryky_copy_member(mempool)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::parser::Base<hryky_template_arg>::Base(this_type && rhs)
	: base_type(::std::move(rhs))
	  , hryky_move_member(mempool)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::parser::Base<hryky_template_arg>::~Base()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::parser::Base<hryky_template_arg>::clear()
{
	this->base_type::clear();
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::parser::Base<hryky_template_arg>::write_to(
	StreamT & out) const
{
	switch (this->last_result()) {
	case Result::accept:
		out << "accept";
		break;
	case Result::abort:
		out << "abort";
		break;
	case Result::pause:
		out << "pause";
		break;
	default:
		out << "invlaid";
		break;
	}
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::parser::Base<hryky_template_arg>::swap(this_type & src)
{
	this->base_type::swap(src);
	hryky_swap_member(mempool);
}
/**
  @brief retrieves the memory pool.
 */
template <hryky_template_param>
hryky::mempool_type
hryky::parser::Base<hryky_template_arg>::mempool() const
{
	return this->mempool_.get();
}
/**
  @brief outputs an information about error.
 */
template <hryky_template_param>
void hryky::parser::Base<hryky_template_arg>::trace(
	typename base_type::error_type const & error)
{
	switch (error.level()) {
	case Error::Level::debug:
		hryky_log_debug(error.cstr());
		break;
		
	case Error::Level::error:
		hryky_log_debug(error.cstr());
		break;

	default:
		hryky_log_debug("invalid error level");
		break;
	}
}
/**
  @brief        parses an array of characters as a part of URI.
  @param        octets is the array of parsed characters.
  @return       the number of the parsed units.
 */
template <hryky_template_param>
template <size_t Size>
hryky::size_t hryky::parser::Base<hryky_template_arg>::operator()(
	octet_type const (&octets)[Size])
{
	return (
		2 > Size ? 0 :
		this->parse(Range<octet_type const *>(&octets[0], &octets[Size - 1])));
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
namespace parser
{

} // namespace parser
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // PARSER_BASE_H_20130103094805075
// end of file
