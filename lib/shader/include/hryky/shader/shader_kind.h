/**
  @file     shader_kind.h
  @brief    Kinds of shaders.
  @author   HRYKY
  @version  $Id: shader_kind.h 377 2014-08-15 02:49:04Z hryky.private@gmail.com $
 */
#ifndef SHADER_KIND_H_20140804064520948
#define SHADER_KIND_H_20140804064520948
#include "hryky/kind.h"
#include "hryky/literal_string.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
	struct Kind {
		enum Raw {
			vshader,
			fshader,

			num,
		};
		static LiteralString<> const tokens[num];
	};

	typedef hryky::Kind<
		Kind, Kind::vshader, Kind::num, LiteralString<>, Kind::tokens>
			kind_type;
	
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // SHADER_KIND_H_20140804064520948
// end of file
