/**
  @file     opengl_context.h
  @brief    retains the context of OpenGL.
  @author   HRYKY
  @version  $Id: opengl_context.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef OPENGL_CONTEXT_H_20140107231106632
#define OPENGL_CONTEXT_H_20140107231106632
#include "hryky/config.h"
#include "hryky/sdl/sdl_opengl_context.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/with_is_null.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace opengl
{
	/// retains the context of OpenGL.
	class Context;

} // namespace opengl
namespace window
{
	class Context;
}
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the context of OpenGL.
 */
class hryky::opengl::Context :
	public WithStreamOut<Context>,
	public WithSwap<Context>,
	public WithIsNull<Context>
{
public :

	typedef Context this_type;
	typedef window::Context window_type;

#if HRYKY_USE_SDL
	typedef sdl::opengl::Context raw_type;
#else
	static_assert(false, "unsupported");
#endif // HRYKY_USE_SDL

	/// creates an instance associating with the window.
	Context(window_type const & window);

	/// move constructor.
	Context(this_type &&);

	/// destructor.
	~Context();

	/// move assignment operator.
	hryky_move_assign_op;

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// retrieves the implementation of OpenGL context.
	raw_type & raw();

	/// retrieves the implementation of OpenGL context as immutable.
	raw_type const & raw() const;

	/// confirms whether this instance is invalid.
	bool is_null() const;

protected :

private :
	hryky_delete_default_constructor(Context);
	hryky_delete_copy_constructor(Context);
	hryky_delete_copy_assign_op(Context);

	raw_type raw_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace opengl
{
} // namespace opengl
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::opengl::Context::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(raw);

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
namespace opengl
{
} // namespace opengl
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // OPENGL_CONTEXT_H_20140107231106632
// end of file
