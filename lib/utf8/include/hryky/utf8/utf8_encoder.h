/**
  @file     utf8_encoder.h
  @brief    encode character to UTF-8 string.
  @author   HRYKY
  @version  $Id: utf8_encoder.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef UTF8_ENCODER_H_20140325231446635
#define UTF8_ENCODER_H_20140325231446635
#include "hryky/retention/retention_value.h"
#include "hryky/utf8/utf8_common.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
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
	/// encode character to UTF-8 string.
	template <
		typename Utf8StreamT,
		template <typename> class RetainT = retention::Value
	>
	class Encoder;

} // namespace utf8
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief encode character to UTF-8 string.
 */
template <hryky_template_param>
class hryky::utf8::Encoder :
	public RetainT<Utf8StreamT>,
	public WithStreamOut<Encoder<hryky_template_arg> >,
	public WithSwap<Encoder<hryky_template_arg> >
{
public :

	typedef Encoder<hryky_template_arg>                 this_type;
	typedef RetainT<Utf8StreamT>                        retention_type;
	typedef typename retention_type::initializer_type   initializer_type;

	// default constructor.
	Encoder();
	
	/// instantiates with an initializer.
	Encoder(initializer_type stream);

	/// copy constructor.
	Encoder(this_type const &);

	/// move constructor.
	Encoder(this_type &&);

	/// destructor.
	~Encoder();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// converts a UTF-32 character to UTF-8 string.
	this_type & operator<<(char32_t const rhs);

	/// inputs the UTF-32 character from an arbitrary stream.
	template <typename RhsT>
	this_type & operator<<(RhsT & rhs);

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// confirms whether the iterator reaches the end.
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
hryky::utf8::Encoder<hryky_template_arg>::Encoder()
	: retention_type()
	  , flags_()
{
}
/**
  @brief instantiates with an initializer.
 */
template <hryky_template_param>
hryky::utf8::Encoder<hryky_template_arg>::Encoder(
	initializer_type stream)
	: retention_type(stream)
	  , flags_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::utf8::Encoder<hryky_template_arg>::Encoder(
	this_type const & rhs)
	: retention_type(rhs)
	  , hryky_copy_member(flags)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::utf8::Encoder<hryky_template_arg>::Encoder(
	this_type && rhs)
	: retention_type(::std::move(rhs))
	  , hryky_move_member(flags)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::utf8::Encoder<hryky_template_arg>::~Encoder()
{
}
/**
  @brief converts a UTF-32 character to UTF-8 string.
 */
template <hryky_template_param>
hryky::utf8::Encoder<hryky_template_arg> & 
hryky::utf8::Encoder<hryky_template_arg>::operator<<(
	char32_t const rhs)
{
	if (!utf8::encode(*this->get(), rhs)) {
		this->flag_.fail_ = true;
		return *this;
	}
	
	return *this;
}
/**
  @brief inputs the UTF-32 character from an arbitrary stream.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::utf8::Encoder<hryky_template_arg> & 
hryky::utf8::Encoder<hryky_template_arg>::operator<<(
	RhsT & rhs)
{
	char32_t ucs;
	rhs >> ucs;
	
	return this->operator<<(ucs);
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::utf8::Encoder<hryky_template_arg>::clear()
{
	hryky::clear(this->flags_);
	this->retention_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::utf8::Encoder<hryky_template_arg>::swap(this_type & src)
{
	this->retention_type::swap(src);
	hryky_swap_member(flags);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::utf8::Encoder<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return this->retention_type::write_to(out);
}
/**
  @brief confirms whether the iterator reaches the end.
 */
template <hryky_template_param>
bool hryky::utf8::Encoder<hryky_template_arg>::eof() const
{
	return this->get()->eof();
}
/**
  @brief confirms whether some errors occurred.
 */
template <hryky_template_param>
bool hryky::utf8::Encoder<hryky_template_arg>::fail() const
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
	/// creates an utf8::Encoder.
	template <typename Utf8StreamT>
	Encoder<Utf8StreamT> encoder(Utf8StreamT const & stream);

} // namespace utf8
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates an utf8::Encoder.
 */
template <typename Utf8StreamT>
hryky::utf8::Encoder<Utf8StreamT>
hryky::utf8::encoder(Utf8StreamT const & stream)
{
	return Encoder<Utf8StreamT>(stream);
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // UTF8_ENCODER_H_20140325231446635
// end of file
