/**
  @file     runnable_function.h
  @brief    calls an arbitrary function as runnable object on thread.
  @author   HRYKY
  @version  $Id: runnable_value.h 376 2014-07-29 10:46:52Z hryky.private@gmail.com $
 */
#ifndef RUNNABLE_VALUE_H_20140302075820998
#define RUNNABLE_VALUE_H_20140302075820998
#include "hryky/mempool/mempool_ptr.h"
#include "hryky/retention/retention_value.h"
#include "hryky/runnable/runnable_base.h"
#include "hryky/tuple/tuple_call.h"
#include "hryky/is_null.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename FunctorT, typename BaseT
#define hryky_template_arg \
	FunctorT, BaseT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace runnable
{
	/// calls an arbitrary function as runnable object on thread.
	template <
		typename FunctorT,
		typename BaseT = Base<>
	>
	class Value;

} // namespace runnable
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief calls an arbitrary function as runnable object on thread.
 */
template <hryky_template_param>
class hryky::runnable::Value :
	public BaseT,
	public retention::Value<FunctorT>,
	public WithStreamOut<Value<hryky_template_arg> >,
	private WithoutCopy
{
public :

	typedef Value<hryky_template_arg>   this_type;
	typedef retention::Value<FunctorT>  retention_type;
	typedef BaseT                       base_type;
	typedef typename BaseT::pointer     pointer;
	typedef typename BaseT::result_type result_type;
	typedef typename BaseT::args_type   args_type;

	/// instantiates with a functor.
	Value(initializer_type initializer);

	/// instantiates with a functor and memory pool.
	Value(initializer_type initializer, mempool::Ptr const & mempool);

	/// destructor.
	~Value();

	/// releases the internal resources.
	void clear();

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// executes the functor.
	result_type operator()(args_type const & args);

protected :

private :

	hryky_delete_default_constructor(Value);
	hryky_delete_this_copy_constructor(Value);
	hryky_delete_this_copy_assign_op(Value);

};
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
/**
  @brief instantiates with a functor.
 */
template <hryky_template_param>
hryky::runnable::Value<hryky_template_arg>::Value(
	initializer_type initializer)
	: base_type()
	  , retention_type(initializer)
{
}
/**
  @brief instantiates with a functor and memory pool.
 */
template <hryky_template_param>
hryky::runnable::Value<hryky_template_arg>::Value(
	initializer_type initializer, mempool::Ptr const & mempool)
	: base_type(mempool)
	  , retention_type(initializer)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::runnable::Value<hryky_template_arg>::~Value()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::runnable::Value<hryky_template_arg>::clear()
{
	this->retention_type::clear();
	this->base_type::clear();
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::runnable::Value<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return this->retention_type::write_to(out);
}
/**
  @brief executes the functor.
 */
template <hryky_template_param>
typename hryky::runnable::Value<hryky_template_arg>::result_type
hryky::runnable::Value<hryky_template_arg>::operator()(
	args_type const & args)
{
	return tuple::Call<result_type, args_type>::by(
		*this->get(), args);
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
namespace runnable
{
	/// creates the runnable object by an abitrary functor.
	template <typename FunctorT>
	typename Value<FunctorT>::pointer
		value(FunctorT const & functor);

	/**
	   creates the runnable object by an abitrary functor
	  with the memory pool.
	 */
	template <typename FunctorT>
	typename Value<FunctorT>::pointer
		value(
			FunctorT const & functor,
			mempool::Ptr const & mempool);

} // namespace runnable
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates the runnable object by an abitrary functor.
 */
template <typename FunctorT>
typename hryky::runnable::Value<FunctorT>::pointer
hryky::runnable::value(
	FunctorT const & functor)
{
	return value(functor, mempool::Ptr());
}
/**
  @brief creates the runnable object by an abitrary functor
    with the memory pool.
 */
template <typename FunctorT>
typename hryky::runnable::Value<FunctorT>::pointer
hryky::runnable::value(
	FunctorT const & functor,
	mempool::Ptr const & mempool)
{
	typedef Value<FunctorT>::pointer pointer;
	
	auto instance = mempool::instantiate<Value<FunctorT> >(
		mempool, functor, mempool);
	if (hryky_is_null(instance)) {
		hryky_log_alert(
			"failed to instantiate a runnable function.");
		return pointer();
	}
	return pointer(instance.release());
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // RUNNABLE_VALUE_H_20140302075820998
// end of file
