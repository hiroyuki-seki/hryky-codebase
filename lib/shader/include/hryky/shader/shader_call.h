/**
  @file     shader_call.h
  @brief    expresses a function-call.
  @author   HRYKY
  @version  $Id: shader_call.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_CALL_H_20140829074106986
#define SHADER_CALL_H_20140829074106986
#include "hryky/array.h"
#include "hryky/shader/shader_dispatchee.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	size_t ArgsSize
#define hryky_template_arg \
	ArgsSize
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
	/// expresses a function-call.
	template <size_t ArgsSize>
	class Call;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief expresses a function-call.
 */
template <hryky_template_param>
class hryky::shader::Call :
	public Dispatchee<Call<hryky_template_arg> >
{
public :

	typedef Call<hryky_template_arg> this_type;
	typedef Dispatchee<this_type> base_type;

	/// default constructor.
	Call();

	/// copy constructor.
	Call(this_type const &);

	/// move constructor.
	Call(this_type &&);

	/// destructor.
	~Call();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & Write_to_impl(StreamT & out) const;

protected :

private :

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
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::shader::Call<hryky_template_arg>::Call()
	: base_type()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::shader::Call<hryky_template_arg>::Call(
	this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::shader::Call<hryky_template_arg>::Call(
	this_type && rhs)
	: base_type(std::move(rhs))
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::shader::Call<hryky_template_arg>::~Call()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::shader::Call<hryky_template_arg>::clear()
{
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::shader::Call<hryky_template_arg>::swap(
	this_type & src)
{
	this->base_type::swap(src);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::shader::Call<hryky_template_arg>::Write_to_impl(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(name);
	hryky_write_member(args);
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
#endif // SHADER_CALL_H_20140829074106986
// end of file
