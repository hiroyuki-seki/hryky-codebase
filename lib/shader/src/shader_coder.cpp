/**
  @file     shader_coder.cpp
  @brief    writes out the source to be compiled as shader.
  @author   HRYKY
  @version  $Id: shader_coder.cpp 380 2014-08-24 07:41:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/shader/shader_coder.h"
#include "hryky/shader/shader_node.h"
#include "hryky/shader/shader_node_ptr.h"
#include "hryky/swap.h"
#include "hryky/string.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
namespace
{
} // namespace "anonymous"
} // namespace shader
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
  @brief default constructor.
 */
hryky::shader::Coder::Coder()
	: stream_()
{
}
/**
  @brief copy constructor.
 */
hryky::shader::Coder::Coder(this_type const & rhs)
	: hryky_copy_member(stream)
{
}
/**
  @brief move constructor.
 */
hryky::shader::Coder::Coder(this_type && rhs)
	: hryky_move_member(stream)
{
}
/**
  @brief destructor.
 */
hryky::shader::Coder::~Coder()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::shader::Coder::clear()
{
	hryky::clear(this->stream_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::shader::Coder::swap(this_type & src)
{
	hryky_swap_member(stream);
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines functions used in this file
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
namespace
{
} // namespace "anonymous"
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
