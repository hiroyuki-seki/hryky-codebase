/**
  @file     thread_processor_id.cpp
  @brief    retains the valid id of processor.
  @author   HRYKY
  @version  $Id: thread_processor_id.cpp 335 2014-03-16 03:00:56Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/thread/thread_processor_id.h"
#include "hryky/swap.h"
#include "hryky/clear.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace thread
{
namespace
{
} // namespace "anonymous"
} // namespace thread
} // namespace hryky
//------------------------------------------------------------------------------
// static variable
//------------------------------------------------------------------------------
hryky::thread::raw_processor_id_type const
hryky::thread::ProcessorId::size_ =
hryky::thread::hardware_concurrency();
//------------------------------------------------------------------------------
// function prototype
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
hryky::thread::ProcessorId::ProcessorId()
	: raw_()
{
}
/**
  @brief copy constructor.
 */
hryky::thread::ProcessorId::ProcessorId(this_type const & rhs)
	: hryky_copy_member(raw)
{
}
/**
  @brief move constructor.
 */
hryky::thread::ProcessorId::ProcessorId(this_type && rhs)
	: hryky_move_member(raw)
{
}
/**
  @brief destructor.
 */
hryky::thread::ProcessorId::~ProcessorId()
{
}
/**
  @brief rotates the internal value.
 */
hryky::thread::ProcessorId &
hryky::thread::ProcessorId::operator++()
{
	if (this_type::size_ <= ++this->raw_) {
		this->raw_ = 0u;
	}
	return *this;
}
/**
  @brief releases the internal resources.
 */
void hryky::thread::ProcessorId::clear()
{
	hryky::clear(this->raw_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::thread::ProcessorId::swap(this_type & src)
{
	hryky_swap_member(raw);
}
/**
  @brief retrieves the raw value.
 */
hryky::thread::ProcessorId::raw_type
hryky::thread::ProcessorId::raw() const
{
	return this->raw_;
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
namespace thread
{
namespace
{
} // namespace "anonymous"
} // namespace thread
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
