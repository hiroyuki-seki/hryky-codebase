/**
  @file         testing_registry.h
  @brief        the collection of all tests.
  @author       HRYKY
  @version      $Id: testing_registry.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef TESTING_REGISTRY_H_20111217183516441
#define TESTING_REGISTRY_H_20111217183516441
#include "hryky/std/std_map.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace testing
{
	/// the collection of all tests.
	class Registry;

	/// the implementation of the entry point.
	int main_impl(int, char const * const[]);

namespace unit
{
	class Base;
}
}
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief the collection of all tests.
 */
class hryky::testing::Registry
{
public :

	
	typedef hryky::testing::Registry                this_type;
	typedef unit::Base *                            unit_type;

	/// invokes enregister() from hryky::testing::unit::Base only.
	class Enregister
	{
		friend class unit::Base;
		Enregister(
			Registry & registry, char const * name, unit_type unit) {
			registry.enregister(name, unit);
		}
	};

	/// retrieves the singleton instance.
	static Registry & instance();

	/// retrieves the functor of the test.
	unit_type operator[](char const * name) const;

protected :

private :

	typedef ::std::map< ::std::string, unit_type >   table_type;

	hryky_delete_this_copy_constructor(Registry);
	hryky_delete_this_copy_assign_op(Registry);

	/// default constructor.
	Registry();

	/// destructor.
	~Registry();

	/// maps the name of the test and the function to invoke the test.
	void enregister(char const * name, unit_type unit);

	table_type table_;

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
#endif // TESTING_REGISTRY_H_20111217183516441
// end of file
