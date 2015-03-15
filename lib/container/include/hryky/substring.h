/**
  @file         substring.h
  @brief        represents the part of string.
  @author       HRYKY
  @version      $Id: substring.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef SUBSTRING_H_20120713004852700
#define SUBSTRING_H_20120713004852700
#include "hryky/iterator/iterator_random.h"
#include "hryky/offset_ptr.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename OriginT, typename OffsetT, typename ValueT
#define hryky_template_arg \
	OriginT, OffsetT, ValueT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// represents the part of string.
	template <hryky_template_param>
	class Substring;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief represents the part of string.
 */
template <
	typename OriginT,
	typename OffsetT = typename hryky::RemovePointer<OriginT>::type::size_type,
	typename ValueT = typename hryky::RemovePointer<OriginT>::type::value_type>
class hryky::Substring
{
public :
	typedef Substring<hryky_template_arg>                   this_type;
	typedef OffsetT                                         size_type;
	typedef ::std::ptrdiff_t                                  difference_type;
	typedef ValueT                                          value_type;
	typedef typename AddConst<ValueT>::type                 const_value_type;
	typedef OffsetPtr<hryky_template_arg>                   pointer;
	typedef typename AddReference<ValueT>::type             reference;
	typedef OffsetPtr<OriginT, OffsetT, const_value_type>   const_pointer;
	typedef typename AddReference<const_value_type>::type   const_reference;

	typedef hryky::iterator::random::Mutable<
		value_type, pointer, reference >
			iterator;
	typedef hryky::iterator::random::Immutable<
		value_type, pointer, reference, const_pointer, const_reference >
			const_iterator;

	typedef ::std::reverse_iterator<iterator>             reverse_iterator;
	typedef ::std::reverse_iterator<const_iterator>       const_reverse_iterator;

	typedef typename AsParameter<OriginT>::type    origin_param_type;
	typedef typename AsParameter<OffsetT>::type    offset_param_type;

	/// default constructor.
	Substring();

	/// constructor with the entire string and the range.
	Substring(
		origin_param_type origin,
		offset_param_type begin,
		offset_param_type end);

	/// retrieves the beginning of the container.
	iterator begin();

	/// retrieves the end of the container.
	iterator end();

	/// retrieves the beginning of the immutable container.
	const_iterator begin() const;

	/// retrieves the end of the immutable container.
	const_iterator end() const;

	/// retrieves the length of the container.
	size_type size() const;

	/// retrieves a subset of this string.
	this_type substr(size_type const pos, size_type const size) const;

	/// searches a string in this string.
	template < typename IteratorT >
	size_type find(
		IteratorT first, IteratorT last, size_type const pos) const;

	/// formats the information of the Substring.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

private :

	OriginT     origin_;
	OffsetT     begin_;
	OffsetT     end_;

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
hryky::Substring<hryky_template_arg>::Substring()
	: origin_()
	  , begin_()
	  , end_()
{
	return;
}
/**
  @brief constructor with the entire string and the range.
 */
template <hryky_template_param>
hryky::Substring<hryky_template_arg>::Substring(
	origin_param_type origin,
	offset_param_type begin,
	offset_param_type end)
	: origin_(origin)
	  , begin_(begin)
	  , end_(end)
{
	return;
}
/**
  @brief retrieves the beginning of the container.
 */
template <hryky_template_param>
typename hryky::Substring<hryky_template_arg>::iterator 
hryky::Substring<hryky_template_arg>::begin()
{
	return pointer(this->origin_, this->begin_);
}
/**
  @brief retrieves the end of the container.
 */
template <hryky_template_param>
typename hryky::Substring<hryky_template_arg>::iterator 
hryky::Substring<hryky_template_arg>::end()
{
	return pointer(this->origin_, this->end_);
}
/**
  @brief retrieves the beginning of the immutable container.
 */
template <hryky_template_param>
typename hryky::Substring<hryky_template_arg>::const_iterator 
hryky::Substring<hryky_template_arg>::begin() const
{
	return const_pointer(this->origin_, this->begin_);
}
/**
  @brief retrieves the end of the immutable container.
 */
template <hryky_template_param>
typename hryky::Substring<hryky_template_arg>::const_iterator 
hryky::Substring<hryky_template_arg>::end() const
{
	return const_pointer(this->origin_, this->end_);
}
/**
  @brief retrieves the length of the container.
 */
template <hryky_template_param>
OffsetT hryky::Substring<hryky_template_arg>::size() const
{
	return this->end_ - this->begin_;
}
/**
  @brief retrieves a subset of this string.
 */
template <hryky_template_param>
hryky::Substring<hryky_template_arg> 
hryky::Substring<hryky_template_arg>::substr(
	size_type const pos, size_type const size) const
{
	if (pos < this->begin_
		 || pos > this->end_
		 || pos + size > this->end_) {
		hryky_throw(
			::std::out_of_range,
			"argument 'pos' and 'size' exceed the range of this instance"
			<< (json::writer()
				<< hryky_stream_denote(pos)
				<< hryky_stream_denote(size)),
			return this_type());
	}

	return this_type(this->origin_, pos, pos + size);
}
/**
  @brief searches a string in this string.
 */
template <hryky_template_param>
template < typename IteratorT >
typename hryky::Substring<hryky_template_arg>::size_type 
hryky::Substring<hryky_template_arg>::find(
	IteratorT src_begin, IteratorT src_end, size_type const pos) const
{
	size_type const size = this->size();

	if (size < pos) {
		hryky_throw(
			::std::out_of_range,
			"argument 'pos' exceeds the range of this instance"
			<< (json::writer()
				<< hryky_stream_denote(pos)),
			return size);
	}

	difference_type const src_size = static_cast<difference_type>(
		::std::distance(src_begin, src_end));

	if (0 > src_size) {
		hryky_throw(
			::std::invalid_argument,
			"The inserter range is invalid"
			<< " : difference " << src_size,
			return size);
	}
	
	if (size < src_size + pos) {
		return size;
	}

	const_iterator const end = ::std::prev(this->end(), src_size);
	const_iterator itr = ::std::next(this->begin(), pos);

	for (; end != itr; ++itr) {
		IteratorT src_itr = src_begin;
		const_iterator dest_itr = itr;
		for (; src_end != src_itr; ++src_itr, ++dest_itr) {
			if (*src_itr != *dest_itr) {
				break;
			}
		}
		if (src_end == src_itr) {
			return static_cast<size_type>(
				::std::distance(this->begin(), itr));
		}
	}

	return size;
}
/**
  @brief formats the information of the Substring.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::Substring<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(begin);
	hryky_write_member(end);
	hryky_write_pointer_member(origin);
	
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
#endif // SUBSTRING_H_20120713004852700
// end of file
