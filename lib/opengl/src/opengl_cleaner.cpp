/**
  @file     opengl_cleaner.cpp
  @brief    clears the current framebuffer.
  @author   HRYKY
  @version  $Id: opengl_cleaner.cpp 377 2014-08-15 02:49:04Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "./opengl_common_internal.h"
#include "hryky/clear.h"
#include "hryky/json/json_writer.h"
#include "hryky/opengl/opengl_cleaner.h"
#include "hryky/opengl/opengl_common.h"
#include "hryky/opengl/opengl_version.h"
#include "hryky/log.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace opengl
{
namespace
{
} // namespace "anonymous"
} // namespace opengl
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
hryky::opengl::Cleaner::Cleaner()
	: glClear_()
	  , glClearColor_()
	  , glClearDepth_()
	  , glClearStencil_()
	  , color_()
	  , depth_()
	  , stencil_()
{
	if (!this->reset(Version().load())) {
		hryky_log_err(
			"failed to initialize the function to clear "
			"the rendering buffer.");
		return;
	}
}
/**
  @brief copy constructor.
 */
hryky::opengl::Cleaner::Cleaner(this_type const & rhs)
	: hryky_copy_member(glClear)
	  , hryky_copy_member(glClearColor)
	  , hryky_copy_member(glClearDepth)
	  , hryky_copy_member(glClearStencil)
	  , hryky_copy_member(color)
	  , hryky_copy_member(depth)
	  , hryky_copy_member(stencil)
{
}
/**
  @brief move constructor.
 */
hryky::opengl::Cleaner::Cleaner(this_type && rhs)
	: hryky_move_member(glClear)
	  , hryky_move_member(glClearColor)
	  , hryky_move_member(glClearDepth)
	  , hryky_move_member(glClearStencil)
	  , hryky_move_member(color)
	  , hryky_move_member(depth)
	  , hryky_move_member(stencil)
{
}
/**
  @brief destructor.
 */
hryky::opengl::Cleaner::~Cleaner()
{
}
/**
  @brief clears framebuffer with the comprehensive parameters.
 */
bool hryky::opengl::Cleaner::operator()(
	Parameter const & param) const
{
	GLbitfield const bit = static_cast<GLbitfield>(
		(param.for_color() ? GL_COLOR_BUFFER_BIT : 0)
		| (param.for_depth() ? GL_DEPTH_BUFFER_BIT : 0)
		| (param.for_stencil() ? GL_STENCIL_BUFFER_BIT : 0));

	if (0 == bit) {
		return true;
	}

	if (param.update_color() && this->color_ != param.color()) {
		this->color_ = param.color();
		this->glClearColor_(
			this->color_.red(),
			this->color_.green(),
			this->color_.blue(),
			this->color_.alpha());
	}

	if (param.update_depth() && this->depth_ != param.depth()) {
		this->depth_ = param.depth();
		this->glClearDepth_(this->depth_);
	}

	if (param.update_stencil() && this->stencil_ != param.stencil()) {
		this->stencil_ = param.stencil();
		this->glClearStencil_(this->stencil_);
	}

	return hryky_call_gl1(this->glClear_, bit);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::opengl::Cleaner::swap(this_type & src)
{
	hryky_swap_member(glClear);
	hryky_swap_member(glClearColor);
	hryky_swap_member(glClearDepth);
	hryky_swap_member(glClearStencil);
	hryky_swap_member(color);
	hryky_swap_member(depth);
	hryky_swap_member(stencil);
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief clears the existing resources and creates new resources.
 */
bool hryky::opengl::Cleaner::reset(version_type const &)
{
	hryky_get_gl_proc(glClear);
	hryky_get_gl_proc(glClearColor);
	hryky_get_gl_proc(glClearDepth);
	hryky_get_gl_proc(glClearStencil);

	this->glClearColor_(
		this->color_.red(),
		this->color_.green(),
		this->color_.blue(),
		this->color_.alpha());
	this->glClearDepth_(this->depth_);
	this->glClearStencil_(this->stencil_);
	
	return true;
}
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace opengl
{
namespace
{
} // namespace "anonymous"
} // namespace opengl
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
