/**
  @file     sdl_display_mode.h
  @brief    retains a ::SDL_DisplayMode.
  @author   HRYKY
  @version  $Id: sdl_display_mode.h 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#ifndef SDL_DISPLAY_MODE_H_20130504144723282
#define SDL_DISPLAY_MODE_H_20130504144723282
#include "hryky/definition.h"
#include "hryky/sdl/sdl_common.h"
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
	/// retains a ::SDL_DisplayMode.
	class DisplayMode;

} // namespace sdl
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains a ::SDL_DisplayMode.
 */
class hryky::sdl::DisplayMode :
	public WithStreamOut<DisplayMode>,
	public WithSwap<DisplayMode>
{
public :

	typedef DisplayMode this_type;

	/// default constructor.
	DisplayMode();

	/// copy constructor.
	DisplayMode(this_type const &);

	/// move constructor.
	DisplayMode(this_type &&);

	/// destructor.
	~DisplayMode();

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

protected :

private :

	::SDL_DisplayMode raw_;

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
hryky::sdl::DisplayMode::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << stream::denote("width") << this->raw_.w;
	out << stream::denote("height") << this->raw_.h;
	out << stream::denote("refresh_rate") << this->raw_.refresh_rate;

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
} // namespace sdl
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // SDL_DISPLAY_MODE_H_20130504144723282
// end of file
