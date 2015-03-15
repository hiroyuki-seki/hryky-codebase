/**
  @file         literal_string.h
  @brief        retains a literal string.
  @author       HRYKY
  @version      $Id: literal_string.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef LITERAL_STRING_H_20120922194704491
#define LITERAL_STRING_H_20120922194704491
#include "hryky/iterator/iterator_random.h"
#include "hryky/pragma.h"
#include "hryky/stream/stream_denote.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/std/std_iterator.h"
#include "hryky/strstr.h"
#include "hryky/is_null.h"
//------------------------------------------------------------------------------
// disable warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_padded
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename CharT
#define hryky_template_arg \
	CharT
/**
  defines a literal string with the size.
 */
#define hryky_literal_string(value) \
	hryky::LiteralString<>(#value)
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retains a literal string and its length.
	template <
		typename CharT = char
	>
	class LiteralString;

	extern LiteralString<> const g_empty_literal_string;
	
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains a literal string and its length.
 */
template <hryky_template_param>
class hryky::LiteralString :
	public WithStreamOut<LiteralString<hryky_template_arg> >,
	public WithSwap<LiteralString<hryky_template_arg> >
{
public :
	typedef LiteralString<hryky_template_arg>               this_type;
	typedef CharT                                           value_type;
	typedef CharT const *                                   pointer;
	typedef CharT const &                                   reference;
	typedef CharT const *                                   const_pointer;
	typedef CharT const &                                   const_reference;
	typedef ::std::size_t                                     size_type;
	typedef ::std::ptrdiff_t                                  difference_type;
	typedef hryky::iterator::random::Immutable<this_type>   iterator;
	typedef hryky::iterator::random::Immutable<this_type>   const_iterator;
	typedef ::std::reverse_iterator<iterator>                 reverse_iterator;
	typedef ::std::reverse_iterator<iterator>                 const_reverse_iterator;

	/// the index which specifies the end of string.
	static size_type const npos = static_cast<size_type>(-1);

	/// default constructor.
	LiteralString();

	/// constructor wit a literal string.
	template < size_type Size >
	explicit LiteralString(CharT const (&c_str)[Size]);

	/// copy constructor.
	LiteralString(this_type const & rhs);

	/// move constructor.
	LiteralString(this_type && rhs);

	/// instantiates with a null-terminated string and its length.
	LiteralString(pointer const c_str, size_type const size);

	/// destructor.
	~LiteralString();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// assigns a new literal string.
	template <size_t Size>
	this_type & operator=(CharT const (&rhs)[Size]);

	/// confirms the equality between two instances.
	bool operator==(this_type const & rhs) const;

	/// confirms whether each instance has a different value.
	bool operator!=(this_type const & rhs) const;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// retrieves the null-terminated string.
	const_pointer c_str() const;

	/// retrieves the internal array of characters.
	const_pointer data() const;

	/// retrieves the length of the literal string.
	size_type size() const;

	/// confirms whether the literal string has not character.
	bool empty() const;

	/// retrieves the beginning of the literal string.
	const_iterator begin() const;

	/// retrieves the end of the literal string.
	const_iterator end() const;

	/// refers the element of the listeral string by index.
	const_reference operator[](size_type const index) const;

	/// finds the first substring.
	template <typename TargetT>
	size_type find(TargetT const & target) const;

	/// finds the first substring following the specified position.
	template <typename TargetT>
	size_type find(
		TargetT const & target,
		size_type const position) const;

	/// outputs the information of LiteralString.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// splits this string by the delimiter.
	template <typename OutputIteratorT, typename DelimiterT>
	void split_to(
		OutputIteratorT dest,
		DelimiterT const & delimiter) const;

	/// provides separated substrings to functor.
	template <typename FunctorT, typename DelimiterT>
	void split(
		FunctorT const & functor,
		DelimiterT const & delimiter) const;

	/// resets the internal data by a new array.
	template <size_t Size>
	void assign(CharT const (&c_str)[Size]);

	/// resets the internal data by the range of characters.
	void assign(pointer const ptr, size_type const size);

private :
	static value_type const null = 0;

	pointer     c_str_;
	size_type   size_;
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
hryky::LiteralString<hryky_template_arg>::LiteralString()
	: c_str_(&this_type::null)
	  , size_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::LiteralString<hryky_template_arg>::LiteralString(
	this_type const & rhs)
	: hryky_copy_member(c_str)
	  , hryky_copy_member(size)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::LiteralString<hryky_template_arg>::LiteralString(
	this_type && rhs)
	: hryky_move_member(c_str)
	  , hryky_move_member(size)
{
}
/**
  @brief constructor with an array of characters.
 */
template <hryky_template_param>
template <size_t Size>
hryky::LiteralString<hryky_template_arg>::LiteralString(
	CharT const (&c_str)[Size])
	: c_str_(c_str)
	  , size_(Size - 1)
{
	return;
}
/**
  @brief instantiates with a null-terminated string and its length.
 */
template <hryky_template_param>
hryky::LiteralString<hryky_template_arg>::LiteralString(
	pointer const c_str, size_type const size)
	: c_str_(c_str)
	  , size_(size)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::LiteralString<hryky_template_arg>::~LiteralString()
{
}
/**
  @brief refers the element of the listeral string by index.
 */
template <hryky_template_param>
typename hryky::LiteralString<hryky_template_arg>::const_reference
hryky::LiteralString<hryky_template_arg>::operator[](
	size_type const index) const
{
	return this->c_str_[index];
}
/**
  @brief assigns a new literal string.
 */
template <hryky_template_param>
template <size_t Size>
hryky::LiteralString<hryky_template_arg> &
hryky::LiteralString<hryky_template_arg>::operator=(
	CharT const (&rhs)[Size])
{
	this_type(rhs).swap(*this);

	return *this;
}
/**
  @brief confirms the equality between two instances.
 */
template <hryky_template_param>
bool hryky::LiteralString<hryky_template_arg>::operator==(
	this_type const & rhs) const
{
	if (this->size_ != rhs.size_) {
		return false;
	}
	return 0 == hryky::memcmp(
		this->c_str_, rhs.c_str_, sizeof(value_type) * this->size_);
}
/**
  @brief confirms whether each instance has a different value.
 */
template <hryky_template_param>
bool hryky::LiteralString<hryky_template_arg>::operator!=(
	this_type const & rhs) const
{
	return !this->operator==(rhs);
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::LiteralString<hryky_template_arg>::clear()
{
	hryky::clear(this->size_);
	hryky::clear(this->c_str_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::LiteralString<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(c_str);
	hryky_swap_member(size);
}
/**
  @brief retrieves the null-terminated string.
 */
template <hryky_template_param>
typename hryky::LiteralString<hryky_template_arg>::const_pointer
hryky::LiteralString<hryky_template_arg>::c_str() const
{
	return this->c_str_;
}
/**
  @brief retrieves the internal array of characters.
 */
template <hryky_template_param>
typename hryky::LiteralString<hryky_template_arg>::const_pointer
hryky::LiteralString<hryky_template_arg>::data() const
{
	return this->c_str_;
}
/**
  @brief retrieves the length of the literal string.
 */
template <hryky_template_param>
typename hryky::LiteralString<hryky_template_arg>::size_type
hryky::LiteralString<hryky_template_arg>::size() const
{
	return this->size_;
}
/**
  @brief confirms whether the literal string has not character.
 */
template <hryky_template_param>
bool hryky::LiteralString<hryky_template_arg>::empty() const
{
	return 0u == this->size();
}
/**
  @brief retrieves the beginning of the literal string.
 */
template <hryky_template_param>
typename hryky::LiteralString<hryky_template_arg>::const_iterator
hryky::LiteralString<hryky_template_arg>::begin() const
{
	return const_iterator(this, 0u);
}
/**
  @brief retrieves the end of the literal string.
 */
template <hryky_template_param>
typename hryky::LiteralString<hryky_template_arg>::const_iterator
hryky::LiteralString<hryky_template_arg>::end() const
{
	return const_iterator(this, this->size());
}
/**
  @brief outputs the information of LiteralString.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::LiteralString<hryky_template_arg>::write_to(StreamT & out) const
{
	out.write(this->c_str_, this->size_);
	return out;
}
/**
  @brief finds the first substring.
 */
template <hryky_template_param>
template <typename TargetT>
typename hryky::LiteralString<hryky_template_arg>::size_type 
hryky::LiteralString<hryky_template_arg>::find(
	TargetT const & target) const
{
	return this->find(target, 0u);
}
/**
  @brief finds the first substring following the specified position.
 */
template <hryky_template_param>
template <typename TargetT>
typename hryky::LiteralString<hryky_template_arg>::size_type 
hryky::LiteralString<hryky_template_arg>::find(
	TargetT const & target, size_type const position) const
{
	size_type const target_size = target.size();

	if (0u == target_size) {
		return this_type::npos;
	}
	
	if (this->size() < target_size + position) {
		return this_type::npos;
	}

	const_pointer const src = this->c_str();
	const_pointer const found = hryky::strstr(
		src + position, target.c_str());
	
	return static_cast<size_type>(
		hryky_is_null(found)
		? this_type::npos
		: ::std::distance(src, found));
}
/**
  @brief splits this string by the delimiter.
 */
template <hryky_template_param>
template <typename OutputIteratorT, typename DelimiterT>
void hryky::LiteralString<hryky_template_arg>::split_to(
	OutputIteratorT dest, DelimiterT const & delimiter) const
{
	typedef ::std::iterator_traits<OutputIteratorT> output_iterator_traits;
	typedef output_iterator_traits::value_type output_value_type;
	
	this->split([&dest](
		const_iterator const & begin,
		const_iterator const & end) {

		*dest = output_value_type(begin, end);
		
		++dest;
	}, delimiter);
}
/**
  @brief provides separated substrings to functor.
 */
template <hryky_template_param>
template <typename FunctorT, typename DelimiterT>
void hryky::LiteralString<hryky_template_arg>::split(
	FunctorT const & functor, DelimiterT const & delimiter) const
{
	if (this->empty()) {
		return;
	}

	size_type token_begin = 0u;
	size_type const size = this->size();
	while (size != token_begin) {
		size_type const token_end = this->find(delimiter, token_begin);
		if (this_type::npos == token_end) {
			functor(
				this->begin()
				+ static_cast<difference_type>(token_begin),
				this->end());
			return;
		}
		else {
			functor(
				this->begin()
				+ static_cast<difference_type>(token_begin),
				this->begin()
				+ static_cast<difference_type>(token_end));
			token_begin = token_end + delimiter.size();
		}
	}
	functor(this->end(), this->end());
}
/**
  @brief resets the internal data by a new array.
 */
template <hryky_template_param>
template <size_t Size>
void hryky::LiteralString<hryky_template_arg>::assign(
	CharT const (&c_str)[Size])
{
	this->c_str_ = c_str;
	this->size_ = Size - 1u;
}
/**
  @brief resets the internal data by the range of characters.
 */
template <hryky_template_param>
void hryky::LiteralString<hryky_template_arg>::assign(
	pointer const ptr, size_type const size)
{
	this->c_str_ = ptr;
	this->size_ = size;
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
namespace stream
{
	/// creates a notation by a literal string.
	template <typename CharT, size_t Size>
	Denote<LiteralString<CharT> > denote(CharT const (&str)[Size]);

} // namespace stream

	/// creates a LiteralString with a null-terminated string and its length.
	template <hryky_template_param>
	hryky::LiteralString<hryky_template_arg>
		literal_string(CharT const * const c_str, size_t const size);

	/// creates a LiteralString from a literal string.
	template <typename CharT, size_t Size>
	hryky::LiteralString<hryky_template_arg>
		literal_string(CharT const (&str)[Size]);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates a notation by a literal string.
 */
template <typename CharT, size_t Size>
hryky::stream::Denote<hryky::LiteralString<CharT> >
hryky::stream::denote(
	CharT const (&str)[Size])
{
	return Denote<LiteralString<CharT> >(LiteralString<CharT>(str));
}
/**
  @brief creates a LiteralString with a null-terminated string and its length.
 */
template <hryky_template_param>
hryky::LiteralString<hryky_template_arg>
hryky::literal_string(
	CharT const * const c_str, size_t const size)
{
	return LiteralString<hryky_template_arg>(c_str, size);
}
/**
  @brief creates a LiteralString from a literal string.
 */
template <typename CharT, size_t Size>
hryky::LiteralString<hryky_template_arg>
hryky::literal_string(
	CharT const (&str)[Size])
{
	return LiteralString<CharT>(str);
}
//------------------------------------------------------------------------------
// revokes macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // LITERAL_STRING_H_20120922194704491
// end of file
