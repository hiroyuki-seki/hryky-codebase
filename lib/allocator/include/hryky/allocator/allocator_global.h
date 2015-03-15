/**
  @file         allocator_global.h
  @brief        allocator using global new/delete.
  @author       HRYKY
  @version      $Id: allocator_global.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef ALLOCATOR_GLOBAL_H_20111026155330328
#define ALLOCATOR_GLOBAL_H_20111026155330328
#include "hryky/allocator/allocator_base.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace allocator
{
	/// allocator using global new/delete
	template < typename ValueT >
	class Global;
}
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief allocator using global new/delete.
 */
template < typename ValueT >
class hryky::allocator::Global
	: public hryky::allocator::Base<ValueT>
{
public :

	typedef Global<ValueT>          this_type;

	template<typename OtherT>
	struct rebind
	{
		typedef Global<OtherT>      other;
	};

	/// default constructor
	Global() {}

	/// destructor
	~Global() {}

	/// copy constructor
	Global(this_type const&) {}

	/// constructor with allocator for other type
	template<typename OtherT>
	Global(Global<OtherT> const&) {}

	/// allocates memory
	pointer allocate(size_type count, void const * = 0) {
		return reinterpret_cast<pointer>(::operator new(count * sizeof(ValueT)));
	}

	/// deallocates memory
	void deallocate(pointer p, size_type) {
		::operator delete(p);
	}

};
//------------------------------------------------------------------------------
// inline functions
//------------------------------------------------------------------------------
#endif // ALLOCATOR_GLOBAL_H_20111026155330328
// end of file
