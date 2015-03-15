/**
  @file     utf16_decoder.h
  @brief    converts UTF-16 characters to a UTF-32 character.
  @author   HRYKY
  @version  $Id: utf16_decoder.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef UTF16_DECODER_H_20140326225717623
#define UTF16_DECODER_H_20140326225717623
#include "hryky/literal_string.h"
#include "hryky/retention/retention_value.h"
#include "hryky/stream/istream_range.h"
#include "hryky/tmp/tmp_equal.h"
#include "hryky/type_traits/conditional.h"
#include "hryky/type_traits/integral_constant.h"
#include "hryky/type_traits/remove_const_reference.h"
#include "hryky/utf16/utf16_common.h"
#include "hryky/utf16/utf16_compatible.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename Utf16StreamT, template <typename> class RetainT
#define hryky_template_arg \
	Utf16StreamT, RetainT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace utf16
{
	/// converts UTF-16 characters to a UTF-32 character.
	template <
		typename Utf16StreamT,
		template <typename> class RetainT = retention::Value
	>
	class Decoder;

} // namespace utf16
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief converts UTF-16 characters to a UTF-32 character.
 */
template <hryky_template_param>
class hryky::utf16::Decoder :
	public RetainT<Utf16StreamT>,
	public WithStreamOut<Decoder<hryky_template_arg> >,
	public WithSwap<Decoder<hryky_template_arg> >
{
public :

	typedef Decoder<hryky_template_arg>                 this_type;
	typedef RetainT<Utf16StreamT>                       retention_type;
	typedef typename retention_type::initializer_type   initializer_type;

	/// default constructor.
	Decoder();

	/// instantiates with an internal stream.
	Decoder(initializer_type stream);

	/// copy constructor.
	Decoder(this_type const &);

	/// move constructor.
	Decoder(this_type &&);

	/// destructor.
	~Decoder();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// converts UTF-16 octets to a UTF-32 character.
	this_type & operator>>(char32_t & dest);

	/// writes the converted UTF-32 character to an arbitrary stream.
	template <typename RhsT>
	this_type & operator>>(RhsT & rhs);

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// confirms whether the internal stream reaches the end.
	bool eof() const;

	/// confirms whether some errors occurred.
	bool fail() const;

protected :

private :

	union
	{
		uint32_t flags_;
		struct
		{
			bool fail_:1;
		} flag_;
	};
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace utf16
{
} // namespace utf16
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::utf16::Decoder<hryky_template_arg>::Decoder()
	: retention_type()
	  , flags_()
{
}
/**
  @brief instantiates with an internal stream.
 */
template <hryky_template_param>
hryky::utf16::Decoder<hryky_template_arg>::Decoder(initializer_type stream)
	: retention_type(stream)
	  , flags_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::utf16::Decoder<hryky_template_arg>::Decoder(
	this_type const & rhs)
	: retention_type(rhs)
	  , hryky_copy_member(flags)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::utf16::Decoder<hryky_template_arg>::Decoder(this_type && rhs)
	: retention_type(::std::move(rhs))
	  , hryky_move_member(flags)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::utf16::Decoder<hryky_template_arg>::~Decoder()
{
}
/**
  @brief converts UTF-16 octets to a UTF-32 character.
 */
template <hryky_template_param>
hryky::utf16::Decoder<hryky_template_arg> & 
hryky::utf16::Decoder<hryky_template_arg>::operator>>(
	char32_t & dest)
{
	if (this->eof()) {
		return *this;
	}
	
	if (!utf16::decode(dest, *this->get())) {
		this->flag_.fail_ = true;
	}
	
	return *this;
}
/**
  @brief writes the converted UTF-32 character to an arbitrary stream.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::utf16::Decoder<hryky_template_arg> & 
hryky::utf16::Decoder<hryky_template_arg>::operator>>(
	RhsT & rhs)
{
	if (this->eof()) {
		return *this;
	}

	char32_t dest;
	if (!utf16::decode(dest, *this->get())) {
		this->flag_.fail_ = true;
		return *this;
	}

	rhs << dest;
	
	return *this;
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::utf16::Decoder<hryky_template_arg>::clear()
{
	hryky::clear(this->flags_);
	this->retention_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::utf16::Decoder<hryky_template_arg>::swap(
	this_type & src)
{
	this->retention_type::swap(src);
	hryky_swap_member(flags);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::utf16::Decoder<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return this->retention_type::write_to(out);
}
/**
  @brief confirms whether the internal stream reaches the end.
 */
template <hryky_template_param>
bool hryky::utf16::Decoder<hryky_template_arg>::eof() const
{
	return this->get()->eof();
}
/**
  @brief confirms whether some errors occurred.
 */
template <hryky_template_param>
bool hryky::utf16::Decoder<hryky_template_arg>::fail() const
{
	return this->flag_.fail_;
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
namespace utf16
{
	/// creates an utf16::Decoder.
	template <typename Utf16StreamT>
	Decoder<Utf16StreamT> decoder(Utf16StreamT const & stream);

	/// converts string from utf16 to utf32 through two streams.
	template <typename OutputStreamT, typename InputStreamT>
	bool decode(
		OutputStreamT & out,
		InputStreamT & in);

	/// converts string between two iterators.
	template <typename OutputStreamT, typename InputIteratorT>
	bool decode(
		OutputStreamT & out,
		InputIteratorT begin,
		InputIteratorT end);

	/// converts a null-terminated string.
	template <typename OutputStreamT>
	bool decode(OutputStreamT & out, char16_t const * const c_str);

	/// converts a null-terminated wide string.
	template <typename OutputStreamT>
	bool decode(
		OutputStreamT & out,
		wchar_t const * const c_str);

	/// converts a null-terminated wide string as 16bit.
	template <typename OutputStreamT>
	bool decode(
		OutputStreamT & out,
		wchar_t const * const c_str,
		uint16_t const *);

	/// converts a null-terminated wide string as 32bit.
	template <typename OutputStreamT>
	bool decode(
		OutputStreamT & out,
		wchar_t const * const c_str,
		uint32_t const *);

} // namespace utf16
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates an utf16::Decoder.
 */
template <typename Utf16StreamT>
hryky::utf16::Decoder<Utf16StreamT>
hryky::utf16::decoder(Utf16StreamT const & stream)
{
	return Decoder<Utf16StreamT>(stream);
}
/**
  @brief converts string from utf16 to utf32 through two streams.
 */
template <typename OutputStreamT, typename InputStreamT>
bool hryky::utf16::decode(
	OutputStreamT & out, InputStreamT & input)
{
	auto decoder = utf16::decoder(input);
	
	while (!decoder.eof() && !decoder.fail()) {
		decoder >> out;
	}

	return !decoder.fail();
}
/**
  @brief converts string between two iterators.
 */
template <typename OutputStreamT, typename InputIteratorT>
bool hryky::utf16::decode(
	OutputStreamT & out, InputIteratorT begin, InputIteratorT end)
{
	auto input = istream::range(begin, end);
	return utf16::decode(out, input);
}
/**
  @brief converts a null-terminated string.
 */
template <typename OutputStreamT>
bool hryky::utf16::decode(
	OutputStreamT & out, char16_t const * const c_str)
{
	LiteralString<char16_t const> const str(c_str, length(c_str));
	
	return utf16::decode(out, str.begin(), str.end());
}
/**
  @brief converts a null-terminated wide string.
 */
template <typename OutputStreamT>
bool hryky::utf16::decode(
	OutputStreamT & out,
	wchar_t const * const c_str)
{
	return utf16::decode(
		out,
		c_str,
		reinterpret_cast<
			Conditional<tmp::Equal<
					IntegralConstant<size_t, 2>,
					IntegralConstant<size_t, sizeof(wchar_t)>
				>,
				uint16_t const *,
				Conditional<tmp::Equal<
						IntegralConstant<size_t, 4>,
						IntegralConstant<size_t, sizeof(wchar_t)>
					>,
					uint32_t const *,
					uint64_t const *
				>::type
			>::type
		>(hryky_nullptr));
}
/**
  @brief converts a null-terminated wide string as 16bit.
 */
template <typename OutputStreamT>
bool hryky::utf16::decode(
	OutputStreamT & out,
	wchar_t const * const c_str,
	uint16_t const *)
{
	return utf16::decode(
		out, reinterpret_cast<char16_t const *>(c_str));
}
/**
  @brief converts a null-terminated wide string as 32bit.
 */
template <typename OutputStreamT>
bool hryky::utf16::decode(
	OutputStreamT & out,
	wchar_t const * const c_str,
	uint32_t const *)
{
	wchar_t const * ptr = c_str;
	while (!hryky_is_null(*ptr) && !out.fail()) {
		out << *ptr;
	}
	
	return !out.fail();
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // UTF16_DECODER_H_20140326225717623
// end of file
