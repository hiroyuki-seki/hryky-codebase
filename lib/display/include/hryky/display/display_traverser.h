/**
  @file         display_traverser.h
  @brief        traverses the all display configurations in the environment.
  @author       HRYKY
  @version      $Id: display_traverser.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef DISPLAY_TRAVERSER_H_20120917075431996
#define DISPLAY_TRAVERSER_H_20120917075431996
#include "hryky/display/display_common.h"
#include "hryky/std/std_functional.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/without_copy.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_virtual_destructor
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace display
{
	/// traverses the all display configurations in the environment.
	class Traverser;

	class Config;

} // namespace display
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief traverses the all display configurations in the environment.
 */
class hryky::display::Traverser :
	public ::std::unary_function<Config const &, bool>,
	public WithStreamOut<Traverser>,
	public WithSwap<Traverser>,
	private WithoutNew
{
public :

	typedef Traverser this_type;

	/// default constructor.
	Traverser();

	/// copy constructor.
	Traverser(this_type const &);

	/// move constructor.
	Traverser(this_type && rhs);

	/// destructor.
	~Traverser();

	/// assignment operator.
	hryky_assign_op;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/**
	  @brief implements the traversal of each display configuration.
	  @retval true when the following traversal will continue.
	  @retval false when the following traversal is canceled.
	 */
	virtual result_type operator()(argument_type config) = 0;


protected :

private :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace display
{
} // namespace display
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::display::Traverser::write_to(
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
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace display
{
} // namespace display
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // DISPLAY_TRAVERSER_H_20120917075431996
// end of file
