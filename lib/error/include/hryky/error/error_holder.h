/**
  @file         error_holder.h
  @brief        retains the pointer to an instance of error::Base.
  @author       HRYKY
  @version      $Id: error_holder.h 376 2014-07-29 10:46:52Z hryky.private@gmail.com $
 */
#ifndef ERROR_HOLDER_H_20120611173248397
#define ERROR_HOLDER_H_20120611173248397
#include "hryky/intrusive_ptr.h"
#include "hryky/with_is_null.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
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
	class Base;
	
	/// retains the pointer to an instance of error::Base.
	class Holder;

} // namespace error
typedef error::Holder error_type;
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the pointer to an instance of error::Base.
 */
class hryky::error::Holder :
	public WithStreamOut<Holder>,
	public WithSwap<Holder>,
	public WithIsNull<Holder>
{
public :

	typedef Holder                      this_type;
	typedef IntrusivePtr<error::Base>   entity_type;

	/// default constructor.
	Holder();

	/// copy constructor.
	Holder(this_type const & rhs);

	/// move constructor.
	Holder(this_type && rhs);

	/// constructor with a pointer to error::Base.
	Holder(entity_type const & entity);

	/// destructor.
	~Holder();

	/// assignment operator
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// retrieves the description of the held error.
	char const * what() const;

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// confirms whether no error occurred.
	bool is_null() const;

protected :

private :

	entity_type entity_;

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
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::error::Holder::write_to(
	StreamT & out) const
{
	out << this->what();
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
namespace error
{
} // namespace error
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // ERROR_HOLDER_H_20120611173248397
// end of file
