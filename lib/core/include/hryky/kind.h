/**
  @file         kind.h
  @brief        template for the class that represents the kind.
  @author       HRYKY
  @version      $Id: kind.h 377 2014-08-15 02:49:04Z hryky.private@gmail.com $
 */
#ifndef KIND_H_20120717234044653
#define KIND_H_20120717234044653
#include "hryky/common.h"
#include "hryky/literal_string.h"
#include "hryky/sieve.h"
#include "hryky/nullptr.h"
#include "hryky/pragma.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_padded
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ImplT, \
	typename ImplT::Raw Initial, \
	size_t Num, \
	typename TokenT, \
	TokenT const * Tokens
#define hryky_template_arg \
	ImplT, Initial, Num, TokenT, Tokens
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// template for the class that represents the kind.
	template <hryky_template_param>
	class Kind;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief template for the class that represents the kind.
 */
template <
	typename ImplT,
	typename ImplT::Raw Initial = static_cast<typename ImplT::Raw>(0),
	size_t Num = ImplT::num,
	typename TokenT = hryky::LiteralString<>,
	TokenT const * Tokens = &hryky::g_empty_literal_string
>
class hryky::Kind :
	public WithStreamOut<Kind<hryky_template_arg> >,
	public WithSwap<Kind<hryky_template_arg> >
{
public :
	typedef Kind<hryky_template_arg> this_type;
	typedef typename ImplT::Raw raw_type;

	/// default constructor.
	Kind();

	/// constructor with a raw data.
	Kind(raw_type const raw);

	/// copy constructor
	Kind(this_type const & rhs);

	/// move constructor.
	Kind(this_type && rhs);

	/// constructor from the range of octets.
	template <typename InputIteratorT>
	Kind(InputIteratorT begin, InputIteratorT end);

	/// constructor from the range of octets with binary predicator.
	template <typename InputIteratorT, typename EqualT>
	Kind(InputIteratorT begin, InputIteratorT end, EqualT const & equal);

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// assigns a new kind.
	this_type & operator=(raw_type const rhs);

	/// pre increment.
	this_type & operator++();

	/// post increment.
	this_type operator++(int);

	/// pre decrement.
	this_type & operator--();

	/// post decrement.
	this_type operator--(int);

	/// convert to the raw value.
	operator raw_type() const;

	/// releases the internal resources.
	void clear();

	/// confirms the value to exist in the range.
	bool verify() const;

	/// retrieves the raw data.
	raw_type raw() const;

	/// interchanges values
	void swap(this_type & src);

	/// outputs the information of Kind<RaWT, Initial>.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

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
hryky::Kind<hryky_template_arg>::Kind()
	: raw_(Initial)
{
}
/**
  @brief constructor with a raw data.
 */
template <hryky_template_param>
hryky::Kind<hryky_template_arg>::Kind(raw_type const raw)
	: raw_(raw)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::Kind<hryky_template_arg>::Kind(this_type const & rhs)
	: hryky_copy_member(raw)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::Kind<hryky_template_arg>::Kind(this_type && rhs)
	: hryky_move_member(raw)
{
}
/**
  @brief constructor from the range of octets.
 */
template <hryky_template_param>
template <typename InputIteratorT>
hryky::Kind<hryky_template_arg>::Kind(
	InputIteratorT begin, InputIteratorT end)
	: raw_(static_cast<raw_type>(Num))
{
	Sieve<this_type, Num> sieve;

	if (1u == sieve(
		begin,
		end,
		Range<TokenT const *>(&Tokens[0], &Tokens[Num]))) {
		*this = sieve.result();
	}
}
/**
  @brief constructor from the range of octets with binary predicator.
 */
template <hryky_template_param>
template <typename InputIteratorT, typename EqualT>
hryky::Kind<hryky_template_arg>::Kind(
	InputIteratorT begin, InputIteratorT end, EqualT const & equal)
	: raw_(static_cast<raw_type>(Num))
{
	Sieve<this_type, Num> sieve;

	if (1u == sieve(
		begin,
		end,
		Range<TokenT const *>(&Tokens[0], &Tokens[Num]),
		equal)) {
		*this = sieve.result();
	}
}
/**
  @brief assigns a new kind.
 */
template <hryky_template_param>
hryky::Kind<hryky_template_arg> &
hryky::Kind<hryky_template_arg>::operator=(
	raw_type const rhs)
{
	this->raw_ = rhs;
	return *this;
}
/**
  @brief pre increment.
 */
template <hryky_template_param>
hryky::Kind<hryky_template_arg> &
hryky::Kind<hryky_template_arg>::operator++()
{
	this->raw_ = static_cast<raw_type>(
		static_cast<int>(this->raw()) + 1);
	return *this;
}
/**
  @brief post increment.
 */
template <hryky_template_param>
hryky::Kind<hryky_template_arg>
hryky::Kind<hryky_template_arg>::operator++(int)
{
	this_type const ret(*this);

	this->raw_ = static_cast<raw_type>(
		static_cast<int>(this->raw()) + 1);
	
	return ret;
}
/**
  @brief pre decrement.
 */
template <hryky_template_param>
hryky::Kind<hryky_template_arg> &
hryky::Kind<hryky_template_arg>::operator--()
{
	this->raw_ = static_cast<raw_type>(
		static_cast<int>(this->raw()) - 1);
	return *this;
}
/**
  @brief post decrement.
 */
template <hryky_template_param>
hryky::Kind<hryky_template_arg>
hryky::Kind<hryky_template_arg>::operator--(int)
{
	this_type const ret(*this);

	this->raw_ = static_cast<raw_type>(
		static_cast<int>(this->raw()) - 1);
	
	return ret;
}
/**
  @brief convert to the raw value.
 */
template <hryky_template_param>
hryky::Kind<hryky_template_arg>::operator typename ImplT::Raw() const
{
	return this->raw();
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::Kind<hryky_template_arg>::clear()
{
	this->raw_ = Initial;
}
/**
  @brief retrieves the raw data.
 */
template <hryky_template_param>
typename ImplT::Raw hryky::Kind<hryky_template_arg>::raw() const
{
	return this->raw_;
}
/**
  @brief confirms the value to exist in the range.
 */
template <hryky_template_param>
bool hryky::Kind<hryky_template_arg>::verify() const
{
	return 0u <= static_cast<size_t>(this->raw())
		&& Num > static_cast<size_t>(this->raw());
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::Kind<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(raw);
}
/**
  @brief outputs the information of Kind<RaWT, Initial>.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::Kind<hryky_template_arg>::write_to(
	StreamT & out) const
{
	if (Tokens == &g_empty_literal_string) {
		out << static_cast<int>(this->raw_);
	}
	else if (0 > this->raw_ || Num <= this->raw_) {
		out << "N/A";
	}
	else {
		out << Tokens[this->raw_];
	}
	return out;
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
//------------------------------------------------------------------------------
// restores warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // KIND_H_20120717234044653
// end of file
