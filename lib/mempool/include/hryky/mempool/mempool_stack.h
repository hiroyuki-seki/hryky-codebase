/**
  @file         mempool_stack.h
  @brief        allocates memory in the method of FILO.
  @author       HRYKY
  @version      $Id: mempool_stack.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef POOL_STACK_H_20130224174832408
#define POOL_STACK_H_20130224174832408
#include "hryky/align.h"
#include "hryky/definition.h"
#include "hryky/integer/bits_enough_unsigned.h"
#include "hryky/stdint.h"
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
namespace mempool
{
	/// allocates memory in the method of FILO.
	class Stack;

	typedef Stack stack_type;

} // namespace mempool
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief allocates memory in the method of FILO.
 */
class hryky::mempool::Stack :
	public WithStreamOut<Stack>,
	public WithSwap<Stack>
{
public :

	typedef Stack this_type;

	/// default constructor.
	Stack();

	/// constructor with buffer.
	Stack(void * const buffer, size_t const buffer_size);

	/// copy constructor.
	Stack(this_type const &);

	/// move constructor.
	Stack(this_type &&);

	/// destructor.
	~Stack();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// resets the internal pointer to the beginning of the buffer.
	void rewind();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/**
	  assigns a new buffer.
	  
	   The allocated regions before the this calling are invalidated.
	 */
	void buffer(void * const buffer, size_t const buffer_size);

	/// allocates a region on the default address alignment.
	void * allocate(size_t const size);

	/// allocates a region with the address alignment.
	void * allocate(size_t const size, alignment_type const alignment);

	/**
	  rewinds the state until just before the address is allocated.
	  
	   The all regions allocated after this address was allocated are
	  invalidated.
	 */
	bool deallocate(void * address);

	/// retrieves the maximum size which allocate() can be successful.
	size_t allocatable_size() const;

	/**
	  retrieves the maximum size which allocate() can be succesful
	  on the alignment.
	 */
	size_t allocatable_size(alignment_type const alignment) const;

	/// assigns a new default alignment.
	void alignment(alignment_type const src);

	/// retrieves the size of buffer.
	size_t capacity() const;

protected :

private :

	typedef uint8_t * pointer;

	/// The minimum address alignment in bits.
	static const alignment_type min_alignment_ =
		BitsEnoughUnsigned<sizeof(void *) - 1, alignment_type>::value;

	/// aligns an address on the alignment.
	template <typename ValueT>
	ValueT align(ValueT ptr, alignment_type const alignment) const;

	pointer buffer_;
	size_t buffer_size_;
	pointer current_;
	alignment_type alignment_;

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
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::mempool::Stack::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(buffer);
	hryky_write_member(buffer_size);
	hryky_write_member(current);
	hryky_write_member(alignment);
	return out;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief aligns an address on the alignment.
 */
template <typename ValueT>
ValueT hryky::mempool::Stack::align(
	ValueT ptr, alignment_type const alignment) const
{
	return hryky::align_ceil(
		ptr,
		::std::max<alignment_type>(this->alignment_, alignment));
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
#endif // POOL_STACK_H_20130224174832408
// end of file
