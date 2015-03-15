/**
  @file     sdl_opengl_context.h
  @brief    manages the context of OpenGL in SDL.
  @author   HRYKY
  @version  $Id: sdl_opengl_context.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef SDL_OPENGL_CONTEXT_H_20140107224117612
#define SDL_OPENGL_CONTEXT_H_20140107224117612
#if HRYKY_USE_SDL
#include "hryky/definition.h"
#include "hryky/sdl/sdl_common.h"
#include "hryky/stream/stream_definition.h"
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
namespace sdl
{
namespace window
{
	class Context;
}

namespace opengl
{
	/// manages the context of OpenGL in SDL.
	class Context;

} // namespace opengl
} // namespace sdl
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief manages the context of OpenGL in SDL.
 */
class hryky::sdl::opengl::Context :
	public WithStreamOut<Context>,
	public WithSwap<Context>,
	public WithIsNull<Context>
{
public :

	typedef Context         this_type;
	typedef ::SDL_GLContext raw_type;
	typedef window::Context window_type;

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

	/// retrieves the raw resource.
	raw_type raw() const;

	/// confirms whether this instance is invalid.
	bool is_null() const;

protected :

private :
	hryky_delete_default_constructor(Context);
	hryky_delete_copy_constructor(Context);
	hryky_delete_copy_assign_op(Context);

	/// releases the internal resources.
	void clear();

	/// provisions the internal resources.
	bool reset(window_type const & window);

	raw_type raw_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace sdl
{
namespace opengl
{
} // namespace opengl
} // namespace sdl
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::sdl::opengl::Context::write_to(
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
namespace sdl
{
namespace opengl
{
} // namespace opengl
} // namespace sdl
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HRYKY_USE_SDL
#endif // SDL_OPENGL_CONTEXT_H_20140107224117612
// end of file
