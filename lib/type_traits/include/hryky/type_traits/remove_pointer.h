/**
  @file         remove_pointer.h
  @brief        dereferences the pointer of any type.
  @author       HRYKY
  @version      $Id: remove_pointer.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
  @addtogroup   generic_programming
  @{
 */
#ifndef TYPE_REMOVE_POINTER_H_20120226104330113
#define TYPE_REMOVE_POINTER_H_20120226104330113
#include "hryky/type_traits/add_reference.h"
#include "hryky/type_traits/is_pointer.h"
#include "hryky/type_traits/enable_if.h"
#include "hryky/nullptr.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// dereferences the pointer of any type.
	template < typename PointerT >
	class RemovePointer;
	
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief dereferences the pointer of any type.
 */
template < typename ValueT >
class hryky::RemovePointer
{
public :
	typedef RemovePointer<ValueT> this_type;

	/// represents the type which ValueT is dereferenced.
	typedef ValueT                                  type;
	
	typedef typename AddReference<ValueT>::type     reference;
	typedef reference                               result_type;

	RemovePointer(reference value) : value_(value) {}

	result_type operator()() const {
		return this->value_;
	}

private :
	RemovePointer(this_type const &);
	this_type & operator=(this_type const &);
	
	reference   value_;

};
//------------------------------------------------------------------------------
// class specialization
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @internal
  @brief        dereferences the pointer of any type.
  @note
  - specializes RemovePointer for pointer
  @endinternal
 */
template < typename ValueT >
class RemovePointer<ValueT *>
{
public :

	typedef ValueT                                  type;
	typedef ValueT *                                pointer;
	typedef typename AddReference<ValueT>::type     result_type;

	RemovePointer(pointer ptr) : ptr_(ptr) {}

	result_type operator()() const {
		return *this->ptr_;
	}

private :
	pointer     ptr_;

};
/**
  @internal
  @brief        dereferences the pointer of any type.
  @note
  - specializes RemovePointer for pointer
  @endinternal
 */
template < typename ValueT >
class RemovePointer<ValueT * const>
{
public :

	typedef ValueT                                  type;
	typedef ValueT *                                pointer;
	typedef typename AddReference<ValueT>::type     result_type;

	RemovePointer(pointer ptr) : ptr_(ptr) {}

	result_type operator()() const {
		return *this->ptr_;
	}

private :
	pointer     ptr_;

};
}
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
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
	  @brief    dereferences a value if the value can behave as a pointer.
	  @param    src is dereferenced.
	 */
	template < typename ValueT >
	typename RemovePointer<ValueT>::result_type dereference(
		ValueT & src,
		typename EnableIf<IsPointer<ValueT> >::type * = hryky_nullptr);

	/**
	  @brief    dereferences a value if the value behaves as a pointer.
	  @param    src is dereferenced.
	 */
	template < typename ValueT >
	typename RemovePointer<ValueT>::result_type dereference(
		ValueT & src,
		typename DisableIf<IsPointer<ValueT> >::type * = hryky_nullptr);

}
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief dereferences a value if the value can behave as a pointer.
 */
template <typename ValueT>
typename hryky::RemovePointer<ValueT>::result_type
hryky::dereference(
	ValueT & src,
	typename EnableIf<IsPointer<ValueT> >::type *)
{
	return *src;
}
/**
  @brief dereferences a value if the value can behave as a pointer.
 */
template <typename ValueT>
typename hryky::RemovePointer<ValueT>::result_type
hryky::dereference(
	ValueT & src,
	typename DisableIf<IsPointer<ValueT> >::type *)
{
	return src;
}
#endif // TYPE_REMOVE_POINTER_H_20120226104330113
/// @}
// end of file
