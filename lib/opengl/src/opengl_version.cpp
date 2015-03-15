/**
  @file         opengl_version.cpp
  @brief        deals with the version of OpenGL.
  @author       HRYKY
  @version      $Id: opengl_version.cpp 377 2014-08-15 02:49:04Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/opengl/opengl_version.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace opengl
{
namespace
{
} // namespace
} // namespace opengl
} // namespace hryky
//------------------------------------------------------------------------------
// static variable
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// function prototype
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief constructor.
 */
hryky::opengl::Version::Version()
	: major_(2), minor_(1)
{
}
/**
  @brief constructor with version numbers.
 */
hryky::opengl::Version::Version(
	major_type major, minor_type minor)
	: major_(major), minor_(minor)
{
	return;
}
/**
  @brief retrieves the major version.
 */
hryky::opengl::Version::major_type
hryky::opengl::Version::major() const
{
	return this->major_;
}
/**
  @brief retrieves the minor version.
 */
hryky::opengl::Version::minor_type
hryky::opengl::Version::minor() const
{
	return this->minor_;
}
/**
  @brief compares to less than.
 */
bool hryky::opengl::Version::operator<(
	this_type const & rhs) const
{
	return this->major_ < rhs.major_
		|| (this->major_ == rhs.major_
			&& this->minor_ < rhs.minor_);
}
/**
  @brief compares to less than or equal.
 */
bool hryky::opengl::Version::operator<=(
	this_type const & rhs) const
{
	return this->major_ < rhs.major_
		|| (this->major_ == rhs.major_
			&& this->minor_ <= rhs.minor_);
}
/**
  @brief compares to equal.
 */
bool hryky::opengl::Version::operator==(
	this_type const & rhs) const
{
	return this->major_ == rhs.major_
		&& this->minor_ == rhs.minor_;
}
/**
  @brief applies for the preferred vesion of OpenGL to the implementation.
 */
void hryky::opengl::Version::prefer() const
{
	impl_type(this->major_, this->minor_).prefer();
}
/**
  @brief retrieves the current version applied to the implementation.
 */
hryky::opengl::Version &
hryky::opengl::Version::load()
{
	this->assign(impl_type().load());
	return *this;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief constructs with a impl type.
 */
hryky::opengl::Version::Version(
	impl_type const & impl)
	: major_(static_cast<major_type>(impl.major()))
	  , minor_(static_cast<minor_type>(impl.minor()))
{
}
/**
  @brief assigns a new value from the implementation.
 */
void hryky::opengl::Version::assign(
	impl_type const & impl)
{
	this->major_ = static_cast<major_type>(impl.major());
	this->minor_ = static_cast<minor_type>(impl.minor());
}
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates the instance that represents OpenGL version 2.1.
 */
hryky::opengl::Version
hryky::opengl::version_2_1()
{
	return Version(2, 1);
}
/**
  @brief creates the instance that represents OpenGL version 3.2.
 */
hryky::opengl::Version
hryky::opengl::version_3_2()
{
	return Version(3, 2);
}
/**
  @brief creates the instance that represents OpenGL version 4.1.
 */
hryky::opengl::Version
hryky::opengl::version_4_1()
{
	return Version(4, 1);
}
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace opengl
{
namespace
{
} // namespace
} // namespace opengl
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
