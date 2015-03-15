/**
  @file         http_header_product_comment_dispatcher_base.h
  @brief        dispatches the implementation of http::header::product_comment::Base.
  @author       HRYKY
  @version      $Id: http_header_product_comment_dispatcher_base.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_PRODUCT_COMMENT_DISPATCHER_BASE_H_20130112010817714
#define HTTP_HEADER_PRODUCT_COMMENT_DISPATCHER_BASE_H_20130112010817714
#include "hryky/http/http_header_product_entity.h"
#include "hryky/http/http_header_comment_sequence.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_virtual_destructor
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
namespace header
{
namespace product_comment
{
namespace dispatcher
{
	/// dispatches the implementation of http::header::product_comment::Base.
	class Base;

} // namespace dispatcher
} // namespace product_comment
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief dispatches the implementation of http::header::product_comment::Base.
 */
class hryky::http::header::product_comment::dispatcher::Base :
	private WithoutNew
{
public :

	typedef Base this_type;

	/// applies a 'product' value.
	bool operator()(header::product_type & src)
	{
		return this->on_header_product(src);
	};

	/// applies the 'comment' value.
	bool operator()(header::comment::sequence_type & src)
	{
		return this->on_header_comment_sequence(src);
	};

protected :

	/// default constructor.
	Base();

	/// copy constructor.
	Base(this_type const &);

	/// move constructor.
	Base(this_type && rhs);

	/// destructor.
	~Base();

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

private :

	/// applies a 'product' value.
	virtual bool on_header_product(header::product_type &)
	{
		return true;
	};

	/// applies the 'comment' value.
	virtual bool on_header_comment_sequence(
		header::comment::sequence_type &)
	{
		return true;
	};

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
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT & 
hryky::http::header::product_comment::dispatcher::Base::write_to(
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
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // HTTP_HEADER_PRODUCT_COMMENT_DISPATCHER_BASE_H_20130112010817714
// end of file
