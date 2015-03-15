/**
  @file         memory.h
  @brief        memory constrol modules.
  @author       HRYKY
  @version      $Id: memory.h 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#ifndef MEMORY_H_20120109165111368
#define MEMORY_H_20120109165111368

/**
  @page hryky::memory allocating memory
  
  @section mempool_Arbitrary hryky::mempool::Arbitrary

  hryky::mempool::Arbitrary allocates memory space from
  passed buffer. The size of the allocating region can be arbitrary.
  Besides, the address alignment can be specified.

  Following example is based on @ref test_mempool_arbitrary.cpp

  @dontinclude  test_mempool_arbitrary.cpp
  
  @subsection   Initialization Initialization
  @skip         mempool::Arbitrary<OffsetT>
  @until        }
  
  @subsection   allocation dynamic allocations from mempool memory 
  @skip         mempool.allocate(
  @until        break;
  @until        }
  
  @subsection   deallocation deallocating the allocated memory
  @skip         mempool.deallocate(
  @until        return false;
  @until        }
  
  @section mempool_Fixed hryky::mempool::Fixed

  hryky::mempool::Fixed allocates a memory block from passed buffer.
  The size of the allocating region is fixed length.
  The address alignment is hryky::mempool::Fixed::min_alignment bits.

  Following example is based on @ref test_mempool_fixed.cpp
  
  @dontinclude test_mempool_fixed.cpp

  @subsection   Initialization Initialization
  @skipline     mempool_type
  @skip         mempool_type mempool;
  @until        }

  @subsection   allocation allocations of fixed size memory
  @skip         mempool.allocate()
  @until        break;
  @until        }
  
  @subsection   deallocation deallocating the memory
  @skip         mempool.deallocate(
  @until        return false;
  @until        }
  
  @example test_mempool_arbitrary.cpp
  @example test_mempool_fixed.cpp
 */
#include "hryky/memory/memory_common.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
/// modules to manage memory allocation.
namespace memory
{
}
}
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// define global functions
//------------------------------------------------------------------------------
#endif // MEMORY_H_20120109165111368
// end of file
