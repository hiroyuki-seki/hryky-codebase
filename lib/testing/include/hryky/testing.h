/**
  @file         testing.h
  @brief        testing modules.
  @author       HRYKY
  @version      $Id: testing.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef TESTING_H_20120428175055410
#define TESTING_H_20120428175055410

/**
  @page hryky::testing unit test
  @section unit_test    hryky::testing::unit::Base

  hryky::testing::unit::Base is the base class of each unit test.

  @section registry     hryky::testing::Registry

  hryky::testing::Registry is used as the associative array of the unit tests.
  hryky::testing::Registry::operator[]() returns the corresponding unit test.
  
 */
#include "hryky/testing/testing_log.h"
#include "hryky/testing/testing_random.h"
#include "hryky/testing/testing_registry.h"
#include "hryky/testing/testing_unit_base.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
/// modules for testing
namespace testing
{
} // namespace testing
} // namespace hryky
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// define global functions
//------------------------------------------------------------------------------
#endif // TESTING_H_20120428175055410
// end of file
