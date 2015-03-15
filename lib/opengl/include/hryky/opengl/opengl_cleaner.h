/**
  @file     opengl_cleaner.h
  @brief    clears the current framebuffer.
  @author   HRYKY
  @version  $Id: opengl_cleaner.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef OPENGL_CLEANER_H_20140105104226112
#define OPENGL_CLEANER_H_20140105104226112
#include "hryky/gl.h"
#include "hryky/color/color_rgba.h"
#include "hryky/type_traits/as_parameter.h"
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
	/// clears the current framebuffer.
	class Cleaner;

	class Version;
	typedef Version version_type;

} // namespace opengl
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief clears the current framebuffer.
 */
class hryky::opengl::Cleaner :
	public WithStreamOut<Cleaner>,
	public WithSwap<Cleaner>
{
public :

	typedef Cleaner this_type;

	typedef color::Rgba<float>  color_type;  ///< format to clear color buffer
	typedef float               depth_type;  ///< format to clear depth buffer
	typedef int32_t             stencil_type;///< format to clear stencil buffer
	
	/// parameters for clear_framebuffer
	struct Parameter
	{
		typedef Parameter this_type;

		Parameter()
			: color_(0.0f, 0.0f, 0.0f, 0.0f)
			  , depth_(0.0)
			  , stencil_(0)
			  , for_color_(false)
			  , for_depth_(false)
			  , for_stencil_(false)
		{}

		this_type & color(
			AsParameter<color_type>::type color) {
			this->color_ = color;
			this->update_color_ = true;
			return *this;
		}
		
		this_type & depth(
			AsParameter<depth_type>::type depth) {
			this->depth_ = depth;
			this->update_depth_ = true;
			return *this;
		}
		
		this_type & stencil(
			AsParameter<stencil_type>::type stencil) {
			this->stencil_ = stencil;
			this->update_stencil_ = true;
			return *this;
		}
		
	private :
		hryky_accessor_read(color_type,     color);
		hryky_accessor_read(depth_type,     depth);
		hryky_accessor_read(stencil_type,   stencil);
		hryky_accessor_read(bool,           update_color);
		hryky_accessor_read(bool,           update_depth);
		hryky_accessor_read(bool,           update_stencil);
		hryky_accessor_row(bool,            for_color);
		hryky_accessor_row(bool,            for_depth);
		hryky_accessor_row(bool,            for_stencil);
	};

	/// default constructor.
	Cleaner();

	/// copy constructor.
	Cleaner(this_type const &);

	/// move constructor.
	Cleaner(this_type &&);

	/// destructor.
	~Cleaner();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// clears framebuffer with the comprehensive parameters.
	bool operator()(Parameter const & param) const;

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

protected :

private :

	PFNGLCLEARPROC          glClear_;
	PFNGLCLEARCOLORPROC     glClearColor_;
	PFNGLCLEARDEPTHPROC     glClearDepth_;
	PFNGLCLEARSTENCILPROC   glClearStencil_;

	mutable color_type      color_;
	mutable depth_type      depth_;
	mutable stencil_type    stencil_;

	/// clears the existing resources and creates new resources.
	bool reset(version_type const & version);

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace opengl
{
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
hryky::opengl::Cleaner::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(glClear);
	hryky_write_member(glClearColor);
	hryky_write_member(glClearDepth);
	hryky_write_member(glClearStencil);
	hryky_write_member(color);
	hryky_write_member(depth);
	hryky_write_member(stencil);

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
} // namespace opengl
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // OPENGL_CLEANER_H_20140105104226112
// end of file
