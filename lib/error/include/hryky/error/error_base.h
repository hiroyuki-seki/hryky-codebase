/**
  @file         error_base.h
  @brief        retains arbitary data polymorphically.
  @author       HRYKY
  @version      $Id: error_base.h 376 2014-07-29 10:46:52Z hryky.private@gmail.com $
 */
#ifndef ERROR_BASE_H_20120606001147674
#define ERROR_BASE_H_20120606001147674
#include "hryky/intrusive_ptr_trait.h"
#include "hryky/tmp/null.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace error
{
	/// retains arbitary data polymorphically.
	class Base;

} // namespace error
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains arbitary data polymorphically.
 */
class hryky::error::Base :
	public IntrusivePtrTrait<Null>

{
public :

	typedef Base this_type;
	typedef IntrusivePtrTrait<Null> intrusive_ptr_trait;

	/// destructor.
	virtual ~Base();

	/// retrieves the description about this error.
	char const * what() const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

protected :
	/// default constructor.
	Base();

	/// copy constructor.
	Base(this_type const & rhs);

private :

	/// implementation of Base::what().
	virtual char const * what_impl() const = 0;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace error
{
} // namespace error
} // namespace hryky
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
namespace error
{
} // namespace error
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // ERROR_BASE_H_20120606001147674
// end of file
