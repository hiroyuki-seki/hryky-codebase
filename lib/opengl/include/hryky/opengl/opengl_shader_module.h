/**
  @file     opengl_shader_module.h
  @brief    retains the interfaces for the operation of OpenGL shader.
  @author   HRYKY
  @version  $Id: opengl_shader_module.h 377 2014-08-15 02:49:04Z hryky.private@gmail.com $
 */
#ifndef OPENGL_SHADER_MODULE_H_20140108180410419
#define OPENGL_SHADER_MODULE_H_20140108180410419
#include "hryky/gl.h"
#include "hryky/opengl/opengl_shader_issuer.h"
#include "hryky/opengl/opengl_shader_entity_vshader.h"
#include "hryky/opengl/opengl_shader_entity_fshader.h"
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
namespace opengl
{
	class Version;
	
namespace shader
{
	/// retains the interfaces for the operation of OpenGL shader.
	class Module;

} // namespace shader
} // namespace opengl
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the interfaces for the operation of OpenGL shader.
 */
class hryky::opengl::shader::Module :
	public WithStreamOut<Module>,
	public WithSwap<Module>
{
public :

	typedef Module this_type;

	/// default constructor.
	Module();

	/// copy constructor.
	Module(this_type const &);

	/// move constructor.
	Module(this_type &&);

	/// destructor.
	~Module();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// creates a new object to retain Vertex Shader.
	vshader_type vshader() const;

	/// creates a new object to retain Fragment Shader.
	fshader_type fshader() const;

	/// creates a raw object of OpenGL Shader.
	raw::shader_type new_raw_shader(
		raw::shader_kind_type const kind) const;

	/**
	  renounces the shader with the confirmation whether the object is
	  already deleted.
	 */
	void delete_raw_shader(
		raw::shader_type const shader) const;

	/// confirms whether this instance is invalid.
	bool is_null() const;

	/// assigns a source to be compiled.
	template <typename StringT>
	bool source(raw::shader_type const shader, StringT str) const;

	/// compiles a shader.
	bool compile(raw::shader_type const shader) const;

protected :

private :

	/// recreates the internal resources.
	bool reset(Version const & version);

	/// assigns characters as a source to be compiled.
	bool source(
		raw::shader_type const shader,
		char const * const str,
		size_t const str_size) const;

	Issuer                      issuer_;
	PFNGLGETSHADERIVPROC        glGetShaderiv_;
	PFNGLCOMPILESHADERPROC      glCompileShader_;
	PFNGLGETSHADERINFOLOGPROC   glGetShaderInfoLog_;
	PFNGLGETSHADERSOURCEPROC    glGetShaderSource_;
	PFNGLSHADERSOURCEPROC       glShaderSource_;
	PFNGLISSHADERPROC           glIsShader_;

	bool initialized_;

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
hryky::opengl::shader::Module::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(issuer);
	hryky_write_member(glGetShaderiv);
	hryky_write_member(glCompileShader);
	hryky_write_member(glGetShaderInfoLog);
	hryky_write_member(glGetShaderSource);
	hryky_write_member(glShaderSource);
	hryky_write_member(glIsShader);

	return out;
}
/**
  @brief assigns a source to be compiled.
 */
template <typename StringT>
bool hryky::opengl::shader::Module::source(
	raw::shader_type const shader, StringT str) const
{
	return this->source(
		shader, hryky::data(str), hryky::size(str));
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
#endif // OPENGL_SHADER_MODULE_H_20140108180410419
// end of file
