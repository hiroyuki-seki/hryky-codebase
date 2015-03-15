/**
  @file         http_header_comment_base.h
  @brief        base class in order to retain octets and node
                composing hierarchical structure.
  @author       HRYKY
  @version      $Id: http_header_comment_base.h 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_COMMENT_BASE_H_20130109234523656
#define HTTP_HEADER_COMMENT_BASE_H_20130109234523656
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
namespace http
{
namespace header
{
namespace comment
{
	/// base class in order to retain octets and node composing hierarchical structure.
	class Base;

} // namespace comment

typedef comment::Base comment_type;

} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief base class in order to retain octets and node composing
    hierarchical structure.
 */
class hryky::http::header::comment::Base :
	public WithStreamOut<Base>,
	public WithSwap<Base>
{
public :

	typedef Base this_type;

	/// default constructor.
	Base();

	/// copy constructor.
	Base(this_type const &);

	/// move constructor.
	Base(this_type && rhs);

	/// destructor.
	virtual ~Base();

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
namespace http
{
namespace header
{
namespace comment
{
} // namespace comment
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
hryky::http::header::comment::Base::write_to(
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
namespace comment
{
} // namespace comment
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_COMMENT_BASE_H_20130109234523656
// end of file
