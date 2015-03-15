/**
  @file         window_context.h
  @brief        creates GUI window.
  @author       HRYKY
  @version      $Id: window_context.h 375 2014-07-29 04:27:53Z hryky.private@gmail.com $
 */
#ifndef WINDOW_CONTEXT_H_20120213151241300
#define WINDOW_CONTEXT_H_20120213151241300
#include "hryky/config.h"
#include "hryky/sdl/sdl_window_context.h"
#include "hryky/window/window_module.h"
#include "hryky/with_is_null.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace window
{
	/// creates GUI window.
	class Context;

namespace context
{
	class Reset;
	class Fullscreen;
}
} // namespace window
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief creates GUI window.
 */
class hryky::window::Context :
	public WithStreamOut<Context>,
	public WithSwap<Context>,
	public WithIsNull<Context>
{
public :

	typedef hryky::window::Context this_type;

#if HRYKY_USE_SDL
	typedef sdl::window::Context raw_type;
#else
	static_assert(false, "unsupported");
#endif // HRYKY_USE_SDL

	/// default constructor.
	Context();

	/// creates an instance with the specified parameters.
	Context(context::Reset const & param);

	/// move constructor.
	Context(this_type && rhs);

	/// destructor.
	~Context();

	/// move assignment operator.
	hryky_move_assign_op;

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// updates the result of rendering.
	void update() const;

	/// sets the window to fullscreen-mode.
	bool fullscreen(context::Fullscreen const & param);

	/// retrieves the implementation of Window.
	raw_type & raw();

	/// retrieves the implementation of Window as immutable.
	raw_type const & raw() const;

	/// confirms whether this instance is invalid.
	bool is_null() const;

protected :

private :
	hryky_delete_copy_constructor(Context);
	hryky_delete_copy_assign_op(Context);

	typedef Module::instance_type module_type;

	/// clears the existing resources and creates new resources.
	bool reset(context::Reset const & param);

	/// recreates the internal resources with default parameters.
	bool reset();

	module_type module_;

	raw_type raw_;

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::window::Context::write_to(
	StreamT & out) const
{
	out << this->raw_;
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
namespace window
{
} // namespace window
} // namespace hryky
#endif // WINDOW_CONTEXT_H_20120213151241300
// end of file
