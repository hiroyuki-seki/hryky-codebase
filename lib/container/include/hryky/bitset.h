/**
  @file         bitset.h
  @brief        bitset of fixed size on compile time.
  @author       HRYKY
  @version      $Id: bitset.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef BITSET_H_20130119105715123
#define BITSET_H_20130119105715123
#include "hryky/array.h"
#include "hryky/bitsize_of.h"
#include "hryky/container/container_const_pointer.h"
#include "hryky/container/container_const_reference.h"
#include "hryky/container/container_pointer.h"
#include "hryky/container/container_reference.h"
#include "hryky/container/popcount_accumulate.h"
#include "hryky/countdown.h"
#include "hryky/foreach.h"
#include "hryky/integer/bits_enough_signed.h"
#include "hryky/integer/signed_enough.h"
#include "hryky/integer/unsigned_enough.h"
#include "hryky/iterator.h"
#include "hryky/repeat.h"
#include "hryky/with_at.h"
#include "hryky/with_iteration.h"
#include "hryky/with_iterator.h"
#include "hryky/with_stream_out.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	size_t Size, \
	typename PopcountT
#define hryky_template_arg \
	Size, PopcountT
#define hryky_size_type \
	typename UnsignedEnoughUint<Size>::type
#define hryky_difference_type \
	typename SignedEnoughInt<Size>::type
#define hryky_reference \
	ContainerReference<\
		Bitset<hryky_template_arg>, \
		bool, \
		hryky_size_type >
#define hryky_const_reference \
	ContainerConstReference< \
		Bitset<hryky_template_arg>, \
		bool, \
		hryky_size_type >
#define hryky_pointer \
	ContainerPointer< \
		Bitset<hryky_template_arg>, \
		bool, \
		hryky_reference, \
		hryky_size_type >
#define hryky_const_pointer \
	ContainerConstPointer< \
		Bitset<hryky_template_arg>, \
		bool, \
		hryky_reference, \
		hryky_size_type >
#define hryky_iterator \
	hryky::iterator::random::Mutable< \
		Bitset<hryky_template_arg>, \
		bool, \
		hryky_pointer, \
		hryky_reference, \
		hryky_size_type, \
		hryky_difference_type>
#define hryky_const_iterator \
	hryky::iterator::random::Immutable< \
		Bitset<hryky_template_arg>, \
		bool, \
		hryky_pointer, \
		hryky_reference, \
		hryky_const_pointer, \
		hryky_const_reference, \
		hryky_size_type, \
		hryky_difference_type>
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// bitset of fixed size on compile time.
	template <hryky_template_param>
	class Bitset;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief bitset of fixed size on compile time.
 */
template <
	size_t Size,
	typename PopcountT = popcount::Accumulate<Size>
>
class hryky::Bitset :
	public WithIterator<
		Bitset<hryky_template_arg>,
		hryky_iterator,
		hryky_const_iterator >,
	public WithIteration<
		Bitset<hryky_template_arg>,
		hryky_iterator,
		hryky_const_iterator >,
	public WithAt<
		Bitset<hryky_template_arg>,
		bool,
		hryky_reference,
		hryky_const_reference,
		hryky_size_type >,
	public WithStreamOut<Bitset<hryky_template_arg> >
{
public :

	typedef Bitset<hryky_template_arg>  this_type;
	typedef hryky_size_type             size_type;
	typedef hryky_difference_type       difference_type;
	typedef bool                        value_type;
	typedef hryky_reference             reference;
	typedef hryky_const_reference       const_reference;
	typedef hryky_pointer               pointer;
	typedef hryky_const_pointer         const_pointer;
	typedef PopcountT                   popcount_type;

	/// default constructor.
	Bitset();

	/// copy constructor.
	Bitset(this_type const &);

	/// move constructor.
	Bitset(this_type && rhs);

	/// destructor.
	~Bitset();

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

	/// accesses a mutable bit element.
	reference operator[](size_type const pos);

	/// accesses a immutable bit element.
	const_reference operator[](size_type const pos) const;

	/// retrieves the bit at the specified position.
	value_type get(size_type const pos) const;

	/// assigns a new bit at the specified position.
	void set(size_type const pos, value_type const src);

	/// enables the bit at the specified position.
	void on(size_type const pos);

	/// enables the all bits.
	void on();

	/// disable the bit at the specified position.
	void off(size_type const pos);

	/// disables the all bits.
	void off();

	/// reverses the bit at the specified position.
	void flip(size_type const pos);

	/// reverses the all bits.
	void flip();

	/// retrieves the size of bits.
	size_type size() const;

	/// retrieves the number of bits which are one.
	size_type count() const;

	/// confirms whether no bit is on.
	bool none() const;

	/// confirms whether any of bits is on.
	bool any() const;

	/// confirms whether the all of bits are on.
	bool all() const;

	/// confirms the equality between two instances.
	bool operator==(this_type const & rhs) const;

	/// confirms the inequality between two instances.
	bool operator!=(this_type const & rhs) const;

	/// calculates logical AND.
	this_type operator&(this_type const & rhs) const;

	/// calculates logical OR.
	this_type operator|(this_type const & rhs) const;

	/// calculates logical XOR.
	this_type operator^(this_type const & rhs) const;

	/// retrieves a new bitset whose bits are moved to the left.
	this_type operator<<(size_type const shift) const;

	/// retrieves a new bitset whose bits are moved to the right.
	this_type operator>>(size_type const shift) const;

	/// calculates logical AND and assigns the result.
	this_type & operator&=(this_type const & rhs);

	/// calculates logical OR and assigns the result.
	this_type & operator|=(this_type const & rhs);

	/// calculates logical XOR and assigns the result.
	this_type & operator^=(this_type const & rhs);

	/// shifts the bits to the left.
	this_type & operator<<=(size_type const shift);

	/// shifts the bits to the right.
	this_type & operator>>=(size_type const shift);

protected :

private :

	friend PopcountT;

	typedef UnsignedEnoughBytes<sizeof(void *)>::type element_type;
	typedef typename AsParameter<element_type>::type element_param_type;

	/**
	  The exponent of bit width of each element.

	  element_type  exponent_
	  uint32_t      5
	  uint64_t      6
	 */
	static size_t const exponent_ =
		BitsEnoughUnsigned<sizeof(element_type)>::value + 3 - 1;

	/**
	  (element_type=uint32_t, N>=0)
	  Size      fraction_mask (0xFFFFFFFF >> (0x20-1)&(0x20-(Size&(0x20-1))))
	  32*N      0xFFFFFFFF
	  32*N+1    0x00000001
	  32*N+2    0x00000003
	  32*N+3    0x00000007
	  32*N+31   0xEFFFFFFF

	  ;; The test code by xyzzy lisp.
	  (lambda (size)
	  (format nil "0x~X"
	   (ash #xFFFFFFFF
	    (* -1 (logand (- #x20 1) (- #x20 (logand size (- #x20 1))))))))
	 */
	static element_type const fraction_mask_ = (
		static_cast<element_type>(-1) >>
		((BitsizeOf<element_type>::value - 1) &
		 (BitsizeOf<element_type>::value -
		  (Size & (BitsizeOf<element_type>::value - 1)))));

	typedef Array<
		element_type, ((Size - 1) >> this_type::exponent_) + 1>
			buffer_type;

	typedef typename buffer_type::size_type index_type;

	/**
	  The bit width of each element.

	  element_type  bitpos_type
	  uint32_t      uint8_t
	  uint64_t      uint8_t
	 */
	typedef typename UnsignedEnoughBits<exponent_>::type bitpos_type;

	/**
	  casts to prevent the conversion to 32bit integer.
	 */
	static element_type const one_ =
		static_cast<element_type>(1u);

	/// converts the position to the index of array.
	index_type index_of(size_type const pos) const;

	/// converts the position to the bit-position in the element.
	bitpos_type bitpos_of(size_type const pos) const;

	/// retrieves the bit at the specified index and bitpos.
	uint8_t bit_at(index_type const index, bitpos_type const bitpos) const;

	buffer_type buffer_;
	mutable popcount_type popcount_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::Bitset<hryky_template_arg>::Bitset()
	: buffer_()
	  , popcount_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::Bitset<hryky_template_arg>::Bitset(this_type const & rhs)
	: hryky_copy_member(buffer)
	  , hryky_copy_member(popcount)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::Bitset<hryky_template_arg>::Bitset(this_type && rhs)
	: hryky_move_member(buffer)
	  , hryky_move_member(popcount)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::Bitset<hryky_template_arg>::~Bitset()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::Bitset<hryky_template_arg>::clear()
{
	hryky::clear(this->popcount_);
	hryky::clear(this->buffer_);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::Bitset<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(buffer);
	hryky_write_member(popcount);

	out << hryky_stream_denote(Size);
	
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::Bitset<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(buffer);
	hryky_swap_member(popcount);
}
/**
  @brief accesses a mutable bit element.
 */
template <hryky_template_param>
typename hryky::Bitset<hryky_template_arg>::reference
hryky::Bitset<hryky_template_arg>::operator[](
	size_type const pos)
{
	return reference(this, pos);
}
/**
  @brief accesses a immutable bit element.
 */
template <hryky_template_param>
typename hryky::Bitset<hryky_template_arg>::const_reference 
hryky::Bitset<hryky_template_arg>::operator[](
	size_type const pos) const
{
	return const_reference(this, pos);
}
/**
  @brief retrieves the bit at the specified position.
 */
template <hryky_template_param>
typename hryky::Bitset<hryky_template_arg>::value_type 
hryky::Bitset<hryky_template_arg>::get(size_type const pos) const
{
	/**
	  @note
	  index = pos / (8(bit) * sizeof(element_type));
	  bit = pos % (8(bit) * sizeof(element_type));
	 */
	bitpos_type const bitpos = this->bitpos_of(pos);
	index_type const index = this->index_of(pos);
	
	return 1u == this->bit_at(index, bitpos);
}
/**
  @brief assigns a new bit at the specified position.
 */
template <hryky_template_param>
void hryky::Bitset<hryky_template_arg>::set(
	size_type const pos, value_type const src)
{
	bitpos_type const bitpos = this->bitpos_of(pos);
	index_type const index = this->index_of(pos);

	this->popcount_.set(*this, index, bitpos, src);

#if 0
	/**
	  @note
	  The way to assign a bit is
	  1. clears the bit.
	  2. applies OR operation to the bit.
	 */
	element_type const clear_mask = ~(this_type::one_ << bitpos);
	element_type const add =
		((src ?
		  this_type::one_ :
		  static_cast<element_type>(0u)) << bitpos);
	this->buffer_[index] &= clear_mask;
	this->buffer_[index] |= add;
#else
	this->buffer_[index] =
		(src ?
		 this->buffer_[index] | (this_type::one_ << bitpos) :
		 this->buffer_[index] & ~(this_type::one_ << bitpos));
#endif
}
/**
  @brief enables the bit at the specified position.
 */
template <hryky_template_param>
void hryky::Bitset<hryky_template_arg>::on(size_type const pos)
{
	if (this->size() <= pos) {
		return;
	}
	
	bitpos_type const bitpos = this->bitpos_of(pos);
	index_type const index = this->index_of(pos);

	this->popcount_.on(*this, index, bitpos);

	this->buffer_[index] |= (this_type::one_ << bitpos);
}
/**
  @brief enables the all bits.
 */
template <hryky_template_param>
void hryky::Bitset<hryky_template_arg>::on()
{
	this->buffer_.foreach([](buffer_type::reference element) {
		element = static_cast<element_type>(-1);
	});
	this->buffer_[static_cast<size_type>(this->buffer_.size() - 1u)]
		&= this_type::fraction_mask_;

	this->popcount_.assign(static_cast<size_type>(Size));
}
/**
  @brief disables the all bits.
 */
template <hryky_template_param>
void hryky::Bitset<hryky_template_arg>::off()
{
	hryky::clear(this->buffer_);
	hryky::clear(this->popcount_);
}
/**
  @brief disables the bit at the specified position.
 */
template <hryky_template_param>
void hryky::Bitset<hryky_template_arg>::off(size_type const pos)
{
	bitpos_type const bitpos = this->bitpos_of(pos);
	index_type const index = this->index_of(pos);

	this->popcount_.off(*this, index, bitpos);

	this->buffer_[index] &= ~(this_type::one_ << bitpos);
}
/**
  @brief reverses the bit at the specified position.
 */
template <hryky_template_param>
void hryky::Bitset<hryky_template_arg>::flip(size_type const pos)
{
	if (this->size() <= pos) {
		return;
	}
	
	bitpos_type const bitpos = this->bitpos_of(pos);
	index_type const index = this->index_of(pos);

	this->popcount_.flip(*this, index, bitpos);

	this->buffer_[index] ^= (this_type::one_ << bitpos);
}
/**
  @brief reverses the all bits.
 */
template <hryky_template_param>
void hryky::Bitset<hryky_template_arg>::flip()
{
	size_type const prev_count = this->count();
	
	this->buffer_.foreach([](buffer_type::reference element) {
		element = ~element;
	});
	this->buffer_[static_cast<size_type>(this->buffer_.size() - 1u)]
		&= this_type::fraction_mask_;

	this->popcount_.assign(static_cast<size_type>(Size - prev_count));
}
/**
  @brief retrieves the size of bits.
 */
template <hryky_template_param>
typename hryky::Bitset<hryky_template_arg>::size_type
hryky::Bitset<hryky_template_arg>::size() const
{
	return Size;
}
/**
  @brief retrieves the number of bits which are one.
 */
template <hryky_template_param>
typename hryky::Bitset<hryky_template_arg>::size_type 
hryky::Bitset<hryky_template_arg>::count() const
{
	return this->popcount_.count(*this);
}
/**
  @brief confirms whether no bit is on.
 */
template <hryky_template_param>
bool hryky::Bitset<hryky_template_arg>::none() const
{
	return 0 == this->count();
}
/**
  @brief confirms whether any of bits is on.
 */
template <hryky_template_param>
bool hryky::Bitset<hryky_template_arg>::any() const
{
	return !this->none();
}
/**
  @brief confirms whether the all of bits are on.
 */
template <hryky_template_param>
bool hryky::Bitset<hryky_template_arg>::all() const
{
	return this->size() == this->count();
}
/**
  @brief confirms the equality between two instances.
 */
template <hryky_template_param>
bool hryky::Bitset<hryky_template_arg>::operator==(
	this_type const & rhs) const
{
	return this->buffer_ == rhs.buffer_;
}
/**
  @brief confirms the inequality between two instances.
 */
template <hryky_template_param>
bool hryky::Bitset<hryky_template_arg>::operator!=(
	this_type const & rhs) const
{
	return this->buffer_ != rhs.buffer_;
}
/**
  @brief calculates logical AND.
 */
template <hryky_template_param>
hryky::Bitset<hryky_template_arg>
hryky::Bitset<hryky_template_arg>::operator&(
	this_type const & rhs) const
{
	this_type ret;

	typedef AsParameter<element_type>::type param_type;

	this->buffer_.foreach_at([&rhs, &ret](
		param_type lhs, index_type const index) {
		ret.buffer_[index] = lhs & rhs.buffer_[index];
	});

	ret.popcount_.update(ret);
	
	return ret;
}
/**
  @brief calculates logical OR.
 */
template <hryky_template_param>
hryky::Bitset<hryky_template_arg>
hryky::Bitset<hryky_template_arg>::operator|(
	this_type const & rhs) const
{
	this_type ret;

	typedef AsParameter<element_type>::type param_type;

	this->buffer_.foreach_at([&rhs, &ret](
		param_type lhs, index_type const index) {
		ret.buffer_[index] = lhs | rhs.buffer_[index];
	});

	ret.popcount_.update(ret);
	
	return ret;
}
/**
  @brief calculates logical XOR.
 */
template <hryky_template_param>
hryky::Bitset<hryky_template_arg>
hryky::Bitset<hryky_template_arg>::operator^(
	this_type const & rhs) const
{
	this_type ret;

	typedef AsParameter<element_type>::type param_type;

	this->buffer_.foreach_at([&rhs, &ret](
		param_type lhs, index_type const index) {
		ret.buffer_[index] = lhs ^ rhs.buffer_[index];
	});

	ret.popcount_.update(ret);
	
	return ret;
}
/**
  @brief calculates logical AND and assigns the result.
 */
template <hryky_template_param>
hryky::Bitset<hryky_template_arg> &
hryky::Bitset<hryky_template_arg>::operator&=(
	this_type const & rhs)
{
	this->buffer_.foreach_at([&rhs](
		buffer_type::reference lhs, index_type const index) {
		lhs &= rhs.buffer_[index];
	});

	this->popcount_.update(*this);
	
	return *this;
}
/**
  @brief calculates logical OR and assigns the result.
 */
template <hryky_template_param>
hryky::Bitset<hryky_template_arg> &
hryky::Bitset<hryky_template_arg>::operator|=(
	this_type const & rhs)
{
	this->buffer_.foreach_at([&rhs](
		buffer_type::reference lhs, index_type const index) {
		lhs |= rhs.buffer_[index];
	});

	this->popcount_.update(*this);
	
	return *this;
}
/**
  @brief calculates logical XOR and assigns the result.
 */
template <hryky_template_param>
hryky::Bitset<hryky_template_arg> &
hryky::Bitset<hryky_template_arg>::operator^=(
	this_type const & rhs)
{
	this->buffer_.foreach_at([&rhs](
		buffer_type::reference lhs, index_type const index) {
		lhs ^= rhs.buffer_[index];
	});

	this->popcount_.update(*this);
	
	return *this;
}
/**
  @brief shifts the bits to the left.
 */
template <hryky_template_param>
hryky::Bitset<hryky_template_arg> & 
hryky::Bitset<hryky_template_arg>::operator<<=(
	size_type const shift)
{
	if (0u == shift) {
		return *this;
	}

	if (this->size() <= shift) {
		this->off();
		return *this;
	}

	bitpos_type const bit_shift = this->bitpos_of(shift);
	index_type const index_shift = this->index_of(shift);

	index_type const buffer_size = this->buffer_.size();
	buffer_type & buffer = this->buffer_;

	if (0u == bit_shift) {
		/**
		   If both index_shift and bit_shift are zero, shift must be zero
		  and the context doesn't come to this point.
		 */
		hryky::countdown(index_shift, buffer_size).foreach_at(
			[&buffer, index_shift](index_type const index) {
				buffer[index]
					= buffer[static_cast<size_type>(index - index_shift)];
			});
	}
	else {
		/**
		  The index_shift must be less than the size of buffer.
		 */
		bitpos_type const lsb_shift =
			(1u << this_type::exponent_) - bit_shift;
		hryky::countdown<index_type>(index_shift + 1u, buffer_size).foreach_at(
			[&buffer, bit_shift, index_shift, lsb_shift](
				index_type const index) {
				buffer[index] = (
					(buffer[static_cast<size_type>(index - index_shift)]
					 << bit_shift) |
					(buffer[static_cast<size_type>(index - index_shift - 1u)]
					 >> lsb_shift));
			});
		buffer[index_shift] = buffer[0] << bit_shift;
	}

	hryky::repeat(index_shift).foreach_at([&buffer](index_type const index) {
		hryky::clear(buffer[index]);
	});

	this->buffer_[static_cast<size_type>(buffer_size - 1u)]
		&= this_type::fraction_mask_;

	this->popcount_.update(*this);
	
	return *this;
}
/**
  @brief retrieves a new bitset whose bits are moved to the left.
 */
template <hryky_template_param>
hryky::Bitset<hryky_template_arg>
hryky::Bitset<hryky_template_arg>::operator<<(
	size_type const shift) const
{
	this_type result(*this);
	return result.operator<<=(shift);
}
/**
  @brief shifts the bits to the right.
 */
template <hryky_template_param>
hryky::Bitset<hryky_template_arg> & 
hryky::Bitset<hryky_template_arg>::operator>>=(
	size_type const shift)
{
	if (0u == shift) {
		return *this;
	}

	if (this->size() <= shift) {
		this->off();
		return *this;
	}

	bitpos_type const bit_shift = this->bitpos_of(shift);
	index_type const index_shift = this->index_of(shift);

	index_type const buffer_size = this->buffer_.size();
	buffer_type & buffer = this->buffer_;

	if (0u == bit_shift) {
		/**
		   If both index_shift and bit_shift are zero, shift must be zero
		  and the context doesn't come to this point.
		 */
		hryky::repeat(index_shift, buffer_size).foreach_at(
			[&buffer, index_shift](index_type const index) {
				buffer[static_cast<size_type>(index - index_shift)]
					= buffer[index];
			});
	}
	else {
		/**
		  The index_shift must be less than the size of buffer.
		 */
		bitpos_type const msb_shift =
			(1u << this_type::exponent_) - bit_shift;
		hryky::repeat<index_type>(index_shift, buffer_size - 1u).foreach_at(
			[&buffer, bit_shift, index_shift, msb_shift](
				index_type const index) {
				buffer[static_cast<size_type>(index - index_shift)] = (
					(buffer[index] >> bit_shift) |
					(buffer[index + 1u] << msb_shift));
			});
		buffer[static_cast<size_type>(buffer_size - index_shift - 1u)]
			= buffer[static_cast<size_type>(buffer_size - 1u)] >> bit_shift;
	}

	hryky::repeat<index_type>(
		static_cast<index_type>(buffer_size - index_shift),
		buffer_size).foreach_at([&buffer](
			index_type const index) {
			hryky::clear(buffer[index]);
		});

	this->popcount_.update(*this);
	
	return *this;
}
/**
  @brief retrieves a new bitset whose bits are moved to the right.
 */
template <hryky_template_param>
hryky::Bitset<hryky_template_arg>
hryky::Bitset<hryky_template_arg>::operator>>(
	size_type const shift) const
{
	this_type result(*this);
	return result.operator>>=(shift);
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief converts the position to the index of array.
 */
template <hryky_template_param>
typename hryky::Bitset<hryky_template_arg>::index_type 
hryky::Bitset<hryky_template_arg>::index_of(size_type const pos) const
{
	return static_cast<index_type>(pos >> this_type::exponent_);
}
/**
  @brief converts the position to the bit-position in the element.
 */
template <hryky_template_param>
typename hryky::Bitset<hryky_template_arg>::bitpos_type 
hryky::Bitset<hryky_template_arg>::bitpos_of(size_type const pos) const
{
	return static_cast<bitpos_type>(pos & ((1 << this_type::exponent_) - 1));
}
/**
  @brief retrieves the bit at the specified index and bitpos.
 */
template <hryky_template_param>
hryky::uint8_t
hryky::Bitset<hryky_template_arg>::bit_at(
	index_type const index, bitpos_type const bitpos) const
{
	return static_cast<uint8_t>(
		0x1u & (this->buffer_[index] >> bitpos));
}
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros.
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#undef hryky_size_type
#undef hryky_difference_type
#undef hryky_reference
#undef hryky_const_reference
#undef hryky_pointer
#undef hryky_const_pointer
#undef hryky_iterator
#undef hryky_const_iterator
#endif // BITSET_H_20130119105715123
// end of file
