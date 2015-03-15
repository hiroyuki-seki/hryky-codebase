/**
  @file         opengl_common.h
  @brief        common definitions of OpenGL module.
  @author       HRYKY
  @version      $Id: opengl_common.h 376 2014-07-29 10:46:52Z hryky.private@gmail.com $
 */
#ifndef OPENGL_COMMON_H_20120220132905228
#define OPENGL_COMMON_H_20120220132905228
#include "hryky/gl.h"
#include "hryky/log/log_definition.h"
#include "hryky/tuple.h"
#include "hryky/color/color_rgba.h"
#include "hryky/debug/debug_common.h"
#include "hryky/stream/stream_showbase.h"
#include "hryky/stream/stream_hex.h"
#include "hryky/stream/ostream_string.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//--------------------------------
// call OpenGL function
//--------------------------------
#define hryky_call_gl0(func) \
	(\
	 func(),\
	 hryky::opengl::check_gl(\
		#func, hryky::make_tuple(), \
		hryky_source_position)\
	 )

#define hryky_call_gl1(func, a0) \
	(\
	 func(a0),\
	 hryky::opengl::check_gl(\
		#func, hryky::make_tuple(a0), \
		hryky_source_position)\
	 )

#define hryky_call_gl2(func, a0, a1) \
	(\
	 func(a0, a1),\
	 hryky::opengl::check_gl(\
		#func, hryky::make_tuple(a0, a1), \
		hryky_source_position)\
	 )

#define hryky_call_gl3(func, a0, a1, a2) \
	(\
	 func(a0, a1, a2),\
	 hryky::opengl::check_gl(\
		#func, hryky::make_tuple(a0, a1, a2), \
		hryky_source_position)\
	 )

#define hryky_call_gl4(func, a0, a1, a2, a3) \
	(\
	 func(a0, a1, a2, a3),\
	 hryky::opengl::check_gl(\
		#func, hryky::make_tuple(a0, a1, a2, a3), \
		hryky_source_position)\
	 )

#define hryky_call_gl5(func, a0, a1, a2, a3, a4) \
	(\
	 func(a0, a1, a2, a3, a4),\
	 hryky::opengl::check_gl(\
		#func, hryky::make_tuple(a0, a1, a2, a3, a4), \
		hryky_source_position)\
	 )

#define hryky_call_gl6(func, a0, a1, a2, a3, a4, a5) \
	(\
	 func(a0, a1, a2, a3, a4, a5),\
	 hryky::opengl::check_gl(\
		#func, hryky::make_tuple(a0, a1, a2, a3, a4, a5), \
		hryky_source_position)\
	 )

#define hryky_call_gl7(func, a0, a1, a2, a3, a4, a5, a6) \
	(\
	 func(a0, a1, a2, a3, a4, a5, a6),\
	 hryky::opengl::check_gl(\
		#func, hryky::make_tuple(a0, a1, a2, a3, a4, a5, a6), \
		hryky_source_position)\
	 )

#define hryky_call_gl8(func, a0, a1, a2, a3, a4, a5, a6, a7) \
	(\
	 func(a0, a1, a2, a3, a4, a5, a6, a7),\
	 hryky::opengl::check_gl(\
		#func, hryky::make_tuple(a0, a1, a2, a3, a4, a5, a6, a7), \
		hryky_source_position)\
	 )

#define hryky_call_gl9(func, a0, a1, a2, a3, a4, a5, a6, a7, a8) \
	(\
	 func(a0, a1, a2, a3, a4, a5, a6, a7, a8),\
	 hryky::opengl::check_gl(\
		#func, hryky::make_tuple(a0, a1, a2, a3, a4, a5, a6, a7, a8), \
		hryky_source_position)\
	 )
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace opengl
{
	/// checks whether OpenGL API failed.
	template <typename TupleT>
	bool check_gl(
		char const * const func,
		TupleT const & tuple,
		debug::Source const & source);

}
}
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// define global functions
//------------------------------------------------------------------------------
/**
  @brief checks whether OpenGL API failed.
 */
template <typename TupleT>
bool hryky::opengl::check_gl(
	char const * const func,
	TupleT const & tuple,
	debug::Source const & source)
{
	bool success = true;
	
	GLenum error = GL_NO_ERROR;
	while (GL_NO_ERROR != (error = glGetError())) {
		ostream::String<String<> > os;
		
		os << stream::Showbase() << hryky::stream::Hex();
		os << func << "(" << tuple << ")";
		
		hryky_log_err(
			"OpenGL Error "
			<< (json::writer()
				<< hryky_stream_denote(source)
				<< hryky_stream_denote(error)
				<< "call" << os.str().c_str()));
		success = false;
	}

	return success;
}
#endif // OPENGL_COMMON_H_20120220132905228
// end of file
