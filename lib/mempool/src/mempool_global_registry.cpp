/**
  @file     mempool_global.cpp
  @brief    The registry of allocator used by multiple contexts.
  @author   HRYKY
  @version  $Id: mempool_global_registry.cpp 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/mempool/mempool_global_registry.h"
#include "hryky/mempool/mempool_adapter.h"
#include "hryky/mempool/mempool_standard.h"
#include "hryky/mempool/mempool_lock.h"
#include "hryky/nullptr.h"
#include "hryky/clear.h"
#include "hryky/intrusive_ptr.h"
#include "hryky/is_null.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_disable_warning_unthreadsafe_instance
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace mempool
{
namespace global
{
namespace
{
	mempool_type g_mempool = hryky_nullptr;
	
} // namespace "anonymous"
} // namespace global
} // namespace mempool
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
  @brief retrieves the mempool shared by multiple contexts.
 */
hryky::mempool_type
hryky::mempool::global::Registry::instance()
{
	mempool_type const mempool = g_mempool;
	
	if (hryky_is_null(mempool)) {
		static mempool::Adapter<mempool::Standard> boot;
		
		return &boot;
	}

	return mempool;
}
/**
  @brief default constructor.
 */
hryky::mempool::global::Registry::Registry()
	: prev_(g_mempool)
	  , valid_(true)
{
	g_mempool = hryky_nullptr;
}
/**
  @brief constructs with a memory pool used in the current scope.
 */
hryky::mempool::global::Registry::Registry(mempool_type const mempool)
	: prev_(g_mempool)
	  , valid_(true)
{
	g_mempool = mempool;
}
/**
  @brief move constructor.
 */
hryky::mempool::global::Registry::Registry(this_type && rhs)
	: hryky_move_member(prev)
	  , hryky_move_member(valid)
{
	hryky::clear(rhs.valid_);
}
/**
  @brief destructor.
 */
hryky::mempool::global::Registry::~Registry()
{
	this->clear();
}
/**
  @brief releases the internal resources.
 */
void hryky::mempool::global::Registry::clear()
{
	if (this->valid_) {
		g_mempool = this->prev_;
	}
	hryky::clear(this->valid_);
	hryky::clear(this->prev_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::mempool::global::Registry::swap(this_type & src)
{
	hryky_swap_member(prev);
	hryky_swap_member(valid);
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
namespace mempool
{
namespace
{
} // namespace "anonymous"
} // namespace mempool
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
