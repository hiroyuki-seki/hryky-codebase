/**
  @file     scoped_increment.h
  @brief    increments the value only in the current scope.
  @author   HRYKY
  @version  $Id: scoped_increment.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef SCOPED_INCREMENT_H_20140315191232467
#define SCOPED_INCREMENT_H_20140315191232467
#include "hryky/raii/auto_decrement.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT
#define hryky_template_arg \
	ValueT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// increments the value only in the current scope.
	template <typename ValueT>
	class ScopedIncrement;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief increments the value only in the current scope.
 */
template <hryky_template_param>
class hryky::ScopedIncrement :
	public WithStreamOut<ScopedIncrement<hryky_template_arg> >,
	public WithSwap<ScopedIncrement<hryky_template_arg> >,
	private WithoutCopy
{
public :

	typedef ScopedIncrement<hryky_template_arg> this_type;

	/// increments a value.
	ScopedIncrement(ValueT & value);

	/// move constructor.
	ScopedIncrement(this_type &&);

	/// destructor.
	~ScopedIncrement();

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

private :

	hryky_delete_default_constructor(ScopedIncrement);
	hryky_delete_this_copy_constructor(ScopedIncrement);
	hryky_delete_this_copy_assign_op(ScopedIncrement);

	AutoDecrement<ValueT> decrement_;

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
  @brief increments a value.
 */
template <hryky_template_param>
hryky::ScopedIncrement<hryky_template_arg>::ScopedIncrement(ValueT & value)
	: decrement_(value)
{
	++value;
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::ScopedIncrement<hryky_template_arg>::ScopedIncrement(this_type && rhs)
	: hryky_move_member(decrement)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::ScopedIncrement<hryky_template_arg>::~ScopedIncrement()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::ScopedIncrement<hryky_template_arg>::clear()
{
	hryky::clear(this->decrement_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::ScopedIncrement<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(decrement);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::ScopedIncrement<hryky_template_arg>::write_to(
	StreamT & out) const
{
	out << this->decrement_;
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
	/// creates a ScopedIncrement instance.
	template <hryky_template_param>
	ScopedIncrement<hryky_template_arg> scoped_increment(ValueT & value);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates a ScopedIncrement instance.
 */
template <hryky_template_param>
hryky::ScopedIncrement<hryky_template_arg> hryky::scoped_increment(
	ValueT & value)
{
	return ScopedIncrement<hryky_template_arg>(value);
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // SCOPED_INCREMENT_H_20140315191232467
// end of file
