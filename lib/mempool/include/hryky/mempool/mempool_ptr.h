/**
  @file     mempool_ptr.h
  @brief    retains the implementation of mempool::Base.
  @author   HRYKY
  @version  $Id: mempool_ptr.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef MEMPOOL_PTR_H_20140301153928319
#define MEMPOOL_PTR_H_20140301153928319
#include "hryky/mempool/mempool_base.h"
#include "hryky/retention/retention_pointer.h"
#include "hryky/with_is_null.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/is_null.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace mempool
{
	/// retains the implementation of mempool::Base.
	class Ptr;

	typedef Ptr ptr_type;

} // namespace mempool
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the implementation of mempool::Base.
 */
class hryky::mempool::Ptr :
	public WithStreamOut<Ptr>,
	public WithSwap<Ptr>,
	public retention::Pointer<Base>,
	public WithIsNull<Ptr>
{
public :

	typedef Ptr                         this_type;
	typedef retention::Pointer<Base>    retain_type;

	/// default constructor.
	Ptr();

	/// copy constructor.
	Ptr(this_type const &);

	/// move constructor.
	Ptr(this_type &&);

	/// constructs an instance with the implementation.
	Ptr(pointer const ptr);

	/// destructor.
	~Ptr();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// assigns a new pointer.
	this_type & operator=(pointer const ptr);

	/// releases the internal resources.
	void clear();

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// confirms whether the internal pointer is null.
	bool is_null() const;

protected :

private :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace mempool
{
} // namespace mempool
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::mempool::Ptr::write_to(StreamT & out) const
{
	return this->retain_type::write_to(out);
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
namespace mempool
{
} // namespace mempool
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // MEMPOOL_PTR_H_20140301153928319
// end of file
