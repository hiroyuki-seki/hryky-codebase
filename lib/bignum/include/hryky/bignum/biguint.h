/**
  @file     biguint.h
  @brief    unsigned integer of long length.
  @author   HRYKY
  @version  $Id: biguint.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef BIGUINT_H_20130921153720317
#define BIGUINT_H_20130921153720317
#include "hryky/integer/min_of.h"
#include "hryky/integer/max_of.h"
#include "hryky/integer/lower_of.h"
#include "hryky/integer/unsigned_enough.h"
#include "hryky/debug/debug_common.h"
#include "hryky/bits_length.h"
#include "hryky/bitsize_of.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/std/std_random.h"
#include "hryky/type_traits/is_unsigned.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename LowerT
#define hryky_template_arg \
	LowerT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// unsigned integer with higher precision.
	template <hryky_template_param>
	class Biguint;

	typedef Biguint<uint64_t>   uint128_t;
	typedef Biguint<uint128_t>  uint256_t;
	typedef Biguint<uint256_t>  uint512_t;
	typedef Biguint<uint512_t>  uint1024_t;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief unsigned integer with higher precision.

  @attention
  The all artuments have to refer different instances.
 */
template <hryky_template_param>
class hryky::Biguint :
	public WithSwap<Biguint<hryky_template_arg> >,
	public WithStreamOut<Biguint<hryky_template_arg> >
{
public :

	typedef Biguint this_type;
	typedef LowerT lower_type;

	/// retrieves the value representing one.
	static this_type const & one();

	/// default constructor.
	Biguint();

	/// constructs with high and low values.
	Biguint(lower_type const high, lower_type const low);

	/// constructs with a lower type.
	Biguint(lower_type const low);

	/// constructs with an int value.
	Biguint(int const src);

	/// constructs with an int value.
	Biguint(unsigned int const src);

	/// copy constructor.
	Biguint(this_type const &);

	/// move constructor.
	Biguint(this_type &&);

	/// destructor.
	~Biguint();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// assigns an int value.
	template <typename RhsT>
	this_type & operator=(RhsT const src);

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// compares with ==.
	bool operator==(this_type const & rhs) const;

	/// compares with !=.
	bool operator!=(this_type const & rhs) const;

	/// compares with <.
	bool operator<(this_type const & rhs) const;

	/// compares with >.
	bool operator>(this_type const & rhs) const;

	/// compares with <=.
	bool operator<=(this_type const & rhs) const;

	/// compares with >=.
	bool operator>=(this_type const & rhs) const;

	/// adds a value of the same type.
	this_type operator+(this_type const & rhs) const;

	/// adds a value of arbitrary type.
	template <typename RhsT>
	this_type operator+(RhsT rhs) const;

	/// subtracts a value of the same type.
	this_type operator-(this_type const & rhs) const;

	/// subtracts a value of arbitrary type.
	template <typename RhsT>
	this_type operator-(RhsT rhs) const;

	/// multiplies a value of same type.
	this_type operator*(this_type const & rhs) const;

	/// multiplies a value of arbitrary type.
	template <typename RhsT>
	this_type operator*(RhsT rhs) const;

	/// divides by a value of same type.
	this_type operator/(this_type const & rhs) const;

	/// divides by a value of arbitrary type.
	template <typename RhsT>
	this_type operator/(RhsT rhs) const;

	/// calculates the remainder of division.
	this_type operator%(this_type const & rhs) const;

	/// calculates the remainder of division.
	template <typename RhsT>
	this_type operator%(RhsT rhs) const;

	/// bitwise logical OR.
	this_type operator|(this_type const & rhs) const;

	/// bitwise logical OR with arbitrary type.
	template <typename RhsT>
	this_type operator|(RhsT rhs) const;

	/// bitwise logical AND.
	this_type operator&(this_type const & rhs) const;

	/// bitwise logical AND with arbitrary type.
	template <typename RhsT>
	this_type operator&(RhsT rhs) const;

	/// bitwise logical XOR.
	this_type operator^(this_type const & rhs) const;

	/// bitwise logical XOR with arbitrary type.
	template <typename RhsT>
	this_type operator^(RhsT rhs) const;

	/// adds a value of the same type in a disruptive way.
	this_type & operator+=(this_type const & rhs);

	/// subtracts a value of the same type in a disruptive way.
	this_type & operator-=(this_type const & rhs);

	/// multiplies a value in a disruptive way.
	this_type & operator*=(this_type const & rhs);

	/// divides by a value of same type in a disruptive way.
	this_type & operator/=(this_type const & rhs);

	/// calculates the remainder of division in a disruptive way.
	this_type & operator%=(this_type const & rhs);

	/// Arithmetic Left Shift.
	this_type operator<<(size_t const shift) const;

	/// Arithmetic Left Shift by signed integer.
	this_type operator<<(signed int const shift) const;

	/// Arithmetic Right Shift.
	this_type operator>>(size_t const shift) const;

	/// Arithmetic Right Shift by signed integer.
	this_type operator>>(signed int const shift) const;

	/// Arithmetic Left Shift (disruptive).
	this_type & operator<<=(signed int const shift);

	/// Arithmetic Left Shift (disruptive).
	this_type & operator<<=(size_t const shift);

	/// Arithmetic Right Shift (disruptive).
	this_type & operator>>=(signed int const shift);

	/// Arithmetic Right Shift (disruptive).
	this_type & operator>>=(size_t const shift);

	/// bitwise logical OR (disruptive).
	this_type & operator|=(this_type const & rhs);

	/// bitwise logical AND (disruptive).
	this_type & operator&=(this_type const & rhs);

	/// bitwise logical XOR (disruptive).
	this_type & operator^=(this_type const & rhs);

	/// retrieves the complement.
	this_type operator~() const;

	/// pre-increment.
	this_type & operator++();

	/// post-increment.
	this_type operator++(int);

	/// pre-decrement.
	this_type & operator--();

	/// post-decrement.
	this_type operator--(int);

	/// casts at the lower type.
	operator lower_type() const;

	/// retrieves the higher part of bits.
	lower_type high() const;

	/// retrieves the lower part of bits.
	lower_type low() const;

protected :

private :

	static this_type const one_;
	static this_type const min_;
	static this_type const max_;

	/// calculates the quotient and the remainder of division.
	static void divide(
		this_type & quotient,
		this_type & remainder,
		this_type const & lhs, 
		this_type const & rhs);

	/// calculates the multiply of two instances.
	static void multiply(
		this_type & dest, this_type const & lhs, this_type const & rhs);

	lower_type high_;
	lower_type low_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
#if 1800 <= _MSC_VER
namespace std
{
	template <>
	struct _Is_UIntType<hryky::uint8_t>
	{
		static bool const value = true;
	};
	template <>
	struct _Is_UIntType<hryky::uint128_t>
	{
		static bool const value = true;
	};
	template <>
	struct _Is_UIntType<hryky::uint256_t>
	{
		static bool const value = true;
	};
	template <>
	struct _Is_UIntType<hryky::uint512_t>
	{
		static bool const value = true;
	};
	template <>
	struct _Is_UIntType<hryky::uint1024_t>
	{
		static bool const value = true;
	};
}
#endif
namespace hryky
{
/**
  The minimum value of Biguint.
 */
template <hryky_template_param>
class MinOf<Biguint<hryky_template_arg> >
{
public :
	static Biguint<hryky_template_arg> const value;
};
/**
  instantiates the minimum value of Biguint.
 */
template <hryky_template_param>
Biguint<hryky_template_arg> const
MinOf<Biguint<hryky_template_arg> >::value = hryky::Biguint<hryky_template_arg>(
	MinOf<Biguint<hryky_template_arg>::lower_type>::value,
	MinOf<Biguint<hryky_template_arg>::lower_type>::value);

/**
  The minmum value of Biguint.
 */
template <hryky_template_param>
class MaxOf<Biguint<hryky_template_arg> >
{
public :
	static Biguint<hryky_template_arg> const value;
};
/**
  instantiates the maximum value of Biguint.
 */
template <hryky_template_param>
Biguint<hryky_template_arg> const
MaxOf<Biguint<hryky_template_arg> >::value = hryky::Biguint<hryky_template_arg>(
	MaxOf<Biguint<hryky_template_arg>::lower_type>::value,
	MaxOf<Biguint<hryky_template_arg>::lower_type>::value);

/**
  @brief retrieves the lower type of Biguint.
 */
template <hryky_template_param>
class LowerOf<Biguint<hryky_template_arg> >
{
public :
	typedef typename Biguint<hryky_template_arg>::lower_type type;
};
/**
  @brief retrieves the bit size of Biguint.
 */
template <hryky_template_param, typename ResultT>
class BitsizeOf<Biguint<hryky_template_arg>, ResultT >
{
public :
	static ResultT const value =
		BitsizeOf<typename Biguint<hryky_template_arg>::lower_type>::value << 1;
};
/**
  @brief The type of unsigned integer which can store 2^4 bytes value.
 */
template <>
class UnsignedEnoughBytesExponent<4>
{
public :
	typedef uint128_t type;
};
/**
  @brief The type of unsigned integer which can store 2^5 bytes value.
 */
template <>
class UnsignedEnoughBytesExponent<5>
{
public :
	typedef uint256_t type;
};
/**
  @brief The type of unsigned integer which can store 2^6 bytes value.
 */
template <>
class UnsignedEnoughBytesExponent<6>
{
public :
	typedef uint512_t type;
};
/**
  @brief The type of unsigned integer which can store 2^6 bytes value.
 */
template <>
class UnsignedEnoughBytesExponent<7>
{
public :
	typedef uint1024_t type;
};
/**
  @brief Biguint is regarded as unsigned type.
 */
template <hryky_template_param>
class IsUnsigned<Biguint<hryky_template_arg> >
{
public :
	typedef true_type type;
};
} // namespace hryky
namespace std
{
template <hryky_template_param>
struct make_unsigned<hryky::Biguint<hryky_template_arg> >
{
	typedef hryky::Biguint<hryky_template_arg> type;
};

template <hryky_template_param>
class numeric_limits<hryky::Biguint<hryky_template_arg> >
{
public :
	typedef hryky::Biguint<hryky_template_arg> biguint_type;
	typedef hryky::BitsizeOf<biguint_type> bitsize_of_type;
	
	static bool const is_specialized = true;
	
	static int const digits = bitsize_of_type::value;
	static int const digits10;
	static bool const is_signed = false;
	static bool const is_integer = true;
	static bool const is_exact = true;
	static int const radix = 2;
	static int const min_exponent = 0;
	static int const min_exponent10 = 0;
	static int const max_exponent = 0;
	static int const max_exponent10 = 0;
	static bool const has_infinity = false;
	static bool const has_quiet_NaN = false;
	static bool const has_signaling_NaN = false;
	static float_denorm_style const has_denorm = denorm_absent;
	static bool const has_drnorm_loss = false;
	static bool const is_iec559 = false;
	static bool const is_bounded = true;
	static bool const is_modulo = true;
	static bool const traps = false;
	static bool const tinyness_before = false;
	static float_round_style const round_style = round_toward_zero;
	
	static biguint_type min()
	{
		return MinOf<biguint_type>::value;
	}
	
	static biguint_type max()
	{
		return MaxOf<biguint_type>::value;
	}
	
	static biguint_type lowest()
	{
		return MinOf<biguint_type>::value;
	}

	static biguint_type epsilon()
	{
		return biguint_type::one();
	}

	static biguint_type round_error()
	{
		return biguint_type();
	}

	static biguint_type infinity()
	{
		return biguint_type();
	}

	static biguint_type quiet_NaN()
	{
		return biguint_type();
	}

	static biguint_type signaling_NaN()
	{
		return biguint_type();
	}

	static biguint_type denorm_min()
	{
		return biguint_type();
	}
};
template <hryky_template_param>
int const
numeric_limits<hryky::Biguint<hryky_template_arg> >::digits10 =
hryky::digits10(hryky::Biguint<hryky_template_arg>::max()) - 1;

} // namespace std
//------------------------------------------------------------------------------
// public static functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the value representing one.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg> const & 
hryky::Biguint<hryky_template_arg>::one()
{
	return this_type::one_;
}
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg>::Biguint()
	: high_()
	  , low_()
{
}
/**
  @brief constructs with high and low values.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg>::Biguint(
	lower_type const high, lower_type const low)
	: high_(high)
	  , low_(low)
{
}
/**
  @brief constructs with a lower type.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg>::Biguint(lower_type const low)
	: high_()
	  , low_(low)
{
}
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_sign_conversion
/**
  @brief constructs with an int value.
 */
template <hryky_template_param> 
hryky::Biguint<hryky_template_arg>::Biguint(int const src)
	: high_(0 > src ? MaxOf<lower_type>::value : lower_type())
	  , low_(src)
{
}
#pragma hryky_pragma_pop_warning
/**
  @brief constructs with an unsigned int value.
 */
template <hryky_template_param> 
hryky::Biguint<hryky_template_arg>::Biguint(unsigned int const src)
	: high_()
	  , low_(src)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg>::Biguint(this_type const & rhs)
	: hryky_copy_member(high)
	  , hryky_copy_member(low)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg>::Biguint(this_type && rhs)
	: hryky_move_member(high)
	  , hryky_move_member(low)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg>::~Biguint()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void
hryky::Biguint<hryky_template_arg>::clear()
{
	hryky::clear(this->high_);
	hryky::clear(this->low_);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::Biguint<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(high);
	hryky_write_member(low);
	
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void
hryky::Biguint<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(high);
	hryky_swap_member(low);
}
/**
  @brief assigns an int value.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::Biguint<hryky_template_arg> &
hryky::Biguint<hryky_template_arg>::operator=(RhsT const src)
{
	this_type(src).swap(*this);
	
	return *this;
}
/**
  @brief compares with ==.
 */
template <hryky_template_param>
bool
hryky::Biguint<hryky_template_arg>::operator==(this_type const & rhs) const
{
	return this->high_ == rhs.high_ && this->low_ == rhs.low_;
}
/**
  @brief compares with !=.
 */
template <hryky_template_param>
bool
hryky::Biguint<hryky_template_arg>::operator!=(this_type const & rhs) const
{
	return !this->operator==(rhs);
}
/**
  @brief compares with <.
 */
template <hryky_template_param>
bool
hryky::Biguint<hryky_template_arg>::operator<(this_type const & rhs) const
{
	return (
		this->high_ < rhs.high_ ||
		(this->high_ == rhs.high_ && this->low_ < rhs.low_));
}
/**
  @brief compares with >.
 */
template <hryky_template_param>
bool
hryky::Biguint<hryky_template_arg>::operator>(this_type const & rhs) const
{
	return (
		this->high_ > rhs.high_ ||
		(this->high_ == rhs.high_ && this->low_ > rhs.low_));
}
/**
  @brief compares with <=.
 */
template <hryky_template_param>
bool
hryky::Biguint<hryky_template_arg>::operator<=(this_type const & rhs) const
{
	return !this->operator>(rhs);
}
/**
  @brief compares with >=.
 */
template <hryky_template_param>
bool
hryky::Biguint<hryky_template_arg>::operator>=(this_type const & rhs) const
{
	return !this->operator<(rhs);
}
/**
  @brief adds a value of the same type.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg>
hryky::Biguint<hryky_template_arg>::operator+(this_type const & rhs) const
{
	return (
		// no effect.
		MinOf<this_type>::value == rhs ? *this :
		// adds a value.
		this_type(
		this->high_ + rhs.high_ +
		static_cast<lower_type>(
			this->low_ > MaxOf<lower_type>::value - rhs.low_ ? 1 : 0),
		this->low_ + rhs.low_));
}
/**
  @brief adds a value of arbitrary type.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::Biguint<hryky_template_arg>
hryky::Biguint<hryky_template_arg>::operator+(RhsT rhs) const
{
	return this->operator+(this_type(rhs));
}
/**
  @brief subtracts a value of the same type.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg>
hryky::Biguint<hryky_template_arg>::operator-(this_type const & rhs) const
{
	return (
		// no effect.
		MinOf<this_type>::value == rhs ? *this :
		// subtracts a value.
		this_type(
		this->high_ - rhs.high_ -
		static_cast<lower_type>(
			this->low_ < rhs.low_ ? 1 : 0),
		this->low_ - rhs.low_));
}
/**
  @brief subtracts a value of arbitrary type.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::Biguint<hryky_template_arg>
hryky::Biguint<hryky_template_arg>::operator-(RhsT rhs) const
{
	return this->operator-(this_type(rhs));
}
/**
  @brief multiplies a value of same type.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg> 
hryky::Biguint<hryky_template_arg>::operator*(
	this_type const & rhs) const
{
	if (this_type::one_ == rhs) {
		// no effect.
		return *this;
	}

	this_type result;
	this_type::multiply(result, *this, rhs);
	return result;
}
/**
  @brief multiplies a value of arbitrary type.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::Biguint<hryky_template_arg> 
hryky::Biguint<hryky_template_arg>::operator*(RhsT rhs) const
{
	return this->operator*(this_type(rhs));
}
/**
  @brief divides by a value of same type.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg>
hryky::Biguint<hryky_template_arg>::operator/(this_type const & rhs) const
{
	if (this_type::one_ == rhs) {
		// no effect.
		return *this;
	}

	if (this->operator<(rhs)) {
		// sweeps all.
		return MinOf<this_type>::value;
	}

	if (lower_type() == this->high_) {
		// Just the lower part is affected.
		return this_type(lower_type(), this->low_ / rhs.low_);
	}

	this_type quotient;
	this_type remainder;
	this_type::divide(quotient, remainder, *this, rhs);
	
	return quotient;
}
/**
  @brief divides by a value of arbitrary type.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::Biguint<hryky_template_arg>
hryky::Biguint<hryky_template_arg>::operator/(RhsT rhs) const
{
	return this->operator/(this_type(rhs));
}
/**
  @brief calculates the remainder of division.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg>
hryky::Biguint<hryky_template_arg>::operator%(this_type const & rhs) const
{
	if (this->operator<(rhs)) {
		// no effect.
		return *this;
	}

	if (this_type::one_ == rhs) {
		// sweeps all.
		return MinOf<this_type>::value;
	}

	if (lower_type() == this->high_) {
		// Just the lower part is affected.
		return this_type(lower_type(), this->low_ % rhs.low_);
	}

	this_type quotient;
	this_type remainder;
	this_type::divide(quotient, remainder, *this, rhs);
	
	return remainder;
}
/**
  @brief calculates the remainder of division.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::Biguint<hryky_template_arg>
hryky::Biguint<hryky_template_arg>::operator%(RhsT rhs) const
{
	return this->operator%(this_type(rhs));
}
/**
  @brief bitwise logical OR.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg>
hryky::Biguint<hryky_template_arg>::operator|(this_type const & rhs) const
{
	if (MinOf<this_type>::value == rhs) {
		// no effect.
		return *this;
	}
	
	return this_type(
		this->high_ | rhs.high_,
		this->low_ | rhs.low_);
}
/**
  @brief bitwise logical OR with arbitrary type.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::Biguint<hryky_template_arg>
hryky::Biguint<hryky_template_arg>::operator|(RhsT rhs) const
{
	return this->operator|(this_type(rhs));
}
/**
  @brief bitwise logical AND.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg>
hryky::Biguint<hryky_template_arg>::operator&(this_type const & rhs) const
{
	if (MaxOf<this_type>::value == rhs) {
		// no effect.
		return *this;
	}
	
	return this_type(
		this->high_ & rhs.high_,
		this->low_ & rhs.low_);
}
/**
  @brief bitwise logical AND with arbitrary type.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::Biguint<hryky_template_arg>
hryky::Biguint<hryky_template_arg>::operator&(RhsT rhs) const
{
	return this->operator&(this_type(rhs));
}
/**
  @brief bitwise logical XOR.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg>
hryky::Biguint<hryky_template_arg>::operator^(this_type const & rhs) const
{
	if (MinOf<this_type>::value == rhs) {
		// no effect.
		return *this;
	}
	
	return this_type(
		this->high_ ^ rhs.high_,
		this->low_ ^ rhs.low_);
}
/**
  @brief bitwise logical XOR with arbitrary type.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::Biguint<hryky_template_arg>
hryky::Biguint<hryky_template_arg>::operator^(RhsT rhs) const
{
	return this->operator^(this_type(rhs));
}
/**
  @brief adds a value of the same type in a disruptive way.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg> &
hryky::Biguint<hryky_template_arg>::operator+=(this_type const & rhs)
{
	if (MinOf<this_type>::value == rhs) {
		// no effect.
		return *this;
	}
	
	this->high_ += (
		rhs.high_ + static_cast<lower_type>(
			this->low_ > MaxOf<lower_type>::value - rhs.low_ ? 1 : 0));
	this->low_ += rhs.low_;
	return *this;
}
/**
  @brief subtracts a value of the same type in a disruptive way.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg> &
hryky::Biguint<hryky_template_arg>::operator-=(this_type const & rhs)
{
	if (MinOf<this_type>::value == rhs) {
		// no effect.
		return *this;
	}
	
	this->high_ -= (
		rhs.high_ + static_cast<lower_type>(
			this->low_ < rhs.low_ ? 1 : 0));
	this->low_ -= rhs.low_;
	return *this;
}
/**
  @brief multiplies a value in a disruptive way.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg> & 
hryky::Biguint<hryky_template_arg>::operator*=(
	this_type const & rhs)
{
	if (this_type::one_ == rhs) {
		// no effect.
		return *this;
	}

	this_type::multiply(*this, *this, rhs);
	return *this;
}
/**
  @brief divides by a value of same type in a disruptive way.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg> &
hryky::Biguint<hryky_template_arg>::operator/=(this_type const & rhs)
{
	if (this_type::one_ == rhs) {
		// no effect.
		return *this;
	}

	if (this->operator<(rhs)) {
		// sweeps all.
		hryky::clear(*this);
		return *this;
	}

	if (lower_type() == this->high_) {
		// The effect is restricted to the lower part.
		hryky::clear(this->high_);
		this->low_ /= rhs.low_;
		return *this;
	}

	this_type remainder;
	this_type::divide(*this, remainder, *this, rhs);
	
	return *this;
}
/**
  @brief calculates the remainder of division in a disruptive way.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg> &
hryky::Biguint<hryky_template_arg>::operator%=(this_type const & rhs)
{
	if (this->operator<(rhs)) {
		// no effect.
		return *this;
	}

	if (this_type::one_ == rhs) {
		// sweeps all.
		this->clear();
		return *this;
	}

	if (lower_type() == this->high_) {
		// The effect is restricted to the lower part.
		hryky::clear(this->high_);
		this->low_ %= rhs.low_;
		return *this;
	}

	this_type quotient;
	this_type::divide(quotient, *this, *this, rhs);
	
	return remainder;
}
/**
  @brief Arithmetic Left Shift by signed integer.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg>
hryky::Biguint<hryky_template_arg>::operator<<(signed int const shift) const
{
	return (
		0 > shift ?
		this->operator>>(static_cast<size_t>(-shift)) :
		this->operator<<(static_cast<size_t>(shift)));
}
/**
  @brief Arithmetic Left Shift.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg>
hryky::Biguint<hryky_template_arg>::operator<<(size_t const shift) const
{
	return (
		// no effect.
		0 == shift ? *this :
		// sweeps all bits.
		BitsizeOf<this_type>::value <= shift ? MinOf<this_type>::value :
		// sweeps the all higher bits
		BitsizeOf<lower_type>::value <= shift ? this_type(
			static_cast<lower_type>(
				this->low_ << (shift - BitsizeOf<lower_type>::value)),
			lower_type()) :
		// shifts the lower part to the higher part.
		this_type(
			static_cast<lower_type>(this->high_ << shift) |
			static_cast<lower_type>(
				this->low_ >> (BitsizeOf<lower_type>::value - shift)),
			this->low_ << shift));
}
/**
  @brief Arithmetic Right Shift by signed integer.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg>
hryky::Biguint<hryky_template_arg>::operator>>(signed int const shift) const
{
	return (
		0 > shift ?
		this->operator<<(static_cast<size_t>(-shift)) :
		this->operator>>(static_cast<size_t>(shift)));
}
/**
  @brief Arithmetic Right Shift.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg>
hryky::Biguint<hryky_template_arg>::operator>>(size_t const shift) const
{
	return (
		// no effect.
		0 == shift ? *this :
		// sweeps all bits
		BitsizeOf<this_type>::value <= shift ? MinOf<this_type>::value :
		// sweeps the all lower bits.
		BitsizeOf<lower_type>::value <= shift ? this_type(
			lower_type(),
			static_cast<lower_type>(
				this->high_ >> (shift - BitsizeOf<lower_type>::value))) :
		// shifts the higher part to the lower part.
		this_type(
			this->high_ >> shift,
			static_cast<lower_type>(this->low_ >> shift) |
			static_cast<lower_type>(
				static_cast<lower_type>(
					this->high_ & static_cast<lower_type>(
						(static_cast<lower_type>(1) << shift) - 1)) <<
				(BitsizeOf<lower_type>::value - shift))));
}
/**
  @brief Arithmetic Left Shift (disruptive).
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg> &
hryky::Biguint<hryky_template_arg>::operator<<=(signed int const shift)
{
	return (
		0 > shift ?
		this->operator>>=(static_cast<size_t>(-shift)) :
		this->operator<<=(static_cast<size_t>(shift)));
}
/**
  @brief Arithmetic Left Shift (disruptive).
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg> &
hryky::Biguint<hryky_template_arg>::operator<<=(size_t const shift)
{
	if (0 == shift) {
		// no effect.
		return *this;
	}
	if (BitsizeOf<this_type>::value <= shift) {
		// sweeps all bits.
		this->clear();
		return *this;
	}
	if (BitsizeOf<lower_type>::value <= shift) {
		// sweeps the all higher bits.
		this->high_ = this->low_ << (shift - BitsizeOf<lower_type>::value);
		hryky::clear(this->low_);
		return *this;
	}

	// shifts the lower part to the higher part.
	this->high_ = (
		static_cast<lower_type>(
			this->high_ << shift) |
		static_cast<lower_type>(
			this->low_ >> (BitsizeOf<lower_type>::value - shift))
		);
	this->low_ <<= shift;
	return *this;
}
/**
  @brief Arithmetic Right Shift (disruptive).
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg> &
hryky::Biguint<hryky_template_arg>::operator>>=(signed int const shift)
{
	return (
		0 > shift ?
		this->operator<<=(static_cast<size_t>(-shift)) :
		this->operator>>=(static_cast<size_t>(shift)));
}
/**
  @brief Arithmetic Right Shift (disruptive).
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg> &
hryky::Biguint<hryky_template_arg>::operator>>=(size_t const shift)
{
	if (0 == shift) {
		// no effect.
		return *this;
	}
	if (BitsizeOf<this_type>::value <= shift) {
		// sweeps all bits.
		this->clear();
		return *this;
	}
	if (BitsizeOf<lower_type>::value <= shift) {
		// sweeps the all lower bits.
		this->low_ = this->high_ >> (shift - BitsizeOf<lower_type>::value);
		hryky::clear(this->high_);
		return *this;
	}

	// shifts the higher part to the lower part.
	this->low_ = (
		static_cast<lower_type>(
			this->low_ >> shift) |
		static_cast<lower_type>(
			static_cast<lower_type>(
				this->high_ & static_cast<lower_type>(
				(static_cast<lower_type>(1) << shift) - 1)) <<
			(BitsizeOf<lower_type>::value - shift))
		);
	this->high_ >>= shift;
	return *this;
}
/**
  @brief bitwise logical OR (disruptive).
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg> &
hryky::Biguint<hryky_template_arg>::operator|=(this_type const & rhs)
{
	if (MinOf<this_type>::value == rhs) {
		// no effect.
		return *this;
	}
	this->high_ |= rhs.high_;
	this->low_ |= rhs.low_;
	return *this;
}
/**
  @brief bitwise logical AND (disruptive).
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg> &
hryky::Biguint<hryky_template_arg>::operator&=(this_type const & rhs)
{
	if (MaxOf<this_type>::value == rhs) {
		// no effect.
		return *this;
	}
	this->high_ &= rhs.high_;
	this->low_ &= rhs.low_;
	return *this;
}
/**
  @brief bitwise logical XOR (disruptive).
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg> &
hryky::Biguint<hryky_template_arg>::operator^=(this_type const & rhs)
{
	if (MinOf<this_type>::value == rhs) {
		// no effect.
		return *this;
	}
	this->high_ ^= rhs.high_;
	this->low_ ^= rhs.low_;
	return *this;
}
/**
  @brief retrieves the complement.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg> 
hryky::Biguint<hryky_template_arg>::operator~() const
{
	return this_type(~this->high_, ~this->low_);
}
/**
  @brief pre-increment.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg> & 
hryky::Biguint<hryky_template_arg>::operator++()
{
	return this->operator+=(1);
}
/**
  @brief post-increment.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg> 
hryky::Biguint<hryky_template_arg>::operator++(int)
{
	this_type const result(*this);
	this->operator++();
	return result;
}
/**
  @brief pre-decrement.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg> & 
hryky::Biguint<hryky_template_arg>::operator--()
{
	return this->operator-=(1);
}
/**
  @brief post-decrement.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg> 
hryky::Biguint<hryky_template_arg>::operator--(int)
{
	this_type const result(*this);
	this->operator--();
	return result;
}
/**
  @brief casts at the lower type.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg>::operator LowerT() const
{
	return this->low_;
}
/**
  @brief retrieves the higher part of bits.
 */
template <hryky_template_param>
typename hryky::Biguint<hryky_template_arg>::lower_type 
hryky::Biguint<hryky_template_arg>::high() const
{
	return this->high_;
}
/**
  @brief retrieves the lower part of bits.
 */
template <hryky_template_param>
typename hryky::Biguint<hryky_template_arg>::lower_type 
hryky::Biguint<hryky_template_arg>::low() const
{
	return this->low_;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// private static variable
//------------------------------------------------------------------------------
/**
  The representation of one.
 */
template <hryky_template_param>
hryky::Biguint<hryky_template_arg> const
hryky::Biguint<hryky_template_arg>::one_ = hryky::Biguint<hryky_template_arg>(
	hryky::Biguint<hryky_template_arg>::lower_type(),
	hryky::Biguint<hryky_template_arg>::lower_type(1));
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief calculates the multiply of two instances.
  LHS:              LHH,LHL,LLH,LLL
  RHS:              RHH,RHL,RLH,RLL
                            LLL*RLL
                        LLH*RLL
                    LHL*RLL
                LHH*RLL             (half no effect)
                        LLL*RLH
                    LLH*RLH
                LHL*RLH             (half no effect)
            LHH*RLH                 (no effect)
                    LLL*RHL
                LLH*RHL             (half no effect)
            LHL*RHL                 (all no effect)
        LHH*RHL                     (all no effect)
                LLL*RHH             (half no effect)
            LLH*RHH                 (all no effect)
        LHL*RHH                     (all no effect)
    LHH*RHH                         (all no effect)
 */
template <hryky_template_param>
void hryky::Biguint<hryky_template_arg>::multiply(
	this_type & dest, this_type const & lhs, this_type const & rhs)
{
	lower_type const lhh = high_bits(lhs.high_);
	lower_type const lhl = low_bits(lhs.high_);
	lower_type const llh = high_bits(lhs.low_);
	lower_type const lll = low_bits(lhs.low_);
	lower_type const rhh = high_bits(rhs.high_);
	lower_type const rhl = low_bits(rhs.high_);
	lower_type const rlh = high_bits(rhs.low_);
	lower_type const rll = low_bits(rhs.low_);

	lower_type const lll_rll = lll * rll;
	lower_type const llh_rll = llh * rll;
	lower_type const lhl_rll = lhl * rll;
	lower_type const lhh_rll = lhh * rll;
	
	lower_type const lll_rlh = lll * rlh;
	lower_type const llh_rlh = llh * rlh;
	lower_type const lhl_rlh = lhl * rlh;
	
	lower_type const lll_rhl = lll * rhl;
	lower_type const llh_rhl = llh * rhl;
	
	lower_type const lll_rhh = lll * rhh;

	lower_type const lll_rll_l = low_bits(lll_rll);
	lower_type const lll_rll_h = high_bits(lll_rll);
	lower_type const llh_rll_l = low_bits(llh_rll);
	lower_type const llh_rll_h = high_bits(llh_rll);
	lower_type const lhl_rll_l = low_bits(lhl_rll);
	lower_type const lhl_rll_h = high_bits(lhl_rll);
	lower_type const lhh_rll_l = low_bits(lhh_rll);

	lower_type const lll_rlh_l = low_bits(lll_rlh);
	lower_type const lll_rlh_h = high_bits(lll_rlh);
	lower_type const llh_rlh_l = low_bits(llh_rlh);
	lower_type const llh_rlh_h = high_bits(llh_rlh);
	lower_type const lhl_rlh_l = low_bits(lhl_rlh);
	
	lower_type const lll_rhl_l = low_bits(lll_rhl);
	lower_type const lll_rhl_h = high_bits(lll_rhl);
	lower_type const llh_rhl_l = low_bits(llh_rhl);
	
	lower_type const lll_rhh_l = low_bits(lll_rhh);

	lower_type const lh = lll_rll_h + llh_rll_l + lll_rlh_l;
	lower_type const hl =
		llh_rll_h + lhl_rll_l + lll_rlh_h + llh_rlh_l + lll_rhl_l;
	lower_type const hh =
		lhl_rll_h + lhh_rll_l + llh_rlh_h + lhl_rlh_l + lll_rhl_h
			+ llh_rhl_l + lll_rhh_l;

	dest = this_type(
		lower_type(
			(hh << BitsizeOf<LowerOf<lower_type>::type>::value) + hl),
		lower_type(
			(lh << BitsizeOf<LowerOf<lower_type>::type>::value) | lll_rll_l));
}
/**
  @brief calculates the quotient and the remainder of division.
 */
template <hryky_template_param>
void hryky::Biguint<hryky_template_arg>::divide(
	this_type & quotient, this_type & remainder,
	this_type const & lhs, this_type const & rhs)
{
	hryky_throw_if(
		MinOf<this_type>::value == rhs,
		::std::invalid_argument,
		"The divisor is zero." << hryky::endl,
		return);
	
	size_t const divisor_size = bits_length(rhs);
	size_t const dividend_size = bits_length(lhs);

	size_t position = dividend_size - divisor_size;
	this_type divisor = rhs << position;

	remainder = lhs;

	/**
	  1010101
	  10-----
	 */
	while (remainder < divisor) {
		divisor >>= 1;
		--position;
	}

	/**
	  0010101
	  10-----
	  1
	 */
	remainder -= divisor;
	quotient = 1;

	while (0 < position && remainder >= rhs) {
		do {
			/**
			  1st
			  0010101   0010101
			  010----   0010---
			  10        100

			  2nd
			  0000101   0000101
			  00010--   000010-
			  1010      10100
			 */
			if (0 == position) {
				return;
			}
			--position;
			divisor >>= 1;
			quotient <<= 1;
		} while (remainder < divisor);
		/**
		  1st
		  0000101
		  0010---
		  101

		  2nd
		  0000001
		  000010-
		  10101
		 */
		remainder -= divisor;
		quotient |= 1;
	}

	quotient <<= position;
}
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{

	/// conpares with Biguint.
	template <typename LhsT, hryky_template_param>
	bool operator<(
		LhsT const lhs,
		Biguint<hryky_template_arg> const & rhs);

	/// retrieves the higher part of bits.
	template <hryky_template_param>
	typename Biguint<hryky_template_arg>::lower_type
		high_bits(Biguint<hryky_template_arg> const & src);

	/// retrieves the lower part of bits.
	template <hryky_template_param>
	typename Biguint<hryky_template_arg>::lower_type
		low_bits(Biguint<hryky_template_arg> const & src);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief conpares with Biguint.
 */
template <typename LhsT, hryky_template_param>
bool hryky::operator<(
	LhsT const lhs,
	Biguint<hryky_template_arg> const & rhs)
{
	return Biguint<hryky_template_arg>(lhs) < rhs;
}
/**
  @brief retrieves the higher part of bits.
 */
template <hryky_template_param>
typename hryky::Biguint<hryky_template_arg>::lower_type
hryky::high_bits(
	Biguint<hryky_template_arg> const & src)
{
	return src.high();
}
/**
  @brief retrieves the lower part of bits.
 */
template <hryky_template_param>
typename hryky::Biguint<hryky_template_arg>::lower_type
hryky::low_bits(
	Biguint<hryky_template_arg> const & src)
{
	return src.low();
}
#undef hryky_template_param
#undef hryky_template_arg
#endif // BIGUINT_H_20130921153720317
// end of file
