/**
  @file         testing_random.cpp
  @brief        initializes the generator of pseudo random number.
  @author       HRYKY
  @version      $Id: testing_random.cpp 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing/testing_random.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace
{
} // namespace "anonymous"
//------------------------------------------------------------------------------
// static variable
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// function prototype
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief constructor.
 */
hryky::testing::Random::Random()
	: generator_()
	  , seed_(0)
{
	this->seed(static_cast<uint32_t>(::std::time(0)));
}
/**
  @brief destructor.
 */
hryky::testing::Random::~Random()
{
}
/**
  @brief retrieves the generator of pseudo random number.
 */
hryky::testing::Random::generator_type &
hryky::testing::Random::generator()
{
	return this->generator_;
}
/**
  @brief resets the seed of the generator.
 */
hryky::testing::Random &
hryky::testing::Random::seed(seed_type src)
{
	this->seed_ = src;
	this->generator_.seed(src);
	return *this;
}
/**
  @brief retrieves the seed of this generator.
 */
hryky::testing::Random::seed_type
hryky::testing::Random::seed() const
{
	return this->seed_;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace
{
} // namespace "anonymous"
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
