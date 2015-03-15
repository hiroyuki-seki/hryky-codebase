/**
  @file         mempool_arbitrary.h
  @brief        'not' thread-safe memory allocation for usage in one thread.
  @author       HRYKY
  @version      $Id: mempool_arbitrary.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef POOL_ARBITRARY_H_20111026171221383
#define POOL_ARBITRARY_H_20111026171221383
#include "hryky/align.h"
#include "hryky/common.h"
#include "hryky/integer/bits_enough_unsigned.h"
#include "hryky/log/log_definition.h"
#include "hryky/mempool/mempool_global_registry.h"
#include "hryky/stream/stream_array_scope.h"
#include "hryky/stream/stream_denote.h"
#include "hryky/stream/stream_hex.h"
#include "hryky/stream/stream_map_scope.h"
#include "hryky/without_copy.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename OffsetT
#define hryky_template_arg \
	OffsetT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace mempool
{
	/// 'not' thread-safe memory allocation for usage in one thread
	template <typename OffsetT = size_t>
	class Arbitrary;

} // namespace mempool
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief 'not' thread-safe memory allocation for usage in one thread.
  @attention
  
  restrictions:

   The total size of allocations depends on an address alignment passed to 
  Arbitrary::reset(). The bit-width of capacity depends on the alignment(A) and
  the bit-width(B) of offset_type. For example, if the (A) is "4" and the (B)
  is "16", the bit-width of capacity is "16 + 4 = 20". Then, the instance can
  allocate the retions of memory amount to about 0x10000(2^20) bytes at most.

   The total number of allocation units depends on the @a OffsetT template
  argument. @a OffsetT represents the position of each memory block internally.
  Therefore, if the argument is <uint8_t>, the instance can allocate
  (256 - system usage) blocks at most.

   The all of member functions are "not" thread-safe. hryky::mempool::Lock
  is able to wrap this instance for thraed-safe operations.

 */
template <hryky_template_param>
class hryky::mempool::Arbitrary :
	public WithStreamOut<Arbitrary<hryky_template_arg> >
{
public :
	typedef Arbitrary<hryky_template_arg> this_type;

	/**
	  You can handle memory blocks up to the maximum number of @a offset_type.
	 */
	typedef OffsetT offset_type;

	/**
	  The minimum address alignment in bits.
	  Even if OffsetT is uint8_t, the minimum alignment is 2^1byte because
	  of the size of a node.
	 */
	static alignment_type const min_alignment =
		BitsEnoughUnsigned<sizeof(OffsetT) - 1, alignment_type>::value;

	/// wrapper to print an @a address allocated from @a mempool
	struct Address :
		public WithStreamOut<Address>,
		private WithoutCopy
	{
		typedef Address this_type;
		
		Address(Arbitrary const & mempool, void const * const address)
			: mempool_(mempool), address_(address)
		{
		}

		template <typename StreamT>
		StreamT & write_to(StreamT & out) const
		{
			return this->mempool_.write_to(out, this->address_);
		}

		hryky_accessor_read(Arbitrary const &, mempool);
		hryky_accessor_read(void const *, address);

	private :
		hryky_delete_this_copy_constructor(Address);
		hryky_delete_this_copy_assign_op(Address);
	};

	/// default constructor
	Arbitrary();

	/// destrunctor
	~Arbitrary();

	/**
	  @brief    allocates memory on default alignment.
	  @param    size is the size of allocated memory
	  @note
	  - the address alignment of the returned address is based on the
	    alignment past at Arbitrary::reset().
	 */
	void * allocate(size_t const size);

	/**
	  @brief    allocates memory.
	  @param    size is the size of allocated memory.
	  @param    alignment is the address alingment of returned address.
	  @retval   hryky_nullptr if this function failed.
	  @retval   !hryky_nullptr as the allocated address.
	 */
	void * allocate(size_t const size, alignment_type const alignment);

	/**
	  @brief deallocates memory.
	  @param address        is the deallocated address.
	  @return               success and failure.
	 */
	bool deallocate(void * const address);

	/**
	  @brief    clears previous buffer and reinitialize instance.
	  @param    buffer is buffer in which the mempool is created
	  @param    buffer_size is the size of @a buffer
	  @param    alignment is the unit of each allocation
	  @return   success and failure.
	  @attention
	  - The maximum size of available buffer depends on @a offset_type and
	    @a alignment.
	 */
	bool reset(
		void * const buffer,
		size_t const buffer_size,
		alignment_type const alignment);

	/**
	  @brief    clears previous buffer and reinitialize instance with default
	            alignment
	  @param    buffer is buffer in which the mempool is created
	  @param    buffer_size is the size of @a buffer
	  @return   success and failure
	 */
	bool reset(void * const buffer, size_t const buffer_size);

	/**
	  @brief    retrieves the maximum size of allocate() can be successful.
	  @return   the maximim size of allocate() can be successful.

	  - address alignment is based on the alignment past at Arbitrary::reset().
	 */
	size_t allocatable_size() const;

	/**
	  @brief    retrieves the maximum size of allocate() can be successful.
	  @param    alignment is the unit of each allocation
	  @return   the maximim size of allocate() can be successful.
	 */
	size_t allocatable_size(alignment_type const alignment) const;

	/// checks validity
	bool verify() const;

	/**
	  @brief gets the initial available size in bytes.
	 */
	size_t capacity() const;

	/// retrieves the current number of the fragmented spaces.
	offset_type free_nodes_size() const;

	/// outputs the information of mempool.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/**
	  outputs the information of the address allocated by
	  hryky::mempool::Arbitrary.
	 */
	template <typename StreamT>
	StreamT & write_to(
		StreamT & out, void const * const address) const;

	/// confirms whether no memory is allocated.
	bool unused() const;

protected :

private :

	/// header information placed just before an allocated address
	struct BlockHeader
	{
		offset_type     prev_;
		offset_type     next_;

		union
		{
			uint16_t    flags_;
			struct
			{
				alignment_type  alignment_;
				bool            used_:1;
			} flag_;
		};
	};

	/**
	  node of bidirectional link list.
	  This can be placed after the BlockHeader.
	 */
	struct FreeNode
	{
		offset_type     prev_;
		offset_type     next_;
	};

	/// copy constructor
	explicit Arbitrary(Arbitrary const &);

	/// assignment operator
	Arbitrary & operator=(Arbitrary const &rhs);

	/// converts a header address to the offset from the beginning of mempool.
	offset_type to_offset(BlockHeader const * const address) const;

	/// converts an offset from the beginning of mempool to the header address.
	BlockHeader * to_block(offset_type const offset) const;

	/// retrieves the immutable free node from a block.
	FreeNode const * to_free_node(BlockHeader const * const block) const;

	/// retrieves the mutable free node from a block.
	FreeNode * to_free_node(BlockHeader * const block) const;

	/// retrieves the immutable block to which a free node belongs.
	BlockHeader const * to_block(FreeNode const * const free_node) const;

	/// retrieves the mutable block to which a free node belongs.
	BlockHeader * to_block(FreeNode * const free_node) const;

	/**
	  removes free node from list.
	 */
	bool remove_free_node(FreeNode * const free_node);

	/**
	  inserts a new free node to the list of free nodes.
	 */
	void insert_free_node(FreeNode * const next, FreeNode * const current);

	/**
	  inserts a new free node to the list of free nodes
	  and set it as the first candidate of searching.
	 */
	void insert_free_node(FreeNode * const current);

	/// confirms whether the address is allocated from this mempool.
	bool verify(void * const address) const;

	/// concatenates the backward and forward blocks to the free block.
	bool concat(
		BlockHeader * const current,
		BlockHeader * const prev,
		BlockHeader * const next);

	/// concatenates the forward block to the free block.
	bool concat_next(
		BlockHeader * const current,
		BlockHeader * const next);

	/// concatenates the backward block to the free block.
	bool concat_prev(
		BlockHeader * const current,
		BlockHeader * const prev,
		BlockHeader * const next);

	size_t              capacity_;
	size_t              total_available_size_;
	size_t              buffer_size_;

	BlockHeader *       head_;
	offset_type         free_nodes_;
	offset_type         terminator_;
	
	offset_type         blocks_size_;
	offset_type         free_nodes_size_;

	alignment_type      alignment_;
	
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace mempool
{
} // namespace mempool
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member function
//------------------------------------------------------------------------------
/**
  @brief allocates memory on the default alignment.
 */
template <hryky_template_param>
void *
hryky::mempool::Arbitrary<hryky_template_arg>::allocate(
	size_t const size)
{
	return this->allocate(size, this->alignment_);
}
/**
  @brief clears the previous buffer and reinitializes this instance.
 */
template <hryky_template_param>
bool hryky::mempool::Arbitrary<hryky_template_arg>::reset(
	void * const buffer, size_t const buffer_size)
{
	return this->reset(
		buffer,
		buffer_size,
		static_cast<alignment_type>(this_type::min_alignment));
}
/**
  @brief retrieves the maximum size for which allocate() can be successful.
 */
template <hryky_template_param>
hryky::size_t 
hryky::mempool::Arbitrary<hryky_template_arg>::allocatable_size() const
{
	return this->allocatable_size(this->alignment_);
}
/**
  @brief retrieves the initial size of the buffer.
 */
template <hryky_template_param>
hryky::size_t hryky::mempool::Arbitrary<hryky_template_arg>::capacity() const
{
	return this->capacity_;
}
/**
  @brief retrieves the current number of the fragmented spaces.
 */
template <hryky_template_param>
OffsetT 
hryky::mempool::Arbitrary<hryky_template_arg>::free_nodes_size() const
{
	return this->free_nodes_size_;
}
/**
  @brief confirms whether no memory is allocated.
 */
template <hryky_template_param>
bool hryky::mempool::Arbitrary<hryky_template_arg>::unused() const
{
	return 1 == this->free_nodes_size_ && 1 == this->blocks_size_;
}
//------------------------------------------------------------------------------
// defines protected member function
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member function
//------------------------------------------------------------------------------
/**
  @brief converts a header address to the offset from the beginning of mempool.
 */
template <hryky_template_param>
OffsetT hryky::mempool::Arbitrary<hryky_template_arg>::to_offset(
	BlockHeader const * const address) const
{
	return static_cast<offset_type>(
		(reinterpret_cast<size_t>(address)
		 - reinterpret_cast<size_t>(this->head_))
		>> this->alignment_);
}
/**
  @brief converts an offset from the beginning of mempool to the header address.
 */
template <hryky_template_param>
typename hryky::mempool::Arbitrary<hryky_template_arg>::BlockHeader * 
hryky::mempool::Arbitrary<hryky_template_arg>::to_block(
	offset_type const offset) const
{
	return reinterpret_cast<BlockHeader *>(
		reinterpret_cast<size_t>(this->head_)
		+ static_cast<size_t>(offset << this->alignment_));
}
/**
  @brief retrieves the immutable free node from a block.
 */
template <hryky_template_param>
typename hryky::mempool::Arbitrary<hryky_template_arg>::FreeNode const * 
hryky::mempool::Arbitrary<hryky_template_arg>::to_free_node(
	BlockHeader const * const block) const
{
	return reinterpret_cast<FreeNode const *>(block + 1);
}
/**
  @brief retrieves the mutable free node from a block.
 */
template <hryky_template_param>
typename hryky::mempool::Arbitrary<hryky_template_arg>::FreeNode * 
hryky::mempool::Arbitrary<hryky_template_arg>::to_free_node(
	BlockHeader * const block) const
{
	return reinterpret_cast<FreeNode *>(block + 1);
}
/**
  @brief retrieves the immutable block to which a free node belongs.
 */
template <hryky_template_param>
typename hryky::mempool::Arbitrary<hryky_template_arg>::BlockHeader const *
hryky::mempool::Arbitrary<hryky_template_arg>::to_block(
	FreeNode const * const free_node) const
{
	return reinterpret_cast<BlockHeader const *>(free_node) - 1;
}
/**
  @brief retrieves the mutable block to which a free node belongs.
 */
template <hryky_template_param>
typename hryky::mempool::Arbitrary<hryky_template_arg>::BlockHeader * 
hryky::mempool::Arbitrary<hryky_template_arg>::to_block(
	FreeNode * const free_node) const
{
	return reinterpret_cast<BlockHeader*>(free_node) - 1;
}
/**
  @brief inserts a new free node to the list of free nodes.
 */
template <hryky_template_param>
void hryky::mempool::Arbitrary<hryky_template_arg>::insert_free_node(
	FreeNode * const current)
{
	this->insert_free_node(
		this->to_free_node(this->to_block(this->free_nodes_)),
		current);

	// the next allocation begins at the new free node
	this->free_nodes_ = this->to_offset(this->to_block(current));
}
/**
  @brief outputs the information of the address allocated by
    hryky::mempool::Arbitrary.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::mempool::Arbitrary<hryky_template_arg>::write_to(
	StreamT & out, void const * const address) const
{
	stream::map::Scope<StreamT> const map(out);

	BlockHeader const * const block =
		reinterpret_cast<BlockHeader const *>(address) - 1;
	offset_type const block_offset = this->to_offset(block);

	out << stream::denote("used") << block->flag_.used_;
	out << stream::denote("alignment")
		<< static_cast<uint16_t>(block->flag_.alignment_);
	out << stream::denote("size")
		<< ((block->next_ - block_offset) << this->alignment_) -
			sizeof(BlockHeader);
	out << stream::denote("prev") << static_cast<size_t>(block->prev_);
	out << stream::denote("prev_addr") << this->to_block(block->prev_);
	out << stream::denote("block") << static_cast<size_t>(block_offset);
	out << stream::denote("block_addr") << this->to_block(block_offset);
	out << stream::denote("next") << static_cast<size_t>(block->next_);
	out << stream::denote("next_addr") << this->to_block(block->next_);

	return out;
}
/**
  @brief outputs the information of this mempool.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::mempool::Arbitrary<hryky_template_arg>::write_to(
	StreamT & out) const
{
	global::Registry const global_mempool;
	
	stream::map::Scope<StreamT> const map(out);

	out << stream::denote("head")
		<< reinterpret_cast<size_t>(this->head_);
	hryky_write_member(capacity);
	hryky_write_member(total_available_size);
	out << stream::denote("alignment")
		<< static_cast<uint16_t>(this->alignment_);
	hryky_write_member(buffer_size);
	out << stream::denote("blocks")
		<< static_cast<size_t>(this->blocks_size_);
	out << stream::denote("free nodes")
		<< static_cast<size_t>(this->free_nodes_size_);

	{
		out << stream::denote("terminator");
		
		void const * const address = this->to_block(this->terminator_) + 1;

		BlockHeader const * block =
			reinterpret_cast<BlockHeader const *>(address) - 1;
		offset_type const block_offset = this->to_offset(block);

		ostream::String<String<> > os;
		os << hryky::stream::Hex();

		(os
		 << (block->flag_.used_ ?
			 LiteralString<>("used") : LiteralString<>("free")) <<
		 ":" << static_cast<uint16_t>(block->flag_.alignment_) <<
		 ":" << (((block->next_ - block_offset) <<
				  this->alignment_) - sizeof(BlockHeader)) <<
		 ":" << static_cast<size_t>(block->prev_) <<
		 "[" << this->to_block(block->prev_) << "]<-" <<
		 static_cast<size_t>(block_offset) <<
		 "[" << this->to_block(block_offset) <<
		 "]->" << static_cast<size_t>(block->next_) <<
		 "[" << this->to_block(block->next_) << "]"
		 );

		out << os;
	}

	{
		size_t blocks_size = 0u;

		{
			out << stream::denote("blocks");
			stream::array::Scope<StreamT> const blocks(out);

			BlockHeader const * const terminator =
				this->to_block(this->terminator_);
		
			offset_type offset = terminator->next_;

			while (this->terminator_ != offset) {
				if (++blocks_size > this->blocks_size_) {
					break;
				}

				BlockHeader const * const block = this->to_block(offset);

				size_t const raw_allocated_size = static_cast<size_t>(
					(block->next_ - offset) << this->alignment_);
				size_t const allocated_size =
					raw_allocated_size - sizeof(BlockHeader);

				ostream::String<String<> > address_str;
				address_str << hryky::stream::Hex();

				(address_str
				 << (block->flag_.used_ ?
					 LiteralString<>("x:") : LiteralString<>("-:")) <<
				 static_cast<uint16_t>(block->flag_.alignment_) <<
				 ":" << allocated_size << ":" <<
				 static_cast<size_t>(block->prev_) <<
				 "[" << this->to_block(block->prev_) <<
				 "]<-" << static_cast<size_t>(offset) <<
				 "[" << this->to_block(offset) <<
				 "]->" << static_cast<size_t>(block->next_) <<
				 "[" << this->to_block(block->next_) << "]"
				 );

				out << address_str;

				offset = block->next_;
			}
		}

		out << stream::denote("verify_the_number_of_blocks")
			<< (blocks_size == this->blocks_size_ ? "OK" : "NG");
	}

	{
		size_t free_nodes_size = 0u;
		size_t total_available_size = 0u;

		{
			out << stream::denote("free_nodes");
			stream::array::Scope<StreamT> const free_nodes(out);

			offset_type const begin_offset = this->free_nodes_;
			offset_type offset = this->free_nodes_;

			do {
				if (this->terminator_ == offset) {
					break;
				}

				if (++free_nodes_size > this->free_nodes_size_) {
					break;
				}

				BlockHeader const * const block = this->to_block(offset);
				FreeNode const * const free_node = this->to_free_node(block);

				size_t const free_size =
					((block->next_ - offset) << this->alignment_) -
						sizeof(BlockHeader);

				total_available_size += free_size;

				ostream::String<String<> > os;
				os << hryky::stream::Hex();

				(os
				 << free_size << ":" <<
				 static_cast<size_t>(free_node->prev_) <<
				 "[" << this->to_block(free_node->prev_) << "]<-" <<
				 static_cast<size_t>(offset) <<
				 "[" << this->to_block(offset) << "]->" <<
				 static_cast<size_t>(free_node->next_) <<
				 "[" << this->to_block(free_node->next_) << "]"
				 );

				out << os;

				offset = free_node->next_;

			} while (begin_offset != offset);
		}

		out << stream::denote("verify_the_number_of_free_nodes")
			<< (free_nodes_size == this->free_nodes_size_ ?
				"OK" : "NG");
		out << hryky_stream_denote(free_nodes_size);
		out << stream::denote("verify_total_available_size")
			<< (total_available_size == this->total_available_size_ ?
				"OK" : "NG");
		out << hryky_stream_denote(total_available_size);
	}

	return out;
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
#endif // POOL_ARBITRARY_H_20111026171221383
// end of file
