/**
  @file     auto_decrement.h
  @brief    decrements the value at the end of the current scope.
  @author   HRYKY
  @version  $Id: auto_decrement.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef AUTO_DECREMENT_H_20140315190324460
#define AUTO_DECREMENT_H_20140315190324460
#include "hryky/definition.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/without_copy.h"
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
	/// decrements the value at the end of the current scope.
	template <typename ValueT>
	class AutoDecrement;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief decrements the value at the end of the current scope.
 */
template <hryky_template_param>
class hryky::AutoDecrement :
	public WithStreamOut<AutoDecrement<hryky_template_arg> >,
	private WithoutCopy
{
public :

	typedef AutoDecrement<hryky_template_arg> this_type;

	/// instantiates with the decremented value.
	AutoDecrement(ValueT & value);

	/// move constructor.
	AutoDecrement(this_type &&);

	/// destructor.
	~AutoDecrement();

	/// releases the internal resources.
	void clear();

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// cancels the decrement.
	void disable();

protected :

private :

	hryky_delete_default_constructor(AutoDecrement);
	hryky_delete_this_copy_constructor(AutoDecrement);
	hryky_delete_this_copy_assign_op(AutoDecrement);

	ValueT & value_;
	bool disabled_;

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
  @brief instantiates with the decremented value.
 */
template <hryky_template_param>
hryky::AutoDecrement<hryky_template_arg>::AutoDecrement(ValueT & value)
	: value_(value)
	  , disabled_()
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::AutoDecrement<hryky_template_arg>::AutoDecrement(this_type && rhs)
	: hryky_move_member(value)
	  , hryky_move_member(disabled)
{
	rhs.disable();
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::AutoDecrement<hryky_template_arg>::~AutoDecrement()
{
	if (!this->disabled_) {
		--this->value_;
	}
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::AutoDecrement<hryky_template_arg>::clear()
{
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::AutoDecrement<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(value);
	hryky_write_member(disabled);
	return out;
}
/**
  @brief cancels the decrement.
 */
template <hryky_template_param>
void hryky::AutoDecrement<hryky_template_arg>::disable()
{
	this->disabled_ = true;
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
#endif // AUTO_DECREMENT_H_20140315190324460
// end of file
