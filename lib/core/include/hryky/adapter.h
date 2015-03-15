/**
  @file         adapter.h
  @brief        provides the interface in behalf of the valueementation.
  @author       HRYKY
  @version      $Id: adapter.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef ADAPTER_H_20130113170714380
#define ADAPTER_H_20130113170714380
#include "hryky/clear.h"
#include "hryky/retention/retention_value.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/type_traits/is_base_of.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_virtual_destructor
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename BaseT, typename ClientT, template <typename> class RetainT
#define hryky_template_arg \
	BaseT, ClientT, RetainT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// provides the interface in behalf of the valueementation.
	template <
		typename BaseT,
		typename ClientT,
		template <typename> class RetainT = retention::Value
	>
	class Adapter;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief provides the interface in behalf of the valueementation.
 */
template <hryky_template_param>
class hryky::Adapter :
	public BaseT,
	public RetainT<ClientT>,
	public WithStreamOut<Adapter<hryky_template_arg> >,
	public WithSwap<Adapter<hryky_template_arg> >
{
public :

	typedef Adapter<hryky_template_arg>             this_type;
	typedef BaseT                                   base_type;
	typedef RetainT<ClientT>                        retain_type;
	typedef typename retain_type::pointer           pointer;
	typedef typename retain_type::const_pointer     const_pointer;
	typedef typename retain_type::reference         reference;
	typedef typename retain_type::const_reference   const_reference;
	typedef typename retain_type::initializer_type  initializer_type;

	/// default constructor.
	Adapter();

	/// copy constructor.
	Adapter(this_type const &);

	/// move constructor.
	Adapter(this_type && rhs);

	/// constructor with an adatee.
	Adapter(initializer_type initializer);

	/// creates an instance with two arguments for base_type.
	template <typename Arg1T, typename Arg2T>
	Adapter(
		Arg1T arg1,
		Arg2T arg2,
		initializer_type initializer);

	/// destructor.
	~Adapter();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// retrieves the pointer to the mutable value.
	pointer get();

	/// retrieves the pointer to the immutable value.
	const_pointer get() const;

protected :

private :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::Adapter<hryky_template_arg>::Adapter()
	: base_type()
	  , retain_type()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::Adapter<hryky_template_arg>::Adapter(this_type const & rhs)
	: base_type(rhs)
	  , retain_type(rhs)
{
}
/**
  @brief creates an instance with two arguments.
 */
template <hryky_template_param>
template <typename Arg1T, typename Arg2T>
hryky::Adapter<hryky_template_arg>::Adapter(
	Arg1T arg1, Arg2T arg2, initializer_type initializer)
	: base_type(arg1, arg2)
	  , retain_type(initializer)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::Adapter<hryky_template_arg>::Adapter(this_type && rhs)
	: base_type(::std::move(rhs))
	  , retain_type(::std::move(rhs))
{
}
/**
  @brief constructor.
 */
template <hryky_template_param>
hryky::Adapter<hryky_template_arg>::Adapter(initializer_type initializer)
	: base_type()
	  , retain_type(initializer)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::Adapter<hryky_template_arg>::~Adapter()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::Adapter<hryky_template_arg>::clear()
{
	this->retain_type::clear();
	this->base_type::clear();
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::Adapter<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return this->retain_type::write_to(out);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::Adapter<hryky_template_arg>::swap(this_type & src)
{
	this->base_type::swap(src);
	this->retain_type::swap(src);
}
/**
  @brief retrieves the mutable reference to the value.
 */
template <hryky_template_param>
typename hryky::Adapter<hryky_template_arg>::pointer 
hryky::Adapter<hryky_template_arg>::get()
{
	return this->retain_type::get();
}
/**
  @brief retrieves the immutable reference to the value.
 */
template <hryky_template_param>
typename hryky::Adapter<hryky_template_arg>::const_pointer 
hryky::Adapter<hryky_template_arg>::get() const
{
	return this->retain_type::get();
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
#endif // ADAPTER_H_20130113170714380
// end of file

