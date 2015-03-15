/**
  @file     shader_dispatchee.h
  @brief    dispatches a derived class.
  @author   HRYKY
  @version  $Id: shader_dispatchee.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_DISPATCHEE_H_20140830181612427
#define SHADER_DISPATCHEE_H_20140830181612427
#include "hryky/shader/shader_node.h"
#include "hryky/shader/shader_with_code.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename DerivedT
#define hryky_template_arg \
	DerivedT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
	/// dispatches a derived class.
	template <typename DerivedT>
	class Dispatchee;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief dispatch a derived class.
 */
template <hryky_template_param>
class hryky::shader::Dispatchee :
	public Node,
	public WithCode<DerivedT>,
	public WithStreamOut<DerivedT>
{
public :

	typedef Node base_type;

	typedef Dispatchee<hryky_template_arg> this_type;

protected :

	/// default constructor.
	Dispatchee();

	/// copy constructor.
	Dispatchee(this_type const &);

	/// move constructor.
	Dispatchee(this_type &&);

	/// destructor.
	~Dispatchee();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

private :

	/// dispatches the derived class as mutable.
	virtual void dispatch_impl(
		dispatcher_type & dispatcher);

	/// dispatches the derived class as immutable.
	virtual void dispatch_impl(
		const_dispatcher_type & dispatcher) const;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::shader::Dispatchee<hryky_template_arg>::Dispatchee()
	: base_type()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::shader::Dispatchee<hryky_template_arg>::Dispatchee(
	this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::shader::Dispatchee<hryky_template_arg>::Dispatchee(
	this_type && rhs)
	: base_type(std::move(rhs))
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::shader::Dispatchee<hryky_template_arg>::~Dispatchee()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::shader::Dispatchee<hryky_template_arg>::clear()
{
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::shader::Dispatchee<hryky_template_arg>::swap(this_type & src)
{
	this->base_type::swap(src);
}
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief dispatches the derived class as mutable.
 */
template <hryky_template_param>
void hryky::shader::Dispatchee<hryky_template_arg>::dispatch_impl(
	dispatcher_type & dispatcher)
{
	return dispatcher.dispatch(static_cast<DerivedT &>(*this));
}
/**
  @brief dispatches the derived class as immutable.
 */
template <hryky_template_param>
void hryky::shader::Dispatchee<hryky_template_arg>::dispatch_impl(
	const_dispatcher_type & dispatcher) const
{
	return dispatcher.dispatch(static_cast<DerivedT const &>(*this));
}
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // SHADER_DISPATCHEE_H_20140830181612427
// end of file
