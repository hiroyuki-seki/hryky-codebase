/**
  @file     opengl_raw_common.h
  @brief    The raw definitions of OpenGL.
  @author   HRYKY
  @version  $Id: opengl_raw_common.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef OPENGL_RAW_COMMON_H_20140111172142390
#define OPENGL_RAW_COMMON_H_20140111172142390
#include "hryky/gl.h"
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
namespace raw
{
	typedef GLuint shader_type;
	typedef GLuint program_type;
	typedef GLenum shader_kind_type;
	typedef GLint shader_property_type;

	GLint const g_true = GL_TRUE;
	GLint const g_false = GL_FALSE;
	shader_type const g_invalid_shader = 0u;

	
} // namespace raw
} // namespace opengl
} // namespace hryky
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace opengl
{
namespace raw
{
} // namespace raw
} // namespace opengl
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // OPENGL_RAW_COMMON_H_20140111172142390
// end of file
