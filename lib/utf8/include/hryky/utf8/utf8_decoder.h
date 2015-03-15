/**
  @file     utf8_decoder.h
  @brief    decodes characters in UTF-8 string as the corresponding characters encoded by UTF-32.
  @author   HRYKY
  @version  $Id: utf8_decoder.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef UTF8_DECODER_H_20140701171652386
#define UTF8_DECODER_H_20140701171652386
#include "hryky/retention/retention_value.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/stream/istream_range.h"
#include "hryky/utf8/utf8_common.h"
#include "hryky/strlen.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename Utf8StreamT, template <typename> class RetainT
#define hryky_template_arg \
	Utf8StreamT, RetainT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace utf8
{
	/// decodes characters in UTF-8 string as the corresponding characters encoded by UTF-32.
	template <
		typename Utf8StreamT,
		template <typename> class RetainT = retention::Value
	>
	class Decoder;

} // namespace utf8
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief decodes characters in UTF-8 string as the corresponding characters encoded by UTF-32.
 */
template <hryky_template_param>
class hryky::utf8::Decoder :
	public RetainT<Utf8StreamT>,
	public WithStreamOut<Decoder<hryky_template_arg> >,
	public WithSwap<Decoder<hryky_template_arg> >
{
public :

	typedef Decoder<hryky_template_arg>                 this_type;
	typedef RetainT<Utf8StreamT>                        retention_type;
	typedef typename retention_type::initializer_type   initializer_type;

	/// default constructor.
	Decoder();

	/// creates an instance with a stream.
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

	/// converts UTF-8 octets to the UTF-32 character.
	this_type & operator>>(char32_t & dest);

	/// outputs the decoded character to the arbitrary stream.
	template <typename RhsT>
	this_type & operator>>(RhsT & rhs);

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// confirms whether the internal stream is at the end.
	bool eof() const;

	/// confirms whether the past conversion was failed.
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
namespace utf8
{
} // namespace utf8
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::utf8::Decoder<hryky_template_arg>::Decoder()
	: retention_type()
	  , flags_()
{
}
/**
  @brief creates an instance with a stream.
 */
template <hryky_template_param>
hryky::utf8::Decoder<hryky_template_arg>::Decoder(initializer_type stream)
	: retention_type(stream)
	  , flags_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::utf8::Decoder<hryky_template_arg>::Decoder(this_type const & rhs)
	: retention_type(rhs)
	  , hryky_copy_member(flags)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::utf8::Decoder<hryky_template_arg>::Decoder(this_type && rhs)
	: retention_type(::std::move(rhs))
	  , hryky_move_member(flags)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::utf8::Decoder<hryky_template_arg>::~Decoder()
{
}
/**
  @brief converts UTF-8 octets to the UTF-32 character.
 */
template <hryky_template_param>
hryky::utf8::Decoder<hryky_template_arg> & 
hryky::utf8::Decoder<hryky_template_arg>::operator>>(
	char32_t & dest)
{
	if (this->eof()) {
		return *this;
	}
	
	if (!utf8::decode(dest, *this->get())) {
		this->flag_.fail_ = true;
	}
	
	return *this;
}
/**
  @brief outputs the decoded character to the arbitrary stream.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::utf8::Decoder<hryky_template_arg> & 
hryky::utf8::Decoder<hryky_template_arg>::operator>>(
	RhsT & rhs)
{
	if (this->eof()) {
		return *this;
	}

	char32_t dest;
	if (!utf8::decode(dest, *this->get())) {
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
void hryky::utf8::Decoder<hryky_template_arg>::clear()
{
	hryky::clear(this->flags_);
	this->retention_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::utf8::Decoder<hryky_template_arg>::swap(this_type & src)
{
	this->retention_type::swap(src);
	hryky_swap_member(flags);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::utf8::Decoder<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return this->retention_type::write_to(out);
}
/**
  @brief confirms whether the internal stream is at the end.
 */
template <hryky_template_param>
bool hryky::utf8::Decoder<hryky_template_arg>::eof() const
{
	return this->get()->eof();
}
/**
  @brief confirms whether the past conversion was failed.
 */
template <hryky_template_param>
bool hryky::utf8::Decoder<hryky_template_arg>::fail() const
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
namespace utf8
{
	/// creates an utf8::Decoder.
	template <typename Utf8StreamT>
	Decoder<Utf8StreamT> decoder(Utf8StreamT const & stream);

	/// converts string from UTF-8 to UTF-32 between two streams.
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
	bool decode(OutputStreamT & out, char const * const c_str);

} // namespace utf8
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates an utf8::Decoder.
 */
template <typename Utf8StreamT>
hryky::utf8::Decoder<Utf8StreamT>
hryky::utf8::decoder(Utf8StreamT const & stream)
{
	return Decoder<Utf8StreamT>(stream);
}
/**
  @brief converts string from UTF-8 to UTF-32 between two streams.
 */
template <typename OutputStreamT, typename InputStreamT>
bool hryky::utf8::decode(
	OutputStreamT & out, InputStreamT & input)
{
	auto decoder = utf8::decoder(input);
	
	while (!decoder.eof() && !decoder.fail()) {
		decoder >> out;
	}

	return !decoder.fail();
}
/**
  @brief converts string between two iterators.
 */
template <typename OutputStreamT, typename InputIteratorT>
bool hryky::utf8::decode(
	OutputStreamT & out, InputIteratorT begin, InputIteratorT end)
{
	auto input = istream::range(begin, end);
	return utf8::decode(out, input);
}
/**
  @brief converts a null-terminated string.
 */
template <typename OutputStreamT>
bool hryky::utf8::decode(OutputStreamT & out, char const * const c_str)
{
	LiteralString<char const> const str(c_str, hryky::strlen(c_str));
	
	return utf8::decode(out, str.begin(), str.end());
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // UTF8_DECODER_H_20140701171652386
// end of file
