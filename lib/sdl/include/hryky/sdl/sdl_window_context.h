/**
  @file     sdl_window_context.h
  @brief    manages a Window GUI for SDL.
  @author   HRYKY
  @version  $Id: sdl_window_context.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef SDL_WINDOW_CONTEXT_H_20130512175202411
#define SDL_WINDOW_CONTEXT_H_20130512175202411
#if HRYKY_USE_SDL
#include "hryky/sdl/sdl_common.h"
#include "hryky/definition.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/with_is_null.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_user_constructor
#pragma hryky_pragma_disable_warning_create_default_constructor
#pragma hryky_pragma_disable_warning_create_assign_operator
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
	/// manages a Window GUI for SDL.
	class Context;
}
namespace opengl
{
	class Context;
}
} // namespace sdl
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief manages a Window GUI for SDL.
 */
class hryky::sdl::window::Context :
	public WithStreamOut<Context>,
	public WithSwap<Context>,
	public WithIsNull<Context>
{
public :

	typedef Context this_type;
	typedef ::SDL_Window * raw_type;

	struct Reset
	{
		char const * const caption;
		int const x;
		int const y;
		int const width;
		int const height;
		bool const use_opengl;
		bool const hidden;
	};

	struct Fullscreen
	{
		uint32_t const format;
		int width;
		int height;
		int refresh_rate;
	};

	/// default constructor.
	Context();

	/// creates an instance with the parameters.
	Context(Reset const & param);

	/// move constructor.
	Context(this_type && rhs);

	/// destructor.
	~Context();

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// displaies this window at fullscreen mode.
	bool fullscreen(Fullscreen const & param);

	/// reflects the result of rendering to the window.
	void update() const;

	/// retrieves the raw window.
	raw_type raw() const;

	/// associates a context of OpenGL to this window.
	bool opengl_context(
		sdl::opengl::Context const & context) const;

	/// confirms whether this instance is invalid.
	bool is_null() const;

protected :

private :
	hryky_delete_copy_constructor(Context);
	hryky_delete_copy_assign_op(Context);

	raw_type            raw_;
	::SDL_DisplayMode   prev_sdl_display_mode_;

	union
	{
		uint32_t    flags_;
		struct
		{
			bool    fullscreen_:1;
			bool    use_opengl_:1;
			bool    change_display_mode_:1;
		} flag_;
	};

	/// rebuilds the internal resources with the default parameters.
	bool reset();

	/// releases the existing resources and creates new resources.
	bool reset(Reset const & param);

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace sdl
{
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
hryky::sdl::window::Context::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(raw);
	hryky_write_member(flags);
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
namespace window
{
} // namespace window
} // namespace sdl
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // HRYKY_USE_SDL
#endif // SDL_WINDOW_CONTEXT_H_20130512175202411
// end of file
