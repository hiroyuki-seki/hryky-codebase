/**
  @file     sdl_module.h
  @brief    manages the presence of the primary system of SDL.
  @author   HRYKY
  @version  $Id: sdl_module.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef SDL_MODULE_H_20130512161113341
#define SDL_MODULE_H_20130512161113341
#include "hryky/definition.h"
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
	/// manages the presence of the primary system of SDL.
	class Module;

} // namespace sdl
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief manages the presence of the primary system of SDL.
 */
class hryky::sdl::Module
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

	/// starts using SDL without a subsystem.
	bool reset();

protected :

private :

	hryky_delete_this_copy_constructor(Module);
	hryky_delete_this_copy_assign_op(Module);

	bool initialized_;

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
hryky::sdl::Module::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(initialized);

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
#endif // SDL_MODULE_H_20130512161113341
// end of file
