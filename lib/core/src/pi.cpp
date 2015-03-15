/**
  @file     pi.cpp
  @brief    represents mathematical constant PI.
  @author   HRYKY
  @version  $Id: pi.cpp 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/pi.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace
{
} // namespace "anonymous"
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
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
	/**
	  Mathematical Constant PI/4 as single precision floating point.
	 */
	float const QuarterPi<float>::value = ::std::atan(1.0f);
	/**
	  Mathematical Constant PI/4 as double precision floating point.
	 */
	double const QuarterPi<double>::value = ::std::atan(1.0f);
	/**
	  Mathematical Constant PI/2 as single precision floating point.
	 */
	float const HalfPi<float>::value = QuarterPi<float>::value * 2.0f;
	/**
	  Mathematical Constant PI/2 as double precision floating point.
	 */
	double const HalfPi<double>::value = QuarterPi<double>::value * 2.0f;
	/**
	  Mathematical Constant PI as single precision floating point.
	 */
	float const Pi<float>::value = HalfPi<float>::value * 2.0f;
	/**
	  Mathematical Constant PI as double precision floating point.
	 */
	double const Pi<double>::value = HalfPi<double>::value * 2.0f;
}
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace
{
} // namespace "anonymous"
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
