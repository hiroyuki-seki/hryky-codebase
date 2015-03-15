/**
  @file         allocator_base.h
  @brief        interface of allocator.
  @author       HRYKY
  @version      $Id: allocator_base.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef ALLOCATOR_BASE_H_20111105154314321
#define ALLOCATOR_BASE_H_20111105154314321
#include "hryky/std/std_new.h"
#include "hryky/type_traits/add_const_pointer.h"
#include "hryky/type_traits/add_const_reference.h"
#include "hryky/type_traits/add_pointer.h"
#include "hryky/type_traits/add_reference.h"
#include "hryky/type_traits/remove_const.h"
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
namespace allocator
{
	/// interface of allocator
	template <hryky_template_param>
	class Base;
}
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief interface of allocator.
 */
template <hryky_template_param>
class hryky::allocator::Base
{
public :
	typedef Base<ValueT>                                    this_type;
	typedef typename RemoveConst<ValueT>::type              value_type;
	typedef typename AddPointer<value_type>::type           pointer;
	typedef typename AddConstPointer<value_type>::type      const_pointer;
	typedef typename AddReference<value_type>::type         reference;
	typedef typename AddConstReference<value_type>::type    const_reference;
	typedef ::std::size_t                                   size_type;
	typedef ::std::ptrdiff_t                                difference_type;

	template<typename OtherT>
	struct rebind
	{
		typedef Base<OtherT> other;
	};

	/// default constructor.
	Base();

	/// destructor.
	~Base();

	/// copy constructor.
	Base(this_type const & rhs);

	/// move constructor.
	Base(this_type && rhs);

	/// constructs with the other allocator.
	template <typename OtherT>
	Base(Base<OtherT> const & rhs);

	/// confirms the equality.
	bool operator==(this_type const & rhs) const;

	/// confirms the inequality.
	bool operator!=(this_type const & rhs) const;

	/// retrieves the address of a mutable object.
	pointer address(reference src) const;

	/// retrieves the address of an immutable object.
	const_pointer address(const_reference src) const;

	/// creates an instance by the default constructor.
	void construct(pointer ptr);

	/// creates an instance by copy-constructor.
	void construct(pointer ptr, const_reference src);

	/// creates an instance with an argument.
	template <typename Arg1T>
	void construct(pointer ptr, Arg1T && arg1);

	/// creates an instance with two arguments.
	template <typename Arg1T, typename Arg2T>
	void construct(pointer ptr, Arg1T && arg1, Arg2T && arg2);

	/// creates an instance with three arguments.
	template <typename Arg1T, typename Arg2T, typename Arg3T>
	void construct(pointer ptr, Arg1T && arg1, Arg2T && arg2, Arg3T && arg3);

	/// calls the destructor on the memory.
	void destroy(pointer ptr);

	/// retrieves the number of objects which can be allocated by this allocator.
	size_type max_size() const;

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::allocator::Base<hryky_template_arg>::Base()
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::allocator::Base<hryky_template_arg>::~Base()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::allocator::Base<hryky_template_arg>::Base(this_type const & rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::allocator::Base<hryky_template_arg>::Base(this_type && rhs)
{
}
/**
  @brief constructs with the other allocator.
 */
template <hryky_template_param>
template <typename OtherT>
hryky::allocator::Base<hryky_template_arg>::Base(Base<OtherT> const & rhs)
{
}
/**
  @brief confirms the equality.
 */
template <hryky_template_param>
bool hryky::allocator::Base<hryky_template_arg>::operator==(
	this_type const & rhs) const
{
	return true;
}
/**
  @brief confirms the inequality.
 */
template <hryky_template_param>
bool hryky::allocator::Base<hryky_template_arg>::operator!=(
	this_type const & rhs) const
{
	return !this->operator==(rhs);
}
/**
  @brief retrieves the address of an object.
 */
template <hryky_template_param>
typename hryky::allocator::Base<hryky_template_arg>::pointer 
hryky::allocator::Base<hryky_template_arg>::address(
	reference src) const
{
	return &src;
}
/**
  @brief retrieves the address of an immutable object.
 */
template <hryky_template_param>
typename hryky::allocator::Base<hryky_template_arg>::const_pointer 
hryky::allocator::Base<hryky_template_arg>::address(
	const_reference src) const
{
	return &src;
}
/**
  @brief creates an instance by the default constructor.
 */
template <hryky_template_param>
void hryky::allocator::Base<hryky_template_arg>::construct(pointer ptr)
{
	new(ptr) value_type();
}
/**
  @brief creates an instance by copy-constructor.
 */
template <hryky_template_param>
void hryky::allocator::Base<hryky_template_arg>::construct(
	pointer ptr, const_reference src)
{
	new(ptr) value_type(src);
}
/**
  @brief creates an instance with a argument.
 */
template <hryky_template_param>
template <typename Arg1T>
void hryky::allocator::Base<hryky_template_arg>::construct(
	pointer ptr, Arg1T && arg1)
{
	new(ptr) value_type(::std::forward<Arg1T>(arg1));
}
/**
  @brief creates an instance with two arguments.
 */
template <hryky_template_param>
template <typename Arg1T, typename Arg2T>
void hryky::allocator::Base<hryky_template_arg>::construct(
	pointer ptr, Arg1T && arg1, Arg2T && arg2)
{
	new(ptr) value_type(
		::std::forward<Arg1T>(arg1),
		::std::forward<Arg2T>(arg2));
}
/**
  @brief creates an instance with three arguments.
 */
template <hryky_template_param>
template <typename Arg1T, typename Arg2T, typename Arg3T>
void hryky::allocator::Base<hryky_template_arg>::construct(
	pointer ptr, Arg1T && arg1, Arg2T && arg2, Arg3T && arg3)
{
	new(ptr) value_type(
		::std::forward<Arg1T>(arg1),
		::std::forward<Arg2T>(arg2),
		::std::forward<Arg3T>(arg3));
}
/**
  @brief calls the destructor on the memory.
 */
template <hryky_template_param>
void hryky::allocator::Base<hryky_template_arg>::destroy(pointer ptr)
{
	(void)ptr;
	(*ptr).~value_type();
}
/**
  @brief retrieves the number of objects which can be allocated by this allocator.
 */
template <hryky_template_param>
typename hryky::allocator::Base<hryky_template_arg>::size_type
hryky::allocator::Base<hryky_template_arg>::max_size() const
{
	return ::std::numeric_limits<size_type>::(max)()
		/ sizeof(value_type);
}
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace allocator
{
} // namespace allocator
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes macro.
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // ALLOCATOR_BASE_H_20111105154314321
// end of file
