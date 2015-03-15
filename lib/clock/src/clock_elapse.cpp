/**
  @file     clock_elapse.cpp
  @brief    measures an elapsed time.
  @author   HRYKY
  @version  $Id: clock_elapse.cpp 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/clock/clock_elapse.h"
#include "hryky/clock/clock_common.h"
#include "hryky/swap.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace clock
{
namespace
{
} // namespace "anonymous"
} // namespace clock
} // namespace hryky
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
  @brief default constructor.
 */
hryky::clock::Elapse::Elapse()
	: start_(clock_type::now())
{
}
/**
  @brief copy constructor.
 */
hryky::clock::Elapse::Elapse(this_type const & rhs)
	: hryky_copy_member(start)
{
}
/**
  @brief move constructor.
 */
hryky::clock::Elapse::Elapse(this_type && rhs)
	: hryky_move_member(start)
{
}
/**
  @brief destructor.
 */
hryky::clock::Elapse::~Elapse()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::clock::Elapse::clear()
{
	this->start_ = clock::now();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::clock::Elapse::swap(this_type & src)
{
	hryky_swap_member(start);
}
/**
  @brief retrieves the current elapsed time.
 */
hryky::clock::duration_type
hryky::clock::Elapse::operator()() const
{
	return clock::now() - this->start_;
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
// defines functions used in this file
//------------------------------------------------------------------------------
namespace hryky
{
namespace clock
{
namespace
{
} // namespace "anonymous"
} // namespace clock
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
