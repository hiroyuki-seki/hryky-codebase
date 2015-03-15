/**
  @file     kademlia_endpoint.h
  @brief    An interface to the Kademlia network.
  @author   HRYKY
  @version  $Id: kademlia_endpoint.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef KADEMLIA_ENDPOINT_H_20130915192503475
#define KADEMLIA_ENDPOINT_H_20130915192503475
#include "hryky/allocator/allocator_mempool.h"
#include "hryky/array.h"
#include "hryky/integer/unsigned_enough.h"
#include "hryky/kademlia/kademlia_node.h"
#include "hryky/list.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	size_t NodeIdBits, typename NodeT, typename AllocatorT
#define hryky_template_arg \
	NodeIdBits, NodeT, AllocatorT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace kademlia
{
	/// An interface to the Kademlia network.
	template <
		size_t NodeIdBits,
		typename NodeT = kademlia::Node,
		typename AllocatorT = allocator::Mempool<NodeT>
	>
	class Endpoint;

} // namespace kademlia
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief An interface to the Kademlia network.
 */
template <hryky_template_param>
class hryky::kademlia::Endpoint :
	public WithStreamOut<Endpoint<hryky_template_arg> >,
	public WithSwap<Endpoint<hryky_template_arg> >
{
public :

	static_assert(0 < NodeIdBits, "NodeIdBits has to be greater than 1.");

	typedef Endpoint<hryky_template_arg>                    this_type;
	typedef typename UnsignedEnoughBits<NodeIdBits>::type   id_type;
	typedef AllocatorT                                      allocator_type;
	typedef NodeT                                           node_type;
	typedef List<node_type, AllocatorT>                     bucket_type;
	typedef typename bucket_type::size_type                 bucket_size_type;

	static bucket_size_type const default_max_bucket_size = 20u;

	/// default constructor.
	Endpoint();

	/// constructor with an allocator.
	Endpoint(allocator_type const & allocator);

	/// copy constructor.
	Endpoint(this_type const &);

	/// move constructor.
	Endpoint(this_type &&);

	/// destructor.
	~Endpoint();

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

	/// specifies the maximum size of one bucket.
	void max_bucket_size(bucket_size_type const size);

	/// expands the lengh of the bucket up to the current max_bucket_size.
	bool reserve();

protected :

private :

	typedef Array<bucket_type, NodeIdBits> buckets_type;

	buckets_type            buckets_;
	bucket_size_type        max_bucket_size_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace kademlia
{
} // namespace kademlia
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::kademlia::Endpoint<hryky_template_arg>::Endpoint()
	: max_bucket_size_(default_max_bucket_size)
{
}
/**
  @brief constructor with an allocator.
 */
template <hryky_template_param>
hryky::kademlia::Endpoint<hryky_template_arg>::Endpoint(
	allocator_type const & allocator)
{
	this->buckets_.foreach([&allocator](bucket_type & bucket) {
		bucket = bucket_type(allocator);
	});
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::kademlia::Endpoint<hryky_template_arg>::Endpoint(this_type const & rhs)
	: hryky_copy_member(max_bucket_size)
{
	this->buckets_.foreach_at([&rhs](
		bucket_type & bucket, size_t const index) {
		bucket = rhs.buckets_[index];
	});
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::kademlia::Endpoint<hryky_template_arg>::Endpoint(this_type && rhs)
	: hryky_move_member(max_bucket_size)
{
	this->buckets_.foreach_at([&rhs](
		bucket_type & bucket, size_t const index) {
		bucket = rhs.buckets_[index];
	});
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::kademlia::Endpoint<hryky_template_arg>::~Endpoint()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::kademlia::Endpoint<hryky_template_arg>::clear()
{
	hryky::clear(this->buckets_);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & 
hryky::kademlia::Endpoint<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::kademlia::Endpoint<hryky_template_arg>::swap(this_type & src)
{
}
/**
  @brief specifies the maximum size of one bucket.
 */
template <hryky_template_param>
void hryky::kademlia::Endpoint<hryky_template_arg>::max_bucket_size(
	bucket_size_type const size)
{
	this->max_bucket_size_ =
		(::std::max)(static_cast<bucket_size_type>(2u), size);
}
/**
  @brief expands the size of each bucket up to the current max_bucket_size.
 */
template <hryky_template_param>
bool hryky::kademlia::Endpoint<hryky_template_arg>::reserve()
{
	buckets_type::size_type index = 0;

	this->buckets_[index].reserve(2);
	++index;

	buckets_type::size_type const buckets_size = this->buckets_.size();

	/**
	  iterates the buckets the size of which is lower than
	  the current maximux size of bucket.
	 */
	for (; buckets_size != index; ++index) {
		bucket_size_type const bucket_size = static_cast<bucket_size_type>(
			1 << index);
		if (this->max_bucket_size_ < bucket_size) {
			break;
		}
		if (!this->buckets_[index].reserve(bucket_size)) {
			return false;
		}
	}
	/**
	  iterates the buckets the size of which is more than or equal to
	  the current maximum size of bucket.
	 */
	for (; buckets_size != index; ++index) {
		if (!this->buckets_[index].reserve(this->max_bucket_size_)) {
			return false;
		}
	}
	return true;
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
namespace kademlia
{

} // namespace kademlia
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // KADEMLIA_ENDPOINT_H_20130915192503475
// end of file
