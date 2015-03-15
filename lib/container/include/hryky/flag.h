/**
  @file     flag.h
  @brief    facilitates to manage a flag as a combination of bits.
  @author   HRYKY
  @version  $Id: flag.h 341 2014-03-29 06:35:02Z hryky.private@gmail.com $
 */
#ifndef FLAG_H_20130504160813339
#define FLAG_H_20130504160813339
#include "hryky/bitsize_of.h"
#include "hryky/container/container_const_pointer.h"
#include "hryky/container/container_const_reference.h"
#include "hryky/container/container_pointer.h"
#include "hryky/container/container_reference.h"
#include "hryky/definition.h"
#include "hryky/integer/bits_enough_signed.h"
#include "hryky/integer/signed_enough.h"
#include "hryky/integer/unsigned_enough.h"
#include "hryky/iterator/iterator_random_immutable.h"
#include "hryky/literal_string.h"
#include "hryky/with_at.h"
#include "hryky/with_iteration.h"
#include "hryky/with_iterator.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename KindT, \
	size_t Num, \
	typename TokenT, \
	TokenT const * Tokens
#define hryky_template_arg \
	KindT, Num, TokenT, Tokens
#define hryky_this_type \
	Flag<hryky_template_arg>
#define hryky_size_type \
	typename UnsignedEnoughUint<Num>::type
#define hryky_difference_type \
	typename SignedEnoughInt<Num>::type
#define hryky_reference \
	ContainerReference<hryky_this_type, bool, hryky_size_type>
#define hryky_const_reference \
	ContainerConstReference<hryky_this_type, bool, hryky_size_type>
#define hryky_pointer \
	ContainerPointer<hryky_this_type, bool, hryky_reference, hryky_size_type>
#define hryky_const_pointer \
	ContainerConstPointer< \
		hryky_this_type, bool, hryky_reference, hryky_size_type>
#define hryky_iterator \
	hryky::iterator::random::Mutable< \
		hryky_this_type, \
		bool, \
		hryky_pointer, \
		hryky_reference, \
		hryky_size_type, \
		hryky_difference_type>
#define hryky_const_iterator \
	hryky::iterator::random::Immutable< \
		hryky_this_type, \
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
	/// facilitates to manage a flag as a combination of bits.
	template <hryky_template_param>
	class Flag;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief facilitates to manage a flag as a combination of bits.
 */
template <
	typename KindT,
	size_t Num = KindT::num,
	typename TokenT = hryky::LiteralString<>,
	TokenT const * Tokens = &hryky::g_empty_literal_string
>
class hryky::Flag :
	public WithIterator<
		hryky_this_type,
		hryky_iterator,
		hryky_const_iterator >,
	public WithIteration<
		hryky_this_type,
		hryky_iterator,
		hryky_const_iterator >,
	public WithAt<
		hryky_this_type,
		bool,
		hryky_reference,
		hryky_const_reference,
		hryky_size_type >,
	public WithStreamOut<Flag<hryky_template_arg> >,
	public WithSwap<Flag<hryky_template_arg> >
{
public :

	typedef hryky_this_type         this_type;
	typedef hryky_size_type         size_type;
	typedef hryky_difference_type   difference_type;
	typedef bool                    value_type;
	typedef hryky_reference         reference;
	typedef hryky_const_reference   const_reference;
	typedef hryky_pointer           pointer;
	typedef hryky_const_pointer     const_pointer;

	typedef typename UnsignedEnoughBits<Num>::type  raw_type;
	typedef KindT                                   kind_type;
	typedef typename KindT::Raw                     raw_kind_type;

	static size_type const num = static_cast<size_type>(Num);

	/// default constructor.
	Flag();

	/// copy constructor.
	Flag(this_type const &);

	/// move constructor.
	Flag(this_type &&);

	/// destructor.
	~Flag();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// retrieves the specified bit as a immutable reference.
	const_reference operator[](size_type const index) const;

	/// retrieves the specified bit as a mutable reference.
	reference operator[](size_type const index);

	/// enables a flag.
	this_type & operator|=(raw_kind_type const kind);

	/// disables a flag.
	this_type & operator^=(raw_kind_type const kind);

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// confirms whether the all bits are off.
	bool none() const;

	/// confirms whether any of the bits is on.
	bool any() const;

	/// confirms whether the all bits are on.
	bool all() const;

	/// enables one bit in this flag.
	void on(raw_kind_type const kind);

	/// enables one bit by the index.
	void on(size_type const index);

	/// disable one bit in this flag.
	void off(raw_kind_type const kind);

	/// disable one bit by the index.
	void off(size_type const index);

	/// inverts one bit in this flag.
	void flip(raw_kind_type const kind);

	/// inverts one bit by the index.
	void flip(size_type const index);

	/// confirms whether the specified bit is on.
	bool test(raw_kind_type const kind) const;

	/// confirms whether the specified bit is on.
	bool test(size_type const index) const;

	/// retrieves the size of this container.
	size_type size() const;

	/// obtains the boolean of the specified bit.
	value_type get(size_type const index) const;

	/// assigns a new boolean to the specified bit.
	void set(size_type const index, value_type const value);

protected :

private :

	raw_type raw_;

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
hryky::Flag<hryky_template_arg>::Flag()
	: raw_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::Flag<hryky_template_arg>::Flag(this_type const & rhs)
	: hryky_copy_member(raw)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::Flag<hryky_template_arg>::Flag(this_type && rhs)
	: hryky_move_member(raw)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::Flag<hryky_template_arg>::~Flag()
{
}
/**
  @brief retrieves the specified bit as a immutable reference.
 */
template <hryky_template_param>
typename hryky::Flag<hryky_template_arg>::const_reference 
hryky::Flag<hryky_template_arg>::operator[](size_type const index) const
{
	return const_reference(this, index);
}
/**
  @brief retrieves the specified bit as a mutable reference.
 */
template <hryky_template_param>
typename hryky::Flag<hryky_template_arg>::reference 
hryky::Flag<hryky_template_arg>::operator[](size_type const index)
{
	return reference(this, index);
}
/**
  @brief enables a flag.
 */
template <hryky_template_param>
hryky::Flag<hryky_template_arg> &
hryky::Flag<hryky_template_arg>::operator|=(raw_kind_type const kind)
{
	this->on(kind);
	return *this;
}
/**
  @brief disables a flag.
 */
template <hryky_template_param>
hryky::Flag<hryky_template_arg> &
hryky::Flag<hryky_template_arg>::operator^=(raw_kind_type const kind)
{
	this->off(kind);
	return *this;
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::Flag<hryky_template_arg>::clear()
{
	hryky::clear(this->raw_);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::Flag<hryky_template_arg>::write_to(
	StreamT & out) const
{
	if (Tokens == &g_empty_literal_string) {
		out << this->raw_;
		return out;
	}

	stream::map::Scope<StreamT> const map(out);

	this->foreach_at([&out](
		value_type const value, size_type const index) {
		if (Num <= index) {
			out << stream::denote("N/A");
			out << "N/A";
		}
		else {
			out << Tokens[index];
			out << (value ? "ON" : "OFF");
		}
	});
	
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::Flag<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(raw);
}
/**
  @brief confirms whether the all bits are off.
 */
template <hryky_template_param>
bool hryky::Flag<hryky_template_arg>::none() const
{
	return raw_type() == this->raw_;
}
/**
  @brief confirms whether any of the bits is on.
 */
template <hryky_template_param>
bool hryky::Flag<hryky_template_arg>::any() const
{
	return !this->none();
}
/**
  @brief confirms whether the all bits are on.
 */
template <hryky_template_param>
bool hryky::Flag<hryky_template_arg>::all() const
{
	/**
	  1. creates the mask all of whose bits are on.
	  2. shifts by the difference between the bit-size of the mask and
	     the bit-size of this flag.

	  If Num is 14,
	  1. The mask is 0xFFFF
	  2. The shifted mask is 0x3FFF.
	 */
	return this->raw_ ==
		static_cast<raw_type>(-1) >> (BitsizeOf<raw_type>::value - Num);
}
/**
  @brief enables one bit in this flag.
 */
template <hryky_template_param>
void hryky::Flag<hryky_template_arg>::on(raw_kind_type const kind)
{
	this->on(static_cast<size_type>(kind));
}
/**
  @brief enables one bit by the index.
 */
template <hryky_template_param>
void hryky::Flag<hryky_template_arg>::on(size_type const index)
{
	this->raw_ |= static_cast<raw_type>(1) << index;
}
/**
  @brief disable one bit in this flag.
 */
template <hryky_template_param>
void hryky::Flag<hryky_template_arg>::off(raw_kind_type const kind)
{
	this->off(static_cast<size_type>(kind));
}
/**
  @brief disable one bit by the index
 */
template <hryky_template_param>
void hryky::Flag<hryky_template_arg>::off(size_type const index)
{
	this->raw_ &=
		static_cast<raw_type>(-1) ^ (static_cast<raw_type>(1) << index);
}
/**
  @brief inverts one bit in this flag.
 */
template <hryky_template_param>
void hryky::Flag<hryky_template_arg>::flip(raw_kind_type const kind)
{
	this->flip(static_cast<size_type>(kind));
}
/**
  @brief inverts one bit by the index.
 */
template <hryky_template_param>
void hryky::Flag<hryky_template_arg>::flip(size_type const index)
{
	this->raw_ ^= static_cast<raw_type>(1) << index;
}
/**
  @brief confirms whether the specified bit is on.
 */
template <hryky_template_param>
bool hryky::Flag<hryky_template_arg>::test(raw_kind_type const kind) const
{
	return this->test(static_cast<size_type>(kind));
}
/**
  @brief confirms whether the specified bit is on.
 */
template <hryky_template_param>
bool hryky::Flag<hryky_template_arg>::test(size_type const index) const
{
	return 0 != (this->raw_ & (static_cast<raw_type>(1) << index));
}
/**
  @brief retrieves the size of this container.
 */
template <hryky_template_param>
typename hryky::Flag<hryky_template_arg>::size_type
hryky::Flag<hryky_template_arg>::size() const
{
	return static_cast<size_type>(Num);
}
/**
  @brief obtains the boolean of the specified bit.
 */
template <hryky_template_param>
typename hryky::Flag<hryky_template_arg>::value_type
hryky::Flag<hryky_template_arg>::get(size_type const index) const
{
	return this->test(index);
}
/**
  @brief assigns a new boolean to the specified bit.
 */
template <hryky_template_param>
void hryky::Flag<hryky_template_arg>::set(
	size_type const index, value_type const value)
{
	if (value) {
		this->on(index);
	}
	else {
		this->off(index);
	}
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

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#undef hryky_this_type
#undef hryky_size_type
#undef hryky_difference_type
#undef hryky_reference
#undef hryky_const_reference
#undef hryky_pointer
#undef hryky_const_pointer
#undef hryky_iterator
#undef hryky_const_iterator
#endif // FLAG_H_20130504160813339
// end of file
