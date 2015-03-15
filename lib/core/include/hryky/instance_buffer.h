/**
  @file     instance_buffer.h
  @brief    stores an instance.
  @author   HRYKY
  @version  $Id: instance_buffer.h 374 2014-07-27 11:54:24Z hryky.private@gmail.com $
 */
#ifndef INSTANCE_BUFFER_H_20140723082343016
#define INSTANCE_BUFFER_H_20140723082343016
#include "hryky/aligned_buffer.h"
#include "hryky/tmp/tmp_binary_logarithm.h"
#include "hryky/with_is_null.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/type_traits/add_pointer.h"
#include "hryky/type_traits/add_const_pointer.h"
#include "hryky/type_traits/add_reference.h"
#include "hryky/type_traits/add_const_reference.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT, size_t AlignedExponent
#define hryky_template_arg \
	ValueT, AlignedExponent
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// stores an instance.
	template <
		typename ValueT,
		size_t AlignedExponent = tmp::BinaryLogarithmC<sizeof(size_t)>::value
	>
	class InstanceBuffer;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief stores an instance.
 */
template <hryky_template_param>
class hryky::InstanceBuffer :
	public WithIsNull<InstanceBuffer<hryky_template_arg> >,
	public WithStreamOut<InstanceBuffer<hryky_template_arg> >,
	public WithSwap<InstanceBuffer<hryky_template_arg> >
{
public :

	typedef InstanceBuffer<hryky_template_arg>          this_type;
	typedef typename AddPointer<ValueT>::type           pointer;
	typedef typename AddConstPointer<ValueT>::type      const_pointer;
	typedef typename AddReference<ValueT>::type         reference;
	typedef typename AddConstReference<ValueT>::type    const_reference;

	/// default constructor.
	InstanceBuffer();

	/// creates an instance by copying an other value.
	InstanceBuffer(ValueT const & rhs);

	/// creates an instance by an argument.
	template <typename Arg1T>
	InstanceBuffer(Arg1T arg1);

	/// creates an instance by moving the other value.
	InstanceBuffer(ValueT && rhs);

	/// copy constructor.
	InstanceBuffer(this_type const &);

	/// move constructor.
	InstanceBuffer(this_type &&);

	/// destructor.
	~InstanceBuffer();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// retrieves the pointer to mutable instance.
	pointer operator->();

	/// retrieves the pointer to immutable instance.
	const_pointer operator->() const;

	/// retrieves the reference to mutable instance.
	reference operator*();

	/// retrieves the reference to immutable instance.
	const_reference operator*() const;

	/// assigns a new value.
	this_type & operator=(ValueT const & rhs);

	/// moves the value.
	this_type & operator=(ValueT && rhs);

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// confirms whether an instance is not instantiated.
	bool is_null() const;

	/// assigns a new instance with an argument.
	template <typename Arg1T>
	void assign(Arg1T arg1);

protected :

private :
	typedef AlignedBuffer<sizeof(ValueT), AlignedExponent> buffer_type;

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
hryky::InstanceBuffer<hryky_template_arg>::InstanceBuffer()
	: buffer_()
	  , instantiated_()
{
}
/**
  @brief creates an instance by copying an other value.
 */
template <hryky_template_param>
hryky::InstanceBuffer<hryky_template_arg>::InstanceBuffer(
	ValueT const & rhs)
	: buffer_()
	  , instantiated_()
{
	new (this->get()) ValueT(rhs);
	this->instantiated_ = true;
}
/**
  @brief creates an instance with an argument.
 */
template <hryky_template_param>
template <typename Arg1T>
hryky::InstanceBuffer<hryky_template_arg>::InstanceBuffer(
	Arg1T arg1)
	: buffer_()
	  , instantiated_()
{
	new (this->get()) ValueT(arg1);
	this->instantiated_ = true;
}
/**
  @brief creates an instance by moving the other value.
 */
template <hryky_template_param>
hryky::InstanceBuffer<hryky_template_arg>::InstanceBuffer(
	ValueT && rhs)
{
	new (this->get()) ValueT(::std::move(rhs));
	this->instantiated_ = true;
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::InstanceBuffer<hryky_template_arg>::InstanceBuffer(
	this_type const & rhs)
	: buffer_()
	  , instantiated_()
{
	if (!rhs.is_null()) {
		new (this->get()) ValueT(*rhs);
		this->instantiated_ = true;
	}
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::InstanceBuffer<hryky_template_arg>::InstanceBuffer(
	this_type && rhs)
	: buffer_()
	  , instantiated_()
{
	if (!rhs.is_null()) {
		new (this->get()) ValueT(::std::move(*rhs));
		this->instantiated_ = true;
	}
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::InstanceBuffer<hryky_template_arg>::~InstanceBuffer()
{
	this->clear();
}
/**
  @brief retrieves the pointer to mutable instance.
 */
template <hryky_template_param>
typename hryky::InstanceBuffer<hryky_template_arg>::pointer 
hryky::InstanceBuffer<hryky_template_arg>::operator->()
{
	return this->is_null() ? hryky_nullptr : this->get();
}
/**
  @brief retrieves the pointer to immutable instance.
 */
template <hryky_template_param>
typename hryky::InstanceBuffer<hryky_template_arg>::const_pointer 
hryky::InstanceBuffer<hryky_template_arg>::operator->() const
{
	return this->is_null() ? hryky_nullptr : this->get();
}
/**
  @brief retrieves the reference to mutable instance.
 */
template <hryky_template_param>
typename hryky::InstanceBuffer<hryky_template_arg>::reference 
hryky::InstanceBuffer<hryky_template_arg>::operator*()
{
	return *this->operator->();
}
/**
  @brief retrieves the reference to immutable instance.
 */
template <hryky_template_param>
typename hryky::InstanceBuffer<hryky_template_arg>::const_reference 
hryky::InstanceBuffer<hryky_template_arg>::operator*() const
{
	return *this->operator->();
}
/**
  @brief assigns a new value.
 */
template <hryky_template_param>
hryky::InstanceBuffer<hryky_template_arg> & 
hryky::InstanceBuffer<hryky_template_arg>::operator=(
	ValueT const & rhs)
{
	if (this->is_null()) {
		new (this->get()) ValueT(rhs);
		this->instantiated_ = true;
	}
	else {
		**this = rhs;
	}
	return *this;
}
/**
  @brief moves the value.
 */
template <hryky_template_param>
hryky::InstanceBuffer<hryky_template_arg> & 
hryky::InstanceBuffer<hryky_template_arg>::operator=(
	ValueT && rhs)
{
	if (this->is_null()) {
		new (this->get()) ValueT(::std::move(rhs));
		this->instantiated_ = true;
	}
	else {
		**this = ::std::move(rhs);
	}
	return *this;
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::InstanceBuffer<hryky_template_arg>::clear()
{
	if (this->is_null()) {
		return;
	}
	this->get()->~ValueT();
	this->instantiated_ = false;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::InstanceBuffer<hryky_template_arg>::swap(
	this_type & src)
{
	if (this->is_null()) {
		if (src.is_null()) {
			return;
		}
		else {
			new (this->get()) ValueT(::std::move(*src));
			this->instantiated_ = true;
			src.clear();
		}
	}
	else {
		if (src.is_null()) {
			new (src.get()) ValueT(::std::move(**this));
			src.instantiated_ = true;
			this->clear();
		}
		else {
			hryky::swap(**this, *src);
		}
	}
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::InstanceBuffer<hryky_template_arg>::write_to(
	StreamT & out) const
{
	if (this->is_null()) {
		out << this->get();
	}
	else {
		out << **this;
	}
	return out;
}
/**
  @brief confirms whether an instance is not instantiated.
 */
template <hryky_template_param>
bool hryky::InstanceBuffer<hryky_template_arg>::is_null() const
{
	return !this->instantiated_;
}
/**
  @brief assigns a new instance with an argument.
 */
template <hryky_template_param>
template <typename Arg1T>
void hryky::InstanceBuffer<hryky_template_arg>::assign(Arg1T arg1)
{
	if (!this->is_null()) {
		this->clear();
	}
	new (this->get()) ValueT(arg1);
	this->instantiated_ = true;
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
typename hryky::InstanceBuffer<hryky_template_arg>::pointer
hryky::InstanceBuffer<hryky_template_arg>::get()
{
	return reinterpret_cast<pointer>(this->buffer_.get());
}
/**
  @brief retrieves the address of immutable instance.
 */
template <hryky_template_param>
typename hryky::InstanceBuffer<hryky_template_arg>::const_pointer 
hryky::InstanceBuffer<hryky_template_arg>::get() const
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
#endif // INSTANCE_BUFFER_H_20140723082343016
// end of file
