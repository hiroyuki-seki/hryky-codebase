/**
  @file     opengl_shader_entity_vshader.h
  @brief    retains a vertex shader.
  @author   HRYKY
  @version  $Id: opengl_shader_entity_vshader.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef OPENGL_SHADER_ENTITY_VSHADER_H_20140109223845610
#define OPENGL_SHADER_ENTITY_VSHADER_H_20140109223845610
#include "hryky/opengl/opengl_shader_entity_base.h"
#include "hryky/opengl/opengl_raw_common.h"
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
namespace shader
{
namespace entity
{
	/// retains a vertex shader.
	class Vshader;

} // namespace entity
} // namespace shader

	typedef shader::entity::Vshader vshader_type;

} // namespace opengl
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains a vertex shader.
 */
class hryky::opengl::shader::entity::Vshader :
	public Base<Vshader>,
	public WithStreamOut<Vshader>,
	public WithSwap<Vshader>
{
public :

	typedef Base base_type;

	typedef Vshader this_type;

	static raw::shader_kind_type const raw_kind = GL_VERTEX_SHADER;

	/// constructs with the shader module.
	Vshader(module_type const module);

	/// move constructor.
	Vshader(this_type &&);

	/// destructor.
	~Vshader();

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
	hryky_delete_default_constructor(Vshader);
	hryky_delete_this_copy_constructor(Vshader);
	hryky_delete_this_copy_assign_op(Vshader);

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
namespace entity
{
} // namespace entity
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
hryky::opengl::shader::entity::Vshader::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << static_cast<base_type const>(*this);
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
namespace entity
{
} // namespace entity
} // namespace shader
} // namespace opengl
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // OPENGL_SHADER_ENTITY_VSHADER_H_20140109223845610
// end of file
