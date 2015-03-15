/**
  @file         display_environment.h
  @brief        collects the available display environments.
  @author       HRYKY
  @version      $Id: display_environment.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef DISPLAY_ENVIRONMENT_H_20120128121804179
#define DISPLAY_ENVIRONMENT_H_20120128121804179
#include "hryky/display/display_driver.h"
#include "hryky/mempool/mempool_base.h"
#include "hryky/without_copy.h"
#include "hryky/vector.h"
#include "hryky/foreach.h"
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
namespace display
{
	/// collects the available display environments.
	class Environment;

	class Mode;
}
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief collects the available display environments.
 */
class hryky::display::Environment :
	public WithStreamOut<Environment>,
	public WithSwap<Environment>
{
public :

	/// self.
	typedef hryky::display::Environment this_type;
	typedef mempool_type           mempool_type;
	typedef Driver                      driver_type;

	/// parameters for reset().
	struct ResetParameter
	{
		ResetParameter()
		{}
	};

	/// default constructor.
	Environment();

	/// constructor with mempool.
	Environment(mempool_type mempool);

	/// copy constructor.
	Environment(this_type const & rhs);

	/// move constructor.
	Environment(this_type && rhs);

	/// destructor.
	~Environment();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// recreates new resources with the default parameters.
	bool reset();

	/// clears the existing resources and creates new resources.
	bool reset(ResetParameter const & param);

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/**
	  @brief traverses the all display configurations.
	  @param functor is called for each display mode.
	  @retval true when the operation is not canceled by user.
	  @retval false when the operation is canceled by user.

	   The function 'bool functor(display::Config &)' is called during the
	  iteration of display modes.
	 */
	template < typename FunctorT >
	bool traverse(FunctorT const & functor) const;

	/// retrieves the number of video drivers.
	size_t drivers_size() const;

	/// retrieves the initial driver.
	Driver const & initial_driver() const;

	/// retrieves the size of the current display.
	size_type const & initial_size() const;

protected :

private :

	typedef Vector<driver_type> drivers_type;

	drivers_type    drivers_;
	driver_id_type  initial_driver_id_;

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief traverses the all display configurations.
 */
template < typename FunctorT >
bool hryky::display::Environment::traverse(FunctorT const & functor) const
{
	return this->drivers_.every([&functor](
		drivers_type::const_reference driver) {
		return driver.traverse(functor);
	});
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::display::Environment::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(initial_driver_id);
	hryky_write_member(drivers);
	
	return out;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// global function prototype
//------------------------------------------------------------------------------
namespace hryky
{
namespace display
{
}
}
#endif // DISPLAY_ENVIRONMENT_H_20120128121804179
// end of file
