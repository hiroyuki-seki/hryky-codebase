/**
  @file         array.h
  @brief        substitutes for ::std::array.
  @author       HRYKY
  @version      $Id: array.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef ARRAY_H_20120331175726414
#define ARRAY_H_20120331175726414
#include "hryky/capacity_of.h"
#include "hryky/type_traits/add_const_pointer.h"
#include "hryky/type_traits/add_const_reference.h"
#include "hryky/type_traits/add_pointer.h"
#include "hryky/type_traits/add_reference.h"
#include "hryky/inner_product.h"
#include "hryky/integer/bits_enough_signed.h"
#include "hryky/integer/signed_enough.h"
#include "hryky/integer/unsigned_enough.h"
#include "hryky/iterator/iterator_random.h"
#include "hryky/memory/memory_common.h"
#include "hryky/resize.h"
#include "hryky/unroll.h"
#include "hryky/stream/stream_definition.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_create_default_constructor
#pragma hryky_pragma_disable_warning_create_assign_operator
#pragma hryky_pragma_disable_warning_user_constructor
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT, size_t Size, bool IsPOD
#define hryky_template_arg \
	ValueT, Size, IsPOD
#define hryky_size_type \
	typename UnsignedEnoughUint<Size>::type
#define hryky_difference_type \
	typename SignedEnoughInt<Size>::type
#define hryky_pointer \
	typename AddPointer<value_type>::type
#define hryky_const_pointer \
	typename AddConstPointer<value_type>::type
#define hryky_reference \
	typename AddReference<value_type>::type
#define hryky_const_reference \
	typename AddConstReference<value_type>::type
#define hryky_iterator \
	hryky::iterator::random::Mutable< \
		this_type, \
		ValueT, \
		hryky_pointer, \
		hryky_reference, \
		hryky_size_type, \
		hryky_difference_type>
#define hryky_const_iterator \
	hryky::iterator::random::Immutable< \
		this_type, \
		ValueT, \
		hryky_pointer, \
		hryky_reference, \
		hryky_const_pointer, \
		hryky_const_reference, \
		hryky_size_type, \
		hryky_difference_type>
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// substitutes for ::std::array.
	template <hryky_template_param>
	class Array;
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief substitutes for ::std::array.

  This class must be plain old data structure (POD).
  POD has ...
  - no assignment operator.
  - no constructor.
  - no destructor.
  - no non-static data member that is not POD.
  - no private/protected non-static data member.
  - no base class.
  - no virtual function.
 */
template <
	typename ValueT,
	size_t Size,
	bool IsPOD = ::std::is_pod<ValueT>::value
>
class hryky::Array
{
public :

	typedef Array<hryky_template_arg>               this_type;
	typedef ValueT                                  value_type;
	typedef hryky_size_type                         size_type;
	typedef hryky_difference_type                   difference_type;
	typedef hryky_pointer                           pointer;
	typedef hryky_reference                         reference;
	typedef hryky_const_pointer                     const_pointer;
	typedef hryky_const_reference                   const_reference;
	typedef hryky_iterator                          iterator;
	typedef hryky_const_iterator                    const_iterator;
	typedef ::std::reverse_iterator<iterator>       reverse_iterator;
	typedef ::std::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef value_type                              raw_type[Size];

	/// confirms the equality between two instances.
	bool operator==(this_type const & rhs) const;

	/// confirms the inequality between two instances.
	bool operator!=(this_type const & rhs) const;

	/// confirms whether this instance is less than an other.
	bool operator<(this_type const & rhs) const;

	/// confirms whether this instance is greater than an other.
	bool operator>(this_type const & rhs) const;

	/// confirms whether this instance is less than or equal to an other.
	bool operator<=(this_type const & rhs) const;

	/// confirms whether this instance is greater than or equal to an other.
	bool operator>=(this_type const & rhs) const;

	/// retrieves the mutable reference at the specified index.
	reference operator[](size_type const index);

	/// retrieves the immutable reference at the specified index.
	const_reference operator[](size_type const index) const;

	/// retrieves the mutable iterator pointing to the beginning.
	iterator begin();

	/// retrieves the immutable iterator pointing to the beginning.
	const_iterator begin() const;

	/// retrieves the mutable iterator pointing to the end.
	iterator end();

	/// retrieves the immutable iterator pointing to the end.
	const_iterator end() const;

	/// retrieves the mutable reverse_iterator pointing to the beginning.
	reverse_iterator rbegin();

	/// retrieves the immutable reverse_iterator pointing to the beginning.
	const_reverse_iterator rbegin() const;

	/// retrieves the mutable reverse_iterator pointing to the end.
	reverse_iterator rend();

	/// retrieves the immutable reverse_iterator pointing to the end.
	const_reverse_iterator rend() const;

	/// retrieves the size of this array.
	size_type size() const;

	/// retrieves the beginning address of the immutable raw data.
	const_pointer data() const;

	/// retrieves the beginning address of the mutable raw data.
	pointer data();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// calls an arbitrary function with each element.
	template <typename FunctorT>
	void foreach(FunctorT const & functor);

	/// calls an arbitrary function with each immutable element.
	template <typename FunctorT>
	void foreach(FunctorT const & functor) const;

	/// calls an arbitrary function with each element and the index.
	template <typename FunctorT>
	void foreach_at(FunctorT const & functor);

	/// calls an arbitrary function with each immutable element and the index.
	template <typename FunctorT>
	void foreach_at(FunctorT const & functor) const;

	/**
	  calls an arbitrary function with each element until the function
	  fails.
	 */
	template <typename FunctorT>
	bool every(FunctorT const & functor);

	/**
	  calls an arbitrary function with each immutable element until
	  the function fails.
	 */
	template <typename FunctorT>
	bool every(FunctorT const & functor) const;

	/**
	  calls an arbitrary function with each element and the index until
	  the function fails.
	 */
	template <typename FunctorT>
	bool every_at(FunctorT const & functor);

	/**
	  calls an arbitrary function with each immutable element and the
	  index until the function fails.
	 */
	template <typename FunctorT>
	bool every_at(FunctorT const & functor) const;

	/**
	  calls an arbitrary function with each element until the function
	  succeeds.
	 */
	template <typename FunctorT>
	bool some(FunctorT const & functor);

	/**
	  calls an arbitrary function with each immutable element until
	  the function succeeds.
	 */
	template <typename FunctorT>
	bool some(FunctorT const & functor) const;

	/**
	  calls an arbitrary function with each element and the index until
	  the function succeeds.
	 */
	template <typename FunctorT>
	bool some_at(FunctorT const & functor);

	/**
	  calls an arbitrary function with each immutable element and the
	  index until the function succeeds.
	 */
	template <typename FunctorT>
	bool some_at(FunctorT const & functor) const;

	/**
	  calls an arbitrary function with each element.
	  This iteration starts from the specified offset.
	 */
	template <typename FunctorT, size_t Offset>
	void foreach_from(FunctorT const & functor);

	/**
	  calls an arbitrary function with each immutable element.
	  This iteration starts from the specified offset.
	 */
	template <typename FunctorT, size_t Offset>
	void foreach_from(FunctorT const & functor) const;

	/**
	  calls an arbitrary function with each element and the index.
	  This iteration starts from the specified offset.
	 */
	template <typename FunctorT, size_t Offset>
	void foreach_at_from(FunctorT const & functor);

	/**
	  calls an arbitrary function with each immutable element and the index.
	  This iteration starts from the specified offset.
	 */
	template <typename FunctorT, size_t Offset>
	void foreach_at_from(FunctorT const & functor) const;

	/**
	  calls an arbitrary function with each element until the function
	  fails. This iteration starts from the specified offset.
	 */
	template <typename FunctorT, size_t Offset>
	bool every_from(FunctorT const & functor);

	/**
	  calls an arbitrary function with each immutable element until
	  the function fails. This iteration starts from the specified offset.
	 */
	template <typename FunctorT, size_t Offset>
	bool every_from(FunctorT const & functor) const;

	/**
	  calls an arbitrary function with each element and the index until
	  the function fails. This iteration starts from the specified offset.
	 */
	template <typename FunctorT, size_t Offset>
	bool every_at_from(FunctorT const & functor);

	/**
	  calls an arbitrary function with each immutable element and the
	  index until the function fails. This iteration starts from the
	  specified offset.
	 */
	template <typename FunctorT, size_t Offset>
	bool every_at_from(FunctorT const & functor) const;

	/**
	  calls an arbitrary function with each element until the function
	  succeeds. This iteration starts from the specified offset.
	 */
	template <typename FunctorT, size_t Offset>
	bool some_from(FunctorT const & functor);

	/**
	  calls an arbitrary function with each immutable element until
	  the function succeeds. This iteration starts from the specified offset.
	 */
	template <typename FunctorT, size_t Offset>
	bool some_from(FunctorT const & functor) const;

	/**
	  calls an arbitrary function with each element and the index until
	  the function succeeds. This iteration starts from the specified offset.
	 */
	template <typename FunctorT, size_t Offset>
	bool some_at_from(FunctorT const & functor);

	/**
	  calls an arbitrary function with each immutable element and the
	  index until the function succeeds. This iteration starts from the
	  specified offset.
	 */
	template <typename FunctorT, size_t Offset>
	bool some_at_from(FunctorT const & functor) const;

	raw_type raw_;

protected :

private :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
// /**
//   @brief specialization for non-POD value.
//  */
// template <
// 	typename ValueT,
// 	size_t Size
// >
// class Array<ValueT, Size, false>
// {
// };
/**
  @brief retrieves the capacity of Array.
 */
template <hryky_template_param, typename RetT>
class CapacityOf<Array<hryky_template_arg>, RetT>
{
public :
	static RetT const value = Size;
};
/**
  @brief retrieves the new type of array whose size is different.
 */
template <hryky_template_param, size_t NewSize>
class Resize<Array<hryky_template_arg>, NewSize>
{
public :
	typedef Array<ValueT, NewSize> type;
};
}
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief confirms the equality between two instances.
 */
template <hryky_template_param>
bool hryky::Array<hryky_template_arg>::operator==(this_type const & rhs) const
{
	return ::std::equal(this->begin(), this->end(), rhs.begin());
}
/**
  @brief confirms the inequality between two instances.
 */
template <hryky_template_param>
bool hryky::Array<hryky_template_arg>::operator!=(this_type const & rhs) const
{
	return !this->operator==(rhs);
}
/**
  @brief confirms whether this instance is less than an other.
 */
template <hryky_template_param>
bool hryky::Array<hryky_template_arg>::operator<(this_type const & rhs) const
{
	if (this->size() < rhs.size()) {
		const_iterator lhs_itr = this->begin();
		const_iterator rhs_itr = rhs.begin();
		const_iterator const lhs_end = this->end();
		for (; lhs_end != lhs_itr; ++lhs_itr, ++rhs_itr) {
			if (*lhs_itr < *rhs_itr) {
				return true;
			}
			else if (*lhs_itr > *rhs_itr) {
				return false;
			}
		}
		return true;
	}
	else {
		const_iterator lhs_itr = this->begin();
		const_iterator rhs_itr = rhs.begin();
		const_iterator const rhs_end = rhs.end();
		for (; rhs_end != rhs_itr; ++lhs_itr, ++rhs_itr) {
			if (*lhs_itr < *rhs_itr) {
				return true;
			}
			else if (*lhs_itr > *rhs_itr) {
				return false;
			}
		}
		return false;
	}
}
/**
  @brief confirms whether this instance is greater than an other.
 */
template <hryky_template_param>
bool hryky::Array<hryky_template_arg>::operator>(this_type const & rhs) const
{
	if (this->size() > rhs.size()) {
		const_iterator lhs_itr = this->begin();
		const_iterator rhs_itr = rhs.begin();
		const_iterator const rhs_end = rhs.end();
		for (; rhs_end != rhs_itr; ++lhs_itr, ++rhs_itr) {
			if (*lhs_itr > *rhs_itr) {
				return true;
			}
			else if (*lhs_itr < *rhs_itr) {
				return false;
			}
		}
		return true;
	}
	else {
		const_iterator lhs_itr = this->begin();
		const_iterator rhs_itr = rhs.begin();
		const_iterator const lhs_end = this->end();
		for (; lhs_end != lhs_itr; ++lhs_itr, ++rhs_itr) {
			if (*lhs_itr > *rhs_itr) {
				return true;
			}
			else if (*lhs_itr < *rhs_itr) {
				return false;
			}
		}
		return false;
	}
}
/**
  @brief confirms whether this instance is less than or equal to an other.
 */
template <hryky_template_param>
bool hryky::Array<hryky_template_arg>::operator<=(this_type const & rhs) const
{
	return !this->operator>(rhs);
}
/**
  @brief confirms whether this instance is greater than or equal to an other.
 */
template <hryky_template_param>
bool hryky::Array<hryky_template_arg>::operator>=(this_type const & rhs) const
{
	return !this->operator<(rhs);
}
/**
  @brief retrieves the mutable reference at the specified index.
 */
template <hryky_template_param>
typename hryky::Array<hryky_template_arg>::reference 
hryky::Array<hryky_template_arg>::operator[](size_type const index)
{
	return this->raw_[index];
}
/**
  @brief retrieves the immutable reference at the specified index.
 */
template <hryky_template_param>
typename hryky::Array<hryky_template_arg>::const_reference 
hryky::Array<hryky_template_arg>::operator[](size_type const index) const
{
	return this->raw_[index];
}
/**
  @brief retrieves the mutable iterator pointing to the beginning.
 */
template <hryky_template_param>
typename hryky::Array<hryky_template_arg>::iterator
hryky::Array<hryky_template_arg>::begin()
{
	return iterator(this, 0);
}
/**
  @brief retrieves the immutable iterator pointing to the beginning.
 */
template <hryky_template_param>
typename hryky::Array<hryky_template_arg>::const_iterator
hryky::Array<hryky_template_arg>::begin() const
{
	return const_iterator(this, 0);
}
/**
  @brief retrieves the mutable iterator pointing to the end.
 */
template <hryky_template_param>
typename hryky::Array<hryky_template_arg>::iterator
hryky::Array<hryky_template_arg>::end()
{
	return iterator(this, this->size());
}
/**
  @brief retrieves the immutable iterator pointing to the end.
 */
template <hryky_template_param>
typename hryky::Array<hryky_template_arg>::const_iterator
hryky::Array<hryky_template_arg>::end() const
{
	return const_iterator(this, this->size());
}
/**
  @brief retrieves the mutable reversed iterator pointing to the beginning.
 */
template <hryky_template_param>
typename hryky::Array<hryky_template_arg>::reverse_iterator
hryky::Array<hryky_template_arg>::rbegin()
{
	return reverse_iterator(this->end());
}
/**
  @brief retrieves the immutable reversed iterator pointing to the beginning.
 */
template <hryky_template_param>
typename hryky::Array<hryky_template_arg>::const_reverse_iterator
hryky::Array<hryky_template_arg>::rbegin() const
{
	return const_reverse_iterator(this->end());
}
/**
  @brief retrieves the mutable reversed iterator pointing to the end.
 */
template <hryky_template_param>
typename hryky::Array<hryky_template_arg>::reverse_iterator
hryky::Array<hryky_template_arg>::rend()
{
	return reverse_iterator(this->begin());
}
/**
  @brief retrieves the immutable reversed iterator pointing to the end.
 */
template <hryky_template_param>
typename hryky::Array<hryky_template_arg>::const_reverse_iterator
hryky::Array<hryky_template_arg>::rend() const
{
	return const_reverse_iterator(this->begin());
}
/**
  @brief retrieves the size of this array.
 */
template <hryky_template_param>
typename hryky::Array<hryky_template_arg>::size_type 
hryky::Array<hryky_template_arg>::size() const
{
	return static_cast<size_type>(Size);
}
/**
  @brief retrieves the beginning address of the immutable raw data.
 */
template <hryky_template_param>
typename hryky::Array<hryky_template_arg>::const_pointer 
hryky::Array<hryky_template_arg>::data() const
{
	return this->raw_;
}
/**
  @brief retrieves the beginning address of the mutable raw data.
 */
template <hryky_template_param>
typename hryky::Array<hryky_template_arg>::pointer 
hryky::Array<hryky_template_arg>::data()
{
	return this->raw_;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::Array<hryky_template_arg>::swap(this_type & src)
{
	this->foreach_at([&src](reference lhs, size_type const index) {
		hryky::swap(lhs, src[index]);
	});
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::Array<hryky_template_arg>::clear()
{
	this->foreach([](reference ref) {
		hryky::clear(ref);
	});
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::Array<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	out << hryky_stream_denote(Size);
	out << stream::denote("elements");

	stream::array::Scope<StreamT> const array(out);

	this->foreach([&out](const_reference value) {
		out << value;
	});

	return out;
}
/**
  @brief calls an arbitrary function with each element.
 */
template <hryky_template_param>
template <typename FunctorT>
void hryky::Array<hryky_template_arg>::foreach(
	FunctorT const & functor)
{
	this->foreach_from<FunctorT, 0>(functor);
}
/**
  @brief calls an arbitrary function with each immutable element.
 */
template <hryky_template_param>
template <typename FunctorT>
void hryky::Array<hryky_template_arg>::foreach(
	FunctorT const & functor) const
{
	this->foreach_from<FunctorT, 0>(functor);
}
/**
  @brief calls an arbitrary function with each element and the index.
 */
template <hryky_template_param>
template <typename FunctorT>
void hryky::Array<hryky_template_arg>::foreach_at(
	FunctorT const & functor)
{
	this->foreach_at_from<FunctorT, 0>(functor);
}
/**
  @brief calls an arbitrary function with each immutable element
    and the index.
 */
template <hryky_template_param>
template <typename FunctorT>
void hryky::Array<hryky_template_arg>::foreach_at(
	FunctorT const & functor) const
{
	this->foreach_at_from<FunctorT, 0>(functor);
}
/**
  @brief calls an arbitrary function with each element until
    the function fails.
 */
template <hryky_template_param>
template <typename FunctorT>
bool hryky::Array<hryky_template_arg>::every(
	FunctorT const & functor)
{
	return this->every_from<FunctorT, 0>(functor);
}
/**
  @brief calls an arbitrary function with each immutable element until
    the function fails.
 */
template <hryky_template_param>
template <typename FunctorT>
bool hryky::Array<hryky_template_arg>::every(
	FunctorT const & functor) const
{
	return this->every_from<FunctorT, 0>(functor);
}
/**
  @brief calls an arbitrary function with each element and the index
    until the function fails.
 */
template <hryky_template_param>
template <typename FunctorT>
bool hryky::Array<hryky_template_arg>::every_at(
	FunctorT const & functor)
{
	return this->every_at_from<FunctorT, 0>(functor);
}
/**
  @brief calls an arbitrary function with each immutableelement and
    the index until the function fails.
 */
template <hryky_template_param>
template <typename FunctorT>
bool hryky::Array<hryky_template_arg>::every_at(
	FunctorT const & functor) const
{
	return this->every_at_from<FunctorT, 0>(functor);
}
/**
  @brief calls an arbitrary function with each element until
    the function succeeds.
 */
template <hryky_template_param>
template <typename FunctorT>
bool hryky::Array<hryky_template_arg>::some(
	FunctorT const & functor)
{
	return this->some_from<FunctorT, 0>(functor);
}
/**
  @brief calls an arbitrary function with each immutable element until
    the function succeeds.
 */
template <hryky_template_param>
template <typename FunctorT>
bool hryky::Array<hryky_template_arg>::some(
	FunctorT const & functor) const
{
	return this->some_from<FunctorT, 0>(functor);
}
/**
  @brief calls an arbitrary function with each element
    and the index until the function succeeds.
 */
template <hryky_template_param>
template <typename FunctorT>
bool hryky::Array<hryky_template_arg>::some_at(
	FunctorT const & functor)
{
	return this->some_at_from<FunctorT, 0>(functor);
}
/**
  @brief calls an arbitrary function with each immutable element
    and the index until the function succeeds.
 */
template <hryky_template_param>
template <typename FunctorT>
bool hryky::Array<hryky_template_arg>::some_at(
	FunctorT const & functor) const
{
	return this->some_at_from<FunctorT, 0>(functor);
}
/**
  @brief calls an arbitrary function with each element.
    This iteration starts from the specified offset.
 */
template <hryky_template_param>
template <typename FunctorT, size_t Offset>
void hryky::Array<hryky_template_arg>::foreach_from(
	FunctorT const & functor)
{
	this_type & that = *this;
	Unroll<Size - Offset, Offset>::foreach_at([&that, &functor](
		size_type const index) {
		functor(that[index]);
	});
}
/**
  @brief calls an arbitrary function with each immutable element.
    This iteration starts from the specified offset.
 */
template <hryky_template_param>
template <typename FunctorT, size_t Offset>
void hryky::Array<hryky_template_arg>::foreach_from(
	FunctorT const & functor) const
{
	this_type const & that = *this;
	Unroll<Size - Offset, Offset>::foreach_at([&that, &functor](
		size_type const index) {
		functor(that[index]);
	});
}
/**
  @brief calls an arbitrary function with each element and the index.
    This iteration starts from the specified offset.
 */
template <hryky_template_param>
template <typename FunctorT, size_t Offset>
void hryky::Array<hryky_template_arg>::foreach_at_from(
	FunctorT const & functor)
{
	this_type & that = *this;
	Unroll<Size - Offset, Offset>::foreach_at([&that, &functor](
		size_type const index) {
		functor(that[index], index);
	});
}
/**
  @brief calls an arbitrary function with each immutable element
    and the index. This iteration starts from the specified offset.
 */
template <hryky_template_param>
template <typename FunctorT, size_t Offset>
void hryky::Array<hryky_template_arg>::foreach_at_from(
	FunctorT const & functor) const
{
	this_type const & that = *this;
	Unroll<Size - Offset, Offset>::foreach_at([&that, &functor](
		size_type const index) {
		functor(that[index], index);
	});
}
/**
  @brief calls an arbitrary function with each element until
    the function fails. This iteration starts from the specified offset.
 */
template <hryky_template_param>
template <typename FunctorT, size_t Offset>
bool hryky::Array<hryky_template_arg>::every_from(
	FunctorT const & functor)
{
	this_type & that = *this;
	return Unroll<Size - Offset, Offset>::every_at([&that, &functor](
		size_type const index) {
		return functor(that[index]);
	});
}
/**
  @brief calls an arbitrary function with each immutable element until
    the function fails. This iteration starts from the specified offset.
 */
template <hryky_template_param>
template <typename FunctorT, size_t Offset>
bool hryky::Array<hryky_template_arg>::every_from(
	FunctorT const & functor) const
{
	this_type const & that = *this;
	return Unroll<Size - Offset, Offset>::every_at([&that, &functor](
		size_type const index) {
		return functor(that[index]);
	});
}
/**
  @brief calls an arbitrary function with each element and the index
    until the function fails. This iteration starts from the specified
    offset.
 */
template <hryky_template_param>
template <typename FunctorT, size_t Offset>
bool hryky::Array<hryky_template_arg>::every_at_from(
	FunctorT const & functor)
{
	this_type & that = *this;
	return Unroll<Size - Offset, Offset>::every_at([&that, &functor](
		size_type const index) {
		return functor(that[index], index);
	});
}
/**
  @brief calls an arbitrary function with each immutableelement and
    the index until the function fails. This iteration starts from the
    specified offset.
 */
template <hryky_template_param>
template <typename FunctorT, size_t Offset>
bool hryky::Array<hryky_template_arg>::every_at_from(
	FunctorT const & functor) const
{
	this_type const & that = *this;
	return Unroll<Size - Offset, Offset>::every_at([&that, &functor](
		size_type const index) {
		return functor(that[index], index);
	});
}
/**
  @brief calls an arbitrary function with each element until
    the function succeeds. This iteration starts from the specified offset.
 */
template <hryky_template_param>
template <typename FunctorT, size_t Offset>
bool hryky::Array<hryky_template_arg>::some_from(
	FunctorT const & functor)
{
	this_type & that = *this;
	return Unroll<Size - Offset, Offset>::some_at([&that, &functor](
		size_type const index) {
		return functor(that[index]);
	});
}
/**
  @brief calls an arbitrary function with each immutable element until
    the function succeeds. This iteration starts from the specified offset.
 */
template <hryky_template_param>
template <typename FunctorT, size_t Offset>
bool hryky::Array<hryky_template_arg>::some_from(
	FunctorT const & functor) const
{
	this_type const & that = *this;
	return Unroll<Size - Offset, Offset>::some_at([&that, &functor](
		size_type const index) {
		return functor(that[index]);
	});
}
/**
  @brief calls an arbitrary function with each element
    and the index until the function succeeds. This iteration starts from
    the specified offset.
 */
template <hryky_template_param>
template <typename FunctorT, size_t Offset>
bool hryky::Array<hryky_template_arg>::some_at_from(
	FunctorT const & functor)
{
	this_type & that = *this;
	return Unroll<Size - Offset, Offset>::some_at([&that, &functor](
		size_type const index) {
		return functor(that[index], index);
	});
}
/**
  @brief calls an arbitrary function with each immutable element
    and the index until the function succeeds. This iteration starts from
    the specified offset.
 */
template <hryky_template_param>
template <typename FunctorT, size_t Offset>
bool hryky::Array<hryky_template_arg>::some_at_from(
	FunctorT const & functor) const
{
	this_type const & that = *this;
	return Unroll<Size - Offset, Offset>::some_at([&that, &functor](
		size_type const index) {
		return functor(that[index], index);
	});
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
	/// calculates an inner product of arrays as vector.
	template <hryky_template_param>
	typename ValueT inner_product(
		Array<hryky_template_arg> const & lhs,
		Array<hryky_template_arg> const & rhs);

	/// outputs the information of Array<> through stream.
	template <hryky_template_param, typename StreamT>
	StreamT & operator<<(
		StreamT & lhs, Array<hryky_template_arg> const & rhs);

	/// interchanges two instances of the same type.
	template <hryky_template_param>
	void swap(
		Array<hryky_template_arg> & lhs,
		Array<hryky_template_arg> & rhs);

}
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief calculates an inner product of arrays as vector.
 */
template <hryky_template_param>
ValueT hryky::inner_product(
	Array<hryky_template_arg> const & lhs,
	Array<hryky_template_arg> const & rhs)
{
	typedef Array<hryky_template_arg> array_type;
	array_type::value_type result = array_type::value_type();

	lhs.foreach_at([&result, &rhs](
		array_type::const_reference lhs_value,
		array_type::size_type const index) {
		result += inner_product(lhs_value, rhs[index]);
	});
	
	return result;
}
/**
  @brief outputs the information of Array<> through stream.
 */
template <hryky_template_param, typename StreamT>
StreamT & hryky::operator<<(
	StreamT & lhs, Array<hryky_template_arg> const & rhs)
{
	return rhs.write_to(lhs);
}
/**
  @brief interchanges two instances of the same type.
 */
template <hryky_template_param>
void hryky::swap(
	Array<hryky_template_arg> & lhs,
	Array<hryky_template_arg> & rhs)
{
	lhs.swap(rhs);
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#undef hryky_size_type
#undef hryky_difference_type
#undef hryky_pointer
#undef hryky_const_pointer
#undef hryky_reference
#undef hryky_const_reference
#undef hryky_iterator
#undef hryky_const_iterator
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // ARRAY_H_20120331175726414
// end of file
