/**
  @file         mempool_standard.cpp
  @brief        allocates memory by ::std::malloc and deallocates it by ::std::free.
  @author       HRYKY
  @version      $Id: mempool_standard.cpp 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/mempool/mempool_standard.h"
#include "hryky/nullptr.h"
#include "hryky/std/std_cstdlib.h"
#include "hryky/std/std_memory.h"
#include "hryky/stdint.h"
#include "hryky/is_null.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace
{
}
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
hryky::mempool::Standard::Standard()
{
	return;
}
/**
  @brief allocates memory.
 */
void * hryky::mempool::Standard::allocate(size_t size)
{
	if (0u == size) {
		return hryky_nullptr;
	}
	
	return ::std::malloc(size);
}
/**
  @brief deallocates the allocated memory.
 */
bool hryky::mempool::Standard::deallocate(void * ptr)
{
	if (hryky_is_null(ptr)) {
		return true;
	}

	::std::free(ptr);

	return true;
}
/**
  @brief retrieves the maximum size of allocation can be successful.
 */
hryky::size_t hryky::mempool::Standard::allocatable_size() const
{
	return ::std::allocator<uint8_t>().max_size();
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
}
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
