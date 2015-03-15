/**
  @file     opengl_shader_issuer.h
  @brief    accrues and renounces an object of OpenGL Shader.
  @author   HRYKY
  @version  $Id: opengl_shader_issuer.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef OPENGL_SHADER_ISSUER_H_20140111171118382
#define OPENGL_SHADER_ISSUER_H_20140111171118382
#include "hryky/gl.h"
#include "hryky/opengl/opengl_raw_common.h"
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
	class Version;
	
namespace shader
{
	/// accrues and renounces an object of OpenGL Shader.
	class Issuer;

} // namespace shader
} // namespace opengl
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief accrues and renounces an object of OpenGL Shader.
 */
class hryky::opengl::shader::Issuer :
	public WithStreamOut<Issuer>,
	public WithSwap<Issuer>,
	public WithIsNull<Issuer>
{
public :

	typedef Issuer this_type;

	/// default constructor.
	Issuer();

	/// copy constructor.
	Issuer(this_type const &);

	/// move constructor.
	Issuer(this_type &&);

	/// destructor.
	~Issuer();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// accrues the name of OpenGL Shader Object.
	raw::shader_type new_raw(
		raw::shader_kind_type const shader_kind) const;

	/// renounces the shader object without checking the deletion.
	void delete_raw(
		raw::shader_type const raw_shader) const;

	/// confirms whether this instance is invalid.
	bool is_null() const;

protected :

private :

	PFNGLCREATESHADERPROC       glCreateShader_;
	PFNGLDELETESHADERPROC       glDeleteShader_;

	bool initialized_;

	/// reassembles the internal resources.
	bool reset(Version const & version);
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace opengl
{
namespace shader
{
} // namespace shader
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
hryky::opengl::shader::Issuer::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(glCreateShader);
	hryky_write_member(glDeleteShader);

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
namespace shader
{
} // namespace shader
} // namespace opengl
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // OPENGL_SHADER_ISSUER_H_20140111171118382
// end of file
