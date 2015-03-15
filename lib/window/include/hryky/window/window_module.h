/**
  @file         window_module.h
  @brief        manages window module.
  @author       HRYKY
  @version      $Id: window_module.h 375 2014-07-29 04:27:53Z hryky.private@gmail.com $
 */
#ifndef WINDOW_MODULE_H_20120205184502447
#define WINDOW_MODULE_H_20120205184502447
#include "hryky/sdl/sdl_video.h"
#include "hryky/std/std_cstdint.h"
#include "hryky/without_copy.h"
#include "hryky/with_is_null.h"
#include "hryky/singleton_trait.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_singleton_trait \
	hryky::SingletonTrait<Module>
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace window
{
	/// manages window module.
	class Module;
}
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief manages window module.
 */
class hryky::window::Module :
	public WithIsNull<Module>,
	public hryky_singleton_trait
{
public :
	typedef hryky::window::Module this_type;
	typedef hryky_singleton_trait singleton_trait;

	/// destructor.
	~Module();

	/// confirms whether the instance is invalid.
	bool is_null() const;

protected :

private :
	hryky_delete_this_copy_constructor(Module);
	hryky_delete_this_copy_assign_op(Module);

	friend class hryky_singleton_trait;

#if HRYKY_USE_SDL
	typedef sdl::Video impl_type;
#else
	static_assert(false "unsupported");
#endif // HRYKY_USE_SDL

	/// default constructor.
	Module();

	impl_type impl_;

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes macros
//------------------------------------------------------------------------------
#undef hryky_singleton_trait
#endif // WINDOW_MODULE_H_20120205184502447
// end of file
