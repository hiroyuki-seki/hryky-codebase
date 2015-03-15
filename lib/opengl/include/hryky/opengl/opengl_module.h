/**
  @file         opengl_module.h
  @brief        manages OpenGL module.
  @author       HRYKY
  @version      $Id: opengl_module.h 377 2014-08-15 02:49:04Z hryky.private@gmail.com $
 */
#ifndef OPENGL_MODULE_H_20120220142529267
#define OPENGL_MODULE_H_20120220142529267
#include "hryky/gl.h"
#include "hryky/opengl/opengl_common.h"
#include "hryky/opengl/opengl_cleaner.h"
#include "hryky/opengl/opengl_context.h"
#include "hryky/opengl/opengl_shader_module.h"
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
namespace window
{
	class Context;
}
namespace opengl
{
	/// manages OpenGL module.
	class Module;

}
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief manages OpenGL module.
 */
class hryky::opengl::Module :
	public WithStreamOut<Module>,
	public WithSwap<Module>,
	public WithIsNull<Module>
{
public :

	typedef hryky::opengl::Module   this_type;
	typedef shader::Module          shader_type;
	typedef window::Context         window_type;

	/// creates an instance associating with the window.
	Module(window_type const & window);

	/// move constructor.
	Module(this_type && rhs);

	/// destructor.
	~Module();

	/// move assignment operator.
	hryky_move_assign_op;

	/// retrieves the cleaner.
	Cleaner const & cleaner() const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// creates a shader object for Vertex Shader.
	vshader_type vshader() const;

	/// creates a shader object for Fragment Shader.
	fshader_type fshader() const;

	/// confirms whether this instance is invalid.
	bool is_null() const;

protected :

private :
	hryky_delete_default_constructor(Module);
	hryky_delete_copy_constructor(Module);
	hryky_delete_copy_assign_op(Module);

	Context                         context_;
	Cleaner                         cleaner_;
	shader_type                     shader_;
	PFNGLBINDFRAGDATALOCATIONPROC   glBindFragDataLocation_;
	bool                            initialized_;

	/// clears the existing resources and creates new resources.
	bool reset();

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::opengl::Module::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(context);
	hryky_write_member(cleaner);
	hryky_write_member(shader);
	hryky_write_member(glBindFragDataLocation);

	return out;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
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
} // namespace opengl
} // namespace hryky
#endif // OPENGL_MODULE_H_20120220142529267
// end of file
