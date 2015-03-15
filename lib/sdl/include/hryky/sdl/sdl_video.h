/**
  @file     sdl_video.h
  @brief    facilitates the operation to SDL_Video.
  @author   HRYKY
  @version  $Id: sdl_video.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef SDL_VIDEO_H_20130504202847519
#define SDL_VIDEO_H_20130504202847519
#include "hryky/sdl/sdl_module.h"
#include "hryky/string.h"
#include "hryky/with_is_null.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace sdl
{
	/// facilitates the operation to SDL_Video.
	class Video;

} // namespace sdl
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief facilitates the operation to SDL_Video.
 */
class hryky::sdl::Video :
	public WithIsNull<Video>
{
public :

	typedef Video this_type;
	typedef char const * driver_name_type;

	/// default constructor.
	Video();

	/// constructs with the memory pool.
	Video(mempool_type const mempool);

	/// creates an instance with the mempool and the name of driver.
	Video(
		mempool_type const mempool,
		driver_name_type const driver_name);

	/// destructor.
	~Video();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// confirms whether resources are not initialized.
	bool is_null() const;

protected :

private :

	hryky_delete_this_copy_constructor(Video);
	hryky_delete_this_copy_assign_op(Video);

	/// releases the internal resources.
	void clear();

	/// rebuilds the SDL Video System with the particular driver.
	bool reset(driver_name_type const driver_name);

	Module      module_;
	String<>    prev_driver_name_;

	union
	{
		uint8_t flags_;
		struct
		{
			bool    initialized_:1;
			bool    restore_driver_:1;
		} flag_;
	};

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace sdl
{
} // namespace sdl
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::sdl::Video::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(module);
	hryky_write_member(prev_driver_name);
	out << stream::denote("initialized") << this->flag_.initialized_;
	out << stream::denote("restore_driver") << this->flag_.restore_driver_;

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
namespace sdl
{
} // namespace sdl
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // SDL_VIDEO_H_20130504202847519
// end of file
