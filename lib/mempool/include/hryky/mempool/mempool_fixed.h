/**
  @file         mempool_fixed.h
  @brief        memory allocation for fixed length units.
  @author       HRYKY
  @version      $Id: mempool_fixed.h 360 2014-07-05 06:59:57Z hryky.private@gmail.com $
 */
#ifndef POOL_FIXED_H_20111107003330689
#define POOL_FIXED_H_20111107003330689
#include "hryky/without_copy.h"
#include "hryky/align.h"
#include "hryky/clear.h"
#include "hryky/definition.h"
#include "hryky/stdint.h"
#include "hryky/integer/bits_enough_unsigned.h"
#include "hryky/integer/unsigned_of.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename IndexT
#define hryky_template_arg \
	IndexT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace mempool
{
	/// memory allocation for fixed length units
	template <typename IndexT = uint32_t>
	class Fixed;

	/**
	  The information of a address allocated from hryky::mempool::Fixed.
	 */
	template <typename IndexT>
	struct FixedAddress;
	
} // namespace mempool
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief memory allocation for fixed length units.
 */
template <hryky_template_param>
class hryky::mempool::Fixed :
	private WithoutCopy,
	public WithStreamOut<Fixed<hryky_template_arg> >,
	public WithSwap<Fixed<hryky_template_arg> >
{
public :

	typedef Fixed<hryky_template_arg>           this_type;
	typedef typename UnsignedOf<IndexT>::type   index_type;
	typedef size_t                              unit_size_type;
	typedef FixedAddress<IndexT>                address_type;

	/// minimum address alignment in bits.
	static alignment_type const min_alignment =
		BitsEnoughUnsigned<sizeof(IndexT) - 1u, alignment_type>::value;

	/// minimum size of one unit in bytes
	static unit_size_type const min_unit_size = 1u << min_alignment;

	/// default constructor
	Fixed();

	/**
	  contstructor with the size of an allocated unit.
	  @a unit_size is forced to align on this_type::min_alignment bits.
	 */
	Fixed(unit_size_type const unit_size);

	/**
	  constructor with the size of an allocated unit and address alignment.
	  @a unit_size is forced to align on alignment bits.
	 */
	Fixed(unit_size_type const unit_size, alignment_type const alignment);

	/// move constructor.
	Fixed(this_type && rhs);

	/// destrunctor
	~Fixed();

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/**
	  sets up initial buffer.
	  
	  @param buffer         is an address on which allocation units are placed
	  @param buffer_size    is the size of @a buffer
	  @return               success and failure
	  @attention
	  - If you want to use entire region of @a buffer, you must adhere to the
	    following methods.
	    - @a buffer must be alinged on (1 << this->alignment()) bytes.
	 */
	bool reset(void * const buffer, size_t const buffer_size);

	/**
	  finds a free unit.
	  
	  @retval hryky_nullptr    failure
	  @retval !hryky_nullptr   The address to an allocated unit.
	  
	  - The returned address is fixed length. The length is @a unit_size which
	    you passed to reset().
	 */
	void * allocate();

	/**
	  marks a unit as unused.
	  @param src    is the address allocated by this instance.
	  @return       success and failure.
	 */
	bool deallocate(void * const src);

	/**
	  estimates the required size of buffer.
	  
	  @param num    is the number of the units
	  @return       The leastest size to allocate units in bytes
	  
	  - When you pass the returned value of this function to reset() as
	    @a buffer_size, you should pass an address which is aligned on the
	    byte returned from byte_alignment(). If not, the size of units that
	    you can allocate is less than @a num.
	 */
	size_t buffer_size(index_type const num) const;

	/**
	  retrieves the byte boundaries.
	 */
	size_t byte_alignment() const;

	/**
	  checks the validity of the internal data.
	  
	  @return   valid and invalid.
	  
	  - This function checks whether the internal information is corrupted.
	 */
	bool verify() const;

	/**
	  verifies allocated address.
	  
	  @param src    is an address allocated from this instance
	  
	  - This function confirms that the passed address is under the
	    management of this instance.
	 */
	bool verify(void const * const src) const;

	/**
	  outputs the information of this instance.
	  
	  @param name   is the key of key-value pair.
	  @return       an element of logging format.
	 */
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/**
	  outputs the information of an address.
	  
	  @param address    will be the address allocated by this instance.
	 */
	template <typename StreamT>
	StreamT & write_to(
		StreamT & out, void const * const address) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/**
	  @brief retrieves the number of allocated units.
	 */
	index_type allocated_size() const;

	/**
	  @brief retrieves the number of available units.
	 */
	index_type available_size() const;
	
	/**
	  @brief retrieves the number of all units.
	 */
	index_type capacity() const;

	/// retrieves the address alignment in bits.
	alignment_type alignment() const;

	/// retrieves the size of an allocated unit.
	unit_size_type unit_size() const;

	/**
	  retrieves the allocatable size in bytes.
	  The returned value is same to the one by unit_size().
	 */
	size_t allocatable_size() const;

protected :

private :

	/**
	   This instance is stored in an empty allocatable unit.
	 */
	struct FreeNode
	{
		// connects to an other backward FreeNode.
		index_type next_;
	};

	/// retrieves the size in multiple of the length of a FreeNode.
	static unit_size_type aligned_unit_size(
		unit_size_type const unit_size, alignment_type const alignment);

	Fixed(this_type const &);
	this_type & operator=(this_type const &);

	/// converts an index to the mutable FreeNode.
	FreeNode * to_free_node(index_type const index);

	/// converts an index to the immutable FreeNode.
	FreeNode const * to_free_node(index_type const index) const;

	/// converts address to index
	index_type to_index(void const * const address) const;

	/// the beginning of the mempool
	void * head_;
	
	/// The beginning of list of free nodes.
	index_type free_nodes_begin_;
	
	index_type      capacity_;
	index_type      allocated_size_;
	unit_size_type  unit_size_;
	alignment_type  alignment_;
	unit_size_type  aligned_unit_size_;
	
};
/**
  The information of a address allocated from hryky::mempool::Fixed.
 */
template <typename IndexT>
struct hryky::mempool::FixedAddress :
	public WithStreamOut<FixedAddress<IndexT> >,
	private WithoutCopy
{
	typedef FixedAddress<IndexT> this_type;
	typedef Fixed<IndexT> mempool_type;
	
	FixedAddress(
		mempool_type const & mempool,
		void const * const address)
		: mempool_(mempool), address_(address)
	{
	}

	template <typename StreamT>
	StreamT & write_to(StreamT & out) const
	{
		return this->mempool_.write_to(out, this->address_);
	}

	hryky_accessor_read(mempool_type const &, mempool);
	hryky_accessor_read(void const *, address);

private :
	hryky_delete_this_copy_constructor(FixedAddress);
	hryky_delete_this_copy_assign_op(FixedAddress);
};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief contstructor with the size of an allocated unit.
 */
template <hryky_template_param>
hryky::mempool::Fixed<hryky_template_arg>::Fixed(unit_size_type const src)
	: head_()
	  , free_nodes_begin_()
	  , capacity_()
	  , allocated_size_()
	  , unit_size_(src)
	  , alignment_(this_type::min_alignment)
	  , aligned_unit_size_(aligned_unit_size(unit_size_, alignment_))
{
}
/**
  @brief constructor with the size of an allocated unit and address alignment.
 */
template <hryky_template_param>
hryky::mempool::Fixed<hryky_template_arg>::Fixed(
	unit_size_type const unit_size, alignment_type const alignment)
	: head_()
	  , free_nodes_begin_()
	  , capacity_()
	  , allocated_size_()
	  , unit_size_(unit_size)
	  , alignment_(alignment)
	  , aligned_unit_size_(aligned_unit_size(unit_size_, alignment_))
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::mempool::Fixed<hryky_template_arg>::Fixed(this_type && rhs)
	: hryky_move_member(head)
	  , hryky_move_member(free_nodes_begin)
	  , hryky_move_member(capacity)
	  , hryky_move_member(allocated_size)
	  , hryky_move_member(unit_size)
	  , hryky_move_member(alignment)
	  , hryky_move_member(aligned_unit_size)
{
	hryky::clear(rhs);
}
/**
  @brief destrunctor.
 */
template <hryky_template_param>
hryky::mempool::Fixed<hryky_template_arg>::~Fixed()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::mempool::Fixed<hryky_template_arg>::clear()
{
	hryky::clear(this->aligned_unit_size_);
	hryky::clear(this->alignment_);
	hryky::clear(this->unit_size_);
	hryky::clear(this->allocated_size_);
	hryky::clear(this->capacity_);
	hryky::clear(this->free_nodes_begin_);
	hryky::clear(this->head_);
}
/**
  @brief estimates the required size of buffer.
 */
template <hryky_template_param>
hryky::size_t hryky::mempool::Fixed<hryky_template_arg>::buffer_size(
	index_type const num) const
{
	return this->aligned_unit_size_ * num;
}
/**
  @brief retrieves the byte boundaries.
 */
template <hryky_template_param>
hryky::size_t hryky::mempool::Fixed<hryky_template_arg>::byte_alignment() const
{
	return hryky::align_ceil(sizeof(FreeNode), this->alignment_);
}
/**
  @brief sets up an initial buffer.
 */
template <hryky_template_param>
bool hryky::mempool::Fixed<hryky_template_arg>::reset(
	void * const buffer, size_t const buffer_size)
{
	void * const aligned_buffer = hryky::align_ceil_unit(
		buffer, this->byte_alignment());
	size_t const buffer_offset = (
		reinterpret_cast<size_t>(aligned_buffer) -
		reinterpret_cast<size_t>(buffer));

	if (buffer_offset + this->aligned_unit_size_ > buffer_size) {
		hryky_log_err(
			"buffer_size is too small. "
			"At least one unit must be in buffer."
			<< (json::writer()
				<< hryky_stream_denote(buffer_offset)
				<< hryky_stream_denote(buffer_size)
				<< stream::denote("aligned_unit_size")
				<< this->aligned_unit_size_));
		return false;
	}

	size_t const capacity =
		(buffer_size - buffer_offset) / this->aligned_unit_size_;

	if (MaxOf<index_type>::value < capacity) {
		hryky_log_err(
			"buffer_size is too large. "
			"This IndexT can not represent the range of the buffer."
			<< (json::writer()
				<< hryky_stream_denote(buffer_size)
				<< hryky_stream_denote(capacity)
				<< stream::denote("maximum_index")
				<< MaxOf<index_type>::value));
		return false;
	}

	this->head_ = aligned_buffer;
	this->capacity_ = static_cast<index_type>(capacity);

	index_type index = this->capacity_;

	for (; 0u != index; --index) {
		FreeNode * const node = this->to_free_node(index - 1u);
		node->next_ = index;
	}

	this->free_nodes_begin_ = 0u;

	return true;
}
/**
  @brief finds a free unit.
 */
template <hryky_template_param>
void * hryky::mempool::Fixed<hryky_template_arg>::allocate()
{
	if (this->capacity_ == this->free_nodes_begin_) {
		return hryky_nullptr;
	}

	FreeNode * const free_node =
		this->to_free_node(this->free_nodes_begin_);

	this->free_nodes_begin_ = free_node->next_;

	++this->allocated_size_;
	
	return free_node;
}
/**
  @brief marks a unit as unused.
 */
template <hryky_template_param>
bool hryky::mempool::Fixed<hryky_template_arg>::deallocate(
	void * const src)
{
	if (!this->verify(src)) {
		hryky_log_err(
			"invalid address "
			<< (json::writer()
				<< stream::denote("address")
				<< reinterpret_cast<size_t>(src)
				<< stream::denote("head")
				<< reinterpret_cast<size_t>(this->head_)
				<< stream::denote("end")
				<< (reinterpret_cast<size_t>(this->head_) +
					this->aligned_unit_size_ * this->capacity_)
				<< stream::denote("aligned_unit_size")
				<< this->aligned_unit_size_
				<< stream::denote("mempool") << *this));
		return false;
	}
	FreeNode * const free_node = reinterpret_cast<FreeNode *>(src);

	free_node->next_ = this->free_nodes_begin_;
	this->free_nodes_begin_ = this->to_index(src);

	--this->allocated_size_;
	
	return true;
}
/**
  @brief checks the validity of the internal data.
 */
template <hryky_template_param>
bool hryky::mempool::Fixed<hryky_template_arg>::verify() const
{
	index_type free_nodes_size = 0u;
	index_type index = this->free_nodes_begin_;

	while (this->capacity_ > index) {
		if (this->capacity_ <= this->allocated_size_ + free_nodes_size) {
			hryky_log_err(
				"invalid free nodes "
				<< (json::writer()
					<< hryky_stream_denote(index)
					<< hryky_stream_denote(free_nodes_size)
					<< stream::denote("mempool") << *this));
			return false;
		}

		FreeNode const * const free_node = this->to_free_node(index);

		index = free_node->next_;

		++free_nodes_size;
	}

	if (this->capacity_ != index) {
		hryky_log_err(
			"invalid free nodes "
			<< (json::writer()
				<< hryky_stream_denote(index)
				<< stream::denote("mempool") << *this));
		return false;
	}

	if (this->capacity_ != this->allocated_size_ + free_nodes_size) {
		hryky_log_err(
			"invalid free nodes "
			<< (json::writer()
				<< hryky_stream_denote(free_nodes_size)
				<< stream::denote("mempool") << *this));
		return false;
	}
	
	return true;
}
/**
  @brief outputs the information of this instance.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::mempool::Fixed<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(head);
	out << stream::denote("available") <<
		(this->capacity_ - this->allocated_size_);
	hryky_write_member(alignment);
	hryky_write_member(unit_size);
	hryky_write_member(aligned_unit_size);
	hryky_write_member(allocated_size);

	
	index_type free_nodes_size = 0u;
	index_type index = this->free_nodes_begin_;

	out << stream::denote("free_nodes");
	stream::map::Scope<StreamT> const free_nodes_map(out);

	while (this->capacity_ > index) {
		if (this->capacity_ <= this->allocated_size_ + free_nodes_size) {
			hryky_log_err(
				"invalid free nodes "
				<< (json::writer()
					<< hryky_stream_denote(index)
					<< stream::denote("capacity") << this->capacity_
					<< stream::denote("allocated_size")
					<< this->allocated_size_
					<< hryky_stream_denote(free_nodes_size)));
			break;
		}

		FreeNode const * free_node = this->to_free_node(index);

		out << stream::denote("next") << free_node->next_;

		index = free_node->next_;
		++free_nodes_size;
	}

	if (this->capacity_ != index) {
		hryky_log_err(
			"the index of terminator is invalid "
			<< (json::writer()
				<< hryky_stream_denote(index)
				<< stream::denote("capacity") << this->capacity_));
	}

	if (this->capacity_ != this->allocated_size_ + free_nodes_size) {
		hryky_log_err(
			"invalid data"
			"the number of free nodes is less than expected one."
			<< (json::writer()
				<< stream::denote("capacity") << this->capacity_
				<< stream::denote("allocated_size")
				<< this->allocated_size_
				<< hryky_stream_denote(free_nodes_size)));
	}
	
	return out;
}
/**
  @brief outputs the information of an address allocated from
    hryky::mempool::Fixed.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::mempool::Fixed<hryky_template_arg>::write_to(
	StreamT & out, void const * const address) const
{
	stream::map::Scope<StreamT> const map(out);

	if (this->verify(address)) {
		out << hryky_stream_denote(address);
		out << stream::denote("index") << this->to_index(address);
	}
	else {
		out << stream::denote("invalid_address") << address;
	}
	
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::mempool::Fixed<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(head);
	hryky_swap_member(free_nodes_begin);
	hryky_swap_member(capacity);
	hryky_swap_member(allocated_size);
	hryky_swap_member(unit_size);
	hryky_swap_member(alignment);
	hryky_swap_member(aligned_unit_size);
}
/**
  @brief retrieves the number of allocated units.
 */
template <hryky_template_param>
typename hryky::mempool::Fixed<hryky_template_arg>::index_type
hryky::mempool::Fixed<hryky_template_arg>::allocated_size() const
{
	return this->allocated_size_;
}

/**
  @brief retrieves the number of available units.
 */
template <hryky_template_param>
typename hryky::mempool::Fixed<hryky_template_arg>::index_type
hryky::mempool::Fixed<hryky_template_arg>::available_size() const
{
	return static_cast<index_type>(
		this->capacity() - this->allocated_size());
}

/**
  @brief retrieves the number of all units.
 */
template <hryky_template_param>
typename hryky::mempool::Fixed<hryky_template_arg>::index_type
hryky::mempool::Fixed<hryky_template_arg>::capacity() const
{
	return this->capacity_;
}
/**
  @brief retrieves the address alignment in bits.
 */
template <hryky_template_param>
hryky::alignment_type
hryky::mempool::Fixed<hryky_template_arg>::alignment() const
{
	return this->alignment_;
}
/**
  @brief retrieves the size of an allocated unit.
 */
template <hryky_template_param>
typename hryky::mempool::Fixed<hryky_template_arg>::unit_size_type 
hryky::mempool::Fixed<hryky_template_arg>::unit_size() const
{
	return this->unit_size_;
}
/**
  @brief retrieves the allocatable size in bytes.
 */
template <hryky_template_param>
hryky::size_t hryky::mempool::Fixed<hryky_template_arg>::allocatable_size() const
{
	return this->unit_size_;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the size in multiple of the length of a FreeNode.
 */
template <hryky_template_param>
typename hryky::mempool::Fixed<hryky_template_arg>::unit_size_type
hryky::mempool::Fixed<hryky_template_arg>::aligned_unit_size(
	unit_size_type const unit_size, alignment_type const alignment)
{
	return hryky::align_ceil_unit(
		unit_size, hryky::align_ceil(sizeof(FreeNode), alignment));
}
/**
  @brief retrieves the FreeNode from the index.
 */
template <hryky_template_param>
typename hryky::mempool::Fixed<hryky_template_arg>::FreeNode *
hryky::mempool::Fixed<hryky_template_arg>::to_free_node(
	index_type const index)
{
	return reinterpret_cast<FreeNode *>(
		reinterpret_cast<uint8_t *>(this->head_) +
		this->aligned_unit_size_ * index);
}
/**
  @brief retrieves the FreeNode from the index (const version).
 */
template <hryky_template_param>
typename hryky::mempool::Fixed<hryky_template_arg>::FreeNode const * 
hryky::mempool::Fixed<hryky_template_arg>::to_free_node(
	index_type const index) const
{
	return reinterpret_cast<FreeNode const *>(
		reinterpret_cast<uint8_t const *>(this->head_) +
		this->aligned_unit_size_ * index);

}
/**
  @brief converts address to index.
 */
template <hryky_template_param>
typename hryky::mempool::Fixed<hryky_template_arg>::index_type
hryky::mempool::Fixed<hryky_template_arg>::to_index(
	void const * const address) const
{
	return static_cast<index_type>(
		(reinterpret_cast<size_t>(address) -
		 reinterpret_cast<size_t>(this->head_))
		/ this->aligned_unit_size_);
}
/**
  @brief verifies allocated address.
 */
template <hryky_template_param>
bool hryky::mempool::Fixed<hryky_template_arg>::verify(
	void const * const src) const
{
	size_t const head_adrs = reinterpret_cast<size_t>(this->head_);
	size_t const src_adrs = reinterpret_cast<size_t>(src);
	
	size_t const unit_begin = head_adrs;
	size_t const unit_end =
		head_adrs + this->aligned_unit_size_ * this->capacity_;
	
	if (unit_begin > src_adrs || unit_end <= src_adrs) {
		return false;
	}

	size_t const offset = src_adrs - head_adrs;

	if (0 != (offset % this->aligned_unit_size_)) {
		return false;
	}

	return true;
}
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace mempool
{
} // namespace mempool
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // POOL_FIXED_H_20111107003330689
// end of file
