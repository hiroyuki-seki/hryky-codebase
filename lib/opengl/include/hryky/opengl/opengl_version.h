/**
  @file         opengl_version.h
  @brief        deals with the version of OpenGL.
  @author       HRYKY
  @version      $Id: opengl_version.h 377 2014-08-15 02:49:04Z hryky.private@gmail.com $
 */
#ifndef OPENGL_VERSION_H_20120220133049229
#define OPENGL_VERSION_H_20120220133049229
#include "hryky/sdl/sdl_opengl_version.h"
#include "hryky/with_stream_out.h"
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
	/// deals with the version of OpenGL.
	class Version;

	typedef Version version_type;

	/// creates the instance that represents OpenGL version 2.1.
	Version version_2_1();

	/// creates the instance that represents OpenGL version 3.2.
	Version version_3_2();

	/// creates the instance that represents OpenGL version 4.1.
	Version version_4_1();

}
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief deals with the version of OpenGL.
 */
class hryky::opengl::Version :
	public WithStreamOut<Version>
{
public :

	typedef hryky::opengl::Version  this_type;
	typedef uint8_t                 major_type; ///< represents a major version.
	typedef uint8_t                 minor_type; ///< represents a minor version.

#if HRYKY_USE_SDL
	typedef sdl::opengl::Version impl_type;
#else
	static_assert(false, "unsupported");
#endif

	/// default constructor.
	Version();

	/// constructor with version numbers.
	Version(major_type major, minor_type minor);

	/// compares to less than.
	bool operator<(this_type const & rhs) const;

	/// compares to less than or equal.
	bool operator<=(this_type const & rhs) const;

	/// compares to equal.
	bool operator==(this_type const & rhs) const;

	/// retrieves the major version.
	Version::major_type major() const;

	/// retrieves the minor version.
	Version::minor_type minor() const;

	/// applies for the preferred vesion of OpenGL to the system.
	void prefer() const;

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// retrieves the current version applied to system.
	Version & load();

protected :

private :

	/// constructs with a impl type.
	Version(impl_type const & impl);

	/// assigns a new value from the implementation.
	void assign(impl_type const & impl);

	major_type major_;
	minor_type minor_;

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::opengl::Version::write_to(StreamT & out) const
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
// global function declaration
//------------------------------------------------------------------------------
namespace hryky
{
namespace opengl
{
	/// creates the instance that represents OpenGL version 2.1.
	Version version_2_1();

	/// creates the instance that represents OpenGL version 3.2.
	Version version_3_2();

	/// creates the instance that represents OpenGL version 4.1.
	Version version_4_1();

}
}
#endif // OPENGL_VERSION_H_20120220133049229
// end of file
