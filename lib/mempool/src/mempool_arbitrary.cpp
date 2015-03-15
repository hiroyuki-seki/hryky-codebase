/**
  @file         mempool_arbitrary.cpp
  @brief        'not' thread-safe memory allocation for usage in one thread.
  @author       HRYKY
  @version      $Id: mempool_arbitrary.cpp 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#include <precompiled.h>
#include "hryky/integer/max_of.h"
#include "hryky/mempool/mempool_arbitrary.h"
#include "hryky/mempool/mempool_standard.h"
#include "hryky/mempool/mempool_adapter.h"
#include "hryky/stream/stream_denote.h"
#include "hryky/json/json_writer.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename OffsetT
#define hryky_template_arg \
	OffsetT
#define hryky_empty

#define hryky_explicit_instantiation(ret, name, arg, qualification) \
	template ret hryky::mempool::Arbitrary<hryky::uint8_t>::name##arg \
		qualification; \
	template ret hryky::mempool::Arbitrary<hryky::uint16_t>::name##arg \
		qualification; \
	template ret hryky::mempool::Arbitrary<hryky::uint32_t>::name##arg \
		qualification; \
	template ret hryky::mempool::Arbitrary<hryky::uint64_t>::name##arg \
		qualification;

//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace mempool
{
namespace
{
	// prevents the current mempool from allocating recursively.
	struct IsolatePool
	{
		typedef IsolatePool this_type;
		
		IsolatePool()
			: mempool_()
			  , global_(&mempool_)
		{

		}
	private :
		hryky_delete_this_copy_constructor(IsolatePool);
		hryky_delete_this_copy_assign_op(IsolatePool);
		
		Adapter<Standard>           mempool_;
		mempool::global::Registry   global_;
	};
}
} // namespace mempool
} // namespace hryky
//------------------------------------------------------------------------------
// static variable
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// function prototype
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief constructor.
 */
template <hryky_template_param>
hryky::mempool::Arbitrary<hryky_template_arg>::Arbitrary()
	: capacity_()
	  , total_available_size_()
	  , buffer_size_()
	  , head_()
	  , free_nodes_()
	  , terminator_()
	  , blocks_size_()
	  , free_nodes_size_()
	  , alignment_()
{
}
hryky_explicit_instantiation(hryky_empty, Arbitrary, (), hryky_empty);
/**
  @brief destrunctor.
 */
template <hryky_template_param>
hryky::mempool::Arbitrary<hryky_template_arg>::~Arbitrary()
{
}
hryky_explicit_instantiation(hryky_empty, ~Arbitrary, (), hryky_empty);
/**
  @brief clears previous buffer and reinitialize instance.
 */
template <hryky_template_param>
bool hryky::mempool::Arbitrary<hryky_template_arg>::reset(
	void * const buffer,
	size_t const buffer_size,
	alignment_type const alignment)
{
	this->alignment_ = ::std::max<alignment_type>(
		this_type::min_alignment, alignment);

	// The first allocatable address
	void * const aligned_buffer = align_ceil(
		reinterpret_cast<void *>(
			reinterpret_cast<size_t>(buffer) + sizeof(BlockHeader)),
		this->alignment_);

	/**
	   The length from the beginning of the original buffer to the first
	  allocatable address.
	 */
	size_t const prerequisite_head_size =
		reinterpret_cast<size_t>(aligned_buffer) -
			reinterpret_cast<size_t>(buffer);

	/**
	   The minimum necessary length from the beginning of the original buffer
	  to the end of the terminator.
	 */
	size_t const prerequisite_size = prerequisite_head_size
		+ align_ceil(sizeof(FreeNode) + sizeof(BlockHeader), this->alignment_);

	if (buffer_size <= prerequisite_size) {
		IsolatePool const isolate_mempool;
		hryky_log_emerg(
			"too small buffer"
			<< (json::writer()
				<< hryky_stream_denote(buffer_size)
				<< hryky_stream_denote(prerequisite_size)
				<< stream::denote("mempool") << *this));
		return false;
	}

	/**
	   The length from the first allocatable address to the beginning of
	  the terminator.
	 */
	this->capacity_ = align_floor(
		buffer_size - prerequisite_head_size, this->alignment_)
		- sizeof(BlockHeader);

	/**
	   The maximum size that can be represented by OffsetT.
	 */
	size_t const buffer_size_max =
		(MaxOf<offset_type>::value << this->alignment_) - sizeof(BlockHeader);

	// truncates the size of the buffer to the representable size.
	if (buffer_size_max < this->capacity_) {
		IsolatePool const isolate_mempool;
		hryky_log_warning(
			"the capacity is too large to represent address "
			<< (json::writer()
				<< hryky_stream_denote(buffer_size)
				<< stream::denote("capacity") << this->capacity_
				<< hryky_stream_denote(buffer_size_max)));
		this->capacity_ = buffer_size_max;
	}

	// The first header of allocatable block.
	this->head_ = reinterpret_cast<BlockHeader*>(aligned_buffer) - 1;

	// The last header to represent the termination.
	BlockHeader * const terminator = reinterpret_cast<BlockHeader *>(
		reinterpret_cast<size_t>(aligned_buffer) + this->capacity_);
	offset_type const terminator_offset = this->to_offset(terminator);

	if (terminator != this->to_block(terminator_offset)) {
		IsolatePool const isolate_mempool;
		hryky_log_emerg("internal error");
		return false;
	}
	
	offset_type const head_offset = this->to_offset(this->head_);

	// links the head block with the terminator
	this->head_->prev_              = terminator_offset;
	this->head_->next_              = terminator_offset;
	this->head_->flag_.used_        = false;
	this->head_->flag_.alignment_   = this->alignment_;
	terminator->prev_               = head_offset;
	terminator->next_               = head_offset;
	terminator->flag_.used_         = true;
	terminator->flag_.alignment_    = this->alignment_;

	// sets the head block as first free node
	FreeNode * const free_node  = this->to_free_node(this->head_);
	free_node->prev_            = this->to_offset(this->head_);
	free_node->next_            = this->to_offset(this->head_);

	this->total_available_size_ = this->capacity_;
	this->free_nodes_           = head_offset;
	this->terminator_           = terminator_offset;
	this->buffer_size_          = buffer_size;
	this->blocks_size_          = 1u;
	this->free_nodes_size_      = 1u;

	if (reinterpret_cast<size_t>(terminator + 1u)
		 > reinterpret_cast<size_t>(this->head_) + buffer_size) {
		IsolatePool const isolate_mempool;
		hryky_log_emerg(
			"terminator exceeds the end of buffer "
			<< (json::writer()
				<< stream::denote("terminator")
				<< reinterpret_cast<size_t>(terminator + 1u)
				<< stream::denote("head")
				<< reinterpret_cast<size_t>(this->head_)
				<< stream::denote("buffer_size")
				<< buffer_size));
		return false;
	}

	return true;
}
hryky_explicit_instantiation(
	bool,
	reset,
	(void * const, size_t const, alignment_type const),
	hryky_empty);
/**
  @brief allocates memory on specified alignment.
  
   The rule to determine a block is First-fit. The first found block in
  the search is returned.
  
   If there is enough room between a new allocated area and the backward
  block which has been already allocated, a new free block is created
  just behind the new allocated area.
   At the next allocation, the new free block is searched as the first
  candidate.

    ...| prev | found | next |...
    => ...| prev | allocated | !FREE! | next |...
  
   If there is enough room between the forward block which has been already
  allocated and a new allocated area, a new free block is created just before
  the new allocated area.
  At the next allocation, the new free block is searched as the first
  candidate.

    ...| prev | found | next |...
    => ...| prev | !FREE! | allocated | next |...

   If both of the new free blocks described above are created, the
  forward one is searched first at the next allocation.
  
    ...| prev | found | next |...
    => ...| prev | !FREE0! | allocated | FREE1 | next |...
 */
template <hryky_template_param>
void *
hryky::mempool::Arbitrary<hryky_template_arg>::allocate(
	size_t const size, alignment_type const alignment)
{
	if (this->terminator_ == this->free_nodes_) {
		return hryky_nullptr;
	}

	alignment_type const actual_alignment =
		::std::max<alignment_type>(alignment, this->alignment_);

	// enough space for allocating FreeNode is needed.
	size_t const aligned_size = align_ceil(
		::std::max(sizeof(FreeNode), size),
		actual_alignment);

	if (aligned_size < size || this->capacity_ < aligned_size) {
		IsolatePool const isolate_mempool;
		hryky_log_err(
			"too large size "
			<< (json::writer()
				<< hryky_stream_denote(size)
				<< stream::denote("mempool") << *this));
		return hryky_nullptr;
	}

	offset_type search_offset = this->free_nodes_;

	size_t count = 0u;

	// searches a allocatable block from the list of free nodes.
	do {
		if (++count > this->free_nodes_size_) {
			IsolatePool const isolate_mempool;
			hryky_log_emerg(
				"invalid free nodes. "
				<< (json::writer()
					<< stream::denote("mempool") << *this));
			return hryky_nullptr;
		}
		
		BlockHeader * const search = this->to_block(search_offset);
		BlockHeader * const data = search + 1;
		BlockHeader * const aligned_data = align_ceil(data, actual_alignment);

		// confirms whether this block has enough room to allocate a memory.
		if (reinterpret_cast<size_t>(aligned_data) + aligned_size >
			 reinterpret_cast<size_t>(this->to_block(search->next_))) {
			search_offset = this->to_free_node(search)->next_;
			continue;
		}

		/**
		   saves the value of the block before the following operation
		  overwrites the current block.
		 */
		BlockHeader const current = *search;
		BlockHeader * const current_next = this->to_block(current.next_);
		FreeNode * const current_free_node = this->to_free_node(search);

		// removes the current free node.
		if (!this->remove_free_node(current_free_node)) {
			IsolatePool const isolate_mempool;
			hryky_log_emerg(
				"failed to remove free node. "
				<< (json::writer()
					<< stream::denote("mempool") << *this));
			return hryky_nullptr;
		}

		BlockHeader * const aligned_header = aligned_data - 1;
		offset_type const aligned_header_offset =
			this->to_offset(aligned_header);
		
		offset_type lower_bound = aligned_header_offset;
		offset_type upper_bound = aligned_header_offset;

		/**
		   The header of the next block just after the aligned allocated
		  region. The data of the next block has to be aligned.
		 */
		BlockHeader * const next_block = reinterpret_cast<BlockHeader *>(
			align_ceil<size_t>(
				reinterpret_cast<size_t>(aligned_data) +
				aligned_size +
				sizeof(BlockHeader),
				this->alignment_)) - 1;

		offset_type next_offset = 0u;
		
		/**
		   creates a new free block in the interspace between the aligned
		  allocated block and the existing next block.
		 */
		if (reinterpret_cast<size_t>(next_block) +
			sizeof(FreeNode) + sizeof(BlockHeader)
			 <= reinterpret_cast<size_t>(current_next)) {
			next_offset = this->to_offset(next_block);
			
			// inserts the new block.
			BlockHeader * const block   = next_block;
			block->prev_                = aligned_header_offset;
			block->next_                = current.next_;
			block->flag_.used_          = false;
			block->flag_.alignment_     = this->alignment_;

			++this->blocks_size_;

			this->insert_free_node(this->to_free_node(block));

			upper_bound = next_offset;
		}
		else {
			next_offset = current.next_;
		}

		/**
		   The header of a block which can be in the interspace before the
		  alinged allocated region.
		 */
		BlockHeader * const prev_block =
			align_ceil(
				this->to_block(search_offset) + 1, this->alignment_) - 1;

		offset_type prev_offset = 0u;

		/**
		   creates a new free block in the interspace between the existing
		  previous block and the aligned allocated block.
		 */
		if (reinterpret_cast<size_t>(prev_block) +
			sizeof(FreeNode) + sizeof(BlockHeader)
			 <= reinterpret_cast<size_t>(aligned_header)) {
			prev_offset = this->to_offset(prev_block);

			/**
			  inserts the new block.
			  The new block can overwrite the current pre-aligned block.
			 */
			BlockHeader * const block   = prev_block;
			block->prev_                = current.prev_;
			block->next_                = aligned_header_offset;
			block->flag_.used_          = false;
			block->flag_.alignment_     = this->alignment_;

			++this->blocks_size_;

			/**
			  The new free node can overwrite the current
			  pre-aligned free node.
			 */
			this->insert_free_node(this->to_free_node(block));

			lower_bound = prev_offset;
		}
		else {
			prev_offset = current.prev_;
		}

		// re-links the backward and forward existing nodes.
		this->to_block(current.prev_)->next_ = lower_bound;
		this->to_block(current.next_)->prev_ = upper_bound;

		// overwrites the aligned header at last.
		aligned_header->next_ = next_offset;
		aligned_header->prev_ = prev_offset;
		aligned_header->flag_.used_ = true;
		aligned_header->flag_.alignment_ = actual_alignment;

		return aligned_data;

	} while (this->free_nodes_ != search_offset);
	
	return hryky_nullptr;
}
hryky_explicit_instantiation(
	void *,
	allocate,
	(size_t const, alignment_type const),
	hryky_empty);
/**
  @brief deallocates memory.

   If there is a free block preceding the deallocated block, the forward
  free block and the new deallocated block are concatenated.

    ...| free(A) | deallocated(B) | used |...
    => ...| free(A+B) | used |...
  
   If there is a free block following the deallocated block, the backward
  free block and the new deallocated block are concatenated.

    ...| used | deallocated(A) | free(B) |...
    => ...| used | free(A+B) |...
 */
template <hryky_template_param>
bool
hryky::mempool::Arbitrary<hryky_template_arg>::deallocate(
	void * const address)
{
	if (!this->verify(address)) {
		IsolatePool const isolate_mempool;
		hryky_log_err(
			"invalid address. "
			<< (json::writer()
				<< hryky_stream_denote(address)
				<< stream::denote("mempool") << *this));
		return false;
	}

	BlockHeader * const current = reinterpret_cast<BlockHeader *>(address) - 1;
	BlockHeader * const next = this->to_block(current->next_);
	BlockHeader * const prev = this->to_block(current->prev_);

	// concatenates the current and forward unused blocks
	if (!next->flag_.used_) {
		// concatenates backward, current and forward unused blocks
		if (!prev->flag_.used_) {
			if (!this->concat(current, prev, next)) {
				IsolatePool const isolate_mempool;
				hryky_log_emerg("failed to concat three free blocks.");
				return false;
			}
		}
		// concatenates the current and forward unused blocks
		else {
			if (!this->concat_next(current, next)) {
				IsolatePool const isolate_mempool;
				hryky_log_emerg("failed to concat two free blocks.");
				return false;
			}
		}
	}
	else {
		// concatenates the backward and current unused blocks.
		if (!prev->flag_.used_) {
			if (!this->concat_prev(current, prev, next)) {
				IsolatePool const isolate_mempool;
				hryky_log_emerg("failed to concat two free blocks");
				return false;
			}
		}
		// marks the current block as unused.
		else {
			current->flag_.used_ = false;

			this->insert_free_node(this->to_free_node(current));
		}
	}
	
	return true;
}
hryky_explicit_instantiation(
	bool, deallocate, (void * const), hryky_empty);
/**
  @brief checks validity.
 */
template <hryky_template_param>
bool
hryky::mempool::Arbitrary<hryky_template_arg>::verify() const
{
	{
		BlockHeader const * const terminator =
			this->to_block(this->terminator_);
		
		size_t blocks_size = 0u;
		offset_type offset = terminator->next_;
		
		while (this->terminator_ != offset) {
			if (++blocks_size > this->blocks_size_) {
				IsolatePool const isolate_mempool;
				hryky_log_crit(
					"the number of blocks is invalid. "
					<< (json::writer()
						<< stream::denote("mempool") << *this));
				return false;
			}
			
			BlockHeader const * const block = this->to_block(offset);

			size_t const raw_allocated_size = static_cast<size_t>(
				(block->next_ - offset) << this->alignment_);
			size_t const allocated_size =
				raw_allocated_size - sizeof(BlockHeader);

			(void)allocated_size;

			offset = block->next_;
		}

		if (blocks_size != this->blocks_size_) {
			IsolatePool const isolate_mempool;
			hryky_log_crit(
				"the number of blocks is invalid. "
				<< (json::writer()
					<< stream::denote("mempool") << *this));
			return false;
		}
	}

	{
		size_t free_nodes_size = 0u;
		size_t total_available_size = 0u;
		
		offset_type const begin_offset = this->free_nodes_;
		offset_type offset = this->free_nodes_;

		do {
			if (this->terminator_ == offset) {
				break;
			}

			if (++free_nodes_size > this->free_nodes_size_) {
				IsolatePool const isolate_mempool;
				hryky_log_crit(
					"the number of free nodes is invalid. "
					<< (json::writer()
						<< stream::denote("mempool") << *this));
				return false;
			}
			
			BlockHeader const * const block = this->to_block(offset);
			FreeNode const * const free_node = this->to_free_node(block);

			size_t const free_size =
				((block->next_ - offset) << this->alignment_) -
					sizeof(BlockHeader);

			total_available_size += free_size;

			offset = free_node->next_;

		} while (begin_offset != offset);

		if (free_nodes_size != this->free_nodes_size_) {
			IsolatePool const isolate_mempool;
			hryky_log_crit(
				"the number of free nodes is invalid. "
				<< (json::writer()
					<< stream::denote("mempool") << *this));
			return false;
		}
		if (total_available_size != this->total_available_size_) {
			IsolatePool const isolate_mempool;
			hryky_log_crit(
				"total available size is invalid. "
				<< (json::writer()
					<< stream::denote("mempool") << *this));
			return false;
		}
	}
	
	return true;
}
hryky_explicit_instantiation(bool, verify, (), const);
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief removes free node from list.
 */
template <hryky_template_param>
bool hryky::mempool::Arbitrary<hryky_template_arg>::remove_free_node(
	FreeNode * const free_node)
{
	// checks the unexpected condition.
	if (0u == this->free_nodes_size_) {
		IsolatePool const isolate_mempool;
		hryky_log_err(
			"no free nodes."
			<< (json::writer() << stream::denote("mempool") << *this));
		return false;
	}

	BlockHeader const * const current_block = this->to_block(free_node);

	offset_type const offset = this->to_offset(current_block);

	// removes the last free node.
	if (current_block == this->to_block(free_node->next_)) {
		// checks the unexpected condition.
		if (offset != this->free_nodes_ ||
			1u != this->free_nodes_size_) {
			IsolatePool const isolate_mempool;
			hryky_log_err(
				"invalid free node. "
				<< (json::writer()
					<< hryky_stream_denote(free_node)
					<< stream::denote("mempool") << *this));
			return false;
		}
		
		this->free_nodes_ = this->terminator_;
	}
	// removes the free node from the list of free nodes.
	else {
		// updates the head of the list of free nodes.
		if (this->free_nodes_ == offset) {
			this->free_nodes_ = free_node->next_;
		}

		FreeNode * const prev_free_node =
			this->to_free_node(this->to_block(free_node->prev_));
		
		FreeNode * const next_free_node =
			this->to_free_node(this->to_block(free_node->next_));
		
		prev_free_node->next_ = free_node->next_;
		next_free_node->prev_ = free_node->prev_;
	}

	// reduces the total available size.
	{
		BlockHeader const * const next_block =
			this->to_block(current_block->next_);

		this->total_available_size_ -= (
			reinterpret_cast<size_t>(next_block)
			- reinterpret_cast<size_t>(current_block)
			- sizeof(BlockHeader));
	}
	
	--this->free_nodes_size_;
	
	return true;
}
hryky_explicit_instantiation(
	bool, remove_free_node, (FreeNode * const), hryky_empty);
/**
  @brief inserts new free node to list.
 */
template <hryky_template_param>
void hryky::mempool::Arbitrary<hryky_template_arg>::insert_free_node(
	FreeNode * const next, FreeNode * const current)
{
	BlockHeader const * const next_free_block = this->to_block(next);
	BlockHeader const * const current_block = this->to_block(current);
	offset_type const next_offset = this->to_offset(next_free_block);

	// creates the first free node.
	if (this->terminator_ == next_offset) {
		this->free_nodes_ = this->to_offset(current_block);

		current->prev_ = this->free_nodes_;
		current->next_ = this->free_nodes_;
	}
	// inserts a new free node.
	else {
		offset_type const prev_offset = next->prev_;
		
		FreeNode * const prev =
			this->to_free_node(this->to_block(prev_offset));

		offset_type const current_offset = 
			this->to_offset(current_block);

		// inserts the node between the existing nodes.
		prev->next_ = current_offset;
		current->prev_ = prev_offset;
		current->next_ = next_offset;
		next->prev_ = current_offset;
	}

	// increases the total available size.
	{
		BlockHeader const * const next_block =
			this->to_block(current_block->next_);

		this->total_available_size_ += (
			reinterpret_cast<size_t>(next_block)
			- reinterpret_cast<size_t>(current_block)
			- sizeof(BlockHeader));
	}

	++this->free_nodes_size_;
	
	return;
}
hryky_explicit_instantiation(
	void,
	insert_free_node,
	(FreeNode * const, FreeNode * const),
	hryky_empty);
/**
  @brief retrieves the maximum size which allocation can be successful.
 */
template <hryky_template_param>
hryky::size_t hryky::mempool::Arbitrary<hryky_template_arg>::allocatable_size(
	alignment_type const alignment) const
{
	if (this->terminator_ == this->free_nodes_) {
		return 0u;
	}

	alignment_type const actual_alignment =
		::std::max<alignment_type>(alignment, this->alignment_);

	size_t allocatable_size = 0u;

	offset_type search_offset = this->free_nodes_;

	size_t count = 0u;

	// searches from free list
	do {
		if (++count > this->free_nodes_size_) {
			IsolatePool const isolate_mempool;
			hryky_log_emerg(
				"invalid free nodes."
				<< (json::writer()
					<< stream::denote("mempool") << *this));
			return 0u;
		}
		
		BlockHeader const * const search =
			this->to_block(search_offset);
		BlockHeader const * const data =
			search + 1;
		BlockHeader const * const aligned_data =
			align_ceil(data, actual_alignment);

		size_t const data_size = (
			reinterpret_cast<size_t>(this->to_block(search->next_))
			- reinterpret_cast<size_t>(aligned_data));

		if (allocatable_size < data_size) {
			allocatable_size = data_size;
		}
	} while (this->free_nodes_ != search_offset);
	
	return allocatable_size;
}
hryky_explicit_instantiation(
	size_t, allocatable_size, (alignment_type const), const);
/**
  @brief confirms whether the address is allocated from this mempool.
 */
template <hryky_template_param>
bool hryky::mempool::Arbitrary<hryky_template_arg>::verify(
	void * const address) const
{
	if (!is_aligned(address, this->alignment_)) {
		IsolatePool const isolate_mempool;
		hryky_log_err(
			"the address is not aligned."
			<< (json::writer()
				<< stream::denote("address")
				<< reinterpret_cast<size_t>(address)
				<< stream::denote("alignment") << this->alignment_));
		return false;
	}

	size_t const allocatable_begin =
		reinterpret_cast<size_t>(this->head_) + sizeof(BlockHeader);

	size_t const allocatable_end =
		allocatable_begin + this->capacity_;

	if (allocatable_begin > reinterpret_cast<size_t>(address)
		 || allocatable_end <= reinterpret_cast<size_t>(address)) {
		IsolatePool const isolate_mempool;
		hryky_log_err(
			"the addres is over the range of the mempool."
			<< (json::writer()
				<< stream::denote("address")
				<< reinterpret_cast<size_t>(address)
				<< hryky_stream_denote(allocatable_begin)
				<< hryky_stream_denote(allocatable_end)));
		return false;
	}
	
	return true;
}
hryky_explicit_instantiation(
	bool, verify, (void * const), const);
/**
  @brief composes the backward and forward blocks to a free block.
 */
template <hryky_template_param>
bool hryky::mempool::Arbitrary<hryky_template_arg>::concat(
	BlockHeader * const current,
	BlockHeader * const prev,
	BlockHeader * const next)
{
	if (2u > this->blocks_size_) {
		IsolatePool const isolate_mempool;
		hryky_log_emerg(
			"The number of blocks is less than 2."
			<< (json::writer()
				<< stream::denote("blocks_size")
				<< this->blocks_size_));
		return false;
	}

	if (!this->remove_free_node(this->to_free_node(prev))) {
		IsolatePool const isolate_mempool;
		hryky_log_emerg(
			"failed to remove the backward free node."
			<< (json::writer()
				<< stream::denote("free_node")
				<< this->to_free_node(prev)
				<< stream::denote("mempool") << *this));
		return false;
	}

	if (!this->remove_free_node(this->to_free_node(next))) {
		IsolatePool const isolate_mempool;
		hryky_log_emerg(
			"failed to remove the forward free node."
			<< (json::writer()
				<< stream::denote("free_node")
				<< this->to_free_node(next)
				<< stream::denote("mempool") << *this));
		return false;
	}


	this->blocks_size_ -= 2u;

	/**
	  links the backward block with the farther block following after the next.
	 */
	prev->next_ = next->next_;
	this->to_block(next->next_)->prev_ = current->prev_;

	this->insert_free_node(this->to_free_node(prev));
	
	return true;
}
hryky_explicit_instantiation(
	bool,
	concat,
	(BlockHeader * const current,
	 BlockHeader * const prev,
	 BlockHeader * const next),
	hryky_empty);
/**
  @brief concatenates the forward block to the free block.
 */
template <hryky_template_param>
bool hryky::mempool::Arbitrary<hryky_template_arg>::concat_next(
	BlockHeader * const current, BlockHeader * const next)
{
	if (0u == this->blocks_size_) {
		IsolatePool const isolate_mempool;
		hryky_log_emerg(
			"the number of blocks is zero.");
		return false;
	}

	if (!this->remove_free_node(this->to_free_node(next))) {
		IsolatePool const isolate_mempool;
		hryky_log_emerg(
			"failed to remove the forward free node."
			<< (json::writer()
				<< stream::denote("free_node")
				<< this->to_free_node(next)
				<< stream::denote("mempool") << *this));
		return false;
	}

	--this->blocks_size_;

	offset_type const current_offset = this->to_offset(current);

	/**
	  links the current block with the farther block following after
	  the next.
	 */
	current->next_ = next->next_;
	this->to_block(next->next_)->prev_ = current_offset;
	current->flag_.used_ = false;

	this->insert_free_node(this->to_free_node(current));

	return true;
}
hryky_explicit_instantiation(
	bool,
	concat_next,
	(BlockHeader * const current,
	 BlockHeader * const next),
	hryky_empty);
/**
  @brief concatenates the backward block to the free block.
 */
template <hryky_template_param>
bool hryky::mempool::Arbitrary<hryky_template_arg>::concat_prev(
	BlockHeader * const current,
	BlockHeader * const prev,
	BlockHeader * const next)
{
	if (0u == this->blocks_size_) {
		IsolatePool const isolate_mempool;
		hryky_log_emerg("The number of blocks is zero");
		return false;
	}

	if (!this->remove_free_node(this->to_free_node(prev))) {
		IsolatePool const isolate_mempool;
		hryky_log_emerg(
			"failed to remove the backward free node."
			<< (json::writer()
				<< stream::denote("free_node")
				<< this->to_free_node(prev)
				<< stream::denote("mempool") << *this));
		return false;
	}

	--this->blocks_size_;

	/**
	   links the backward block with the farther block following after the
	  current block.
	 */
	prev->next_ = current->next_;
	next->prev_ = current->prev_;

	this->insert_free_node(this->to_free_node(prev));
	
	return true;
}
hryky_explicit_instantiation(
	bool,
	concat_prev,
	(BlockHeader * const current,
	 BlockHeader * const prev,
	 BlockHeader * const next),
	hryky_empty);
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace
{
}
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
// end of file
