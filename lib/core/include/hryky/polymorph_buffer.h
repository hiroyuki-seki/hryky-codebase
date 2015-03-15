/**
  @file     polymorph_buffer.h
  @brief    stores a polymorphic instance.
  @author   HRYKY
  @version  $Id: polymorph_buffer.h 371 2014-07-22 15:08:20Z hryky.private@gmail.com $
 */
#ifndef POLYMORPH_BUFFER_H_20140722185515455
#define POLYMORPH_BUFFER_H_20140722185515455
#include "hryky/aligned_buffer.h"
#include "hryky/tmp/tmp_binary_logarithm.h"
#include "hryky/type_traits/add_pointer.h"
#include "hryky/type_traits/add_const_pointer.h"
#include "hryky/type_traits/add_reference.h"
#include "hryky/type_traits/add_const_reference.h"
#include "hryky/type_traits/is_base_of.h"
#include "hryky/with_is_null.h"
#include "hryky/with_stream_out.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT, size_t Size, size_t AlignedExponent
#define hryky_template_arg \
	ValueT, Size, AlignedExponent
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// stores a polymorphic instance.
	template <
		typename ValueT,
		size_t Size = sizeof(ValueT),
		size_t AlignedExponent = tmp::BinaryLogarithmC<sizeof(size_t)>::value
	>
	class PolymorphBuffer;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief stores a polymorphic instance.
 */
template <hryky_template_param>
class hryky::PolymorphBuffer :
	public WithIsNull<PolymorphBuffer<hryky_template_arg> >,
	public WithStreamOut<PolymorphBuffer<hryky_template_arg> >
{
public :

	typedef PolymorphBuffer<hryky_template_arg>         this_type;
	typedef typename AddPointer<ValueT>::type           pointer;
	typedef typename AddConstPointer<ValueT>::type      const_pointer;
	typedef typename AddReference<ValueT>::type         reference;
	typedef typename AddConstReference<ValueT>::type    const_reference;

	/// default constructor.
	PolymorphBuffer();

	/// creates an instance by copying other instance.
	template <typename RhsT>
	PolymorphBuffer(RhsT const & rhs);

	/// destructor.
	~PolymorphBuffer();

	/// assigns an other instance.
	template <typename RhsT>
	this_type & operator=(RhsT const & rhs);

	/// moves the other instance to this buffer.
	template <typename RhsT>
	this_type & operator=(RhsT && rhs);

	/// retrieves the pointer to immutable instance.
	const_pointer operator->() const;

	/// retrieves the pointer to mutable instance.
	pointer operator->();

	/// retrieves the reference to immutable instance.
	const_reference operator*() const;

	/// retrieves the reference to mutable instance.
	reference operator*();

	/// releases the internal resources.
	void clear();

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// confirms whether the buffer is not instantiated.
	bool is_null() const;

protected :

private :
	hryky_delete_this_copy_constructor(PolymorphBuffer);
	hryky_delete_copy_assign_op(this_type);
	
	typedef AlignedBuffer<Size, AlignedExponent> buffer_type;

	/**
	  @brief confirms the other class can be assigned to buffer.
	 */
	template <typename RhsT>
	struct Assignable
	{
		static_assert(
			IsBaseOf<ValueT, RhsT>::value,
			"The RhsT is not derived from ValueT.");

		static_assert(
			sizeof(buffer_type) >= sizeof(RhsT),
			"The size of buffer is too small to store the instance.");
	};

	/// retrieves the address of mutable instance.
	pointer get();

	/// retrieves the address of immutable instance.
	const_pointer get() const;

	buffer_type buffer_;
	bool instantiated_;

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
hryky::PolymorphBuffer<hryky_template_arg>::PolymorphBuffer()
	: buffer_()
	  , instantiated_()
{
}
/**
  @brief creates an instance by copying other instance.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::PolymorphBuffer<hryky_template_arg>::PolymorphBuffer(
	RhsT const & rhs)
	: buffer_()
	  , instantiated_()
{
	Assignable<RhsT>;
	
	new (this->get()) RhsT(rhs);
	this->instantiated_ = true;
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::PolymorphBuffer<hryky_template_arg>::~PolymorphBuffer()
{
	this->clear();
}
/**
  @brief assigns an other instance.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::PolymorphBuffer<hryky_template_arg> & 
hryky::PolymorphBuffer<hryky_template_arg>::operator=(
	RhsT const & rhs)
{
	Assignable<RhsT>;
	
	this->clear();
	new (this->get()) RhsT(rhs);
	this->instantiated_ = true;
	
	return *this;
}
/**
  @brief moves the other instance to this buffer.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::PolymorphBuffer<hryky_template_arg> & 
hryky::PolymorphBuffer<hryky_template_arg>::operator=(
	RhsT && rhs)
{
	Assignable<RhsT>;
	
	this->clear();
	new (this->get()) RhsT(::std::move(rhs));
	this->instantiated_ = true;
	
	return *this;
}
/**
  @brief retrieves the pointer to immutable instance.
 */
template <hryky_template_param>
typename hryky::PolymorphBuffer<hryky_template_arg>::const_pointer 
hryky::PolymorphBuffer<hryky_template_arg>::operator->() const
{
	return this->is_null() ? hryky_nullptr : this->get();
}
/**
  @brief retrieves the pointer to mutable instance.
 */
template <hryky_template_param>
typename hryky::PolymorphBuffer<hryky_template_arg>::pointer 
hryky::PolymorphBuffer<hryky_template_arg>::operator->()
{
	return this->is_null() ? hryky_nullptr : this->get();
}
/**
  @brief retrieves the reference to immutable instance.
 */
template <hryky_template_param>
typename hryky::PolymorphBuffer<hryky_template_arg>::const_reference
hryky::PolymorphBuffer<hryky_template_arg>::operator*() const
{
	/**
	  @attention This function doesn't check nullptr.
	 */
	return *this->operator->();
}
/**
  @brief retrieves the reference to mutable instance.
 */
template <hryky_template_param>
typename hryky::PolymorphBuffer<hryky_template_arg>::reference 
hryky::PolymorphBuffer<hryky_template_arg>::operator*()
{
	/**
	  @attention This function doesn't check nullptr.
	 */
	return *this->operator->();
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::PolymorphBuffer<hryky_template_arg>::clear()
{
	if (this->is_null()) {
		return;
	}
	this->get()->~ValueT();
	this->instantiated_ = false;
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::PolymorphBuffer<hryky_template_arg>::write_to(
	StreamT & out) const
{
	if (this->is_null()) {
		out << this->get();
	}
	else {
		out << *this->get();
	}
	return out;
}
/**
  @brief confirms whether the buffer is not instantiated.
 */
template <hryky_template_param>
bool hryky::PolymorphBuffer<hryky_template_arg>::is_null() const
{
	return !this->instantiated_;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the address of mutable instance.
 */
template <hryky_template_param>
typename hryky::PolymorphBuffer<hryky_template_arg>::pointer
hryky::PolymorphBuffer<hryky_template_arg>::get()
{
	return reinterpret_cast<pointer>(this->buffer_.get());
}
/**
  @brief retrieves the address of immutable instance.
 */
template <hryky_template_param>
typename hryky::PolymorphBuffer<hryky_template_arg>::const_pointer
hryky::PolymorphBuffer<hryky_template_arg>::get() const
{
	return reinterpret_cast<const_pointer>(this->buffer_.get());
}
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
#endif // POLYMORPH_BUFFER_H_20140722185515455
// end of file
