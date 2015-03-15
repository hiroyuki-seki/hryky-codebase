/**
  @file         pixel_format.h
  @brief        represents the format of a pixel.
  @author       HRYKY
  @version      $Id: pixel_format.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef PIXEL_FORMAT_H_20120204091312050
#define PIXEL_FORMAT_H_20120204091312050
#include "hryky/definition.h"
#include "hryky/without_copy.h"
#include "hryky/sdl/sdl_common.h"
#include "hryky/stdint.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_padded
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace pixel
{
	/// represents the format of a pixel.
	class Format;

}
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief represents the format of a pixel.
 */
class hryky::pixel::Format :
	public WithStreamOut<Format>,
	public WithSwap<Format>
{
public :

	/// self.
	typedef hryky::pixel::Format this_type;

	/// kind of pixel format
	struct Kind
	{
		enum Raw
		{
			invalid,
			r8g8b8x8,
			b8g8r8x8,
			r8g8b8a8,
			b8g8r8a8,
			a8r8g8b8,
			a8b8g8r8,
			r8g8b8,
			b8g8r8,
			r5g6b5,
			b5g6r5,
			num,
		};
	};
	typedef Kind::Raw kind_type;

	/// trait of pixel format
	struct Traits
	{
		typedef Traits          this_type;
		typedef uint8_t         bytes_type;
		typedef char const *    name_type;

		struct Order
		{
			enum Kind
			{
				invalid,
				rgbx,
				bgrx,
				rgba,
				bgra,
				rgb,
				bgr,
				argb,
				abgr,
				num,
			};
		};
		typedef Order::Kind     order_type;

		/// retrieves the name of pixel format
		name_type name() const
		{
			return this->name_;
		}

		/// retrieves the order of each color element
		order_type order() const
		{
			return this->order_;
		}

		/// retrieves the size of pixel format in bytes
		bytes_type bytes() const
		{
			return this->bytes_;
		}

		name_type       name_;
		order_type      order_;
		bytes_type      bytes_;
	};

	/// default constructor.
	Format()
		: kind_()
	{};

	/// constructor with parameter
	Format(kind_type const kind)
		: kind_(kind)
	{
	}

#if HRYKY_USE_SDL
	struct SDLFormat
	{
		explicit SDLFormat(uint32_t raw)
			: raw_(raw)
		{
		}

		uint32_t raw_;
	};
	
	/// constructor with SDL_PIXELFORMAT.
	Format(SDLFormat const & sdl_format);

	/// retrieves SDL_PIXELFORMAT.
	uint32_t sdl_format() const;
#endif // HRYKY_USE_SDL

	/// destructor.
	~Format() {};

	/// copy constructor.
	Format(Format const & rhs)
		: hryky_copy_member(kind)
	{
	};

	/// assignment operator.
	Format & operator=(Format const & rhs)
	{
		this->kind_ = rhs.kind_;
		return *this;
	};

	/// retrieves the characteristic of a pixel format.
	Traits const & traits() const;

	/// retrieves the identifier of format
	kind_type kind() const
	{
		return this->kind_;
	}

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

protected :

private :

	kind_type kind_;

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::pixel::Format::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(kind);
	return out;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // PIXEL_FORMAT_H_20120204091312050
// end of file
