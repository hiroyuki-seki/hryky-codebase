/**
  @file         indent.h
  @brief        indents as string.
  @author       HRYKY
  @version      $Id: indent.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef INDENT_H_20120103174406405
#define INDENT_H_20120103174406405
#include "hryky/clear.h"
#include "hryky/common.h"
#include "hryky/definition.h"
#include "hryky/literal_string.h"
#include "hryky/repeat.h"
#include "hryky/stdint.h"
#include "hryky/swap.h"
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
#define hryky_template_param \
	hryky::LiteralString<> const * Word
#define hryky_template_arg \
	Word
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace detail
{
	extern LiteralString<> const g_default_indent_word;
} // namespace detail
	
	/// indents a line of log
	template <
		LiteralString<> const * Word = &detail::g_default_indent_word
	>
	class Indent;
	
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief indents a line of log.
 */
template <hryky_template_param>
class hryky::Indent :
	public WithStreamOut<Indent<hryky_template_arg> >,
	public WithSwap<Indent<hryky_template_arg> >
{
public :

	typedef Indent<hryky_template_arg> this_type;
	typedef size_t depth_type;

	/// default constructor.
	Indent();

	/// copy constructor.
	Indent(this_type const & rhs);

	/// move constructor.
	Indent(this_type && rhs);

	/// constructor with the depth of indent.
	explicit Indent(depth_type depth);

	/// destructor.
	~Indent();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// pre-increments the depth of indent.
	Indent & operator++();

	/// pre-decrement the depth of indent.
	Indent & operator--();

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// retrieves the depth of this indent.
	depth_type depth() const;

	/// outputs the information of Indent.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

private :

	depth_type      depth_;///< depth of indent

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief constructor.
 */
template <hryky_template_param>
hryky::Indent<hryky_template_arg>::Indent()
	: depth_()
{
}
/**
  @brief constructor with the depth of indent.
 */
template <hryky_template_param>
hryky::Indent<hryky_template_arg>::Indent(
	depth_type depth)
	: depth_(depth)
{
	return;
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::Indent<hryky_template_arg>::Indent(
	this_type const & rhs)
	: hryky_copy_member(depth)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::Indent<hryky_template_arg>::Indent(
	this_type && rhs)
	: hryky_move_member(depth)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::Indent<hryky_template_arg>::~Indent()
{
}
/**
  @brief pre-increments the depth of indent.
 */
template <hryky_template_param>
hryky::Indent<hryky_template_arg> &
hryky::Indent<hryky_template_arg>::operator++()
{
	++this->depth_;
	return *this;
}
/**
  @brief pre-decrement the depth of indent.
 */
template <hryky_template_param>
hryky::Indent<hryky_template_arg> &
hryky::Indent<hryky_template_arg>::operator--()
{
	if (0 == this->depth_) {
		return *this;
	}
	--this->depth_;
	return *this;
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::Indent<hryky_template_arg>::clear()
{
	hryky::clear(this->depth_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::Indent<hryky_template_arg>::swap(
	this_type & src)
{
	hryky_swap_member(depth);
}
/**
  @brief retrieves the depth of this indent.
 */
template <hryky_template_param>
typename hryky::Indent<hryky_template_arg>::depth_type
hryky::Indent<hryky_template_arg>::depth() const
{
	return this->depth_;
}
/**
  @brief outputs the information of Indent.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::Indent<hryky_template_arg>::write_to(
	StreamT & out) const
{
	if (0 == this->depth_) {
		return out;
	}
	
	hryky::repeat(this->depth_).foreach([&out]() {
		out << *Word;
	});

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
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // INDENT_H_20120103174406405
// end of file
