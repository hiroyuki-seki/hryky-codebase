/**
  @file     utf16_encoder.h
  @brief    converts characters from UTF-32 to UTF-16 through stream.
  @author   HRYKY
  @version  $Id: utf16_encoder.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef UTF16_ENCODER_H_20140701190545462
#define UTF16_ENCODER_H_20140701190545462
#include "hryky/retention/retention_value.h"
#include "hryky/utf16/utf16_common.h"
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
	/// converts characters from UTF-32 to UTF-16 through stream.
	template <
		typename Utf16StreamT,
		template <typename> class RetainT = retention::Value
	>
	class Encoder;

} // namespace utf16
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief converts characters from UTF-32 to UTF-16 through stream.
 */
template <hryky_template_param>
class hryky::utf16::Encoder :
	public RetainT<Utf16StreamT>,
	public WithStreamOut<Encoder<hryky_template_arg> >,
	public WithSwap<Encoder<hryky_template_arg> >
{
public :

	typedef Encoder<hryky_template_arg>                 this_type;
	typedef RetainT<Utf16StreamT>                       retention_type;
	typedef typename retention_type::initializer_type   initializer_type;

	/// default constructor.
	Encoder();

	/// creates an instance with a stream.
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

	/// converts a UTF-32 character to the corresponding UTF-16 units.
	this_type & operator<<(char32_t const rhs);

	/// receives a UTF-32 character from an arbitrary stream.
	template <typename RhsT>
	this_type & operator<<(RhsT & rhs);

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

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
hryky::utf16::Encoder<hryky_template_arg>::Encoder()
	: retention_type()
	  , flags_()
{
}
/**
  @brief creates an instance with a stream.
 */
template <hryky_template_param>
hryky::utf16::Encoder<hryky_template_arg>::Encoder(initializer_type stream)
	: retention_type(stream)
	  , flags_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::utf16::Encoder<hryky_template_arg>::Encoder(this_type const & rhs)
	: retention_type(rhs)
	  , hryky_copy_member(flags)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::utf16::Encoder<hryky_template_arg>::Encoder(this_type && rhs)
	: retention_type(::std::move(rhs))
	  , hryky_move_member(flags)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::utf16::Encoder<hryky_template_arg>::~Encoder()
{
}
/**
  @brief converts a UTF-32 character to the corresponding UTF-16 units.
 */
template <hryky_template_param>
hryky::utf16::Encoder<hryky_template_arg> & 
hryky::utf16::Encoder<hryky_template_arg>::operator<<(
	char32_t const rhs)
{
	if (!utf16::encode(*this->get(), rhs)) {
		this->flag_.fail_ = true;
		return *this;
	}
	
	return *this;
}
/**
  @brief receives a UTF-32 character from an arbitrary stream.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::utf16::Encoder<hryky_template_arg> & 
hryky::utf16::Encoder<hryky_template_arg>::operator<<(
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
void hryky::utf16::Encoder<hryky_template_arg>::clear()
{
	hryky::clear(this->flags_);
	this->retention_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::utf16::Encoder<hryky_template_arg>::swap(
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
StreamT & hryky::utf16::Encoder<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return this->retention_type::write_to(out);
}
/**
  @brief confirms whether some errors occurred.
 */
template <hryky_template_param>
bool hryky::utf16::Encoder<hryky_template_arg>::fail() const
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
	/// creates an utf16::Encoder.
	template <typename Utf16StreamT>
	Encoder<Utf16StreamT> encoder(Utf16StreamT const & stream);

} // namespace utf16
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates an utf16::Encoder.
 */
template <typename Utf16StreamT>
hryky::utf16::Encoder<Utf16StreamT>
hryky::utf16::encoder(Utf16StreamT const & stream)
{
	return Encoder<Utf16StreamT>(stream);
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // UTF16_ENCODER_H_20140701190545462
// end of file
