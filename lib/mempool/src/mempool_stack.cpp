/**
  @file         mempool_stack.cpp
  @brief        allocates memory in the method of FILO.
  @author       HRYKY
  @version      $Id: mempool_stack.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/clear.h"
#include "hryky/definition.h"
#include "hryky/json/json_writer.h"
#include "hryky/log.h"
#include "hryky/mempool.h"
#include "hryky/stream/stream_denote.h"
#include "hryky/swap.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace mempool
{
namespace
{
} // namespace "anonymous"
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
  @brief default constructor.
 */
hryky::mempool::Stack::Stack()
	: buffer_()
	  , buffer_size_()
	  , current_()
	  , alignment_(this_type::min_alignment_)
{
}
/**
  @brief constructor with buffer.
 */
hryky::mempool::Stack::Stack(void * const buffer, size_t const buffer_size)
	: buffer_(reinterpret_cast<pointer>(buffer))
	  , buffer_size_(buffer_size)
	  , current_(buffer_)
	  , alignment_(this_type::min_alignment_)
{
}
/**
  @brief copy constructor.
 */
hryky::mempool::Stack::Stack(this_type const & rhs)
	: hryky_copy_member(buffer)
	  , hryky_copy_member(buffer_size)
	  , hryky_copy_member(current)
	  , hryky_copy_member(alignment)
{
}
/**
  @brief move constructor.
 */
hryky::mempool::Stack::Stack(this_type && rhs)
	: hryky_move_member(buffer)
	  , hryky_move_member(buffer_size)
	  , hryky_move_member(current)
	  , hryky_move_member(alignment)
{
}
/**
  @brief destructor.
 */
hryky::mempool::Stack::~Stack()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::mempool::Stack::clear()
{
	this->alignment_ = this_type::min_alignment_;
	hryky::clear(this->current_);
	hryky::clear(this->buffer_size_);
	hryky::clear(this->buffer_);
}
/**
  @brief resets the internal pointer to the beginning of the buffer.
 */
void hryky::mempool::Stack::rewind()
{
	this->current_ = this->buffer_;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::mempool::Stack::swap(this_type & src)
{
	hryky_swap_member(buffer);
	hryky_swap_member(buffer_size);
	hryky_swap_member(current);
	hryky_swap_member(alignment);
}
/**
  @brief assigns a new buffer.
 */
void hryky::mempool::Stack::buffer(
	void * const buffer, size_t const buffer_size)
{
	this->buffer_ = reinterpret_cast<pointer>(buffer);
	this->buffer_size_ = buffer_size;
	this->current_ = this->buffer_;
}
/**
  @brief allocates a region on the default address alignment.
 */
void * hryky::mempool::Stack::allocate(size_t const size)
{
	return this->allocate(size, this->alignment_);
}
/**
  @brief allocates a region with the address alignment.
 */
void * hryky::mempool::Stack::allocate(
	size_t const size, alignment_type const alignment)
{
	pointer const ptr = this->align(this->current_, alignment);

	if (ptr + size > this->buffer_ + this->buffer_size_) {
		return hryky_nullptr;
	}

	this->current_ = ptr + size;
	
	return ptr;
}
/**
  @brief rewinds the state until just before the address is allocated.
 */
bool hryky::mempool::Stack::deallocate(void * address)
{
	if (this->buffer_ > address ||
		this->buffer_ + this->buffer_size_ <=
		reinterpret_cast<pointer>(address)) {
		hryky_log_err(
			"The address is not allocated from this mempool."
			<< (json::writer()
				<< "address"
				<< reinterpret_cast<size_t>(address)
				<< "mempool" << *this));
		return false;
	}

	this->current_ = reinterpret_cast<pointer>(address);
	
	return true;
}
/**
  @brief retrieves the maximum size which allocate() can be successful.
 */
hryky::size_t hryky::mempool::Stack::allocatable_size() const
{
	return this->allocatable_size(this->alignment_);
}
/**
  @brief retrieves the maximum size which allocate() can be successful
                on the alignment.
 */
hryky::size_t
hryky::mempool::Stack::allocatable_size(
	alignment_type const alignment) const
{
	pointer const ptr = this->align(this->current_, alignment);
	pointer const end = this->buffer_ + this->buffer_size_;

	if (ptr >= end) {
		return 0;
	}

	return static_cast<size_t>(end - ptr);
}
/**
  @brief assigns a new default alignment.
 */
void hryky::mempool::Stack::alignment(alignment_type const src)
{
	this->alignment_ =
		::std::max<alignment_type>(this_type::min_alignment_, src);
}
/**
  @brief retrieves the maximum size of an allocatable region.
 */
hryky::size_t hryky::mempool::Stack::capacity() const
{
	return this->buffer_size_;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace mempool
{
namespace
{
} // namespace "anonymous"
} // namespace mempool
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
