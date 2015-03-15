/**
  @file     sdl_window_color.h
  @brief    manages the color of window.
  @author   HRYKY
  @version  $Id: sdl_window_color.h 377 2014-08-15 02:49:04Z hryky.private@gmail.com $
 */
#ifndef SDL_WINDOW_COLOR_H_20140802150542295
#define SDL_WINDOW_COLOR_H_20140802150542295
#include "hryky/definition.h"
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
namespace sdl
{
namespace window
{
	/// manages the color of window.
	class Color;

} // namespace window
} // namespace sdl
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief manages the color of window.
 */
class hryky::sdl::window::Color :
	public WithStreamOut<Color>,
	public WithSwap<Color>
{
public :

	typedef Color this_type;

	/// default constructor.
	Color();

	/// copy constructor.
	Color(this_type const &);

	/// move constructor.
	Color(this_type &&);

	/// destructor.
	~Color();

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
	StreamT & write_to(StreamT & out) const;

	/// requires the preferred settings.
	void prefer() const;

	/// applies this configuration to SDL system.
	void store() const;

	/// retrieves the configuration applied to SDL System.
	Color & load();

protected :

private :

	uint8_t red_;
	uint8_t green_;
	uint8_t blue_;
	uint8_t alpha_;

};
//------------------------------------------------------------------------------
// specializes classes
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
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::sdl::window::Color::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(red);
	hryky_write_member(green);
	hryky_write_member(blue);
	hryky_write_member(alpha);
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
#endif // SDL_WINDOW_COLOR_H_20140802150542295
// end of file
