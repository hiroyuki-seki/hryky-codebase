/**
  @file         http_header_product_comment_dispatcher_apply.h
  @brief        applies the information of 'product' and 'comment' to
                arbitrary class which has 'apply' function.
  @author       HRYKY
  @version      $Id: http_header_product_comment_dispatcher_apply.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_PRODUCT_COMMENT_DISPATCHER_APPLY_H_20130113142642268
#define HTTP_HEADER_PRODUCT_COMMENT_DISPATCHER_APPLY_H_20130113142642268
#include "hryky/http/http_header_product_comment_dispatcher_base.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_virtual_destructor
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ReceiverT
#define hryky_template_arg \
	ReceiverT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace http
{
namespace header
{
namespace product_comment
{
namespace dispatcher
{
	/**
	  applies the information of 'product' and 'comment' to arbitrary class
	  which has 'apply' function.
	 */
	template <hryky_template_param>
	class Apply;

} // namespace dispatcher
} // namespace product_comment
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief applies the information of 'product' and 'comment' to arbitrary
    class which has 'apply' function.
 */
template <hryky_template_param>
class hryky::http::header::product_comment::dispatcher::Apply :
	public Base,
	public WithStreamOut<Apply<hryky_template_arg> >,
	public WithSwap<Apply<hryky_template_arg> >
{
public :

	/// base class of inheritance.
	typedef Base base_type;

	typedef Apply<hryky_template_arg> this_type;

	/// copy constructor.
	Apply(this_type const &);

	/// move constructor.
	Apply(this_type && rhs);

	/// constructor.
	Apply(ReceiverT & receiver);

	/// destructor.
	~Apply();

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

	hryky_delete_default_constructor(Apply);

	/// applies a 'product' value.
	virtual bool on_header_product(
		header::product_type & src);

	/// applies the 'comment' value.
	virtual bool on_header_comment_sequence(
		header::comment::sequence_type & src);

	ReceiverT & receiver_;

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
namespace product_comment
{
namespace dispatcher
{
} // namespace dispatcher
} // namespace product_comment
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::http::header::product_comment::dispatcher::Apply<hryky_template_arg>::
Apply(
	this_type const & rhs)
	: base_type(rhs)
	  , hryky_copy_member(receiver)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::http::header::product_comment::dispatcher::Apply<hryky_template_arg>::
Apply(
	this_type && rhs)
	: base_type(::std::move(rhs))
	  , hryky_move_member(receiver)
{
}
/**
  @brief constructor.
 */
template <hryky_template_param>
hryky::http::header::product_comment::dispatcher::Apply<hryky_template_arg>::
Apply(
	ReceiverT & receiver)
	: base_type()
	  , receiver_(receiver)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::http::header::product_comment::dispatcher::Apply<hryky_template_arg>::
~Apply()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void
hryky::http::header::product_comment::dispatcher::Apply<hryky_template_arg>::
clear()
{
	this->base_type::clear();
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & 
hryky::http::header::product_comment::dispatcher::Apply<hryky_template_arg>::
write_to(
	StreamT & out) const
{
	out << this->receiver_;
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void
hryky::http::header::product_comment::dispatcher::Apply<hryky_template_arg>::
swap(
	this_type & src)
{
	this->base_type::swap(src);
	hryky_swap_member(receiver);
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief applies a 'product' value.
 */
template <hryky_template_param>
bool
hryky::http::header::product_comment::dispatcher::Apply<hryky_template_arg>::
on_header_product(
	header::product_type & src)
{
	return this->receiver_.append(src);
}
/**
  @brief applies the 'comment' value.
 */
template <hryky_template_param>
bool
hryky::http::header::product_comment::dispatcher::Apply<hryky_template_arg>::
on_header_comment_sequence(
	header::comment::sequence_type & src)
{
	return this->receiver_.append(src);
}
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace http
{
namespace header
{
namespace product_comment
{
namespace dispatcher
{

} // namespace dispatcher
} // namespace product_comment
} // namespace header
} // namespace http
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
#endif // HTTP_HEADER_PRODUCT_COMMENT_DISPATCHER_APPLY_H_20130113142642268
// end of file

