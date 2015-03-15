/**
  @file         intrusive_ptr.h
  @brief        basic functionality of intrusive pointer.
  @author       HRYKY
  @version      $Id: intrusive_ptr.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef INTRUSIVE_PTR_H_20120606003103688
#define INTRUSIVE_PTR_H_20120606003103688
#include "hryky/debug/debug_common.h"
#include "hryky/debug/debug_source.h"
#include "hryky/is_null.h"
#include "hryky/nullptr.h"
#include "hryky/type_traits/add_const_pointer.h"
#include "hryky/type_traits/add_const_reference.h"
#include "hryky/type_traits/add_pointer.h"
#include "hryky/type_traits/add_reference.h"
#include "hryky/type_traits/integral_constant.h"
#include "hryky/type_traits/remove_const.h"
#include "hryky/type_traits/remove_pointer.h"
#include "hryky/with_is_null.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT
#define hryky_template_arg \
	ValueT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// basic functionality of intrusive pointer.
	template <hryky_template_param>
	class IntrusivePtr;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief basic functionality of intrusive pointer.
 */
template <hryky_template_param>
class hryky::IntrusivePtr :
	public WithStreamOut<IntrusivePtr<hryky_template_arg> >,
	public WithSwap<IntrusivePtr<hryky_template_arg> >,
	public WithIsNull<IntrusivePtr<hryky_template_arg> >
{
public :

	typedef IntrusivePtr                                    this_type;
	typedef ::std::ptrdiff_t                                difference_type;
	typedef typename RemoveConst<ValueT>::type              value_type;
	typedef typename AddPointer<value_type>::type           pointer;
	typedef typename AddReference<value_type>::type         reference;
	typedef typename AddConstPointer<value_type>::type      const_pointer;
	typedef typename AddConstReference<value_type>::type    const_reference;

	/// default constructor.
	IntrusivePtr();

	/**
	  @brief constructor with a held pointer and specifies whether
	         the reference of the instance is incremented.
	 */
	IntrusivePtr(pointer ptr, bool add_ref);

	/**
	  @brief constructor with a held derived pointer and specifies
	         whether the reference of the instance is incremented.
	 */
	template < typename DerivedT >
	explicit IntrusivePtr(DerivedT * ptr, bool add_ref = true);

	/// constructor with other derived pointer.
	template < typename DerivedT >
	IntrusivePtr(IntrusivePtr<DerivedT> const & src);

	/// copy constructor.
	IntrusivePtr(this_type const & rhs);

	/// move constructor.
	IntrusivePtr(this_type && rhs);

	/// destructor.
	~IntrusivePtr();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// assignment operator with other derived pointer.
	template < typename DerivedT >
	this_type & operator=(IntrusivePtr<DerivedT> const & rhs);

	/// assigns an other pointer.
	this_type & operator=(pointer const rhs);

	/// dereferences the pointer.
	reference operator*() const;

	/// dereferences the pointer.
	pointer operator->() const;

	/// pre-increments the pointer.
	this_type & operator++();

	/// post-increments the pointer.
	this_type operator++(int);

	/// pre-decrements the pointer.
	this_type & operator--();

	/// post-increments the pointer.
	this_type operator--(int);

	/// retrieves a forward pointer.
	this_type operator+(difference_type const offset) const;

	/// retrieves a backward pointer.
	this_type operator-(difference_type const offset) const;

	/// retrieves the distance between the two pointers.
	difference_type operator-(this_type const & rhs) const;

	/// retrieves the distance between this pointer and a raw pointer.
	difference_type operator-(pointer const rhs) const;

	/// confirms that this pointer and other pointer are equal.
	template < typename DerivedT >
	bool operator==(IntrusivePtr<DerivedT> const & rhs) const;

	/// confirms that this pointer and other raw pointer are equal.
	bool operator==(pointer const rhs) const;

	/// confirms that this pointer and other pointer are not equal.
	bool operator!=(this_type const & rhs) const;

	/// confirms that this pointer and other raw pointer are not equal.
	bool operator!=(pointer const rhs) const;

	/// confirms that this pointer is less than other pointer.
	bool operator<(this_type const & rhs) const;

	/// confirms that this pointer is less than other raw pointer.
	bool operator<(pointer const rhs) const;

	/// confirms that this pointer is greater than other pointer.
	bool operator>(this_type const & rhs) const;

	/// confirms that this pointer is greater than other raw pointer.
	bool operator>(pointer const rhs) const;

	/// confirms that this pointer is less than or equal to other pointer.
	bool operator<=(this_type const & rhs) const;

	/// confirms that this pointer is less than or equal to other raw pointer.
	bool operator<=(pointer const rhs) const;

	/// confirms that this pointer is greater than or equal to other pointer.
	bool operator>=(this_type const & rhs) const;

	/**
	  confirms that this pointer is greater than or equal to other
	  raw pointer.
	 */
	bool operator>=(pointer const rhs) const;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the entities between two values.
	void swap(this_type & src);

	/// retrieves the raw pointer of this instance.
	pointer get() const;

	/// confirms whether the internal pointer is null.
	bool is_null() const;

protected :

private :

	/// increments the reference counter of the pointer.
	void add_ref();

	/// decrements the reference counter of the pointer.
	void release();

	pointer     ptr_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  specializes hryky::RemovePointer
 */
template <hryky_template_param>
class RemovePointer<IntrusivePtr<hryky_template_arg> >
{
public :

	typedef ValueT                      type;
	typedef IntrusivePtr<hryky_template_arg>        pointer;
	typedef typename pointer::reference result_type;

	RemovePointer(pointer ptr)
		: ptr_(ptr)
	{}

	result_type operator()() const
	{
		return *this->ptr_;
	}

private :
	pointer     ptr_;

};
/**
  specializes hryky::IsPointer.
 */
template <hryky_template_param>
class IsPointer<IntrusivePtr<hryky_template_arg> >
{
public :
	typedef true_type type;
};
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::IntrusivePtr<hryky_template_arg>::IntrusivePtr()
	: ptr_()
{
	return;
}
/**
  @brief constructor with a held pointer and specifies whether the
    reference of the instance is incremented.
 */
template <hryky_template_param>
hryky::IntrusivePtr<hryky_template_arg>::IntrusivePtr(
	pointer ptr, bool add_ref)
	: ptr_(ptr)
{
	if (add_ref) {
		this->add_ref();
	}
	return;
}
/**
  @brief constructor with a held derived pointer and specifies whether
    the reference of the instance is incremented.
 */
template <hryky_template_param>
template <typename DerivedT>
hryky::IntrusivePtr<hryky_template_arg>::IntrusivePtr(
	DerivedT * ptr, bool add_ref)
	: ptr_(ptr)
{
	if (add_ref) {
		this->add_ref();
	}
	return;
}
/**
  @brief constructor with other derived pointer.
 */
template <hryky_template_param>
template < typename DerivedT >
hryky::IntrusivePtr<hryky_template_arg>::IntrusivePtr(
	IntrusivePtr<DerivedT> const & src)
	: ptr_(src.get())
{
	this->add_ref();
	return;
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::IntrusivePtr<hryky_template_arg>::IntrusivePtr(
	this_type const & rhs)
	: hryky_copy_member(ptr)
{
	this->add_ref();
	return;
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::IntrusivePtr<hryky_template_arg>::IntrusivePtr(
	this_type && rhs)
	: hryky_copy_member(ptr)
{
	rhs.ptr_ = hryky_nullptr;
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::IntrusivePtr<hryky_template_arg>::~IntrusivePtr()
{
	this->release();
}
/**
  @brief assignment operator with other derived pointer.
 */
template <hryky_template_param>
template <typename DerivedT>
hryky::IntrusivePtr<hryky_template_arg> &
hryky::IntrusivePtr<hryky_template_arg>::operator=(
	IntrusivePtr<DerivedT> const & rhs)
{
	if (this == &rhs) {
		return *this;
	}

	this_type const tmp(rhs);

	*this = tmp;
	
	return *this;
}
/**
  @brief assigns an other pointer.
 */
template <hryky_template_param>
hryky::IntrusivePtr<hryky_template_arg> &
hryky::IntrusivePtr<hryky_template_arg>::operator=(
	pointer const rhs)
{
	if (this->ptr_ == rhs) {
		return *this;
	}

	if (!hryky_is_null(rhs)) {
		intrusive_ptr_add_ref(rhs);
	}

	this->release();

	this->ptr_ = rhs;
	
	return *this;
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::IntrusivePtr<hryky_template_arg>::clear()
{
	this->release();
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::IntrusivePtr<hryky_template_arg>::write_to(
	StreamT & out) const
{
	out << this->ptr_;
	return out;
}
/**
  @brief interchanges the entities between two values.
 */
template <hryky_template_param>
void hryky::IntrusivePtr<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(ptr);
}
/**
  @brief dereferences the pointer.
 */
template <hryky_template_param>
typename hryky::IntrusivePtr<hryky_template_arg>::reference
hryky::IntrusivePtr<hryky_template_arg>::operator*() const
{
	if (this->is_null()) {
		hryky_throw(
			::std::logic_error,
			"dereference of null pointer",
			return *this->ptr_);
	}
	return *this->ptr_;
}
/**
  @brief dereferences the pointer.
 */
template <hryky_template_param>
typename hryky::IntrusivePtr<hryky_template_arg>::pointer
hryky::IntrusivePtr<hryky_template_arg>::operator->() const
{
	if (this->is_null()) {
		hryky_throw(
			::std::logic_error,
			"dereference of null pointer",
			return this->ptr_);
	}
	return this->ptr_;
}
/**
  @brief pre-increments the pointer.
 */
template <hryky_template_param>
hryky::IntrusivePtr<hryky_template_arg> &
hryky::IntrusivePtr<hryky_template_arg>::operator++()
{
	if (this->is_null()) {
		hryky_throw(
			::std::logic_error,
			"invalid pointer",
			return *this);
	}
	++this->ptr_;
	
	return *this;
}
/**
  @brief post-increments the pointer.
 */
template <hryky_template_param>
hryky::IntrusivePtr<hryky_template_arg>
hryky::IntrusivePtr<hryky_template_arg>::operator++(int)
{
	if (this->is_null()) {
		hryky_throw(
			::std::logic_error,
			"invalid pointer",
			return *this);
	}

	++this->ptr_;

	return this_type(this->ptr_ - 1);
}
/**
  @brief pre-decrements the pointer.
 */
template <hryky_template_param>
hryky::IntrusivePtr<hryky_template_arg> &
hryky::IntrusivePtr<hryky_template_arg>::operator--()
{
	if (this->is_null()) {
		hryky_throw(
			::std::logic_error,
			"invalid pointer",
			return *this);
	}
	--this->ptr_;
	
	return *this;
}
/**
  @brief post-increments the pointer.
 */
template <hryky_template_param>
hryky::IntrusivePtr<hryky_template_arg>
hryky::IntrusivePtr<hryky_template_arg>::operator--(int)
{
	if (this->is_null()) {
		hryky_throw(
			::std::logic_error,
			"invalid pointer",
			return *this);
	}

	--this->ptr_;

	return this_type(this->ptr_ + 1);
}
/**
  @brief retrieves a forward pointer.
 */
template <hryky_template_param>
hryky::IntrusivePtr<hryky_template_arg>
hryky::IntrusivePtr<hryky_template_arg>::operator+(
	difference_type const offset) const
{
	if (this->is_null()) {
		hryky_throw(
			::std::logic_error,
			"invalid pointer",
			return *this);
	}

	return this_type(this->ptr_ + offset);
}
/**
  @brief retrieves a backward pointer.
 */
template <hryky_template_param>
hryky::IntrusivePtr<hryky_template_arg>
hryky::IntrusivePtr<hryky_template_arg>::operator-(
	difference_type const offset) const
{
	if (this->is_null()) {
		hryky_throw(
			::std::logic_error,
			"invalid pointer",
			return *this);
	}

	return this_type(this->ptr_ - offset);
}
/**
  @brief retrieves the distance between the two pointers.
 */
template <hryky_template_param>
typename hryky::IntrusivePtr<hryky_template_arg>::difference_type 
hryky::IntrusivePtr<hryky_template_arg>::operator-(
	this_type const & rhs) const
{
	if (this->is_null()) {
		hryky_throw(
			::std::logic_error,
			"invalid pointer",
			return *this);
	}

	if (rhs.is_null()) {
		hryky_throw(
			::std::invalid_argument,
			"rhs is null",
			return *this);
	}

	return this->ptr_ - rhs.ptr_;
}
/**
  @brief retrieves the distance between this pointer and a raw pointer.
 */
template <hryky_template_param>
typename hryky::IntrusivePtr<hryky_template_arg>::difference_type 
hryky::IntrusivePtr<hryky_template_arg>::operator-(
	pointer const rhs) const
{
	if (this->is_null()) {
		hryky_throw(
			::std::logic_error,
			"invalid pointer",
			return *this);
	}

	if (hryky_is_null(rhs)) {
		hryky_throw(
			::std::invalid_argument,
			"rhs is null",
			return *this);
	}

	return this->ptr_ - rhs;
}
/**
  @brief confirms that this pointer and other pointer are equal.
 */
template <hryky_template_param>
template < typename DerivedT >
bool hryky::IntrusivePtr<hryky_template_arg>::operator==(
	IntrusivePtr<DerivedT> const & rhs) const
{
	return this->ptr_ == rhs.ptr_;
}
/**
  @brief confirms that this pointer and other raw pointer are equal.
 */
template <hryky_template_param>
bool hryky::IntrusivePtr<hryky_template_arg>::operator==(
	pointer const rhs) const
{
	return this->ptr_ == rhs;
}
/**
  @brief confirms that this pointer and other pointer are not equal.
 */
template <hryky_template_param>
bool hryky::IntrusivePtr<hryky_template_arg>::operator!=(
	this_type const & rhs) const
{
	return this->ptr_ != rhs.ptr_;
}
/**
  @brief confirms that this pointer and other raw pointer are not equal.
 */
template <hryky_template_param>
bool hryky::IntrusivePtr<hryky_template_arg>::operator!=(
	pointer const rhs) const
{
	return this->ptr_ != rhs;
}
/**
  @brief confirms that this pointer is less than other pointer.
 */
template <hryky_template_param>
bool hryky::IntrusivePtr<hryky_template_arg>::operator<(
	this_type const & rhs) const
{
	return this->ptr_ < rhs.ptr_;
}
/**
  @brief confirms that this pointer is less than other raw pointer.
 */
template <hryky_template_param>
bool hryky::IntrusivePtr<hryky_template_arg>::operator<(
	pointer const rhs) const
{
	return this->ptr_ < rhs;
}
/**
  @brief confirms that this pointer is greater than other pointer.
 */
template <hryky_template_param>
bool hryky::IntrusivePtr<hryky_template_arg>::operator>(
	this_type const & rhs) const
{
	return this->ptr_ > rhs.ptr_;
}
/**
  @brief confirms that this pointer is greater than other raw pointer.
 */
template <hryky_template_param>
bool hryky::IntrusivePtr<hryky_template_arg>::operator>(
	pointer const rhs) const
{
	return this->ptr_ > rhs;
}
/**
  @brief confirms that this pointer is less than or equal to
    other pointer.
 */
template <hryky_template_param>
bool hryky::IntrusivePtr<hryky_template_arg>::operator<=(
	this_type const & rhs) const
{
	return this->ptr_ <= rhs.ptr_;
}
/**
  @brief confirms that this pointer is less than or equal to
    other raw pointer.
 */
template <hryky_template_param>
bool hryky::IntrusivePtr<hryky_template_arg>::operator<=(
	pointer const rhs) const
{
	return this->ptr_ <= rhs;
}
/**
  @brief confirms that this pointer is greater than or equal to
    other pointer.
 */
template <hryky_template_param>
bool hryky::IntrusivePtr<hryky_template_arg>::operator>=(
	this_type const & rhs) const
{
	return this->ptr_ >= rhs.ptr_;
}
/**
  @brief confirms that this pointer is greater than or equal to
    other raw pointer.
 */
template <hryky_template_param>
bool hryky::IntrusivePtr<hryky_template_arg>::operator>=(
	pointer const rhs) const
{
	return this->ptr_ >= rhs;
}
/**
  @brief retrieves the raw pointer of this instance.
 */
template <hryky_template_param>
typename hryky::IntrusivePtr<hryky_template_arg>::pointer
hryky::IntrusivePtr<hryky_template_arg>::get() const
{
	return this->ptr_;
}
/**
  @brief confirms whether the internal pointer is null.
 */
template <hryky_template_param>
bool hryky::IntrusivePtr<hryky_template_arg>::is_null() const
{
	return hryky_nullptr == this->ptr_;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief increments the reference counter of the pointer.
 */
template <hryky_template_param>
void hryky::IntrusivePtr<hryky_template_arg>::add_ref()
{
	if (!this->is_null()) {
		intrusive_ptr_add_ref(this->ptr_);
	}
}
/**
  @brief decrements the reference counter of the pointer.
 */
template <hryky_template_param>
void hryky::IntrusivePtr<hryky_template_arg>::release()
{
	if (!this->is_null()) {
		intrusive_ptr_release(this->ptr_);
		this->ptr_ = hryky_nullptr;
	}
}
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
	/// confirms whether an other raw pointer is equal to an intrusive pointer.
	template <typename LhsT, typename RhsT>
	bool operator==(LhsT * const lhs, IntrusivePtr<RhsT> const & rhs);

	/// confirms whether an other raw pointer is not equal to an intrusive pointer.
	template <typename LhsT, typename RhsT>
	bool operator!=(LhsT * const lhs, IntrusivePtr<RhsT> const & rhs);

	/// confirms whether an other raw pointer is less than an intrusive pointer.
	template <typename LhsT, typename RhsT>
	bool operator<(LhsT * const lhs, IntrusivePtr<RhsT> const & rhs);

	/**
	  confirms whether an other raw pointer is greater than an
	  intrusive pointer.
	 */
	template <typename LhsT, typename RhsT>
	bool operator>(LhsT * const lhs, IntrusivePtr<RhsT> const & rhs);

	/**
	  confirms whether an other raw pointer is less than or equal to an
	  intrusive pointer.
	 */
	template <typename LhsT, typename RhsT>
	bool operator<=(LhsT * const lhs, IntrusivePtr<RhsT> const & rhs);

	/**
	  confirms whether an other raw pointer is greater than or equal to an
	  intrusive pointer.
	 */
	template <typename LhsT, typename RhsT>
	bool operator>=(LhsT * const lhs, IntrusivePtr<RhsT> const & rhs);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief confirms whether an other raw pointer is equal to an
    intrusive pointer.
 */
template <typename LhsT, typename RhsT>
bool hryky::operator==(LhsT * const lhs, IntrusivePtr<RhsT> const & rhs)
{
	return lhs == rhs.get();
}
/**
  @brief confirms whether an other raw pointer is not equal to an
    intrusive pointer.
 */
template <typename LhsT, typename RhsT>
bool hryky::operator!=(LhsT * const lhs, IntrusivePtr<RhsT> const & rhs)
{
	return lhs != rhs.get();
}
/**
  @brief confirms whether an other raw pointer is less than an
    intrusive pointer.
 */
template <typename LhsT, typename RhsT>
bool hryky::operator<(LhsT * const lhs, IntrusivePtr<RhsT> const & rhs)
{
	return lhs < rhs.get();
}
/**
  @brief confirms whether an other raw pointer is greater than an
    intrusive pointer.
 */
template <typename LhsT, typename RhsT>
bool hryky::operator>(LhsT * const lhs, IntrusivePtr<RhsT> const & rhs)
{
	return lhs > rhs.get();
}
/**
  @brief confirms whether an other raw pointer is less than or
    equal to an intrusive pointer.
 */
template <typename LhsT, typename RhsT>
bool hryky::operator<=(LhsT * const lhs, IntrusivePtr<RhsT> const & rhs)
{
	return lhs <= rhs.get();
}
/**
  @brief confirms whether an other raw pointer is greater than or
    equal to an intrusive pointer.
 */
template <typename LhsT, typename RhsT>
bool hryky::operator>=(LhsT * const lhs, IntrusivePtr<RhsT> const & rhs)
{
	return lhs >= rhs.get();
}
//------------------------------------------------------------------------------
// revokes macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // INTRUSIVE_PTR_H_20120606003103688
// end of file
