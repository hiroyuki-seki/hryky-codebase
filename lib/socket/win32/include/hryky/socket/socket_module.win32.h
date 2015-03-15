/**
  @file     socket_module.win32.h
  @brief    manages all functionalities of socket module.
  @author   HRYKY
  @version  $Id: socket_module.win32.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef SOCKET_MODULE_WIN32_H_20140121162951354
#define SOCKET_MODULE_WIN32_H_20140121162951354
#include "hryky/definition.h"
#include "hryky/mempool/mempool_base.h"
#include "hryky/mempool/mempool_deleter.h"
#include "hryky/mempool/mempool_ptr.h"
#include "hryky/socket/socket_common.h"
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
namespace socket
{
	/// manages all functionalities of socket module.
	class Module;

} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief manages all functionalities of socket module.
 */
class hryky::socket::Module :
	public WithStreamOut<Module>,
	public WithSwap<Module>,
	private WithoutCopy
{
public :

	typedef Module this_type;

	/// default constructor.
	Module();

	/// move constructor.
	Module(this_type && rhs);

	/// destructor.
	~Module();

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// rebuilds the internal resource.
	bool reset();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

protected :

private :

	hryky_delete_this_copy_constructor(Module);
	hryky_delete_this_copy_assign_op(Module);

	mempool::Ptr mempool_;

	union
	{
		uint32_t flags_;
		struct
		{
			bool started_:1;
			bool initialized_:1;
		} flag_;
	};

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace socket
{
} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::socket::Module::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(mempool);

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
namespace socket
{
} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // SOCKET_MODULE_WIN32_H_20140121162951354
// end of file
