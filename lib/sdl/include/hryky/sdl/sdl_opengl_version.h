/**
  @file     sdl_opengl_version.h
  @brief    applies the preferred version of OpenGL.
  @author   HRYKY
  @version  $Id: sdl_opengl_version.h 377 2014-08-15 02:49:04Z hryky.private@gmail.com $
 */
#ifndef SDL_OPENGL_VERSION_H_20140107234539656
#define SDL_OPENGL_VERSION_H_20140107234539656
#include "hryky/definition.h"
#include "hryky/stdint.h"
#include "hryky/stream/stream_definition.h"
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
namespace opengl
{
	/// applies the preferred version of OpenGL.
	class Version;

} // namespace opengl
} // namespace sdl
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief applies the preferred version of OpenGL.
 */
class hryky::sdl::opengl::Version :
	public WithStreamOut<Version>,
	public WithSwap<Version>
{
public :

	typedef Version this_type;
	typedef int_t major_type;
	typedef int_t minor_type;
	
	/// default constructor.
	Version();

	/// constructs with the specified version.
	Version(major_type const major, minor_type const minor);

	/// copy constructor.
	Version(this_type const &);

	/// move constructor.
	Version(this_type &&);

	/// destructor.
	~Version();

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

	/// applies the preferred version to the current context.
	void prefer() const;

	/// retrieves the major version.
	major_type major() const;

	/// retrieves the minor version.
	minor_type minor() const;

	/// applies the configuration to SDL system.
	void store() const;

	/// retrieves the configuration initialized by the SDL system.
	Version & load();

protected :

private :

	major_type major_;
	minor_type minor_;

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
hryky::sdl::opengl::Version::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(major);
	hryky_write_member(minor);

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
#endif // SDL_OPENGL_VERSION_H_20140107234539656
// end of file
