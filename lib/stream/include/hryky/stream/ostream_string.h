/**
  @file     ostream_string.h
  @brief    output string stream.
  @author   HRYKY
  @version  $Id: ostream_string.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef OSTREAM_STRING_H_20131002224418614
#define OSTREAM_STRING_H_20131002224418614
#include "hryky/definition.h"
#include "hryky/digits10.h"
#include "hryky/float_traits.h"
#include "hryky/power.h"
#include "hryky/pragma.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/is_null.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_padded
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename StringT
#define hryky_template_arg \
	StringT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	class Endl;
	
namespace mempool
{
	class Ptr;
}
namespace ostream
{
	/// output string stream.
	template <typename StringT>
	class String;
} // namespace ostream
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief output string stream.
 */
template <hryky_template_param>
class hryky::ostream::String :
	public WithStreamOut<String<hryky_template_arg> >,
	public WithSwap<String<hryky_template_arg> >
{
public :

	typedef String<hryky_template_arg>      this_type;
	typedef typename StringT::value_type    char_type;

	/// default constructor.
	String();

	/// creates an instance with the mempool.
	String(mempool::Ptr const & mempool);

	/// constructs with the existing string.
	String(StringT const & str);

	/// copy constructor.
	String(this_type const &);

	/// move constructor.
	String(this_type &&);

	/// destructor.
	~String();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// appends a boolean value to a stream.
	this_type & operator<<(
		bool const rhs);

	/// appends a character to an output string-stream.
	this_type & operator<<(
		char const rhs);

	/// appends an addressto an output string-stream.
	this_type & operator<<(
		void const * const rhs);

	/// appends a null-terminated string to an output string-stream.
	this_type & operator<<(
		char const * const rhs);

	/// appends a floating point to an output string-stream.
	this_type & operator<<(
		float const rhs);

	/// appends a double-precision floating point to an output string-stream.
	this_type & operator<<(
		double const rhs);

	/// appends a 8bit signed integer to an output string-stream.
	this_type & operator<<(
		int8_t const rhs);

	/// appends a 8bit unsigned integer to an output string-stream.
	this_type & operator<<(
		uint8_t const rhs);

	/// appends a 16bit signed integer to an output string-stream.
	this_type & operator<<(
		int16_t const rhs);

	/// appends a 16bit unsigned integer to an output string-stream.
	this_type & operator<<(
		uint16_t const rhs);

	/// appends a 32bit signed integer to an output string-stream.
	this_type & operator<<(
		int32_t const rhs);

	/// appends a 32bit unsigned integer to an output string-stream.
	this_type & operator<<(
		uint32_t const rhs);

	/// appends a 64bit signed integer to output string-stream.
	this_type & operator<<(
		int64_t const rhs);

	/// appends a 64bit unsigned integer to output string-stream.
	this_type & operator<<(
		uint64_t const rhs);

	/// appends a 16bit char to output string-stream.
	this_type & operator<<(
		char16_t const rhs);

	/// appends a 32bit char to output string-stream.
	this_type & operator<<(
		char32_t const rhs);

#if hryky_distinct_int_and_int32
	/// appends an signed integer to an output string-stream.
	this_type & operator<<(
		int const rhs);

	/// appends an unsigned integer to an output string-stream.
	this_type & operator<<(
		unsigned int const rhs);
#endif // hryky_distinct_int_and_int32

	/// appends a line-break.
	this_type & operator<<(
		Endl const & rhs);

	/// appends a nullptr.
	this_type & operator<<(
		::std::nullptr_t);

	/// output the information to a stream.
	template <typename RhsT>
	this_type & operator<<(
		WithStreamOut<RhsT> const & rhs);

#if hryky_msvs_ver
	/// appends a DWORD to output string-stream.
	this_type & operator<<(DWORD const rhs);
#endif // hryky_msvs_ver

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// retrieves the reference to the immutable string.
	StringT const & str() const;

	/// appends a character.
	this_type & write(char const src);

	/// appends an array of characters.
	template <size_t Size>
	this_type & write(char_type const (&str)[Size]);

	/// appends characters.
	this_type & write(char_type const * const str, size_t const size);

#if hryky_distinct_int_and_int32
	/// appends an signed integer.
	this_type & write(int const src);

	/// appends an unsigned integer.
	this_type & write(unsigned int const src);
#endif // hryky_distinct_int_and_int32

	/// appends a 32bit signed integer.
	this_type & write(int32_t const src);

	/// appends a 32bit unsigned integer.
	this_type & write(uint32_t const src);

	/// appends a 64bit signed integer.
	this_type & write(int64_t const src);

	/// appends a 64bit unsigned integer.
	this_type & write(uint64_t const src);

	/// appends a 16bit char.
	this_type & write(char16_t const src);

	/// appends a 32bit char.
	this_type & write(char32_t const src);

	/// appends a single precision floating-point.
	this_type & write(float const src);

	/// appends a double precision floating-point.
	this_type & write(double const src);

	/// appends a boolean value.
	this_type & write(bool const src);

	/// appends an address.
	this_type & write(void const * const src);

	/// appends a string.
	this_type & write(StringT const & src);

	/// appends a line-break.
	this_type & write(Endl const &);

#if hryky_msvs_ver
	/// appends a DWORD.
	this_type & write(DWORD const src);
#endif // hryky_msvs_ver
	
	/// prescribes whether a boolean value is represented as string.
	void boolalpha(bool const src);
	
	/// prescribes whether a number is represented as hexadecimal.
	void hex(bool const src);

	/**
	  prescribes whether a number is represented with the specifier of
	  the radix.
	 */
	void showbase(bool const src);

protected :

private :

	/// appends a signed integer.
	template <typename IntT>  
	this_type & write_int(IntT const src);

	/// appends an unsigned integer.
	template <typename UintT>
	this_type & write_uint(UintT const src);

	/// appends a floating-point number.
	template <typename FloatT>
	this_type & write_float(FloatT const src);

	/// appends an unsigned integer as hexadecimal.
	template <typename UintT>
	this_type & write_hex(UintT const src);

	StringT str_;

	union
	{
		uint32_t flags_;
		struct
		{
			bool boolalpha_:1;
			bool hex_:1;
			bool showbase_:1;
		} flag_;
	};

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace ostream
{
} // namespace ostream
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg>::String()
	: str_()
	  , flags_()
{
}
/**
  @brief creates an instance with the mempool.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg>::String(
	mempool::Ptr const & mempool)
	: str_(mempool)
	  , flags_()
{
}
/**
  @brief constructs with the existing string.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg>::String(StringT const & str)
	: str_(str)
	  , flags_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg>::String(this_type const & rhs)
	: hryky_copy_member(str)
	  , hryky_copy_member(flags)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg>::String(this_type && rhs)
	: hryky_move_member(str)
	  , hryky_move_member(flags)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg>::~String()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::ostream::String<hryky_template_arg>::clear()
{
	hryky::clear(this->flags_);
	hryky::clear(this->str_);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::ostream::String<hryky_template_arg>::write_to(
	StreamT & out) const
{
	out << this->str_.c_str();
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::ostream::String<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(str);
	hryky_swap_member(flags);
}
/**
  @brief retrieves the reference to the immutable string.
 */
template <hryky_template_param>
StringT const & hryky::ostream::String<hryky_template_arg>::str() const
{
	return this->str_;
}
/**
  @brief appends a character.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> & 
hryky::ostream::String<hryky_template_arg>::write(
	char const src)
{
	this->str_.append(src);
	return *this;
}
/**
  @brief appends an array of characters.
 */
template <hryky_template_param>
template <size_t Size>
hryky::ostream::String<hryky_template_arg> & 
hryky::ostream::String<hryky_template_arg>::write(
	char_type const (&str)[Size])
{
	this->str_.append(str);
	return *this;
}
/**
  @brief appends characters.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> & 
hryky::ostream::String<hryky_template_arg>::write(
	char_type const * const str, size_t const size)
{
	if (hryky_is_null(str)) {
		return *this;
	}
	this->str_.append(str, size);
	return *this;
}
#if hryky_distinct_int_and_int32
/**
  @brief appends an signed integer.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> & 
hryky::ostream::String<hryky_template_arg>::write(
	int const src)
{
	typedef ::std::make_unsigned<int>::type unsigned_type;
	
	return (
		this->flag_.hex_
		? this->write_hex<unsigned_type>(
			static_cast<unsigned_type>(src))
		: this->write_int<int>(src));
}
/**
  @brief appends an unsigned integer.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> & 
hryky::ostream::String<hryky_template_arg>::write(
	unsigned int const src)
{
	return (
		this->flag_.hex_
		? this->write_hex<uint32_t>(src)
		: this->write_uint<uint32_t>(src));
}
#endif // hryky_distinct_int_and_int32
/**
  @brief appends a 32bit signed integer.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> & 
hryky::ostream::String<hryky_template_arg>::write(
	int32_t const src)
{
	typedef ::std::make_unsigned<int32_t>::type unsigned_type;
	
	return (
		this->flag_.hex_
		? this->write_hex<unsigned_type>(
			static_cast<unsigned_type>(src))
		: this->write_int<int32_t>(src));
}
/**
  @brief appends a 32bit unsigned integer.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> & 
hryky::ostream::String<hryky_template_arg>::write(
	uint32_t const src)
{
	return (
		this->flag_.hex_
		? this->write_hex<uint32_t>(src)
		: this->write_uint<uint32_t>(src));
}
/**
  @brief appends a 64bit signed integer.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> & 
hryky::ostream::String<hryky_template_arg>::write(
	int64_t const src)
{
	typedef ::std::make_unsigned<int64_t>::type unsigned_type;
	
	return (
		this->flag_.hex_
		? this->write_hex<unsigned_type>(
			static_cast<unsigned_type>(src))
		: this->write_int<int64_t>(src));
}
/**
  @brief appends a 64bit unsigned integer.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> & 
hryky::ostream::String<hryky_template_arg>::write(
	uint64_t const src)
{
	return (
		this->flag_.hex_
		? this->write_hex<uint64_t>(src)
		: this->write_uint<uint64_t>(src));
}
/**
  @brief appends a 16bit char.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> & 
hryky::ostream::String<hryky_template_arg>::write(
	char16_t const src)
{
	return this->write(static_cast<uint16_t>(src));
}
/**
  @brief appends a 32bit char.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> & 
hryky::ostream::String<hryky_template_arg>::write(
	char32_t const src)
{
	return this->write(static_cast<uint32_t>(src));
}
/**
  @brief appends a boolean value.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> & 
hryky::ostream::String<hryky_template_arg>::write(
	bool const src)
{
	if (src) {
		this->str_.append("true");
	}
	else {
		this->str_.append("false");
	}
	return *this;
}
/**
  @brief appends a single precision floating-point.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> & 
hryky::ostream::String<hryky_template_arg>::write(
	float const src)
{
	return this->write_float<float>(src);
}
/**
  @brief appends a double precision floating-point.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> & 
hryky::ostream::String<hryky_template_arg>::write(
	double const src)
{
	return this->write_float<double>(src);
}
/**
  @brief appends an address.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> & 
hryky::ostream::String<hryky_template_arg>::write(
	void const * const src)
{
	return this->write_hex<size_t>(
		reinterpret_cast<size_t>(src));
}
/**
  @brief appends a string.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> & 
hryky::ostream::String<hryky_template_arg>::write(
	StringT const & src)
{
	this->str_.append(src);
	return *this;
}
/**
  @brief appends a line-break.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> & 
hryky::ostream::String<hryky_template_arg>::write(
	Endl const &)
{
	return this->write('\n');
}
#if hryky_msvs_ver
/**
  @brief appends a DWORD.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> & 
hryky::ostream::String<hryky_template_arg>::write(
	DWORD const src)
{
	return this->write(static_cast<uint32_t>(src));
}
#endif // hryky_msvs_ver
/**
  @brief prescribes whether a boolean value is represented as string.
 */
template <hryky_template_param>
void
hryky::ostream::String<hryky_template_arg>::boolalpha(
	bool const src)
{
	this->flag_.boolalpha_ = src;
}
/**
  @brief prescribes whether a number is represented as hexadecimal.
 */
template <hryky_template_param>
void
hryky::ostream::String<hryky_template_arg>::hex(
	bool const src)
{
	this->flag_.hex_ = src;
}
/**
  @brief prescribes whether a number is represented with
  the specifier of the radix.
 */
template <hryky_template_param>
void
hryky::ostream::String<hryky_template_arg>::showbase(
	bool const src)
{
	this->flag_.showbase_ = src;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief appends a signed integer.
 */
template <hryky_template_param>
template <typename IntT>
hryky::ostream::String<hryky_template_arg> & 
hryky::ostream::String<hryky_template_arg>::write_int(
	IntT const src)
{
	char_type buf[::std::numeric_limits<IntT>::digits10 + 3] = {0, };
	size_t index = 0u;

	bool const negative = 0 > src;

	IntT dividend = negative ? -src : src;

	do {
		buf[index] = '0' + dividend % 10;
		dividend /= 10;
		++index;
	} while (0 != dividend);

	if (negative) {
		buf[index] = '-';
		++index;
	}

	::std::reverse(&buf[0], &buf[index]);

	this->str_.append(&buf[0], index);

	return *this;
}
/**
  @brief appends an unsigned integer.
 */
template <hryky_template_param>
template <typename UintT>
hryky::ostream::String<hryky_template_arg> & 
hryky::ostream::String<hryky_template_arg>::write_uint(
	UintT const src)
{
	char_type buf[::std::numeric_limits<UintT>::digits10 + 2]
		= {char_type(), };
	size_t index = 0u;

	UintT dividend = src;

	do {
		buf[index] = static_cast<char_type>('0' + dividend % 10u);
		dividend /= 10u;
		++index;
	} while (0u != dividend);

	::std::reverse(&buf[0], &buf[index]);

	this->str_.append(&buf[0], index);

	return *this;
}
/**
  @brief appends an unsigned integer as hexadecimal.
 */
template <hryky_template_param>
template <typename UintT>
hryky::ostream::String<hryky_template_arg> & 
hryky::ostream::String<hryky_template_arg>::write_hex(
	UintT const src)
{
	UintT dividend          = src;
	size_t const hex_num    = ::std::numeric_limits<UintT>::digits >> 2u;
	char_type buf[hex_num]  = {0,};
	size_t const radix      = 16u;
	size_t const radix_exp  = 4u;
	size_t const radix_mask = radix - 1u;

	char_type const hex_chars[radix] = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F', 
	};
	
	size_t hex_id = 0;
	for (; hex_num != hex_id; ++hex_id, dividend >>= radix_exp) {
		buf[hex_num - hex_id - 1] = hex_chars[dividend & radix_mask];
	}

	this->str_.append("0x");
	this->str_.append(&buf[0], hex_num);

	return *this;
}
/**
  @brief appends a floating-point number.
 */
template <hryky_template_param>
template <typename FloatT>
hryky::ostream::String<hryky_template_arg> & 
hryky::ostream::String<hryky_template_arg>::write_float(
	FloatT const src)
{
	typedef FloatTraits<FloatT> traits;
	typedef traits::binary_type binary_type;

	/**
	  0.0 will be frequent.
	 */
	if (0 == src) {
		this->str_.append("0.0");
		return *this;
	}
	/**
	  1.0 will be frequent.
	 */
	else if (1 == src) {
		this->str_.append("1.0");
		return *this;
	}
	
	binary_type const bin
		= *reinterpret_cast<binary_type const *>(&src);
	bool const negative = 0 != (traits::sign_mask & bin);

	if (negative) {
		this->str_.append('-');
	}

	/**
	  special case.
	 */
	if (traits::exponent_mask == (bin & traits::exponent_mask)) {
		if (0 == (bin & traits::fraction_mask)) {
			this->str_.append("INF");
		}
		else {
			this->str_.append("NaN");
		}
	}
	else {
		FloatT dividend = negative ? -src : src;
		binary_type const before_point = static_cast<binary_type>(
			::std::floor(dividend));

		/**
		  1 <= src.
		 */
		if (0 < before_point) {
			binary_type const digits10 = static_cast<binary_type>(
				hryky::digits10(before_point));
			/**
			  The size of integer part is larger than the significant digits.
			 */
			if (traits::significant_width < digits10) {
				size_t const exponent = static_cast<size_t>(
					digits10 - traits::significant_width);
				size_t const exponent_rank = hryky::pow(10u, exponent);
				this->write(before_point / exponent_rank);
				this->str_.append("e+");
				this->write(exponent);
			}
			/**
			  The size of integer part is equal to the significant digits.
			 */
			else if (traits::significant_width == digits10) {
				this->write(before_point);
			}
			/**
			  The size of integer part is smaller than the significant digits
			  but the exponential part isn't needed.
			 */
			else {
				this->write(before_point);
				size_t const after_point_width =
					traits::significant_width - digits10;
				binary_type const after_point_rank =
					hryky::pow<binary_type>(10u, after_point_width);
				this->str_.append('.');
				binary_type const after_point = static_cast<binary_type>(
					::std::floor(
						dividend * after_point_rank)) % after_point_rank;
				this->write(after_point);
			}
		}
		/**
		  1 > src.
		 */
		else {
			size_t const exponent_max = traits::significant_width * 2u;
			size_t exponent = 0u;
			binary_type exponent_rank = 1u;
			/**
			  counts the negative exponent until the first significant
			  number appears.
			 */
			do {
				++exponent;
				if (exponent_max == exponent) {
					this->str_.append("0.0");
					return *this;
				}
				
				exponent_rank *= 10u;
			} while (0 == static_cast<binary_type>(
				::std::floor(dividend * exponent_rank)));

			this->str_.append("0.");
			this->write(static_cast<binary_type>(::std::floor(
				dividend * exponent_rank *
				hryky::pow<binary_type>(
					10u, traits::significant_width - 1u))));
			if (1 < exponent) {
				this->str_.append("e-");
				this->write(exponent - 1u);
			}
		}
	}

	return *this;
}
/**
  @brief appends a boolean value to a stream.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> & 
hryky::ostream::String<hryky_template_arg>::operator<<(
	bool const rhs)
{
	return this->write(rhs);
}
/**
  @brief appends a character to an output string-stream.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> &
hryky::ostream::String<hryky_template_arg>::operator<<(
	char const rhs)
{
	return this->write(rhs);
}
/**
  @brief appends an addressto an output string-stream.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> &
hryky::ostream::String<hryky_template_arg>::operator<<(
	void const * const rhs)
{
	return this->write(rhs);
}
/**
  @brief appends a null-terminated string to an output string-stream.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> &
hryky::ostream::String<hryky_template_arg>::operator<<(
	char const * const rhs)
{
	return (
		hryky::is_null(rhs)
		? *this
		: this->write(rhs, ::std::strlen(rhs)));
}
/**
  @brief appends a floating point to an output string-stream.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> &
hryky::ostream::String<hryky_template_arg>::operator<<(
	float const rhs)
{
	return this->write(rhs);
}
#if hryky_distinct_int_and_int32
/**
  @brief appends an signed integer to an output string-stream.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> &
hryky::ostream::String<hryky_template_arg>::operator<<(
	int const rhs)
{
	return this->write(rhs);
}
/**
  @brief appends an unsigned integer to an output string-stream.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> &
hryky::ostream::String<hryky_template_arg>::operator<<(
	unsigned int const rhs)
{
	return this->write(rhs);
}
#endif // hryky_distinct_int_and_int32
/**
  @brief appends a 8bit signed integer to an output string-stream.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> &
hryky::ostream::String<hryky_template_arg>::operator<<(
	int8_t const rhs)
{
	return this->write(rhs);
}
/**
  @brief appends a 8bit unsigned integer to an output string-stream.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> &
hryky::ostream::String<hryky_template_arg>::operator<<(
	uint8_t const rhs)
{
	return this->write(rhs);
}
/**
  @brief appends a 16bit signed integer to an output string-stream.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> &
hryky::ostream::String<hryky_template_arg>::operator<<(
	int16_t const rhs)
{
	return this->write(rhs);
}
/**
  @brief appends a 16bit unsigned integer to an output string-stream.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> &
hryky::ostream::String<hryky_template_arg>::operator<<(
	uint16_t const rhs)
{
	return this->write(rhs);
}
/**
  @brief appends a 32bit signed integer to an output string-stream.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> &
hryky::ostream::String<hryky_template_arg>::operator<<(
	int32_t const rhs)
{
	return this->write(rhs);
}
/**
  @brief appends a 32bit unsigned integer to an output string-stream.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> &
hryky::ostream::String<hryky_template_arg>::operator<<(
	uint32_t const rhs)
{
	return this->write(rhs);
}
/**
  @brief appends a double-precision floating point to an output string-stream.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> &
hryky::ostream::String<hryky_template_arg>::operator<<(
	double const rhs)
{
	return this->write(rhs);
}
/**
  @brief appends a 64bit signed integer to output string-stream.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> &
hryky::ostream::String<hryky_template_arg>::operator<<(
	int64_t const rhs)
{
	return this->write(rhs);
}
/**
  @brief appends a 64bit unsigned integer to output string-stream.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> &
hryky::ostream::String<hryky_template_arg>::operator<<(
	uint64_t const rhs)
{
	return this->write(rhs);
}
/**
  @brief appends a 16bit char to output string-stream.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> &
hryky::ostream::String<hryky_template_arg>::operator<<(
	char16_t const rhs)
{
	return this->write(rhs);
}
/**
  @brief appends a 32bit char to output string-stream.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> &
hryky::ostream::String<hryky_template_arg>::operator<<(
	char32_t const rhs)
{
	return this->write(rhs);
}
/**
  @brief appends a line-break.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> &
hryky::ostream::String<hryky_template_arg>::operator<<(
	Endl const & rhs)
{
	return this->write(rhs);
}
/**
  @brief appends a nullptr.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> &
hryky::ostream::String<hryky_template_arg>::operator<<(
	::std::nullptr_t)
{
	return this->write(hryky_nullptr);
}
#if hryky_msvs_ver
/**
  @brief appends a DWORD.
 */
template <hryky_template_param>
hryky::ostream::String<hryky_template_arg> &
hryky::ostream::String<hryky_template_arg>::operator<<(
	DWORD const rhs)
{
	return this->write(rhs);
}
#endif // hryky_msvs_ver
/**
  @brief output the information to a stream.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::ostream::String<hryky_template_arg> &
hryky::ostream::String<hryky_template_arg>::operator<<(
	WithStreamOut<RhsT> const & rhs)
{
	return static_cast<RhsT const &>(rhs).write_to(*this);
}
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace ostream
{
} // namespace ostream
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
//------------------------------------------------------------------------------
// restores warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // OSTREAM_STRING_H_20131002224418614
// end of file
