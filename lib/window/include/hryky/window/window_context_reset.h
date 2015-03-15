/**
  @file     window_context_reset.h
  @brief    A parameter for window::context_type::reset().
  @author   HRYKY
  @version  $Id: window_context_reset.h 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#ifndef WINDOW_CONTEXT_RESET_H_20130512223123605
#define WINDOW_CONTEXT_RESET_H_20130512223123605
#include "hryky/window/window_common.h"
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
namespace window
{
	class Module;
	
namespace context
{
	/// A parameter for window::context_type::reset().
	class Reset;

} // namespace context
} // namespace window
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief A parameter for window::context_type::reset().
 */
class hryky::window::context::Reset :
	public WithStreamOut<Reset>,
	public WithSwap<Reset>
{
public :

	typedef Reset this_type;

	/// default constructor.
	Reset();

	/// copy constructor.
	Reset(this_type const &);

	/// move constructor.
	Reset(this_type &&);

	/// destructor.
	~Reset();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// assigns a new region for this window.
	this_type & region(
		int32_t const left,
		int32_t const top,
		int32_t const right,
		int32_t const bottom);

	/// assigns a new caption.
	template <typename CaptionT>
	this_type & caption(CaptionT const & src);

	/// retrives the caption of window.
	caption_type const & caption() const;

	/// confirms whether a window is hidden initially.
	bool hidden() const;

	/// confirms whether a window use OpenGL.
	bool use_opengl() const;

	/// hides a window initially.
	void hidden(bool const src);

	/// indicates to use OpenGL.
	void use_opengl(bool const src);

	/// The region of window.
	hryky_accessor_row(region_type, region);

protected :

private :

	caption_type caption_;

	union
	{
		uint32_t flags_;
		struct
		{
			/// If true, a window is initially hidden.
			bool hidden_:1;
			/// If true, a window uses OpenGL.
			bool use_opengl_:1;
		} flag_;
	};
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace window
{
namespace context
{
} // namespace context
} // namespace window
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief assigns a new caption.
 */
template <typename CaptionT>
hryky::window::context::Reset &
hryky::window::context::Reset::caption(CaptionT const & src)
{
	this->caption_ = src;
	return *this;
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::window::context::Reset::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(region);
	hryky_write_member(caption);
	hryky_write_member(flags);

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
namespace window
{
namespace context
{
} // namespace context
} // namespace window
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // WINDOW_CONTEXT_RESET_H_20130512223123605
// end of file
