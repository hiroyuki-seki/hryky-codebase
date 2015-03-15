/**
  @file     sdl_subsystem_module.h
  @brief    facilitates to manage sub-systems of SDL.
  @author   HRYKY
  @version  $Id: sdl_subsystem_module.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef SDL_SUBSYSTEM_MODULE_H_20130504203218522
#define SDL_SUBSYSTEM_MODULE_H_20130504203218522
#include "hryky/sdl/sdl_subsystem_common.h"
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
namespace subsystem
{
	/// facilitates to manage sub-systems of SDL.
	class Module;
}
} // namespace sdl
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief facilitates to manage sub-systems of SDL.
 */
class hryky::sdl::subsystem::Module
{
public :

	typedef Module this_type;

	/// default constructor.
	Module();

	/// destructor.
	~Module();

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// initializes the sub-systems.
	bool reset(flag_type const flag);

	/// confirms whether the SDL subsystem is initialized.
	bool valid() const;

protected :

private :

	hryky_delete_this_copy_constructor(Module);
	hryky_delete_this_copy_assign_op(Module);

	flag_type flag_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace sdl
{
namespace subsystem
{
} // namespace subsystem
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
hryky::sdl::subsystem::Module::write_to(
	StreamT & out) const
{
	out << this->flag_;
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
namespace subsystem
{
} // namespace subsystem
} // namespace sdl
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // SDL_SUBSYSTEM_MODULE_H_20130504203218522
// end of file
