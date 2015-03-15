/**
  @file         mempool_adapter.h
  @brief        intermediates to hryky::mempool::Base.
  @author       HRYKY
  @version      $Id: mempool_adapter.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef POOL_ADAPTER_H_20130217163715359
#define POOL_ADAPTER_H_20130217163715359
#include "hryky/mempool/mempool_base.h"
#include "hryky/retention/retention_value.h"
#include "hryky/type_traits/add_pointer.h"
#include "hryky/intrusive_ptr.h"
#include "hryky/pragma.h"
#include "hryky/adapter.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_padded
#pragma hryky_pragma_disable_warning_virtual_destructor
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ClientT
#define hryky_template_arg \
	ClientT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace mempool
{
	/// intermediates to hryky::mempool::Base.
	template <hryky_template_param>
	class Adapter;

} // namespace mempool
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief facilitate the definition of a derived class from hryky::mempool::Base.
 */
template <hryky_template_param>
class hryky::mempool::Adapter :
	public hryky::Adapter<Base, ClientT, retention::Value>,
	public WithStreamOut<Adapter<hryky_template_arg> >
{
public :

	typedef Adapter<hryky_template_arg>         this_type;
	typedef hryky::Adapter<Base, ClientT, retention::Value>
		base_type;
	
	/// default constructor.
	Adapter();

	/// constructor with the initial value.
	Adapter(initializer_type client);

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

	/**
	  @brief wraps to call ClientT::allocate()
	 */
	virtual void * allocate_impl(size_t const size)
	{
		return this->get()->allocate(size);
	}

	/**
	  @brief wraps to call ClientT::deallocate()
	 */
	virtual bool deallocate_impl(void * const address)
	{
		return this->get()->deallocate(address);
	}

	/**
	  @brief wraps to call Implt::allocatable_size()
	 */
	virtual size_t allocatable_size_impl() const
	{
		return this->get()->allocatable_size();
	}

private :
	hryky_delete_this_copy_constructor(Adapter);
	hryky_delete_this_copy_assign_op(Adapter);

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
  @brief default constructor.
 */
template <hryky_template_param>
hryky::mempool::Adapter<hryky_template_arg>::Adapter()
	: base_type()
{
}
/**
  @brief constructor with the implementation of derived class.
 */
template <hryky_template_param>
hryky::mempool::Adapter<hryky_template_arg>::Adapter(
	initializer_type client)
	: base_type(client)
{
	return;
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & 
hryky::mempool::Adapter<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return this->get()->write_to(out);
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
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // POOL_ADAPTER_H_20130217163715359
// end of file
