/**
  @file         http_header_comment_sequence.h
  @brief        retains the array of http::header::comment::Base components.
  @author       HRYKY
  @version      $Id: http_header_comment_sequence.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_COMMENT_SEQUENCE_H_20130109235502663
#define HTTP_HEADER_COMMENT_SEQUENCE_H_20130109235502663
#include "hryky/allocator/allocator_instantiate.h"
#include "hryky/http/http_header_comment_base.h"
#include "hryky/mempool/mempool_base.h"
#include "hryky/shared_ptr.h"
#include "hryky/vector.h"
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
	/// retains the array of http::header::comment::Base components.
	class Sequence;

	typedef Sequence sequence_type;

} // namespace comment
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the array of http::header::comment::Base components.
 */
class hryky::http::header::comment::Sequence :
	public WithStreamOut<Sequence>,
	public WithSwap<Sequence>
{
public :

	typedef Sequence this_type;
	typedef SharedPtr<comment::Base, Null> component_type;

	/// default constructor.
	Sequence();

	/// copy constructor.
	Sequence(this_type const &);

	/// move constructor.
	Sequence(this_type && rhs);

	/// constructor.
	Sequence(mempool_type const mempool);

	/// destructor.
	~Sequence();

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

	/// appends a constituent of the array of http::header::comment_type.
	bool append(component_type const & src);

	/// appends a comment::Sequence as a child.
	template <typename ClientT>
	bool append(ClientT const & src);

protected :

private :

	typedef Vector<component_type> components_type;

	components_type components_;

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
  @brief appends a comment::Sequence as a child.
 */
template <typename ClientT>
bool hryky::http::header::comment::Sequence::append(
	ClientT const & src)
{
	typedef components_type::allocator_type allocator_type;

	typename allocator_type::template rebind<comment::Adapter<ClientT> >::other
		adapter_allocator(this->components_.get_allocator());
	
	return this->append(
		component_type(
			allocator::instantiate_by(adapter_allocator, src),
			this->components_.get_allocator()));
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::http::header::comment::Sequence::write_to(
	StreamT & out) const
{
	out << this->components_;
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
#endif // HTTP_HEADER_COMMENT_SEQUENCE_H_20130109235502663
// end of file
