/**
  @file         testing_unit_base.h
  @brief        base class to test one module.
  @author       HRYKY
  @version      $Id: testing_unit_base.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef TESTING_UNIT_BASE_H_20120428133331231
#define TESTING_UNIT_BASE_H_20120428133331231
#include "hryky/type.h"
#include "hryky/without_copy.h"
#include "hryky/without_new.h"
#include "hryky/without_placement_new.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_virtual_destructor
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
	class Registry;

namespace unit
{
	/// base class to test one module.
	class Base;

} // namespace unit
} // namespace testing
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief base class to test one module.
 */
class hryky::testing::unit::Base :
	private WithoutCopy,
	private WithoutNew,
	private WithoutPlacementNew
{
public :

	typedef Base        this_type;
	typedef ::std::string name_type;
	typedef Registry &  registry_type;

	/// enregister self to the singleton hryky::testing::Registry.
	Base(char const * name);

	/// enregisters self to the specified hryky::testing::Registry.
	Base(registry_type registry, char const * const name);

	/// destructor.
	~Base();

	/// executes this test.
	bool run();

	/// retrieves the name of this test.
	name_type const & name() const;

protected :

private :

	hryky_delete_default_constructor(Base);
	hryky_delete_this_copy_constructor(Base);
	hryky_delete_this_copy_assign_op(Base);

	/// This function is implemented by the derived class.
	virtual bool run_impl() = 0;
	
	name_type   name_;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace
{
} // namespace "anonymous"
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
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace testing
{
namespace unit
{

} // namespace unit
} // namespace testing
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // TESTING_UNIT_BASE_H_20120428133331231
// end of file
