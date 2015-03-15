/**
  @file     clock_auto_elapse.h
  @brief    stores the elapsed time at the end of the current scope.
  @author   HRYKY
  @version  $Id: clock_auto_elapse.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef CLOCK_AUTO_ELAPSE_H_20140712174749408
#define CLOCK_AUTO_ELAPSE_H_20140712174749408
#include "hryky/clock/clock_elapse.h"
#include "hryky/without_copy.h"
#include "hryky/ratio.h"
#include "hryky/type_traits/add_pointer.h"
#include "hryky/retention/retention_pointer.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename OutputStreamT
#define hryky_template_arg \
	OutputStreamT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace clock
{
	/// stores the elapsed time at the end of the current scope.
	template <
		typename OutputStreamT
	>
	class AutoElapse;

} // namespace clock
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief stores the elapsed time at the end of the current scope.
 */
template <hryky_template_param>
class hryky::clock::AutoElapse
{
public :

	typedef AutoElapse<hryky_template_arg> this_type;

	/// creates an instance with the destination.
	AutoElapse(OutputStreamT & dest);

	/// move constructor.
	AutoElapse(this_type &&);

	/// destructor.
	~AutoElapse();

	/// move assignment operator.
	hryky_move_assign_op;

protected :

private :
	hryky_delete_default_constructor(AutoElapse);
	hryky_delete_copy_constructor(AutoElapse);
	hryky_delete_copy_assign_op(this_type);

	typedef typename AddPointer<OutputStreamT>::type dest_type;

	Elapse elapse_;
	dest_type dest_;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace clock
{
} // namespace clock
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief creates an instance with the destination.
 */
template <hryky_template_param>
hryky::clock::AutoElapse<hryky_template_arg>::AutoElapse(
	OutputStreamT & dest)
	: dest_(&dest)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::clock::AutoElapse<hryky_template_arg>::AutoElapse(
	this_type && rhs)
	: hryky_move_member(dest)
{
	hryky::clear(rhs.dest_);
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::clock::AutoElapse<hryky_template_arg>::~AutoElapse()
{
	if (!hryky_is_null(this->dest_)) {
		*this->dest_ << this->elapse_();
	}
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
namespace clock
{
	/// creates an AutoElapse.
	template <hryky_template_param>
	AutoElapse<hryky_template_arg> auto_elapse(OutputStreamT & dest);

} // namespace clock
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates an AutoElapse.
 */
template <hryky_template_param>
hryky::clock::AutoElapse<hryky_template_arg>
hryky::clock::auto_elapse(OutputStreamT & dest)
{
	return AutoElapse<hryky_template_arg>(dest);
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // CLOCK_AUTO_ELAPSE_H_20140712174749408
// end of file
