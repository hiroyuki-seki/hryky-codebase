/**
  @file     stream_definition.h
  @brief    defines the macros of stream module.
  @author   HRYKY
  @version  $Id: stream_definition.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef STREAM_DEFINITION_H_20140208231720637
#define STREAM_DEFINITION_H_20140208231720637
#include "hryky/stream/stream_denote.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_write_member(var) \
	out << hryky::stream::denote(#var) << this->var##_;
#define hryky_write_pointer_member(var) \
	out << hryky::stream::denote(#var) << this->var##_;
#define hryky_stream_denote(var) \
	hryky::stream::denote(#var) << var
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace stream
{
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// declares structs
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace stream
{
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // STREAM_DEFINITION_H_20140208231720637
// end of file
