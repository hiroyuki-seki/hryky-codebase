/**
  @file     runnable_reference.h
  @brief    retains the runnable reference.
  @author   HRYKY
  @version  $Id: runnable_reference.h 376 2014-07-29 10:46:52Z hryky.private@gmail.com $
 */
#ifndef RUNNABLE_REFERENCE_H_20140309113251147
#define RUNNABLE_REFERENCE_H_20140309113251147
#include "hryky/mempool/mempool_ptr.h"
#include "hryky/retention/retention_reference.h"
#include "hryky/runnable/runnable_base.h"
#include "hryky/is_null.h"
#include "hryky/tuple/tuple_call.h"
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
	/// retains the runnable reference.
	template <
		typename FunctorT,
		typename BaseT = Base<>
	>
	class Reference;

} // namespace runnable
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the runnable reference.
 */
template <hryky_template_param>
class hryky::runnable::Reference :
	public BaseT,
	public retention::Reference<FunctorT>,
	public WithStreamOut<Reference<hryky_template_arg> >,
	private WithoutCopy
{
public :

	typedef BaseT                           base_type;
	typedef typename BaseT::pointer         pointer;
	typedef retention::Reference<FunctorT>  retention_type;
	typedef Reference<hryky_template_arg>   this_type;
	typedef typename BaseT::result_type     result_type;
	typedef typename BaseT::args_type       args_type;
	
	typedef typename retention_type::initializer_type
		initializer_type;

	/// instantiates with the reference to a runnable object.
	Reference(initializer_type initializer);

	/**
	  instantiates with the reference to a runnable object
	  and the memory pool.
	 */
	Reference(
		initializer_type initializer,
		mempool::Ptr const & mempool);

	/// destructor.
	~Reference();

	/// releases the internal resources.
	void clear();

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// invokes the internal runnable object.
	result_type operator()(args_type const & args);

protected :

private :

	hryky_delete_default_constructor(Reference);
	hryky_delete_this_copy_constructor(Reference);
	hryky_delete_this_copy_assign_op(Reference);

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
  @brief instantiates with the reference to a runnable object.
 */
template <hryky_template_param>
hryky::runnable::Reference<hryky_template_arg>::Reference(
	initializer_type initializer)
	: base_type()
	  , retention_type(initializer)
{
}
/**
  @brief instantiates with the reference to a runnable object
    and the memory pool.
 */
template <hryky_template_param>
hryky::runnable::Reference<hryky_template_arg>::Reference(
	initializer_type initializer, mempool::Ptr const & mempool)
	: base_type(mempool)
	  , retention_type(initializer)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::runnable::Reference<hryky_template_arg>::~Reference()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::runnable::Reference<hryky_template_arg>::clear()
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
hryky::runnable::Reference<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return this->retention_type::write_to(out);
}
/**
  @brief invokes the internal runnable object.
 */
template <hryky_template_param>
typename hryky::runnable::Reference<hryky_template_arg>::result_type
hryky::runnable::Reference<hryky_template_arg>::operator()(
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
	/// creates a new instance of runnable::Reference with the default memory pool.
	template <typename FunctorT>
	typename Reference<FunctorT>::pointer
		reference(FunctorT & functor);

	/// creates a new instance of runnable::Reference with the memory pool.
	template <typename FunctorT>
	typename Reference<FunctorT>::pointer
		reference(
			FunctorT & functor, mempool::Ptr const & mempool);

} // namespace runnable
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates a new instance of runnable::Reference with the default memory pool.
 */
template <typename FunctorT>
typename hryky::runnable::Reference<FunctorT>::pointer
hryky::runnable::reference(FunctorT & functor)
{
	return reference(functor, mempool::Ptr());
}
/**
  @brief creates a new instance of runnable::Reference with the memory pool.
 */
template <typename FunctorT>
typename hryky::runnable::Reference<FunctorT>::pointer
hryky::runnable::reference(
	FunctorT & functor, mempool::Ptr const & mempool)
{
	typedef Reference<FunctorT>::pointer pointer;
	
	auto instance
		= mempool::instantiate<Reference<FunctorT> >(
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
#endif // RUNNABLE_REFERENCE_H_20140309113251147
// end of file
