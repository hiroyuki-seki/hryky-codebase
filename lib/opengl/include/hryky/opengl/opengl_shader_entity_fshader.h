/**
  @file     opengl_shader_entity_fshader.h
  @brief    retains a fragment shader.
  @author   HRYKY
  @version  $Id: opengl_shader_entity_fshader.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef OPENGL_SHADER_ENTITY_FSHADER_H_20140109224115611
#define OPENGL_SHADER_ENTITY_FSHADER_H_20140109224115611
#include "hryky/opengl/opengl_shader_entity_base.h"
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
	/// retains a fragment shader.
	class Fshader;

} // namespace entity
} // namespace shader

	typedef shader::entity::Fshader fshader_type;

} // namespace opengl
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains a fragment shader.
 */
class hryky::opengl::shader::entity::Fshader :
	public Base<Fshader>,
	public WithStreamOut<Fshader>,
	public WithSwap<Fshader>
{
public :

	typedef Base base_type;

	typedef Fshader this_type;

	static raw::shader_kind_type const raw_kind = GL_FRAGMENT_SHADER;

	/// constructs with the shader module.
	Fshader(module_type const module);

	/// move constructor.
	Fshader(this_type &&);

	/// destructor.
	~Fshader();

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

	hryky_delete_default_constructor(Fshader);
	hryky_delete_this_copy_constructor(Fshader);
	hryky_delete_this_copy_assign_op(Fshader);
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
hryky::opengl::shader::entity::Fshader::write_to(
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
#endif // OPENGL_SHADER_ENTITY_FSHADER_H_20140109224115611
// end of file
