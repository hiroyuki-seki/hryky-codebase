/**
  @file         offset_ptr.h
  @brief        refers the value by the offset from the origin.
  @author       HRYKY
  @version      $Id: offset_ptr.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef OFFSET_PTR_H_20120719133424232
#define OFFSET_PTR_H_20120719133424232
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
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
	/// refers the value by the offset from the origin.
	template <hryky_template_param>
	class OffsetPtr;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief refers the value by the offset from the origin.
 */
template <hryky_template_param>
class hryky::OffsetPtr :
	public WithStreamOut<OffsetPtr<hryky_template_arg> >,
	public WithSwap<OffsetPtr<hryky_template_arg> >
{
public :

	typedef OffsetPtr<hryky_template_arg>           this_type;
	typedef ValueT                                  value_type;
	typedef typename AddPointer<ValueT>::type       pointer;
	typedef typename AddReference<ValueT>::type     reference;
	typedef ::std::ptrdiff_t                          difference_type;
	typedef typename AsParameter<OriginT>::type     origin_param_type;
	typedef typename AsParameter<OffsetT>::type     offset_param_type;

	/// default constructor.
	OffsetPtr();

	/// constructor with the origin and the offset.
	OffsetPtr(origin_param_type origin, offset_param_type offset);

	/// copy constructor.
	OffsetPtr(this_type const & rhs);

	/// move constructor.
	OffsetPtr(this_type && rhs);

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// interchanges the entities between two instances.
	void swap(this_type & src);

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

	/// post-decrements the pointer.
	this_type operator--(int);

	/// retrieves a forward pointer.
	this_type operator+(difference_type const difference) const;

	/// retrieves a backward pointer.
	this_type operator-(difference_type const difference) const;

	/// retrieves the distance between the two instances.
	difference_type operator-(this_type const & rhs) const;

	/// confirms that two instances refer the same position.
	bool operator==(this_type const & rhs) const;

	/// confirms that each instance refer a different position.
	bool operator!=(this_type const & rhs) const;

	/// confirms whether the LHS is less than the RHS.
	bool operator<(this_type const & rhs) const;

	/// confirms whether the LHS is greater than the RHS.
	bool operator>(this_type const & rhs) const;

	/// confirms whether the LHS is less than or equal to the RHS.
	bool operator<=(this_type const & rhs) const;

	/// confirms whether the LHS is greater than or equal to the RHS.
	bool operator>=(this_type const & rhs) const;

	/// confirms whether each instance has the same origin.
	bool reachable(this_type const & rhs) const;

	/// retrieves the origin.
	OriginT origin() const;

	/// retrieves the offset.
	OffsetT offset() const;

	/// moves the pointer forward.
	this_type & operator+=(difference_type const rhs);

	/// moves the pointer backward.
	this_type & operator-=(difference_type const rhs);

protected :

private :

	OriginT     origin_;
	OffsetT     offset_;

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
hryky::OffsetPtr<hryky_template_arg>::OffsetPtr()
	: origin_()
	  , offset_()
{
	return;
}
/**
  @brief constructor with the origin and the offset.
 */
template <hryky_template_param>
hryky::OffsetPtr<hryky_template_arg>::OffsetPtr(
	origin_param_type origin, offset_param_type offset)
	: origin_(origin)
	  , offset_(offset)
{
	return;
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::OffsetPtr<hryky_template_arg>::OffsetPtr(this_type const & rhs)
	: hryky_copy_member(origin)
	  , hryky_copy_member(offset)
{
	return;
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::OffsetPtr<hryky_template_arg>::OffsetPtr(this_type && rhs)
	: hryky_move_member(origin)
	  , hryky_move_member(offset)
{
}
/**
  @brief interchanges the entities between two instances.
 */
template <hryky_template_param>
void hryky::OffsetPtr<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(origin);
	hryky_swap_member(offset);
}
/**
  @brief dereferences the pointer.
 */
template <hryky_template_param>
typename hryky::OffsetPtr<hryky_template_arg>::reference
hryky::OffsetPtr<hryky_template_arg>::operator*() const
{
	return (*this->origin_)[this->offset_];
}
/**
  @brief dereferences the pointer.
 */
template <hryky_template_param>
typename hryky::OffsetPtr<hryky_template_arg>::pointer
hryky::OffsetPtr<hryky_template_arg>::operator->() const
{
	return &this->operator*();
}
/**
  @brief pre-increments the pointer.
 */
template <hryky_template_param>
hryky::OffsetPtr<hryky_template_arg> & 
hryky::OffsetPtr<hryky_template_arg>::operator++()
{
	++this->offset_;
	return *this;
}
/**
  @brief post-increments the pointer.
 */
template <hryky_template_param>
hryky::OffsetPtr<hryky_template_arg> 
hryky::OffsetPtr<hryky_template_arg>::operator++(int)
{
	++this->offset_;
	return this_type(this->origin_, this->offset_ - 1);
}
/**
  @brief pre-decrements the pointer.
 */
template <hryky_template_param>
hryky::OffsetPtr<hryky_template_arg> & 
hryky::OffsetPtr<hryky_template_arg>::operator--()
{
	--this->offset_;
	return *this;
}
/**
  @brief post-decrements the pointer.
 */
template <hryky_template_param>
hryky::OffsetPtr<hryky_template_arg> 
hryky::OffsetPtr<hryky_template_arg>::operator--(int)
{
	--this->offset_;
	return this_type(this->origin_, this->offset_ + 1);
}
/**
  @brief retrieves a forward pointer.
 */
template <hryky_template_param>
hryky::OffsetPtr<hryky_template_arg> 
hryky::OffsetPtr<hryky_template_arg>::operator+(
	difference_type const difference) const
{
	return this_type(this->origin_, this->offset_ + difference);
}
/**
  @brief retrieves a backward pointer.
 */
template <hryky_template_param>
hryky::OffsetPtr<hryky_template_arg> 
hryky::OffsetPtr<hryky_template_arg>::operator-(
	difference_type const difference) const
{
	return this_type(this->origin_, this->offset_ - difference);
}
/**
  @brief retrieves the distance between the two instances.
 */
template <hryky_template_param>
::std::ptrdiff_t hryky::OffsetPtr<hryky_template_arg>::operator-(
	this_type const & rhs) const
{
	if (this->origin_ != rhs.origin_) {
		hryky_throw(
			::std::invalid_argument,
			"rhs doesn't have the same origin as this instance.",
			return 0);
	}
	return this->offset_ - rhs.offset_;
}
/**
  @brief confirms that two instances refer the same position.
 */
template <hryky_template_param>
bool hryky::OffsetPtr<hryky_template_arg>::operator==(
	this_type const & rhs) const
{
	return this->origin_ == rhs.origin_ && this->offset_ == rhs.offset_;
}
/**
  @brief confirms that each instance refer a different position.
 */
template <hryky_template_param>
bool hryky::OffsetPtr<hryky_template_arg>::operator!=(
	this_type const & rhs) const
{
	return !this->operator==(rhs);
}
/**
  @brief confirms whether the LHS is less than the RHS.
 */
template <hryky_template_param>
bool hryky::OffsetPtr<hryky_template_arg>::operator<(
	this_type const & rhs) const
{
	return (this->origin_ < rhs.origin_
			? true
			: (this->origin_ > rhs.origin_
			   ? false
			   : this->offset_ < rhs.offset_));
}
/**
  @brief confirms whether the LHS is greater than the RHS.
 */
template <hryky_template_param>
bool hryky::OffsetPtr<hryky_template_arg>::operator>(
	this_type const & rhs) const
{
	return (this->origin_ > rhs.origin_
			? true
			: (this->origin_ < rhs.origin_
			   ? false
			   : this->offset_ > rhs.offset_));
}
/**
  @brief confirms whether the LHS is less than or equal to the RHS.
 */
template <hryky_template_param>
bool hryky::OffsetPtr<hryky_template_arg>::operator<=(
	this_type const & rhs) const
{
	return (this->origin_ < rhs.origin_
			? true
			: (this->origin_ > rhs.origin_
			   ? false
			   : this->offset_ <= rhs.offset_));
}
/**
  @brief confirms whether the LHS is greater than or equal to the RHS.
 */
template <hryky_template_param>
bool hryky::OffsetPtr<hryky_template_arg>::operator>=(
	this_type const & rhs) const
{
	return (this->origin_ > rhs.origin_
			? true
			: (this->origin_ < rhs.origin_
			   ? false
			   : this->offset_ >= rhs.offset_));
}
/**
  @brief confirms whether each instance has the same origin.
 */
template <hryky_template_param>
bool hryky::OffsetPtr<hryky_template_arg>::reachable(
	this_type const & rhs) const
{
	return this->origin_ == rhs.origin_;
}
/**
  @brief retrieves the origin.
 */
template <hryky_template_param>
OriginT hryky::OffsetPtr<hryky_template_arg>::origin() const
{
	return this->origin_;
}
/**
  @brief retrieves the offset.
 */
template <hryky_template_param>
OffsetT hryky::OffsetPtr<hryky_template_arg>::offset() const
{
	return this->offset_;
}
/**
  @brief forwards this pointer.
 */
template <hryky_template_param>
hryky::OffsetPtr<hryky_template_arg> & 
hryky::OffsetPtr<hryky_template_arg>::operator+=(
	difference_type const rhs)
{
	this->offset_ += rhs;
	return *this;
}
/**
  @brief moves the pointer backward.
 */
template <hryky_template_param>
hryky::OffsetPtr<hryky_template_arg> & 
hryky::OffsetPtr<hryky_template_arg>::operator-=(
	difference_type const rhs)
{
	this->offset_ -= rhs;
	return *this;
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
#endif // OFFSET_PTR_H_20120719133424232
// end of file
