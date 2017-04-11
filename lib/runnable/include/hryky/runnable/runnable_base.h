/**
  @file         runnable_base.h
  @brief        the interface to invoke a function at a concurrent unit.
  @author       HRYKY
  @version      $Id: runnable_base.h 376 2014-07-29 10:46:52Z hryky.private@gmail.com $
 */
#ifndef RUNNABLE_BASE_H_20111223183320439
#define RUNNABLE_BASE_H_20111223183320439
#include "hryky/intrusive_ptr.h"
#include "hryky/intrusive_ptr_trait.h"
#include "hryky/exclusion/exclusion_mutex.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/tuple/tuple_n.h"
#include "hryky/function_traits.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename RetT, typename ArgsT, typename LockableT
#define hryky_template_arg \
	RetT, ArgsT, LockableT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace runnable
{
	/// the interface to invoke a function at a concurrent unit
	template <
		typename RetT = void,
		typename ArgsT = Tuple0,
		typename LockableT = exclusion::Mutex
	>
	class Base;
} // namespace runnable
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief the interface to invoke a function at a concurrent unit.
 */
template <hryky_template_param>
class hryky::runnable::Base :
	public IntrusivePtrTrait<LockableT>,
	public WithStreamOut<Base<hryky_template_arg> >,
	public WithSwap<Base<hryky_template_arg> >,
	public FunctionTraitsTuple<RetT, ArgsT>
{
public :

	typedef Base<hryky_template_arg>        this_type;
	typedef IntrusivePtrTrait<LockableT>    intrusive_ptr_trait;
	typedef IntrusivePtr<this_type>         pointer;

	/// default constructor.
	Base();

	/// copy constructor.
	Base(this_type const &);

	/// move constructor.
	Base(this_type &&);

	/// constructor with a memory pool.
	Base(mempool::Ptr const & mempool);

	/// destructor.
	~Base();

	/// assignment operator.
	hryky_assign_op;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// executes the concurrent function.
	RetT run(ArgsT const & args);

protected :

private :

	/**
	  @brief invokes a function at a concurrent unit
	 */
	virtual RetT operator()(ArgsT const & args) = 0;

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::runnable::Base<hryky_template_arg>::Base()
	: intrusive_ptr_trait()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::runnable::Base<hryky_template_arg>::Base(
	this_type const & rhs)
	: intrusive_ptr_trait(rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::runnable::Base<hryky_template_arg>::Base(
	this_type && rhs)
	: intrusive_ptr_trait(::std::move(rhs))
{
}
/**
  @brief constructor with a memory pool.
 */
template <hryky_template_param>
hryky::runnable::Base<hryky_template_arg>::Base(
	mempool::Ptr const & mempool)
	: intrusive_ptr_trait(mempool)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::runnable::Base<hryky_template_arg>::~Base()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::runnable::Base<hryky_template_arg>::clear()
{
	this->intrusive_ptr_trait::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::runnable::Base<hryky_template_arg>::swap(
	this_type & src)
{
}
/**
  @brief executes the concurrent function.
 */
template <hryky_template_param>
RetT hryky::runnable::Base<hryky_template_arg>::run(ArgsT const & args)
{
	return this->operator()(args);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::runnable::Base<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return out;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace runnable
{
} // namespace runnable
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
namespace runnable
{
} // namespace runnable
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // RUNNABLE_BASE_H_20111223183320439
// end of file
