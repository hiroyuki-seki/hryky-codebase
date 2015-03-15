/**
  @file         string.h
  @brief        substitutes for ::std::string.
  @author       HRYKY
  @version      $Id: string.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $

 */
#ifndef STRING_H_20120419000213668
#define STRING_H_20120419000213668
#include "hryky/allocator/allocator_mempool.h"
#include "hryky/common.h"
#include "hryky/iterator/iterator_random.h"
#include "hryky/memory/memory_common.h"
#include "hryky/nullptr.h"
#include "hryky/pragma.h"
#include "hryky/stream/stream_definition.h"
#include "hryky/stream/stream_denote.h"
#include "hryky/stream/stream_map_scope.h"
#include "hryky/swap.h"
#include "hryky/with_at.h"
#include "hryky/with_iteration.h"
#include "hryky/with_iterator.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/std/std_iterator.h"
#include "hryky/strstr.h"
#include "hryky/strlen.h"
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
	typename CharT, typename AllocatorT
#define hryky_template_arg \
	CharT, AllocatorT
#define hryky_iterator \
	hryky::iterator::random::Mutable<String<hryky_template_arg>, CharT>
#define hryky_const_iterator \
	hryky::iterator::random::Immutable<String<hryky_template_arg>, CharT>
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// substitutes for ::std::string.
	template <
		typename CharT = char,
		typename AllocatorT = hryky::allocator::Mempool<CharT>
	>
	class String;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief substitutes for ::std::string.

  @attention
  - This class is under construction.
 */
template <hryky_template_param>
class hryky::String :
	public WithIterator<
		String<hryky_template_arg>,
		hryky_iterator,
		hryky_const_iterator >,
	public WithIteration<
		String<hryky_template_arg>,
		hryky_iterator,
		hryky_const_iterator >,
	public WithAt<
		String<hryky_template_arg>,
		CharT>,
	public WithStreamOut<String<hryky_template_arg> >,
	public WithSwap<String<hryky_template_arg> >
{
public :

	typedef String<hryky_template_arg>              this_type;
	typedef CharT                                   value_type;
	typedef typename AddPointer<CharT>::type        pointer;
	typedef typename AddReference<CharT>::type      reference;
	typedef typename AddConstPointer<CharT>::type   const_pointer;
	typedef typename AddConstReference<CharT>::type const_reference;
	typedef ::std::size_t                           size_type;
	typedef ::std::ptrdiff_t                        difference_type;
	typedef AllocatorT                              allocator_type;

	/// terminator.
	static value_type terminator() {
		return this_type::terminator_;
	}

	/// the index which specifies the end of string.
	static size_type const npos = static_cast<size_type>(-1);

	/// default constructor.
	String();

	/// copy constructor.
	String(this_type const &rhs);

	/// move constructor.
	String(this_type && rhs);

	/// constructor with allocator.
	explicit String(allocator_type const & allocator);

	/// constructor with character array.
	String(
		const_pointer str,
		size_type str_size,
		allocator_type const & allocator = allocator_type());

	/// constructor with null terminated characters.
	String(
		const_pointer str,
		allocator_type const & allocator = allocator_type());

	/// constructs with a literal string.
	template <size_t Size>
	String(
		value_type const (&str)[Size],
		allocator_type const & allocator = allocator_type());

	/// instantiates by the range of two iterator.
	template <typename InputIteratorT>
	String(
		InputIteratorT begin,
		InputIteratorT end,
		allocator_type const & allocator = allocator_type());

	/// destructor.
	~String();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// assigns a new string by null-terminated characters.
	this_type & operator=(const_pointer const rhs);

	/// assigns a new string by array of characters.
	template <size_t Size>
	this_type & operator=(value_type const (&rhs)[Size]);

	/// retrieves the immutable element specified by index.
	const_reference operator[](size_type const index) const;

	/// retrieves the mutable element specified by index.
	reference operator[](size_type const index);

	/// appends the elements of other string at the end of this string.
	this_type & operator+=(this_type const & rhs);

	/// appends a character.
	this_type & operator+=(value_type const rhs);

	/// appends a literal string.
	template <size_t Size>
	this_type & operator+=(value_type const (&rhs)[Size]);

	/// creates a new string with an additional string.
	this_type operator+(this_type const & rhs) const;

	/// creates a new string with a literal string.
	template <size_t Size>
	this_type operator+(value_type const (&rhs)[Size]) const;

	/// confirms whether both strings have same characters.
	bool operator==(this_type const & rhs) const;

	/**
	  confirms whether this string has same characters as the
	  null-terminated characters.
	 */
	bool operator==(CharT const * const rhs) const;

	/// confirms whether each string has different value.
	bool operator!=(this_type const & rhs) const;

	/**
	  confirms whether this string has different characters from the
	  null-terminated characters.
	 */
	bool operator!=(CharT const * const rhs) const;

	/**
	  confirms whether this string is less than the other string in
	  dictionary order.
	 */
	bool operator<(this_type const & rhs) const;

	/**
	  confirms whether this string is less than the null-terminated
	  characters in dictionary order.
	 */
	bool operator<(CharT const * const rhs) const;

	/**
	  confirms whether this string is less than or equal to the other
	  string in dictionary order.
	 */
	bool operator<=(this_type const & rhs) const;

	/**
	  confirms whether this string is less than or equal to the null-
	  terminated characters in dictionary order.
	 */
	bool operator<=(CharT const * const rhs) const;

	/**
	  confirms whether this string is greater than the other string in
	  dictionary order.
	 */
	bool operator>(this_type const & rhs) const;

	/**
	  confirms whether this string is greater than the null-terminated
	  characters in dictionary order.
	 */
	bool operator>(CharT const * const rhs) const;

	/**
	  confirms whether this string is greater than or equal to the other
	  string in dictionary order.
	 */
	bool operator>=(this_type const & rhs) const;

	/**
	  confirms whether this string is greater than or equal to the
	  null-terminated characters in dictionary order.
	 */
	bool operator>=(CharT const * const rhs) const;

	/// retrieves the number of elements.
	size_type size() const;

	/// retrieves the length of this string.
	size_type length() const;

	/// retrieves the maximum number of allocatable elements.
	size_type max_size() const;

	/// expands or shrinks the length of string.
	bool resize(size_type const size);

	/**
	  retrieves the number of elements that is able to be held without
	  additional memory allocation
	 */
	size_type capacity() const;

	/**
	  expands the available region to allocate additional characters.
	 */
	bool reserve(size_type const capacity);

	/// removes the all elements in this string.
	void clear();

	/// confirms whether container has no element.
	bool empty() const;

	/// appends a character.
	this_type & append(value_type const src);

	/// appends the additional string at the end of this instance.
	this_type & append(this_type const & src);

	/**
	  appends the substring of the other string at the end of this instance.
	 */
	this_type & append(
		this_type const & str, size_type offset, size_type size);

	/// appends an array of characters with the lengh of the array.
	this_type & append(const_pointer str, size_type str_size);

	/// appends the elements between two iterators.
	template < typename InputIteratorT >
	this_type & append(InputIteratorT first, InputIteratorT last);

	/// appends a literal string at the end.
	template <size_t Size>
	this_type & append(value_type const (&str)[Size]);

	/// appends a character at the end of this instance.
	bool push_back(value_type const value);

	/// assigns the content from the other string.
	this_type & assign(this_type const & str);

	/// assigns the substring of the other string.
	this_type & assign(
		this_type const & str, size_type pos, size_type size);

	/// assigns an array of characters.
	this_type & assign(const_pointer str, size_type size);

	/// assigns elements between two iterators.
	template < typename InputIteratorT >
	this_type & assign(InputIteratorT first, InputIteratorT last);

	/// inserts the other string.
	this_type & insert(size_type pos, this_type const & str);

	/// inserts the part of the other string.
	this_type & insert(
		size_type dest_pos,
		this_type const & str,
		size_type src_pos,
		size_type src_size);

	/// inserts an array of characters.
	this_type & insert(
		size_type pos, const_pointer str, size_type size);

	/// inserts the elements between two iterators.
	template < typename InputIteratorT >
	this_type & insert(
		iterator dest_itr, InputIteratorT first, InputIteratorT last);

	/// inserts a character.
	this_type & insert(iterator itr, value_type const value);

	/// removes one character at the position specified by iterator.
	iterator erase(iterator itr);

	/// removes characters between two iterators.
	iterator erase(iterator first, iterator last);

	/**
	  replaces the part of the this instance by other string.
	 */
	this_type & replace(
		size_type dest_pos, size_type dest_size, this_type const & src);

	/**
	  replaces the range between two iterators of this instance by
	  other string.
	 */
	this_type & replace(
		iterator dest_first, iterator dest_last, this_type const & src);

	/**
	  replaces the part of the this instance by the substring of other
	  instance.
	 */
	this_type & replace(
		size_type dest_pos,
		size_type dest_size,
		this_type const & src,
		size_type src_pos,
		size_type src_size);

	/**
	  replaces the part of the this instance by the part of the array
	  of characters.
	 */
	this_type & replace(
		size_type dest_pos,
		size_type dest_size,
		const_pointer src,
		size_type src_size);

	/**
	  replaces the range between two iterators of this instance by the
	  part of the array of characters.
	 */
	this_type & replace(
		iterator dest_first,
		iterator dest_last,
		const_pointer src,
		size_type src_size);

	/**
	  replaces the range between two iterators of this instance by the
	  range of the other instance.
	 */
	template < typename InputIteratorT >
	this_type & replace(
		iterator dest_first,
		iterator dest_last,
		InputIteratorT src_first,
		InputIteratorT src_last);

	/// exhanges all internal values.
	void swap(this_type & src);

	/// retrieves null-terminated characters.
	const_pointer c_str() const;

	/// retrieves the internal array of characters.
	const_pointer data() const;

	/// retrieves the allocator of this instance.
	allocator_type get_allocator() const;

	/// outputs the information formatted as string.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// finds the character forward.
	size_type find(
		value_type const value,
		size_type const pos = 0) const;

	/// finds the character backward.
	size_type rfind(
		value_type const value,
		size_type const pos = npos) const;

	/// finds the first substring.
	template <typename TargetT>
	size_type find(TargetT const & target) const;

	/// finds the first substring following the specified position.
	template <typename TargetT>
	size_type find(
		TargetT const & target,
		size_type const position) const;

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

protected :

private :

	static value_type const terminator_ = value_type();

	typedef pointer buffer_type;

	size_type       capacity_;
	size_type       size_;
	allocator_type  allocator_;
	buffer_type     buffer_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
}
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::String<hryky_template_arg>::String()
	: capacity_()
	  , size_()
	  , allocator_()
	  , buffer_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::String<hryky_template_arg>::String(this_type const &rhs)
	: capacity_()
	  , size_()
	  , hryky_copy_member(allocator)
	  , buffer_()
{
	if (rhs.empty()) {
		return;
	}
	
	if (!this->reserve(rhs.size())) {
		return;
	}

	hryky::memcpy(
		this->buffer_, rhs.buffer_, sizeof(value_type) * rhs.size());

	this->size_ = rhs.size();
	this->buffer_[this->size_] = terminator();
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::String<hryky_template_arg>::String(this_type && rhs)
	: capacity_()
	  , size_()
	  , allocator_()
	  , buffer_()
{
	this->swap(rhs);
}
/**
  @brief constructor with allocator.
 */
template <hryky_template_param>
hryky::String<hryky_template_arg>::String(
	allocator_type const & allocator)
	: capacity_()
	  , size_()
	  , allocator_(allocator)
	  , buffer_()
{
}
/**
  @brief constructor with an array of characters.
 */
template <hryky_template_param>
hryky::String<hryky_template_arg>::String(
	const_pointer str,
	size_type str_size,
	allocator_type const & allocator)
	: capacity_()
	  , size_()
	  , allocator_(allocator)
	  , buffer_()
{
	if (0 == str_size) {
		return;
	}
	
	if (!this->reserve(str_size)) {
		return;
	}

	if (0 < str_size) {
		hryky::memcpy(this->buffer_, str, sizeof(value_type) * str_size);
	}
	this->size_ = str_size;
	this->buffer_[this->size_] = terminator();
}
/**
  @brief constructor with null terminated characters.
 */
template <hryky_template_param>
hryky::String<hryky_template_arg>::String(
	const_pointer str, allocator_type const & allocator)
	: capacity_()
	  , size_()
	  , allocator_(allocator)
	  , buffer_()
{
	if (hryky_is_null(str)) {
		return;
	}
	
	size_t const str_size = hryky::strlen(str);
	
	if (0 == str_size) {
		return;
	}
	
	if (!this->reserve(str_size)) {
		return;
	}

	if (0 < str_size) {
		hryky::memcpy(this->buffer_, str, sizeof(value_type) * str_size);
	}
	this->size_ = str_size;
	this->buffer_[this->size_] = terminator();
}
/**
  @brief constructs with a literal string.
 */
template <hryky_template_param>
template <size_t Size>
hryky::String<hryky_template_arg>::String(
	value_type const (&str)[Size], allocator_type const & allocator)
	: capacity_()
	  , size_()
	  , allocator_(allocator)
	  , buffer_()
{
	this->append(str);
}
/**
  @brief instantiates by the range of two iterator.
 */
template <hryky_template_param>
template <typename InputIteratorT>
hryky::String<hryky_template_arg>::String(
	InputIteratorT begin,
	InputIteratorT end,
	allocator_type const & allocator)
	: capacity_()
	  , size_()
	  , allocator_(allocator)
	  , buffer_()
{
	this->append(begin, end);
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::String<hryky_template_arg>::~String()
{
	if (hryky_is_null(this->buffer_)) {
		return;
	}

	this->allocator_.deallocate(this->buffer_, this->capacity_ + 1);
	this->buffer_ = hryky_nullptr;
	this->capacity_ = 0;
	this->size_ = 0;
}
/**
  @brief assigns a new string by null-terminated characters.
 */
template <hryky_template_param>
hryky::String<hryky_template_arg> &
hryky::String<hryky_template_arg>::operator=(
	const_pointer const rhs)
{
	if (hryky_is_null(rhs)) {
		this->clear();
		return *this;
	}
	
	return this->assign(rhs, hryky::strlen(rhs));
}
/**
  @brief assigns a new string by array of characters terminated by null.
 */
template <hryky_template_param>
template <size_t Size>
hryky::String<hryky_template_arg> &
hryky::String<hryky_template_arg>::operator=(
	value_type const (&rhs)[Size])
{
	return 2 > Size ? *this : this->assign(rhs, Size - 1);
}
/**
  @brief retrieves the immutable element specified by index.
 */
template <hryky_template_param>
typename hryky::String<hryky_template_arg>::const_reference
hryky::String<hryky_template_arg>::operator[](
	size_type const index) const
{
	return this->buffer_[index];
}
/**
  @brief retrieves the mutable element specified by index.
 */
template <hryky_template_param>
typename hryky::String<hryky_template_arg>::reference
hryky::String<hryky_template_arg>::operator[](
	size_type const index)
{
	return this->buffer_[index];
}
/**
  @brief appends the elements of other string at the end of this string.
 */
template <hryky_template_param>
hryky::String<hryky_template_arg> &
hryky::String<hryky_template_arg>::operator+=(
	this_type const & rhs)
{
	return this->append(rhs);
}
/**
  @brief appends a character.
 */
template <hryky_template_param>
hryky::String<hryky_template_arg> &
hryky::String<hryky_template_arg>::operator+=(
	value_type const rhs)
{
	this->push_back(rhs);

	return *this;
}
/**
  @brief appends a literal string.
 */
template <hryky_template_param>
template <size_t Size>
hryky::String<hryky_template_arg> & 
hryky::String<hryky_template_arg>::operator+=(
	value_type const (&rhs)[Size])
{
	return this->append(rhs);
}
/**
  @brief creates a new string with an additional string.
 */
template <hryky_template_param>
hryky::String<hryky_template_arg>
hryky::String<hryky_template_arg>::operator+(
	this_type const & rhs) const
{
	return this_type(*this).append(rhs);
}
/**
  @brief creates a new string with a literal string.
 */
template <hryky_template_param>
template <size_t Size>
hryky::String<hryky_template_arg>
hryky::String<hryky_template_arg>::operator+(
	value_type const (&rhs)[Size]) const
{
	return this_type(*this).append(rhs);
}
/**
  @brief confirms whether both strings have same characters.
 */
template <hryky_template_param>
bool hryky::String<hryky_template_arg>::operator==(
	this_type const & rhs) const
{
	size_type const lhs_size = this->size();
	
	if (lhs_size != rhs.size()) {
		return false;
	}
	
	return 0 == hryky::memcmp(
		this->buffer_, rhs.buffer_, sizeof(CharT) * lhs_size);
}
/**
  @brief confirms whether this string has same characters as
                the null-terminated characters.
 */
template <hryky_template_param>
bool hryky::String<hryky_template_arg>::operator==(
	CharT const * const rhs) const
{
	size_type const lhs_size = this->size();
	
	return 0 == hryky::memcmp(this->buffer_, rhs, sizeof(CharT) * lhs_size)
		&& terminator() == rhs[lhs_size];
}
/**
  @brief confirms whether each string has different value.
 */
template <hryky_template_param>
bool hryky::String<hryky_template_arg>::operator!=(
	this_type const & rhs) const
{
	return !((*this) == rhs);
}
/**
  @brief confirms whether this string has different characters from
                the null-terminated characters.
 */
template <hryky_template_param>
bool hryky::String<hryky_template_arg>::operator!=(
	CharT const * const rhs) const
{
	return !((*this) == rhs);
}
/**
  @brief confirms whether this string is less than the other string
                in dictionary order.
 */
template <hryky_template_param>
bool hryky::String<hryky_template_arg>::operator<(
	this_type const & rhs) const
{
	size_type const lhs_size = this->size();
	size_type const rhs_size = rhs.size();
	if (lhs_size < rhs_size) {
		return 0 <= hryky::memcmp(
			this->buffer_, rhs.buffer_, sizeof(CharT) * lhs_size);
	}
	else {
		return 0 < hryky::memcmp(
			this->buffer_, rhs.buffer_, sizeof(charT) * rhs_size);
	}
}
/**
  @brief confirms whether this string is less than the
                null-terminated characters in dictionary order.
 */
template <hryky_template_param>
bool hryky::String<hryky_template_arg>::operator<(
	CharT const * const rhs) const
{
	size_type const lhs_size = this->size();
	
	int const result = hryky::memcmp(
		this->buffer_, rhs, sizeof(CharT) * lhs_size);
	if (0 < result) {
		return true;
	}
	else if (0 == result && terminator() != rhs[lhs_size]) {
		return true;
	}
	
	return false;
}
/**
  @brief confirms whether this string is less than or equal to the
                other string in dictionary order.
 */
template <hryky_template_param>
bool hryky::String<hryky_template_arg>::operator<=(
	this_type const & rhs) const
{
	size_type const lhs_size = this->size();
	size_type const rhs_size = rhs.size();
	if (lhs_size <= rhs_size) {
		return 0 <= hryky::memcmp(
			this->buffer_, rhs.buffer_, sizeof(CharT) * lhs_size);
	}
	else {
		return 0 < hryky::memcmp(
			this->buffer_, rhs.buffer_, sizeof(charT) * rhs_size);
	}
}
/**
  @brief confirms whether this string is less than or equal to the
                null-terminated characters in dictionary order.
 */
template <hryky_template_param>
bool hryky::String<hryky_template_arg>::operator<=(
	CharT const * const rhs) const
{
	size_type const lhs_size = this->size();
	
	return 0 <= hryky::memcmp(
		this->buffer_, rhs, sizeof(CharT) * lhs_size);
}
/**
  @brief confirms whether this string is greater than the other
                string in dictionary order.
 */
template <hryky_template_param>
bool hryky::String<hryky_template_arg>::operator>(
	this_type const & rhs) const
{
	return !((*this) <= rhs);
}
/**
  @brief confirms whether this string is greater than the null-
                terminated characters in dictionary order.
 */
template <hryky_template_param>
bool hryky::String<hryky_template_arg>::operator>(
	CharT const * const rhs) const
{
	return !((*this) <= rhs);
}
/**
  @brief confirms whether this string is greater than or equal to the
                other string in dictionary order.
 */
template <hryky_template_param>
bool hryky::String<hryky_template_arg>::operator>=(
	this_type const & rhs) const
{
	return !((*this) < rhs);
}
/**
  @brief confirms whether this string is greater than or equal to the
                null-terminated characters in dictionary order.
 */
template <hryky_template_param>
bool hryky::String<hryky_template_arg>::operator>=(
	CharT const * const rhs) const
{
	return !((*this) < rhs);
}
/**
  @brief retrieves the number of elements.
 */
template <hryky_template_param>
typename hryky::String<hryky_template_arg>::size_type
hryky::String<hryky_template_arg>::size() const
{
	return this->size_;
}
/**
  @brief retrieves the length of this string.
 */
template <hryky_template_param>
typename hryky::String<hryky_template_arg>::size_type
hryky::String<hryky_template_arg>::length() const
{
	return this->size_;
}
/**
  @brief retrieves the maximum number of allocatable elements.
 */
template <hryky_template_param>
typename hryky::String<hryky_template_arg>::size_type
hryky::String<hryky_template_arg>::max_size() const
{
	size_type const buffer_max_size = this->allocator_.max_size();
	return 0 == buffer_max_size ? 0 : buffer_max_size - 1;
}
/**
  @brief expands or shrinks the length of string.
 */
template <hryky_template_param>
bool
hryky::String<hryky_template_arg>::resize(size_type const size)
{
	if (size == this->size_) {
		return true;
	}

	if (size > this->size_) {
		if (!this->reserve(size)) {
			return false;
		}
		hryky::memset(
			&this->buffer_[this->size_], 0x00u, sizeof(value_type) * size);
	}
	
	this->size_ = size;
	this->buffer_[this->size_] = terminator();
	
	return true;
}
/**
  retrieves the number of elements that is able to be held without
  additional memory allocation
 */
template <hryky_template_param>
typename hryky::String<hryky_template_arg>::size_type
hryky::String<hryky_template_arg>::capacity() const
{
	return this->capacity_;
}
/**
  @brief expands the available region to allocate additional characters.
 */
template <hryky_template_param>
bool
hryky::String<hryky_template_arg>::reserve(size_type const capacity)
{
	if (this->capacity_ >= capacity) {
		return true;
	}

	buffer_type const buffer = this->allocator_.allocate(capacity + 1);

	if (hryky_is_null(buffer)) {
		return false;
	}

	if (0 != this->size_) {
		hryky::memcpy(
			buffer, this->buffer_, sizeof(value_type) * this->size_);
	}

	if (!hryky_is_null(this->buffer_)) {
		this->allocator_.deallocate(this->buffer_, this->capacity_ + 1);
	}

	this->buffer_ = buffer;
	this->capacity_ = capacity;
	this->buffer_[this->size_] = terminator();

	return true;
}
/**
  @brief removes the all elements in this string.
 */
template <hryky_template_param>
void
hryky::String<hryky_template_arg>::clear()
{
	this->resize(0);
}
/**
  @brief confirms whether container has no element.
 */
template <hryky_template_param>
bool
hryky::String<hryky_template_arg>::empty() const
{
	return 0 == this->size_;
}
/**
  @brief appends a character.
 */
template <hryky_template_param>
hryky::String<hryky_template_arg> &
hryky::String<hryky_template_arg>::append(value_type const src)
{
	return this->append(&src, 1);
}
/**
  @brief appends the additional string at the end of this instance.
 */
template <hryky_template_param>
hryky::String<hryky_template_arg> &
hryky::String<hryky_template_arg>::append(this_type const & src)
{
	return this->append(&src.buffer_[0], src.size());
}
/**
  @brief appends the substring of the other string at the end of this instance.
 */
template <hryky_template_param>
hryky::String<hryky_template_arg> &
hryky::String<hryky_template_arg>::append(
	this_type const & str, size_type offset, size_type size)
{
	if (str.size() < offset + size) {
		hryky_throw(
			::std::out_of_range,
			"the position and the size exceed the range of the passed string"
			<< " : string size " << str.size()
			<< " : offset " << offset
			<< " : substring size " << size,
			return *this);
	}

	return this->append(&str.buffer_[offset], size);
}
/**
  @brief appends an array of characters with the lengh of the array.
 */
template <hryky_template_param>
hryky::String<hryky_template_arg> &
hryky::String<hryky_template_arg>::append(
	const_pointer str, size_type str_size)
{
	if (0 == str_size) {
		return *this;
	}

	size_type const size = this->size();

	if (!this->reserve(size + str_size)) {
		return *this;
	}

	hryky::memcpy(&this->buffer_[size], str, sizeof(value_type) * str_size);

	this->size_ += str_size;
	this->buffer_[this->size_] = terminator();

	return *this;
}
/**
  @brief appends the elements between two iterators.
 */
template <hryky_template_param>
template < typename InputIteratorT >
hryky::String<hryky_template_arg> &
hryky::String<hryky_template_arg>::append(
	InputIteratorT first, InputIteratorT last)
{
	typedef ::std::iterator_traits<InputIteratorT> iterator_traits;
	
	iterator_traits::difference_type const str_size = 
		::std::distance(first, last);

	if (0 > str_size) {
		hryky_throw(
			::std::invalid_argument,
			"the first iterator exceeds the last iterator"
			<< " : difference " << str_size,
			return *this);
	}
	
	if (0 == str_size) {
		return *this;
	}

	size_type const size = this->size();

	if (!this->reserve(size + str_size)) {
		return *this;
	}

	hryky::range(first, last).foreach_at([this, size](
		iterator_traits::reference ref, size_type const index) {
		this->allocator_.construct(&this->buffer_[size + index], ref);
	});
	this->size_ += str_size;
	this->buffer_[this->size_] = terminator();

	return *this;
}
/**
  @brief appends a literal string at the end.
 */
template <hryky_template_param>
template <size_t Size>
hryky::String<hryky_template_arg> &
hryky::String<hryky_template_arg>::append(
	value_type const (&str)[Size])
{
	return 2 > Size ? *this : this->append(&str[0], Size - 1);
}
/**
  @brief appends a character at the end of this instance.
 */
template <hryky_template_param>
bool
hryky::String<hryky_template_arg>::push_back(value_type const value)
{
	if (this->size_ == this->capacity_) {
		if (!this->reserve((this->capacity_ + 1) << 1)) {
			return false;
		}
	}

	this->buffer_[this->size_] = value;
	this->size_ += 1;
	this->buffer_[this->size_] = terminator();

	return true;
}
/**
  @brief assigns the content from the other string.
 */
template <hryky_template_param>
hryky::String<hryky_template_arg> &
hryky::String<hryky_template_arg>::assign(this_type const & str)
{
	return this->assign(str.buffer_, str.size());
}
/**
  @brief assigns the substring of the other string.
 */
template <hryky_template_param>
hryky::String<hryky_template_arg> &
hryky::String<hryky_template_arg>::assign(
	this_type const & str, size_type pos, size_type size)
{
	if (str.size() < pos + size) {
		hryky_throw(
			::std::out_of_range,
			"the position and the size exceed the range of the passed string"
			<< " : string size " << str.size()
			<< " : offset " << pos
			<< " : substring size " << size,
			return *this);
	}

	return this->assign(&str.buffer_[pos], size);
}
/**
  @brief assigns an array of characters.
 */
template <hryky_template_param>
hryky::String<hryky_template_arg> &
hryky::String<hryky_template_arg>::assign(
	const_pointer str, size_type size)
{
	if (!this->reserve(size)) {
		return *this;
	}

	if (!hryky_is_null(this->buffer_)) {
		if (0 != size) {
			hryky::memcpy(this->buffer_, str, sizeof(value_type) * size);
		}
		this->buffer_[size] = terminator();
	}
	this->size_ = size;

	return *this;
}
/**
  @brief assigns elements between two iterators.
 */
template <hryky_template_param>
template < typename InputIteratorT >
hryky::String<hryky_template_arg> &
hryky::String<hryky_template_arg>::assign(
	InputIteratorT first, InputIteratorT last)
{
	typedef ::std::iterator_traits<InputIteratorT> iterator_traits;
	iterator_traits::difference_type const size = 
		::std::distance(first, last);

	if (0 > size) {
		hryky_throw(
			::std::invalid_argument,
			"the first iterator exceeds the last iterator"
			<< " : difference " << size,
			return *this);
	}

	if (!this->reserve(static_cast<size_type>(size))) {
		return *this;
	}

	if (!hryky_is_null(this->buffer_)) {
		hryky::range(first, last).foreach_at([this](
			iterator_traits::reference ref, size_type const index) {
			this->allocator_.construct(&this->buffer_[index], ref);
		});
		this->buffer_[size] = terminator();
	}
	this->size_ = static_cast<size_type>(size);

	return *this;
}
/**
  @brief inserts the other string.
 */
template <hryky_template_param>
hryky::String<hryky_template_arg> &
hryky::String<hryky_template_arg>::insert(
	size_type pos, this_type const & str)
{
	return this->insert(pos, str.buffer_, str.size());
}
/**
  @brief inserts the part of the other string.
 */
template <hryky_template_param>
hryky::String<hryky_template_arg> &
hryky::String<hryky_template_arg>::insert(
	size_type dest_pos,
	this_type const & str,
	size_type src_pos,
	size_type src_size)
{
	if (str.size() < src_pos + src_size) {
		hryky_throw(
			::std::out_of_range,
			"argument 'src_pos + src_size' exceeds the range of this instance"
			<< " : string size " << str.size()
			<< " : offset " << src_pos
			<< " : substring size " << src_size,
			return *this);
	}

	return this->insert(dest_pos, &str.buffer_[src_pos], src_size);
}
/**
  @brief inserts an array of characters.
 */
template <hryky_template_param>
hryky::String<hryky_template_arg> &
hryky::String<hryky_template_arg>::insert(
	size_type pos, const_pointer str, size_type size)
{
	size_type const prev_size = this->size();
	
	if (prev_size < pos) {
		hryky_throw(
			::std::out_of_range,
			"argument 'pos' exceeds the range of this instance"
			<< " : destination " << pos
			<< " : size " << prev_size,
			return *this);
	}

	if (0 == size) {
		return *this;
	}

	if (!this->reserve(prev_size + size)) {
		return *this;
	}

	size_type const moved_size = prev_size - pos;

	if (0 != moved_size) {
		hryky::memmove(
			&this->buffer_[pos + size],
			&this->buffer_[pos],
			moved_size * sizeof(value_type));
	}
	hryky::memcpy(&this->buffer_[pos], str, sizeof(value_type) * size);
	
	this->size_ += size;
	this->buffer_[this->size_] = terminator();

	return *this;
}
/**
  @brief inserts the elements between two iterators.
 */
template <hryky_template_param>
template < typename InputIteratorT >
hryky::String<hryky_template_arg> &
hryky::String<hryky_template_arg>::insert(
	iterator dest_itr, InputIteratorT first, InputIteratorT last)
{
	typedef ::std::iterator_traits<InputIteratorT> iterator_traits;
	
	if (this->begin() > dest_itr || this->end() < dest_itr) {
		hryky_throw(
			::std::out_of_range,
			"argument 'dest_itr' exceeds the range of this instance"
			<< " : destination " << (dest_itr - this->begin())
			<< " : size " << this->size(),
			return *this);
	}

	iterator_traits::difference_type const size = 
		::std::distance(first, last);
	
	if (0 > size) {
		hryky_throw(
			::std::invalid_argument,
			"the first iterator exceeds the last iterator"
			<< " : difference " << size,
			return *this);
	}

	if (0 == size) {
		return *this;
	}

	size_type const prev_size = this->size();

	/// @attention dest_itr will be invalidated after reserve().
	size_type const pos = static_cast<size_type>(
		::std::distance(this->begin(), dest_itr));

	if (!this->reserve(prev_size + size)) {
		return *this;
	}

	size_type const moved_size = prev_size - pos;

	if (0 != moved_size) {
		hryky::memmove(
			&this->buffer_[pos + size],
			&this->buffer_[pos],
			moved_size * sizeof(value_type));
	}

	hryky::range(first, last).foreach_at([this, pos](
		iterator_traits::reference ref, size_type const index) {
		this->allocator_.construct(&this->buffer_[pos + index], ref);
	});
	this->size_ += size;
	this->buffer_[this->size_] = terminator();

	return *this;
}
/**
  @brief inserts a character.
 */
template <hryky_template_param>
hryky::String<hryky_template_arg> &
hryky::String<hryky_template_arg>::insert(
	iterator itr, value_type const value)
{
	if (this->begin() > itr || this->end() < itr) {
		hryky_throw(
			::std::out_of_range,
			"argument 'itr' exceeds the range of this instance"
			<< " : destination " << (itr - this->begin())
			<< " : size " << this->size(),
			return *this);
	}

	/// @attention itr will be invalidated after reserve().
	size_type const pos = static_cast<size_type>(
		itr - this->begin());

	if (this->size_ == this->capacity_) {
		if (!this->reserve((this->capacity_ + 1) << 1)) {
			return *this;
		}
	}

	size_type const moved_size = this->size() - pos;

	if (0 != moved_size) {
		hryky::memmove(
			&this->buffer_[pos + 1],
			&this->buffer_[pos],
			moved_size * sizeof(value_type));
	}
	this->buffer_[pos] = value;

	this->size_ += 1;
	this->buffer_[this->size_] = terminator();
	
	return *this;
}
/**
  @brief removes one character at the position specified by iterator.
 */
template <hryky_template_param>
typename hryky::String<hryky_template_arg>::iterator
hryky::String<hryky_template_arg>::erase(iterator itr)
{
	if (this->begin() > itr || this->end() <= itr) {
		hryky_throw(
			::std::out_of_range,
			"argument 'itr' exceeds the range of this instance"
			<< " : position " << (itr - this->begin())
			<< " : size " << this->size(),
			return this->end());
	}

	size_type const pos = static_cast<size_type>(
		itr - this->begin());
	size_type const moved_size  = this->size() - (pos + 1);

	if (0 != moved_size) {
		hryky::memmove(
			&this->buffer_[pos],
			&this->buffer_[pos + 1],
			moved_size * sizeof(value_type));
	}

	this->size_ -= 1;
	this->buffer_[this->size_] = terminator();

	return iterator(this, pos);
}
/**
  @brief removes characters between two iterators.
 */
template <hryky_template_param>
typename hryky::String<hryky_template_arg>::iterator
hryky::String<hryky_template_arg>::erase(iterator first, iterator last)
{
	if (this->begin() > first
		 || this->end() <= first
		 || this->begin() >= last
		 || this->end() < last) {
		hryky_throw(
			::std::out_of_range,
			"argument 'first' or 'last' exceeds the range of this instance"
			<< " : first " << (first - this->begin())
			<< " : last " << (last - this->begin())
			<< " : size " << this->size(),
			return this->end());
	}

	difference_type const size = last - first;
	if (0 >= size) {
		hryky_throw(
			::std::invalid_argument,
			"the first iterator exceeds the last iterator"
			<< " : difference " << size,
			return this->end());
	}

	size_type const pos = static_cast<size_type>(
		first - this->begin());
	size_type const moved_size  = this->size() - (pos + size);

	if (0 != moved_size) {
		hryky::memmove(
			&this->buffer_[pos],
			&this->buffer_[pos + size],
			moved_size * sizeof(value_type));
	}

	this->size_ -= size;
	this->buffer_[this->size_] = terminator();

	return iterator(this, pos);
}
/**
  @brief replaces the part of the this instance by other string.
 */
template <hryky_template_param>
typename hryky::String<hryky_template_arg>::this_type &
hryky::String<hryky_template_arg>::replace(
	size_type dest_pos, size_type dest_size, this_type const & src)
{
	return this->replace(
		dest_pos, dest_size, src, 0, src.size());
}
/**
  @brief replaces the range between two iterators of this instance by
         other string.
 */
template <hryky_template_param>
typename hryky::String<hryky_template_arg>::this_type &
hryky::String<hryky_template_arg>::replace(
	iterator dest_first, iterator dest_last, this_type const & src)
{
	return this->replace(
		dest_first - this->begin(),
		dest_last - dest_first,
		src);
}
/**
  @brief replaces the part of the this instance by the substring of
         other instance.
 */
template <hryky_template_param>
typename hryky::String<hryky_template_arg>::this_type &
hryky::String<hryky_template_arg>::replace(
	size_type dest_pos,
	size_type dest_size,
	this_type const & src,
	size_type src_pos, size_type src_size)
{
	if (src.size() < src_pos + src_size) {
		hryky_throw(
			::std::out_of_range,
			"position of the inserter specifed by argument exceeds "
			"the range of the instance"
			<< " : src_pos " << src_pos
			<< " : src_size " << src_size
			<< " : size " << src.size(),
			return *this);
	}

	return this->replace(
		dest_pos, dest_size, &src.buffer_[src_pos], src_size);
}
/**
  @brief replaces the part of the this instance by the part of the
  array of characters.
 */
template <hryky_template_param>
typename hryky::String<hryky_template_arg>::this_type &
hryky::String<hryky_template_arg>::replace(
	size_type dest_pos,
	size_type dest_size,
	const_pointer src,
	size_type src_size)
{
	if (this->size() < dest_pos + dest_size) {
		hryky_throw(
			::std::out_of_range,
			"inserted position specifed by argument exceeds "
			"the range of this instance"
			<< " : dest_pos " << dest_pos
			<< " : dest_size " << dest_size
			<< " : size " << this->size(),
			return *this);
	}

	if (0 == dest_size && 0 == src_size) {
		return *this;
	}

	if (dest_size < src_size) {
		if (!this->reserve(this->size() + src_size)) {
			return *this;
		}
	}

	size_type const moved_size = this->size() - (dest_pos + dest_size);

	if (0 != moved_size) {
		hryky::memmove(
			&this->buffer_[dest_pos + src_size],
			&this->buffer_[dest_pos + dest_size],
			sizeof(value_type) * moved_size);
	}

	if (0 != src_size) {
		hryky::memcpy(
			&this->buffer_[dest_pos],
			src,
			sizeof(value_type) * src_size);
	}

	this->size_ += (src_size - dest_size);
	this->buffer_[this->size_] = terminator();

	return *this;
}
/**
  @brief replaces the range between two iterators of this instance by the
  part of the array of characters.
 */
template <hryky_template_param>
typename hryky::String<hryky_template_arg>::this_type &
hryky::String<hryky_template_arg>::replace(
	iterator dest_first,
	iterator dest_last,
	const_pointer src,
	size_type src_size)
{
	return this->replace(
		dest_first - this->begin(),
		dest_last - dest_first,
		src,
		src_size);
}
/**
  @brief replaces the range between two iterators of this instance by the
  range of the other instance.
 */
template <hryky_template_param>
template < typename InputIteratorT >
typename hryky::String<hryky_template_arg>::this_type &
hryky::String<hryky_template_arg>::replace(
	iterator dest_first,
	iterator dest_last,
	InputIteratorT src_first,
	InputIteratorT src_last)
{
	typedef ::std::iterator_traits<InputIteratorT> iterator_traits;
	
	if (this->begin() > dest_first
		 || this->end() < dest_first
		 || this->begin() > dest_last
		 || this->end() < dest_last
		 ) {
		hryky_throw(
			::std::out_of_range,
			"inserted position specifed by argument exceeds the range "
			"of this instance"
			<< " : first " << ::std::distance(this->begin(), dest_first)
			<< " : last " << ::std::distance(this->begin(), dest_last)
			<< " : size " << this->size(),
			return *this);
	}

	difference_type const dest_size = ::std::distance(dest_first, dest_last);

	if (0 > dest_size) {
		hryky_throw(
			::std::invalid_argument,
			"the inserted range is invalid"
			<< " : first " << ::std::distance(this->begin(), dest_first)
			<< " : last " << ::std::distance(this->begin(), dest_last),
			return *this);
	}

	iterator_traits::difference_type const src_size =
		::std::distance(src_first, src_last);

	if (0 > src_size) {
		hryky_throw(
			::std::invalid_argument,
			"the inserter range is invalid"
			<< " : difference " << src_size,
			return *this);
	}

	if (0u == dest_size && 0u == src_size) {
		return *this;
	}

	/**
	  @attention dest_first and dest_last will be invalidated after reserve().
	 */
	size_type const dest_pos = static_cast<size_type>(
		::std::distance(this->begin(), dest_first));

	if (dest_size < src_size) {
		if (!this->reserve(this->size() + src_size)) {
			return *this;
		}
	}

	size_type const moved_size = this->size() - (dest_pos + dest_size);

	if (0 != moved_size) {
		hryky::memmove(
			&this->buffer_[dest_pos + src_size],
			&this->buffer_[dest_pos + dest_size],
			sizeof(value_type) * moved_size);
	}

	hryky::range(src_first, src_last).foreach_at([this, dest_pos](
		iterator_traits::reference ref, size_type const index) {
		this->buffer_[dest_pos + index] = ref;
	});

	this->size_ += (src_size - dest_size);
	this->buffer_[this->size_] = terminator();

	return *this;
}
/**
  @brief exhanges all internal values.
 */
template <hryky_template_param>
void 
hryky::String<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(allocator);
	hryky_swap_member(buffer);
	hryky_swap_member(capacity);
	hryky_swap_member(size);
}
/**
  @brief retrieves null-terminated characters.
 */
template <hryky_template_param>
typename hryky::String<hryky_template_arg>::const_pointer
hryky::String<hryky_template_arg>::c_str() const
{
	return hryky_nullptr == this->buffer_ ?
		&this_type::terminator_ : this->buffer_;
}
/**
  @brief retrieves the internal array of characters.
 */
template <hryky_template_param>
typename hryky::String<hryky_template_arg>::const_pointer
hryky::String<hryky_template_arg>::data() const
{
	return this->buffer_;
}
/**
  @brief retrieves the allocator of this instance.
 */
template <hryky_template_param>
typename hryky::String<hryky_template_arg>::allocator_type 
hryky::String<hryky_template_arg>::get_allocator() const
{
	return this->allocator_;
}
/**
  @brief outputs the information formatted as string.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::String<hryky_template_arg>::write_to(
	StreamT & out) const
{
	out << this->c_str();
	
	return out;
}
/**
  @brief finds the character forward.
 */
template <hryky_template_param>
typename hryky::String<hryky_template_arg>::size_type 
hryky::String<hryky_template_arg>::find(
	value_type const value, size_type const pos) const
{
	if (this->size() <= pos) {
		return npos;
	}
	const_pointer ptr = &this->buffer_[pos];
	while (value != *ptr) {
		if (&this->buffer_[this->size_ - 1u] == ptr) {
			return npos;
		}
		++ptr;
	}
	return static_cast<size_type>(ptr - this->buffer_);
}
/**
  @brief finds the character backward.
 */
template <hryky_template_param>
typename hryky::String<hryky_template_arg>::size_type 
hryky::String<hryky_template_arg>::rfind(
	value_type const value, size_type const pos) const
{
	if (this->empty()) {
		return npos;
	}
	const_pointer ptr = (this->size_ <= pos)
		? &this->buffer_[this->size_ - 1u] : &this->buffer_[pos];
	while (value != *ptr) {
		if (this->buffer_ == ptr) {
			return npos;
		}
		--ptr;
	}
	return static_cast<size_type>(ptr - this->buffer_);
}
/**
  @brief finds the first substring.
 */
template <hryky_template_param>
template <typename TargetT>
typename hryky::String<hryky_template_arg>::size_type 
hryky::String<hryky_template_arg>::find(
	TargetT const & target) const
{
	return this->find(target, 0u);
}
/**
  @brief finds the first substring following the specified position.
 */
template <hryky_template_param>
template <typename TargetT>
typename hryky::String<hryky_template_arg>::size_type 
hryky::String<hryky_template_arg>::find(
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
void hryky::String<hryky_template_arg>::split_to(
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
void hryky::String<hryky_template_arg>::split(
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
	/**
	  creates a new string at the beginning of which a null-terminated
	  is appended.
	 */
	template <hryky_template_param>
	String<hryky_template_arg> operator+(
		CharT const * const lhs, String<hryky_template_arg> const & rhs);

	/// confirms whether a null-terminated character is equal to a string.
	template <hryky_template_param>
	bool operator==(
		CharT const * const lhs, String<hryky_template_arg> const & rhs);

	/**
	  confirms whether a null-terminated character is not equal to a string.
	 */
	template <hryky_template_param>
	bool operator!=(
		CharT const * const lhs, String<hryky_template_arg> const & rhs);

	/**
	  confirms whether a null-terminated character is less than a string.
	 */
	template <hryky_template_param>
	bool operator<(
		CharT const * const lhs, String<hryky_template_arg> const & rhs);

	/**
	  confirms whether a null-terminated character is less than or
	  equal to a string.
	 */
	template <hryky_template_param>
	bool operator<=(
		CharT const * const lhs, String<hryky_template_arg> const & rhs);

	/// confirms whether a null-terminated character is greater than a string.
	template <hryky_template_param>
	bool operator>(
		CharT const * const lhs, String<hryky_template_arg> const & rhs);

	/**
	  confirms whether a null-terminated character is greater than or
	  equal to a string.
	 */
	template <hryky_template_param>
	bool operator>=(
		CharT const * const lhs, String<hryky_template_arg> const & rhs);

namespace stream
{
	/// creates a notation by a String.
	template <hryky_template_param>
	stream::Denote<String<hryky_template_arg> > denote(
		String<hryky_template_arg> const &str);
	
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates a new string at the beginning of which a null-terminated
  is appended.
 */
template <hryky_template_param>
hryky::String<hryky_template_arg> hryky::operator+(
	CharT const * const lhs, String<hryky_template_arg> const & rhs)
{
	return String<hryky_template_arg>(lhs).append(rhs);
}
/**
  @brief confirms whether a null-terminated character is equal to
  a string.
 */
template <hryky_template_param>
bool hryky::operator==(
	CharT const * const lhs, String<hryky_template_arg> const & rhs)
{
	return rhs == lhs;
}
/**
  @brief confirms whether a null-terminated character is not equal
  to a string.
 */
template <hryky_template_param>
bool hryky::operator!=(
	CharT const * const lhs, String<hryky_template_arg> const & rhs)
{
	return rhs != lhs;
}
/**
  @brief confirms whether a null-terminated character is less than
  a string.
 */
template <hryky_template_param>
bool hryky::operator<(
	CharT const * const lhs, String<hryky_template_arg> const & rhs)
{
	return rhs > lhs;
}
/**
  @brief confirms whether a null-terminated character is less than or
         equal to a string.
 */
template <hryky_template_param>
bool hryky::operator<=(
	CharT const * const lhs, String<hryky_template_arg> const & rhs)
{
	return rhs >= lhs;
}
/**
  @brief confirms whether a null-terminated character is greater than a string.
 */
template <hryky_template_param>
bool hryky::operator>(
	CharT const * const lhs, String<hryky_template_arg> const & rhs)
{
	return rhs < lhs;
}
/**
  @brief confirms whether a null-terminated character is greater than or
         equal to a string.
 */
template <hryky_template_param>
bool hryky::operator>=(
	CharT const * const lhs, String<hryky_template_arg> const & rhs)
{
	return rhs <= lhs;
}
/**
  @brief creates a notation by a String.
 */
template <hryky_template_param>
hryky::stream::Denote<hryky::String<hryky_template_arg> >
hryky::stream::denote(
	String<hryky_template_arg> const & str)
{
	return Denote<String<hryky_template_arg> >(str);
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#undef hryky_iterator
#undef hryky_const_iterator
//------------------------------------------------------------------------------
// restores warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // STRING_H_20120419000213668
// end of file
