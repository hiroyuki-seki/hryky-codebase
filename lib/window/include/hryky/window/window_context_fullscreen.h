/**
  @file     window_context_fullscreen.h
  @brief    A parameter for window::context_type::fullscreen().
  @author   HRYKY
  @version  $Id: window_context_fullscreen.h 350 2014-04-24 10:10:31Z hryky.private@gmail.com $
 */
#ifndef WINDOW_CONTEXT_FULLSCREEN_H_20130512224204612
#define WINDOW_CONTEXT_FULLSCREEN_H_20130512224204612
#include "hryky/pixel/pixel_format.h"
#include "hryky/window/window_common.h"
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
namespace context
{
	/// A parameter for window::context_type::fullscreen().
	class Fullscreen;

} // namespace context
} // namespace window
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief A parameter for window::context_type::fullscreen().
 */
class hryky::window::context::Fullscreen :
	public WithStreamOut<Fullscreen>,
	public WithSwap<Fullscreen>
{
public :

	typedef Fullscreen this_type;

	/// constructor with the size of window.
	Fullscreen(size_t const width, size_t const height);

	/// copy constructor.
	Fullscreen(this_type const &);

	/// move constructor.
	Fullscreen(this_type &&);

	/// destructor.
	~Fullscreen();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// retrieves the width of fullscreen.
	size_t width() const;

	/// retrieves the height of fullscreen.
	size_t height() const;

	/// retrieves the pixel format of fullscreen.
	pixel::Format const & format() const;

	/// retrieves the refresh rate of fullscreen.
	refresh_rate_type refresh_rate() const;

protected :

private :

	hryky_delete_default_constructor(Fullscreen);

	size_t width_;
	size_t height_;
	pixel::Format format_;
	refresh_rate_type refresh_rate_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace window
{
namespace context
{
} // namespace context
} // namespace window
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::window::context::Fullscreen::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(width);
	hryky_write_member(height);
	hryky_write_member(format);
	hryky_write_member(refresh_rate);

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
namespace context
{
} // namespace context
} // namespace window
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // WINDOW_CONTEXT_FULLSCREEN_H_20130512224204612
// end of file
